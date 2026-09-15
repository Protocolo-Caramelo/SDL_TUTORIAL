#include"GTextSpacing.h"

//
// Methods
//
void TextSpacing_Populate(TextSpacing*a, TextSpacing*b)
{
    if(a->top == TEXTSPACING_UNINITIALIZED_VAL){
        a->top = b->top;
    }
    if(a->bottom == TEXTSPACING_UNINITIALIZED_VAL){
        a->bottom = b->bottom;
    }
    if(a->right == TEXTSPACING_UNINITIALIZED_VAL){
        a->right = b->right;
    }
    if(a->left == TEXTSPACING_UNINITIALIZED_VAL){
        a->left = b->left;
    }

    if(a->color.r == 0 && a->color.g == 0 && a->color.b == 0 && a->color.a == 0){
        a->color = b->color;
    }
}

int TextSpacing_Equals(TextSpacing*a, TextSpacing*b)
{
    return 
        a->left == b->left
        && a->right == b->right
        && a->top == b->top
        && a->bottom == b->bottom

        && a->color.a == b->color.a
        && a->color.r == b->color.r
        && a->color.g == b->color.g
        && a->color.b == b->color.b
        ;
}

int TextSpacing_Zered(TextSpacing*a)
{
    return 
        a->left == TEXTSPACING_UNINITIALIZED_VAL
        && a->right == TEXTSPACING_UNINITIALIZED_VAL
        && a->top == TEXTSPACING_UNINITIALIZED_VAL
        && a->bottom == TEXTSPACING_UNINITIALIZED_VAL
        ;
}
