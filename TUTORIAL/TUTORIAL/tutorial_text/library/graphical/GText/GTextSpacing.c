#include"GTextSpacing.h"

//
// Methods
//
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
        a->left == 0
        && a->right == 0
        && a->top == 0
        && a->bottom == 0

        && a->color.a == 0
        && a->color.r == 0
        && a->color.g == 0
        && a->color.b == 0
        ;
}
