#include"GTextConfig.h"

//
// Methods
//
int TextConfig_Equals(TextConfig*a, TextConfig*b)
{
    return 
        TextSpacing_Equals(&a->padding, &b->padding)
        && TextSpacing_Equals(&a->border, &b->border)
        && TextSpacing_Equals(&a->margin, &b->margin)

        && a->color.a == b->color.a
        && a->color.r == b->color.r
        && a->color.g == b->color.g
        && a->color.b == b->color.b
        //
        && a->fmt == b->fmt
        && a->lineskip == b->lineskip
        && a->wrap == b->wrap
        && a->rotation == b->rotation
        //
        && a->scale_width == b->scale_width
        && a->scale_height == b->scale_height
        //
        && a->chr_dist == b->chr_dist
        && a->chr_rotation == b->chr_rotation
        && a->chr_flip == b->chr_flip;
        ;
}

void TextConfig_Populate(TextConfig*a, TextConfig*b)
{
    if(TextSpacing_Zered(&a->padding)){
        a->padding = b->padding;
    }
    if(TextSpacing_Zered(&a->border)){
        a->border = b->border;
    }
    if(TextSpacing_Zered(&a->margin)){
        a->margin = b->margin;
    }

    DEFAULT_VALUE(a->fmt, b->fmt);
    DEFAULT_VALUE(a->lineskip, b->lineskip);
    DEFAULT_VALUE(a->wrap, b->wrap);
    DEFAULT_VALUE(a->rotation, b->rotation);
    //
    DEFAULT_VALUE(a->scale_width, b->scale_width);
    DEFAULT_VALUE(a->scale_height, b->scale_height);
    //
    DEFAULT_VALUE(a->chr_dist, b->chr_dist);
    DEFAULT_VALUE(a->chr_rotation, b->chr_rotation);
    DEFAULT_VALUE(a->chr_flip, b->chr_flip);
}
