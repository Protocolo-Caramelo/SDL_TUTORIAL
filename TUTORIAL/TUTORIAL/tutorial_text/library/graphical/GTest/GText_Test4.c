#if defined(COMPILATION_DEVQUOTE) || defined(COMPILATION_TOOLCHAIN_WINDOWS_DEVQUOTE)
#include"GTest.h"

SDL_Window *w;
SDL_Renderer *r;
SDL_Event e;
//
typedef struct TextInput TextInput;
struct TextInput {
    Text *text;
    int selected;

    SDL_Texture *cursor_tex;
    int cursor_x, cursor_y;
    size_t cursor_idx;
};
char TI_str[1024];
char *TI_byteUTF8;
int TI_charUTF8;
size_t TI_charUTF8_idx;

void TextInput_checkSelection(TextInput*inp, SDL_Event*e)
{
    if(e->type != SDL_MOUSEBUTTONDOWN){
        return;
    }

    int x, y;
    size_t i;
    TextCharRect *chr_rect;

    x = e->button.x;
    y = e->button.y;
    //
    inp->selected = 
        x >= (*Text_edges(inp->text))[DRAW_EDGE_PADDING_XMIN] && x <= (*Text_edges(inp->text))[DRAW_EDGE_PADDING_XMAX]
        &&
        y >= (*Text_edges(inp->text))[DRAW_EDGE_PADDING_YMIN] && y <= (*Text_edges(inp->text))[DRAW_EDGE_PADDING_YMAX]
        ;

    //
    int dist, min_dist, min_distI;
    int distX, distY;
    TextCharRect *chrs_dest;

    min_dist = INT_MAX;
    min_distI = 0;
    chrs_dest = *Text_chrsDest(inp->text);
    for(i=0; i < Text_GetSizeUTF8(inp->text) && inp->selected; ++i){
        distX = chrs_dest[i].x - x + chrs_dest[i].width;
        distY = chrs_dest[i].y - y + chrs_dest[i].height;
        dist = sqrt(distX * distX + distY * distY);
        if(dist < min_dist){
            min_dist = dist;
            min_distI = i;
        }
    }

    inp->cursor_idx = min_distI;
}

void TextInput_displayCursor(TextInput*inp)
{
    if(!inp->selected){
        return;
    }
    if(!*Text_raw(inp->text)){
        inp->cursor_idx = 0;
    }

    TextCharRect *chrs_dest;
    SDL_Rect dest;

    chrs_dest = *Text_chrsDest(inp->text);
    //
    inp->cursor_x = *Text_marginLeft(inp->text) + *Text_borderLeft(inp->text) + *Text_paddingLeft(inp->text);
    inp->cursor_y = *Text_marginTop(inp->text) + *Text_borderTop(inp->text) + *Text_paddingTop(inp->text);
    if(*Text_raw(inp->text)){
        inp->cursor_x = chrs_dest[inp->cursor_idx].x + chrs_dest[inp->cursor_idx].width - 1;
        inp->cursor_y = chrs_dest[inp->cursor_idx].y;
    }
    // printf("%i (%i %i)\n", min_distI, inp->cursor_x, inp->cursor_y);

    //*
    if(!inp->cursor_tex){
        inp->cursor_tex = SDL_CreateTexture(
            r,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            2,
            *Text_lineskip(inp->text) * *Text_scaleHeight(inp->text)
        );
        if(!inp->cursor_tex){
            printf("Error while creating texture for cursor: %s\n", SDL_GetError());
            exit(1);
        }

        SDL_SetRenderTarget(r, inp->cursor_tex);
        SDL_SetRenderDrawColor(
            r,
            0,
            0,
            0,
            255
        );
        SDL_RenderClear(r);
        SDL_SetRenderTarget(r, NULL);
    }

    dest = (SDL_Rect){
        .x = inp->cursor_x,
        .y = inp->cursor_y
    };
    SDL_QueryTexture(
        inp->cursor_tex,
        NULL, NULL,
        &dest.w, &dest.h
    );
    SDL_RenderCopy(
        r,
        inp->cursor_tex,
        NULL,
        &dest
    );
    // */
}

