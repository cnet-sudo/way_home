#include "GameLibrary.h"

string game::IntToStr(int number)  // приведение целочисленного типа к строковому
{

    ostringstream TextString;    // объявили переменную
    TextString << number;		//занесли в нее число очков, то есть формируем строку
    
    return TextString.str();
}



