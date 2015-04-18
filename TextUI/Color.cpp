//@author A0113736J-reused
#include "Color.h"

Color:: Color(void){
}

Color:: ~Color(void){
}

void Color:: TextColor(int fontcolor,int backgroundcolor,HANDLE screen)
{
   int color_attribute;
   color_attribute = backgroundcolor;
   color_attribute = _rotl(color_attribute,4) | fontcolor;
   SetConsoleTextAttribute(screen,color_attribute);
}