void TextInput_checkInput(TextInput*inp, SDL_Event*e)
{
    if(!inp->selected){
        return;
    }

    if(e->type == SDL_KEYDOWN){
        if(e->key.keysym.sym == SDLK_BACKSPACE && Text_raw(inp->text)){
            memset(TI_str, 0, sizeof(TI_str) / sizeof(TI_str[0]));

            TI_byteUTF8 = TI_str;
            TI_charUTF8_idx = 0;
            while(
                TI_charUTF8_idx < Text_GetSizeUTF8(inp->text) - 1
                && (TI_charUTF8 = Text_getUTF8(inp->text, TI_charUTF8_idx))
                ){
                TI_byteUTF8 = utf8catcodepoint(TI_byteUTF8, TI_charUTF8, utf8codepointsize(TI_charUTF8));
                // printf("%s\n", TI_str);
                ++TI_charUTF8_idx;
            }
            Text_SetUTF8(inp->text, TI_str);
            inp->cursor_idx--;
        }
        //
        if(e->key.keysym.sym == SDLK_LEFT && Text_raw(inp->text) && inp->cursor_idx){
            inp->cursor_idx--;
        }
        else if(e->key.keysym.sym == SDLK_RIGHT && Text_raw(inp->text) && inp->cursor_idx < Text_GetSizeUTF8(inp->text)){
            inp->cursor_idx++;
        }
    }

    if(e->type == SDL_TEXTINPUT){
        char *byte_raw;
        char *byte_str;
        int c;
        size_t i;

        byte_raw = utf8codepoint(*Text_raw(inp->text), &c);
        byte_str = TI_str;
        i = 0;
        *byte_str = '\0';
        do{
            //*
            if(i == inp->cursor_idx){
                utf8cat(byte_str, e->text.text);
                byte_str += utf8size(e->text.text) - 1;
            }
            byte_str = utf8catcodepoint(byte_str, c, sizeof(TI_str) - (size_t)(byte_str - TI_str));
            // */
            ++i;
        } while(c != '\0' && (byte_raw = utf8codepoint(byte_raw, &c)));
        Text_SetUTF8(inp->text, TI_str);
        inp->cursor_idx++;
    }
}

//
SDL_Texture *t_marginTex;
SDL_Rect src_buttonMedium_selected = (SDL_Rect){
    .x = 26,
    .y = 541,
    .w = 1100,
    .h = 1017 - 541
};
SDL_Rect src_buttonMedium_unselected = (SDL_Rect){
    .x = 41,
    .y = 21,
    .w = 1100,
    .h = 1017 - 541
};
int t_selected;

//
void alterMargin_1(Text*t, Texture*tex)
{
    SDL_RenderCopy(
        *Text_renderer(t),
        t_marginTex,
        (!t_selected)? &src_buttonMedium_unselected: &src_buttonMedium_selected,
        NULL
    );
}

