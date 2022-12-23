#include "ExternalWorld.h"

ExternalWorld::ExternalWorld(int NumRect)
{
    SizeRect.x = 0; SizeRect.y = 0;
    SetNumRect(NumRect);
    SpaceObject = new RectangleShape[NumRect]; // Установка массива объектов
    RabObject = NumRect;
    bonus = new int[NumRect];
    TextureObject = new Texture[NumRect];
    InitRectAll();
  }

ExternalWorld::ExternalWorld(int NumRect, float sizex, float sizey)
{
    SizeRect.x = sizex; SizeRect.y = sizey;
    SetNumRect(NumRect);
    SpaceObject = new RectangleShape[NumRect]; // Установка массива объектов
    RabObject = NumRect;
    bonus = new int[NumRect];
    TextureObject = new Texture[NumRect];
    InitRectAll();
}



ExternalWorld::ExternalWorld(int NumRect, string TextureName )
{
    SizeRect.x = 0; SizeRect.y = 0;
    SetNumRect(NumRect);
    SpaceObject = new RectangleShape[NumRect]; // Установка массива объектов
    RabObject = NumRect;
    bonus = new int[NumRect];
    TextureObject = new Texture[1];
    TextureObject[0].loadFromFile(TextureName);
    TextureObject[0].setSmooth(true);
    InitRectAll();
    InitRectTexture();
}
ExternalWorld::ExternalWorld(int NumRect, string TextureName, float sizex, float sizey)
{
    SizeRect.x = sizex; SizeRect.y = sizey;
    SetNumRect(NumRect);
    SpaceObject = new RectangleShape[NumRect]; // Установка массива объектов
    RabObject = NumRect;
    bonus = new int[NumRect];
    TextureObject = new Texture[1];
    TextureObject[0].loadFromFile(TextureName);
    TextureObject[0].setSmooth(true);
    InitRectAll();
    InitRectTexture();
}
ExternalWorld::ExternalWorld()
{   
    SizeRect.x = 0; SizeRect.y = 0;
    SpaceObject = new RectangleShape[1];
    TextureObject = new Texture[1];
    bonus = new int[1];
}

ExternalWorld::~ExternalWorld()
{
    delete[] SpaceObject;
    delete[] bonus;
    delete[] TextureObject;
}

void ExternalWorld::InitObject(int NumRect,string TextureName)
{   

    SizeRect.x = 0; SizeRect.y = 0;
    SetNumRect(NumRect);
    SpaceObject = new RectangleShape[NumRect]; // Установка массива объектов
    RabObject = NumRect;
    bonus = new int[NumRect];
    TextureObject[0].loadFromFile(TextureName);
    TextureObject[0].setSmooth(true);
    InitRectAll();
    InitRectTexture();
}

void ExternalWorld::InitObject(int NumRect, string TextureName, float sizex, float sizey)
{   
    SizeRect.x = sizex; SizeRect.y = sizey;
    SetNumRect(NumRect);
    SpaceObject = new RectangleShape[NumRect]; // Установка массива объектов
    RabObject = NumRect;
    bonus = new int[NumRect];
    TextureObject[0].loadFromFile(TextureName);
    TextureObject[0].setSmooth(true);
    InitRectAll();
    InitRectTexture();
}

void ExternalWorld::InitRectTextureArr(int index, string TextureName)
{
    TextureObject[index].loadFromFile(TextureName);
    TextureObject[index].setSmooth(true);
    SpaceObject[index].setTexture(&TextureObject[index]);
}

void ExternalWorld::InitRectTexture()
{   for (int i=0; i< NumRect;i++)  SpaceObject[i].setTexture(&TextureObject[0]);
}


void ExternalWorld::InitRectAll()
{    for (int i = 0; i < NumRect; i++)
    {
    InitRect(i);
    }
}


void ExternalWorld::InitRect(int index)
{   
    bool tmp;
    Vector2f posRec;
    if (SizeRect.x==0 || SizeRect.y == 0) {
    posRec.x = 30 + rand() % 50;
    posRec.y = posRec.x;
    SpaceObject[index].setSize(posRec);}
    else SpaceObject[index].setSize(SizeRect);
    
    do {
        tmp = false;
        posRec.x = 1280 + rand() % (2560 - 1280);
        posRec.y = 120 + rand() % (680 - 120);
        SpaceObject[index].setPosition(posRec);
        for (int i = 0; i < NumRect; i++) {
            if (i == index)  continue; 
            if (SpaceObject[index].getGlobalBounds().intersects(SpaceObject[i].getGlobalBounds())) tmp = true;
        }

    } while (tmp);

   }


void ExternalWorld::SetNumRect(int NewNumRect)
{
    NumRect = NewNumRect;
}



void ExternalWorld::InitImageBonus(int index, int newbonus)
{   
    int tmprand=0;
    tmprand = rand() % newbonus;
    Setbonus(index, tmprand);
}



void ExternalWorld::Setbonus(int index, int newbonus)
{
    if (index > 4) index = 4;
    bonus[index] = newbonus;
}




void ExternalWorld::Motion()
{
    for (int i = 0; i < NumRect; i++)
    {
        if (SpaceObject[i].getPosition().x >= -80) 
        {
            SpaceObject[i].move(-speed, 0);

            if (SpaceObject[i].getPosition().x < -80)
            {

                if (stop != true) InitRect(i);  else RabObject--;
                
            }
        }

    }

    if (RabObject == 0) NullObject = true;
}


bool ExternalWorld::Collision(FloatRect ob)
{
    bool res=false;
    for (int i = 0; i < NumRect; i++) {
        if (SpaceObject[i].getGlobalBounds().intersects(ob))
    {   
        full = getbonus(i);
        PosBonus = SpaceObject[i].getPosition();
        if (!stop) InitRect(i); else SpaceObject[i].setPosition(Vector2f(-80,-80));
        res = true; 
        
        break;
    }    
    }
    return res;
}


void ExternalWorld::DrawSpaceObject(RenderWindow & window)
{
    for (int i = 0; i < NumRect; i++)
    {
       if ( SpaceObject[i].getPosition().x >= -75)  window.draw(SpaceObject[i]);
    }
}




void ExternalWorld::increaseSpeed()
{
    speed+=0.1;
}

void ExternalWorld::Setspeed(float newspeed)
{
    speed = newspeed;
}

void ExternalWorld::SetStop(bool vector)
{ 
    stop = vector;
}



void ExternalWorld::Restart()
{
    Setspeed(1);
    RabObject = NumRect;
    NullObject = false;
    stop = false;
    full = 0;
    InitRectAll();
    
}




