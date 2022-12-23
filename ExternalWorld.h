#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

using namespace sf;
using namespace std;

class ExternalWorld
{
public:
    ExternalWorld(int NumRect); // определение объектов, конструктор
    ExternalWorld(int NumRect, float sizex, float sizey);
    ExternalWorld(int NumRect, string TextureName); // определение объектов, конструктор
    ExternalWorld(int NumRect, string TextureName, float sizex, float sizey);
    ExternalWorld();
    ~ExternalWorld();                                          // деструктор
    

    void InitRectTexture();
    void InitRectTextureArr(int index, string TextureName);
    void InitObject(int NumRect, string TextureName, float sizex, float sizey);
    void InitObject(int NumRect,string TextureName);
    void InitRectAll();             // инициализация всех объектов случайного размера
    
    
   
    void InitImageBonus(int index, int newbonus);
    void InitRect(int index);                              // инициализация объекта
   
    
    void Motion();                                  // движение объектов 
    

    bool Collision(FloatRect ob);                              // столкновение объекта
    

    void DrawSpaceObject(RenderWindow& window);                // отрисовка объекта
    
    void Restart();                                           // перезапустить объекты
    
    void increaseSpeed();
    void Setspeed(float newspeed);      // установить скорость
    void SetStop(bool vector);
    void Setbonus(int index, int newbonus);
    
    int getbonus(int index)
    {
        return bonus[index];
    }
    
    float getspeed()
    {
        return speed;
    }

    
    FloatRect getGameGlobalBounds(int index)
    {
        return SpaceObject[index].getGlobalBounds();
    }

    int getNumRect()
    {
        return NumRect;
    }

    

    int getRabObject()
    {
        return RabObject;
    }

    int getfull()
    {
        return full;
    }

    Vector2f getPosBonus()
    {
        return  PosBonus;
    }
    
    bool getstop()
    {
        return stop;
    }

    bool getNullObject()
    {
        return NullObject;
    }
private:

    RectangleShape* SpaceObject;           // объекты
    Texture *TextureObject;               // текстура объектов
    int * bonus;       // Размер бонуса
       
    Vector2f PosBonus;
    Vector2f SizeRect;

    int NumRect=1;           // Количество объектов
    int RabObject=1;      // Количестов действующих объектов

    void SetNumRect(int NewNumRect); // установить количество объектов
    
      
    
   
    bool NullObject = false;
    bool stop = false;
    float speed =1;    // текущая скорость объектов
    int full=0;

   
    
   
   
    
    
    
    
       
};


