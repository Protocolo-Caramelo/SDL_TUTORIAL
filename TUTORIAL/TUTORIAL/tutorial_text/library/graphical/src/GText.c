#include<graphical.h>

void Text_measureRaw(Text*t, int*w, int*h)
{
    size_t i;
    int width, height;
    int c;

    width = height = 0;
    i = 0;
    while((c = (*Text_raw(t))[i++])){
        if(c == '\n' && *Text_wrap(t) == 0){
            continue;
        }
    }
}