//
void Text_Test4(char*fpath, unsigned ptsize, char*str)
{
    extern SDL_Window *w;
    extern SDL_Renderer *r;
    extern SDL_Event e;
    //
    int w_width, w_height;
    //
    TextCache *cache;
    Text *t;
    extern SDL_Texture *t_marginTex;
    int t_edges[DRAW_EDGE_AMT] = {};
    int t_marginWidth, t_marginHeight;
    double t_marginRatio;
    //
    double fps;
    unsigned fps_time;
    unsigned fps_delayTime;
    const unsigned fps_delay = 100;
    Text *fps_t;
    char fps_tStr[20] = "FPS 60.00";
    int fps_edges[DRAW_EDGE_AMT] = {};
    //
    TextInput input_r, input_g, input_b;
    TextConfig input_configUnselected, input_configSelected;
    
    graphical_init();
    //
    w = SDL_CreateWindow(
        "4nd test of Text",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        512,
        SDL_WINDOW_RESIZABLE
    );
    r = SDL_CreateRenderer(
        w,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    //
    cache = TextCache_Create(r, fpath, ptsize);
    t_marginTex = IMG_LoadTexture(r, "./library/graphical/GTest/GText_Test4_Asset1.jpeg");
    if(t_marginTex == NULL){
        printf("Errow while loading image ./library/graphical/GTest/GText_Test4_Asset1.jpeg: %s\n", SDL_GetError());
        exit(1);
    }
    //*
    t = Text_Create(
        cache,
        TextConfig_Create(
            .scale_width = 1 / 2.0,
            .scale_height = 1 / 2.0,
            .color = (SDL_Color){.a = 255},
        ),
        str
    );
    SDL_QueryTexture(
        t_marginTex,
        NULL, NULL, 
        &t_marginWidth, &t_marginHeight
    );
    t_marginRatio = t_marginWidth / t_marginHeight;
    //*
    Text_UpdateConfig(
        t,
        TextConfig_Create(

            .func_alterMargin = &alterMargin_1
        )
    );
    t_selected = 0;
    // */
    //*
    fps_delayTime = fps_time = SDL_GetTicks();
    fps_t = Text_Create(
        cache,
        TextConfig_Create(
            .scale_width = 1 / 2.0,
            .scale_height = 1 / 2.0,
            .color = (SDL_Color){.a = 255}
        ),
        fps_tStr
    );
    // */
    input_configUnselected = input_configSelected = *TextConfig_Create(
        .scale_width = 1 / 2.0,
        .scale_height = 1 / 2.0,
        .color = (SDL_Color){.r = 255, .a = 255},
        .margin = {
            .top = 2,
            .bottom = 2,
            .right = 2,
            .left = 2,
            .color = (SDL_Color){.a=255}
        },
        .padding = {
            .top = 5,
            .bottom = 5,
            .right = 5,
            .left = 5,
            .color = (SDL_Color){.r=255, .g=255, .b=255, .a=255}
        },
        .bx_width = 200,
        .bx_height = TTF_FontLineSkip(*TextCache_font(cache)) / 2.0,
    );
    input_configSelected.margin = (TextSpacing){
        .top = 5,
        .bottom = 5,
        .right = 5,
        .left = 5,
        .color = (SDL_Color){.a=255}
    };
    input_r = input_g = input_b = (TextInput){};
    input_r.text = Text_Create(cache, &input_configUnselected);
    input_g.text = Text_Create(cache, &input_configUnselected);
    input_b.text = Text_Create(cache, &input_configUnselected);
    Text_SetUTF8(input_r.text, "");

    while(1){
        if(SDL_GetTicks() - fps_delayTime >= fps_delay){
            fps_delayTime = SDL_GetTicks();
            sprintf(fps_tStr, "FPS %.2lf", fps);
        }

        while(SDL_PollEvent(&e)){
            TextInput_checkSelection(&input_r, &e);
            TextInput_checkSelection(&input_g, &e);
            TextInput_checkSelection(&input_b, &e);
            //
            TextInput_checkInput(&input_r, &e);
            TextInput_checkInput(&input_g, &e);
            TextInput_checkInput(&input_b, &e);

            switch(e.type){
                case SDL_QUIT:
                    SDL_DestroyTexture(t_marginTex);
                    //
                    Text_Destroy(&t);
                    Text_Destroy(&fps_t);
                    //
                    SDL_DestroyRenderer(r);
                    SDL_DestroyWindow(w);
                    SDL_Quit();

                    exit(0);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    int x, y;
                    x = e.button.x;
                    y = e.button.y;
                    if(
                        x >= t_edges[DRAW_EDGE_XMIN] && x <= t_edges[DRAW_EDGE_XMAX]
                        &&
                        y >= t_edges[DRAW_EDGE_YMIN] && y <= t_edges[DRAW_EDGE_YMAX]
                    ){
                        t_selected = !t_selected;
                    }
                    //

                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        SDL_RenderClear(r);
        //*
        SDL_GetWindowSize(w, &w_width, &w_height);
        Text_DrawUTF8(
            fps_t,
            fps_tStr,
            TextConfig_Create(
                .x = w_width - fps_edges[DRAW_TEXT_WIDTH],
                .y = 0,
            ),
            &fps_edges
        );
        // */
        //*
        Text_DrawUTF8(
            t,
            NULL,
            TextConfig_Create(
                .x = w_width / 2 - t_edges[DRAW_WIDTH] / 2,
                .y = w_height / 2 - t_edges[DRAW_HEIGHT] / 2,

                .chr_fmt = (!t_selected)? CHAR_FMT_BOLD: CHAR_FMT_BOLD | CHAR_FMT_UNDERLINE,

                .margin = {
                    .top = t_marginRatio * (t_edges[DRAW_TEXT_HEIGHT] + 40) / 2,
                    .bottom = t_marginRatio * (t_edges[DRAW_TEXT_HEIGHT] + 40) / 2,
                    .right = 40,
                    .left = 40,
                    .color = (SDL_Color){255, 0, 255, 255},
                },
            ),
            &t_edges
        );
        // */
        //*
        Text_DrawUTF8(
            input_r.text,
            NULL,
            (input_r.selected)? &input_configSelected: &input_configUnselected,
            NULL
        );
        TextInput_displayCursor(&input_r);
        //*
        // */

        SDL_RenderPresent(r);
        SDL_Delay(16);
        //
        fps = 1000.0 / (SDL_GetTicks() - fps_time);
        fps_time = SDL_GetTicks();
    }
}

#endif
