#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define MAXFILAS 20
#define MAXCOLUMNAS 31

char mapa_1f[MAXFILAS][MAXCOLUMNAS] = 
{
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X    |      XXXXX      |    X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X|   |     |     |     |   |X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X|   |XX     XXX     XX|   |X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X XXX XX    |   |    XX XXX X",
    " |   |XX XXXXXXXXXXX XX|   | ",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X XXX XX    |   |    XX XXX X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X|   |XX     XXX     XX|   |X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X XXX|  |           |  |XXX X",
    "X XXX XXXX XXXXXXXX XXX XXX X",
    "X XXX XXXX|        |XXX XXX X",
    "X          XXXXXXXX         X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

class Fantasma
{
public:
    int dir = 0;
    int x = 420;
    int y = 330;

    ALLEGRO_BITMAP *fantasma;

    Fantasma();
    void draw();
    ~Fantasma();
};

Fantasma::Fantasma()
{
    fantasma = al_load_bitmap("imagenes/fantasma.png");
}

void Fantasma::draw ()
{
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

Fantasma::~Fantasma()
{
    al_destroy_bitmap(fantasma);
}
