#include "GameLibrary.h"
#include "ExternalWorld.h"


using namespace sf;
using namespace std;
using namespace game;


int main()
{   
    // Параметры игрового окна Windows

    RenderWindow window(VideoMode(1280, 720), L"Путь домой");
    window.setFramerateLimit(100);
    
    Image icon;
    if (!icon.loadFromFile("Image/icon.png"))
    {
        return 1;
    }
    window.setIcon(32, 32, icon.getPixelsPtr());
    
    // Картинка на время загрузки
    Texture texthome;
    texthome.loadFromFile("Image/homen.jpg");
    RectangleShape homecls(Vector2f(1280, 720));
    homecls.setTexture(&texthome);
    homecls.setPosition(Vector2f(0, 0));
    window.draw(homecls);
    window.display();


    srand(time(NULL)); 
    Vector2f pos;  // координаты звёздного неба
    bool pause = true;
    float speedRadar=1;
    float speedplayr = 1;
    int etapgame = 0;
    string masKamTex[]{ "Image/kam.png", "Image/kam1.png", "Image/kam2.png", "Image/kam3.png", "Image/kam4.png", "Image/kam5.png" ,"Image/kam6.png" ,"Image/kam7.png", "Image/kam8.png", "Image/kam9.png" };
    string masInTex[]{ "Image/in9.png", "Image/in10.png", "Image/in3.png", "Image/in4.png", "Image/in4.png", "Image/in6.png" ,"Image/in6.png" ,"Image/in3.png", "Image/in9.png", "Image/in10.png" };
    string masBonusTex[]{ "Image/galon.png","Image/bobo.png", "Image/ved.png" };

    float par = 0;
    bool sonON = true;
    Sound son,sonbonM,sonbonB,falson,sonvic;
    SoundBuffer buffer,bufM,bufB,fal,vic;
    vic.loadFromFile("Music/victoria.wav");
    fal.loadFromFile("Music/faled.wav");
    bufM.loadFromFile("Music/bonusm.wav");
    bufB.loadFromFile("Music/bonusB.wav");
    buffer.loadFromFile("Music/turbo.wav");
    sonvic.setBuffer(vic);
    falson.setBuffer(fal);
    
    sonbonM.setBuffer(bufM);
    sonbonB.setBuffer(bufB);
    son.setBuffer(buffer);
    son.setLoop(true);

           
    Text text_gold, end_game, plusfull,pausetext;
    Font GameFont;
    GameFont.loadFromFile("Font/BankGothic Md BT Medium.otf");
    int full = 100;
    text_gold.setFont(GameFont);
    text_gold.setFillColor(Color::Green);
    text_gold.setCharacterSize(30);
    text_gold.setPosition(1070,20);

    end_game.setFont(GameFont);
    end_game.setFillColor(Color::Red);
    end_game.setCharacterSize(100);
    end_game.setString(L"Конец игры");
    end_game.setPosition(300,333);

    plusfull.setFont(GameFont);
    plusfull.setFillColor(Color::Green);
    plusfull.setCharacterSize(25);
    
    pausetext.setFont(GameFont);
    pausetext.setFillColor(Color::Magenta);
    pausetext.setCharacterSize(50);
    pausetext.setString(L"П А У З А");
    pausetext.setPosition(500, 333);
    


    Texture textEarth;
    textEarth.loadFromFile("Image/earth_PNG39.png");
    
    RectangleShape Earth(Vector2f(500, 500));
    Earth.setTexture(&textEarth);
    Earth.setPosition(Vector2f(1100, 150));

    // Игровая информационная панель

    Texture TexturInfoPanel;
    TexturInfoPanel.loadFromFile("Image/panel.png");

    RectangleShape GamaInfoPanel(Vector2f(1280, 113));
    GamaInfoPanel.setTexture(&TexturInfoPanel);
    GamaInfoPanel.setPosition(Vector2f(0, 0));

    // Логотип разработчика
    Texture textlog;
    textlog.loadFromFile("Image/log.png");
    RectangleShape log(Vector2f(50, 50));
    log.setTexture(&textlog);
    log.setPosition(Vector2f(1210, 650));

    // Игрок
    Texture texplayer;
    texplayer.loadFromFile("Image/player.png");
    RectangleShape player(Vector2f(50, 30));
    player.setTexture(& texplayer);
    player.setPosition(Vector2f(80, 380));


    RectangleShape player2(Vector2f(100, 60));
    player2.setTexture(&texplayer);
    player2.setPosition(Vector2f(80, 380));

    CircleShape Rcircle(5.f);
    Rcircle.setFillColor(Color(255, 0, 0));    // закрашиваем наш круг
    Rcircle.setOutlineThickness(2.f);           // устанавливаем толщину контура круга
    Rcircle.setOutlineColor(Color(255, 155, 0)); // устанавливаем цвет контура
    Rcircle.setPosition(495,33);

    // Звездное время
    Texture imgkos;
    imgkos.loadFromFile("Image/newkos1.jpg");
    RectangleShape FonRec(Vector2f(1280,720));
    FonRec.setTexture(& imgkos);
    RectangleShape FonRec2(Vector2f(1280, 720));
    FonRec2.setTexture(& imgkos);
    FonRec2.setPosition(Vector2f(1280, 0));
    
    Vector2f moveRec;
    Clock clock, clock1,clock2;
    Time GameTime, GameAnTime, GameRadarTime;
    
    ExternalWorld meteor(25, "Image/kam.png");  //  Камни первый этап
    ExternalWorld trash(20);                    // Камни второй этап
    int tmpMasKamTex = 10;
    for (int i = 0; i < trash.getNumRect(); i++) { tmpMasKamTex--; if (tmpMasKamTex < 0) tmpMasKamTex = 9; trash.InitRectTextureArr(i, masKamTex[tmpMasKamTex]); }
    tmpMasKamTex = 10;
    ExternalWorld ships(10,140,70);
    for (int i = 0; i < ships.getNumRect(); i++) { tmpMasKamTex--; if (tmpMasKamTex < 0) tmpMasKamTex = 9; ships.InitRectTextureArr(i, masInTex[tmpMasKamTex]); }
    
    bool fullstop = false;
    ExternalWorld myfull[3];
    myfull[0].InitObject(3,masBonusTex[0],40,40); 
    myfull[1].InitObject(2, masBonusTex[1], 60, 60);
    myfull[2].InitObject(1, masBonusTex[2], 80, 80);

    for (int i = 0; i < 3; i++) myfull[0].Setbonus(i, 5);
    for (int i = 0; i < 2; i++) myfull[1].Setbonus(i, 20);
    myfull[2].Setbonus(0, 50);
     

    // Фоновая музыка   
    bool mus = false; // Переключение музыки
    Music game_music;
    if (!game_music.openFromFile("Music/mgame.ogg"))  return -1;
    game_music.setLoop(true);
     
    // Анимация
    int arrAnim[3]{ 9,59,103};
    int Frame = 3;
    int stepanim = -1;
    Texture herotexture;
    herotexture.loadFromFile("Image/anim.png");
    Sprite herosprite;
    herosprite.setTexture(herotexture);
    


    // Игровой цикл
    while (window.isOpen())
    { 
        Event event;
        while (window.pollEvent(event))
        {
            // проверяем тип события...
            switch (event.type)
            {
                // окно закрыто
            case Event::Closed:
                window.close();
                break;

                // клавиша нажата
            case Event::KeyPressed:
                
                // Управление для разработчика
                switch (event.key.code)
                {
                case Keyboard::P:Rcircle.setPosition(848, 33); break;
                case Keyboard::Num1:etapgame = 1; break;
                case Keyboard::Num3: etapgame = 3; break;
                default:
                    break;
                }

                // Управление игровым процессом
                                      
                if (event.key.code == Keyboard::Pause) pause = !pause;
                if (event.key.code == Keyboard::M) { mus=!mus; if (mus) game_music.play(); else game_music.stop();}
                if (event.key.code == Keyboard::End) window.close();
                
                if (event.key.code == Keyboard::R)
                {
                    meteor.Restart();
                    trash.Restart();
                    ships.Restart();
                    for (int i = 0; i < 3; i++) myfull[i].Restart();
                    GameTime = seconds(0);
                    player.setPosition(Vector2f(80, 380));
                    Rcircle.setPosition(495, 33);
                    full = 100;
                    etapgame = 0;
                    speedRadar = 1;
                }
                
                if ((event.key.code == Keyboard::Numpad5) || (event.key.code == Keyboard::S)) {
                   if (speedplayr<5) speedplayr += 1; moveRec.y = speedplayr;  full -= 1;
                    if (sonON) {
                        son.play(); sonON = !sonON;
                    }
                 }
                if ((event.key.code == Keyboard::Numpad8) || (event.key.code == Keyboard::W)) {
                    if (speedplayr < 5) speedplayr +=1; moveRec.y = - speedplayr;  full -= 1;  if (sonON) {
                        son.play(); sonON = !sonON;
                    }
                    
                }
                if ((event.key.code == Keyboard::Numpad4) || (event.key.code == Keyboard::A)) {
                    if (speedplayr < 5) speedplayr += 1; moveRec.x = -speedplayr;  full -= 1;   if (sonON) {
                        son.play(); sonON = !sonON;
                    }
                    
                }
                if ((event.key.code == Keyboard::Numpad6) || (event.key.code == Keyboard::D)) {
                    if (speedplayr < 5) speedplayr += 1; moveRec.x = speedplayr;  full -= 1;   if (sonON) {
                        son.play(); sonON = !sonON;
                    }
                }
                
                break;

            case Event::KeyReleased:
                if ((event.key.code == Keyboard::Numpad5) || (event.key.code == Keyboard::S)) {  speedplayr = 1; moveRec.y = 0; son.stop(); sonON = !sonON;
                }
                if ((event.key.code == Keyboard::Numpad8) || (event.key.code == Keyboard::W)) {  speedplayr = 1; moveRec.y = 0; son.stop(); sonON = !sonON;
                }
                if ((event.key.code == Keyboard::Numpad4) || (event.key.code == Keyboard::A)) {  speedplayr = 1; moveRec.x = 0; son.stop(); sonON = !sonON;
                }
                if ((event.key.code == Keyboard::Numpad6) || (event.key.code == Keyboard::D)) {  speedplayr = 1; moveRec.x = 0; son.stop(); sonON = !sonON;
                }

                break;
           
            default:
                break;
            }
        }

        if (pause) {

            // Радар корабля
            if (Rcircle.getPosition().x <= 850) {
                
                Time radarTime = clock2.restart(); 
                GameRadarTime += radarTime;

                if (GameRadarTime > seconds(2.8))
                {
                    GameRadarTime = seconds(0);
                    Rcircle.move(speedRadar, 0);
                }

                
                // Анимация

                Time animTime = clock1.restart();  
                GameAnTime += animTime;

                if (GameAnTime > milliseconds(100))
                {
                    GameAnTime = milliseconds(0);
                    Frame+=stepanim;
                   herosprite.setTextureRect(IntRect(0, arrAnim[Frame], 85, 43));
                    if (Frame == 0) stepanim = 1;
                    if (Frame == 2) stepanim = -1;
                }

                Time deltaTime = clock.restart();
                GameTime += deltaTime;

                if (GameTime > seconds(10))
                {
                    GameTime = seconds(0);

                    if (meteor.getspeed() < 2 && etapgame == 0) { meteor.increaseSpeed(); speedRadar = meteor.getspeed(); }
                    else if (etapgame == 0) { etapgame = 1; trash.Setspeed(2); }

                    if (etapgame == 2 && trash.getspeed() < 3) {
                        trash.increaseSpeed(); speedRadar = trash.getspeed();
                    }
                    else if (etapgame == 2) { etapgame = 3; ships.Setspeed(3); }


                    if (etapgame == 4 && ships.getspeed() < 4) { ships.increaseSpeed(); speedRadar = ships.getspeed(); }
                    
                    else if (etapgame == 4) { etapgame = 5; }

                    if (etapgame == 0 || etapgame == 2) for (int i = 0; i < 3; i++) myfull[i].increaseSpeed();


                }

                if (etapgame == 1 && !meteor.getstop()) meteor.SetStop(true);

                if (meteor.getNullObject() && etapgame == 1) etapgame = 2;

                if (etapgame == 3 && !trash.getstop()) { trash.SetStop(true); for (int i = 0; i < 3; i++) myfull[i].SetStop(true); }

                if (trash.getNullObject() && etapgame == 3 && myfull[0].getNullObject() && myfull[1].getNullObject() && myfull[2].getNullObject()) { etapgame = 4; fullstop = true; }

                if (etapgame == 5 && !ships.getstop())  ships.SetStop(true);

                if (ships.getNullObject() && etapgame == 5) etapgame = 6;

                FonRec.move(-0.2, 0); // Звёздное небо
                pos = FonRec.getPosition();
                if (pos.x < -1280) FonRec.setPosition(1280, pos.y);
                FonRec2.move(-0.2, 0);// Звёздное небо 2
                pos = FonRec2.getPosition();
                if (pos.x < -1280) FonRec2.setPosition(1280, pos.y);

                player.move(moveRec);// Космический корабль

                
                herosprite.setPosition(Vector2f(player.getPosition().x-80, player.getPosition().y-4));
                

                pos = player.getPosition();
                if (pos.x > 1200) player.setPosition(1200, pos.y);
                if (pos.x < 50) player.setPosition(50, pos.y);
                if (pos.y > 670) player.setPosition(pos.x, 670);
                if (pos.y < 120) player.setPosition(pos.x, 120);

                if ((pos.x > 1200) && (pos.y < 120))  player.setPosition(1200, 120);
                if ((pos.x > 1200) && (pos.y > 670)) player.setPosition(1200, 670);

                if ((pos.x < 50) && (pos.y < 120))  player.setPosition(50, 120);
                if ((pos.x < 50) && (pos.y > 670)) player.setPosition(50, 670);

                

                if (meteor.getNullObject() != true) meteor.Motion();
                if (etapgame == 2 || etapgame == 3)if (trash.getNullObject() != true) trash.Motion();
                if (etapgame == 4 || etapgame == 5)if (ships.getNullObject() != true) ships.Motion();
               
               
                        if (meteor.Collision(player.getGlobalBounds()) || full == 0 || trash.Collision(player.getGlobalBounds()) || ships.Collision(player.getGlobalBounds()))
                        {
                            meteor.Restart();
                            trash.Restart();
                            ships.Restart();
                            for (int i = 0; i < 3; i++) myfull[i].Restart();
                            fullstop = false;
                            GameTime = seconds(0);
                            player.setPosition(Vector2f(80, 380));
                            Rcircle.setPosition(495, 33);
                            full = 100;
                            falson.play();
                            etapgame = 0;
                            speedRadar=1;
                        }
                        
                        
                        if (!fullstop) {
                            for (int i = 0; i < 3; i++) {

                                myfull[i].Motion();

                                if (myfull[i].Collision(player.getGlobalBounds()))
                                {
                                    full += myfull[i].getfull();

                                    if (myfull[i].getfull() == 50) sonbonB.play(); else sonbonM.play();

                                    plusfull.setString(IntToStr(myfull[i].getfull()));
                                    plusfull.setPosition(myfull[i].getPosBonus().x, myfull[i].getPosBonus().y);
                                    par = 60;
                                }
                            }

                            for (int i = 0; i < 3; i++) {myfull[2].Collision(myfull[0].getGameGlobalBounds(i)); myfull[1].Collision(myfull[0].getGameGlobalBounds(i));   }
                            for (int i = 0; i < 2; i++)  myfull[2].Collision(myfull[1].getGameGlobalBounds(i));
                    
                
                }

                if (meteor.getNullObject() != true) { for (int i = 0; i < 3; i++) for (int i1 = 0; i1 < meteor.getNumRect(); i1++) myfull[i].Collision(meteor.getGameGlobalBounds(i1)); }
                if (trash.getNullObject() != true) { for (int i = 0; i < 3; i++) for (int i1 = 0; i1 < trash.getNumRect(); i1++) myfull[i].Collision(trash.getGameGlobalBounds(i1)); }
                
                if (par > 0)
                {
                    par--;
                    plusfull.move(0, -1);
                }
                if (full >= 100)  text_gold.setFillColor(Color::Green);
                if (full < 100 && full >= 50)  text_gold.setFillColor(Color::Yellow);
                if (full < 50)  text_gold.setFillColor(Color::Red);
                text_gold.setString(IntToStr(full) + L" тонн");
                window.clear(Color::Black);
                window.draw(FonRec);
                window.draw(FonRec2);
                window.draw(GamaInfoPanel);
                window.draw(text_gold);
                window.draw(Rcircle);
                window.draw(player);
                window.draw(herosprite);
                meteor.DrawSpaceObject(window);
                trash.DrawSpaceObject(window);
                ships.DrawSpaceObject(window);
                for (int i = 0; i < 3; i++) myfull[i].DrawSpaceObject(window);
                if (par > 0) window.draw(plusfull);
                window.draw(log);
                window.display();
                if (Rcircle.getPosition().x > 850) { game_music.stop(); sonvic.play(); }

            }
            else
            {   
                
                window.draw(FonRec);
                window.draw(FonRec2);
                window.draw(GamaInfoPanel);
                window.draw(text_gold);
                window.draw(Rcircle);
                window.draw(player2);
                window.draw(Earth);
                window.draw(end_game); 
                window.display();

            }
        }
        else {

        window.draw(pausetext); 
        window.display();}
    }

    return 0;
}


