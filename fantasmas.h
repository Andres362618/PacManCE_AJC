#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define MAXFILAS 20
#define MAXCOLUMNAS 31

char mapa_1f[MAXFILAS][MAXCOLUMNAS] = 
{
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X    |      XXXXXX      |    X",
    "X XXX XXXXX XXXXXX XXXXX XXX X",
    "X XXX XXXXX XXXXXX XXXXX XXX X",
    "X       |            |       X",
    "X XXX XX XXXXXXXXXXXX XX XXX X",
    "X    |XX     XXXX     XX|    X",
    "X XXX XXXXXX XXXX XXXXXX XXX X",
    "X XXX XX    |    |    XX XXX X",
    "     |XX XXXXXXXXXXXX XX|     ",
    "X XXX XX XXXXXXXXXXXX XX XXX X",
    "X XXX XX    |    |    XX XXX X",
    "X XXX XXXXXX XXXX XXXXXX XXX X",
    "X     XX     XXXX     XX     X",
    "X XXX XX XXXXXXXXXXXX XX XXX X",
    "X XXX|  |            |  |XXX X",
    "X XXX XXXX XXXXXXXXX XXX XXX X",
    "X XXX XXXX           XXX XXX X",
    "X    |     XXXXXXXXX    |    X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

char mapa_2f[MAXFILAS][MAXCOLUMNAS] = 
{
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "X                            X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

class Fantasma
{
public:
    int dir = 0;
    int x = 2*30;
    int y = 2*30;

    ALLEGRO_BITMAP *fantasma;

    Fantasma();
    void draw();
    void draw_2();
    ~Fantasma();
};

Fantasma::Fantasma()
{
    fantasma = al_load_bitmap("imagenes/fantasma.png");
}

void Fantasma::draw ()
{
    if (mapa_1f[(y)/30][(x)/30] == '|')
    {
        dir = rand() % 4;
    }
    
    if (dir == 0)
    {
        if (mapa_1f[(y)/30][(x-1)/30] != 'X') x -= 5;
        else dir = rand() % 4;
    }

    if (dir == 1)
    {
        if (mapa_1f[(y)/30][(x+30)/30] != 'X') x += 5;
        else dir = rand() % 4;
    }

    if (dir == 2)
    {
        if (mapa_1f[(y-1)/30][(x)/30] != 'X') y -= 5;
        else dir = rand() % 4;
    }

    if (dir == 3)
    {
        if (mapa_1f[(y+30)/30][(x)/30] != 'X') y += 5;
        else dir = rand() % 4;
    }

    if (x >= 870)
    {
        x = -30;
    }

    else if (x <= -30)
    {
        x = 870;
    }
    
    al_draw_bitmap(fantasma, x, y, 0);
}

void Fantasma::draw_2 ()
{
    if (mapa_2f[(y)/30][(x)/30] == '|')
    {
        dir = rand() % 4;
    }
    
    if (dir == 0)
    {
        if (mapa_2f[(y)/30][(x-1)/30] != 'X') x -= 5;
        else dir = rand() % 4;
    }

    if (dir == 1)
    {
        if (mapa_2f[(y)/30][(x+30)/30] != 'X') x += 5;
        else dir = rand() % 4;
    }

    if (dir == 2)
    {
        if (mapa_2f[(y-1)/30][(x)/30] != 'X') y -= 5;
        else dir = rand() % 4;
    }

    if (dir == 3)
    {
        if (mapa_2f[(y+30)/30][(x)/30] != 'X') y += 5;
        else dir = rand() % 4;
    }

    if (x >= 870)
    {
        x = -30;
    }

    else if (x <= -30)
    {
        x = 870;
    }
    
    al_draw_bitmap(fantasma, x, y, 0);
}

Fantasma::~Fantasma()
{
    al_destroy_bitmap(fantasma);
}
