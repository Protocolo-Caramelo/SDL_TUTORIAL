#include<GTexture.h>

void Texture_loadFromImg(Texture*to, const char*path)
{
    to->raw = IMG_LoadTexture(*Texture_renderer(to), path);
    if(!to->raw){
        printf("Error while loading the image's texture in path %s: %s\n", path, SDL_GetError());
        exit(1);
    }
}
