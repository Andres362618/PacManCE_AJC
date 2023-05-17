#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define MAXFILAS 20
#define MAXCOLUMNAS 31

char mapa_1P[MAXFILAS][MAXCOLUMNAS] = 
{
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X           XXXXX           X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X                           X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X     XX     XXX     XX     X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X XXX XX             XX XXX X",
    "      XX XXXXXXXXXXX XX      ",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X XXX XX             XX XXX X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X     XX     XXX     XX     X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X XXX                   XXX X",
    "X XXX XXXX XXXXXXXX XXX XXX X",
    "X XXX XXXX          XXX XXX X",
    "X          XXXXXXXX         X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

class PacMan
{
public:
    ALLEGRO_BITMAP *pacman_right;
    ALLEGRO_BITMAP *pacman_left;
    ALLEGRO_BITMAP *pacman_up;
    ALLEGRO_BITMAP *pacman_down;
    ALLEGRO_BITMAP *pacman;
    int x;
    int dir;
    int y;
    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidht;
    int frameHeight;

    PacMan();
    ~PacMan();
    void mov_right();
    void mov_left();
    void mov_up();
    void mov_down();
    void animation();
    void Draw();
};

PacMan::PacMan()
{
    pacman_right = al_load_bitmap("imagenes/pacman-right.png");
    pacman_left = al_load_bitmap("imagenes/pacman-left.png");
    pacman_up = al_load_bitmap("imagenes/pacman-up.png");
    pacman_down = al_load_bitmap("imagenes/pacman-down.png");

    pacman = pacman_right;

    x = 420;
    dir = 4;
    y = 330;

    maxFrame = 2;
    curFrame = 0;
    frameCount = 0;
    frameDelay = 6;
    frameWidht = 30;
    frameHeight = 30;
}

void PacMan::mov_right()
{
    pacman = pacman_right;
    dir = 1;
}

void PacMan::mov_left()
{
    pacman = pacman_left;
    dir = 0;
}

void PacMan::mov_up()
{
    pacman = pacman_up;
    dir = 2;
}

void PacMan::mov_down()
{
    pacman = pacman_down;
    dir = 3;
}

void PacMan::animation()
{
    if (++frameCount >= frameDelay)
    {
        if (++curFrame >= maxFrame)
            curFrame = 0;
        
        frameCount = 0;
    }
}

void PacMan::Draw()
{
    if (dir == 0)
    {
        if (mapa_1P[(y)/30][(x-1)/30] != 'X')
        {
            x -= 5;
        }
        else dir = 4;
    }
    
    if (dir == 1)
    {
        if (mapa_1P[(y)/30][(x+30)/30] != 'X')
        {
            x += 5;
        }
        else dir = 4;
    }

    if (dir == 2) 
    {
        if (mapa_1P[(y-1)/30][(x)/30] != 'X')
        {
            y -= 5;
        }
        else dir = 4;
    }
    
    if (dir == 3)
    {
        if (mapa_1P[(y+30)/30][(x)/30] != 'X')
        {
            y += 5;
        }
        else dir = 4;
    }

    if (x >= 870)
    {
        x = -30;
    }

    else if (x <= -30)
    {
        x = 870;
    }
    
    
    
    al_draw_bitmap_region(pacman, curFrame * frameWidht, 0, frameWidht, frameHeight, x, y, 0);
}

PacMan::~PacMan()
{
    al_destroy_bitmap(pacman_right);
    al_destroy_bitmap(pacman_left);
    al_destroy_bitmap(pacman_up);
    al_destroy_bitmap(pacman_down);
}