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
    ExternalWorld(int NumRect); // ����������� ��������, �����������
    ExternalWorld(int NumRect, float sizex, float sizey);
    ExternalWorld(int NumRect, string TextureName); // ����������� ��������, �����������
    ExternalWorld(int NumRect, string TextureName, float sizex, float sizey);
    ExternalWorld();
    ~ExternalWorld();                                          // ����������
    

    void InitRectTexture();
    void InitRectTextureArr(int index, string TextureName);
    void InitObject(int NumRect, string TextureName, float sizex, float sizey);
    void InitObject(int NumRect,string TextureName);
    void InitRectAll();             // ������������� ���� �������� ���������� �������
    
    
   
    void InitImageBonus(int index, int newbonus);
    void InitRect(int index);                              // ������������� �������
   
    
    void Motion();                                  // �������� �������� 
    

    bool Collision(FloatRect ob);                              // ������������ �������
    

    void DrawSpaceObject(RenderWindow& window);                // ��������� �������
    
    void Restart();                                           // ������������� �������
    
    void increaseSpeed();
    void Setspeed(float newspeed);      // ���������� ��������
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

    RectangleShape* SpaceObject;           // �������
    Texture *TextureObject;               // �������� ��������
    int * bonus;       // ������ ������
       
    Vector2f PosBonus;
    Vector2f SizeRect;

    int NumRect=1;           // ���������� ��������
    int RabObject=1;      // ���������� ����������� ��������

    void SetNumRect(int NewNumRect); // ���������� ���������� ��������
    
      
    
   
    bool NullObject = false;
    bool stop = false;
    float speed =1;    // ������� �������� ��������
    int full=0;

   
    
   
   
    
    
    
    
       
};


