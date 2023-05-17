#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "pacman.h"
#include "fantasmas.h"

using namespace std;

#define MAXFILAS 20
#define MAXCOLUMNAS 31

void dibujar_mapa (int x, int y);
bool game_over ();

char mapa_1[MAXFILAS][MAXCOLUMNAS] = 
{
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "XoooooooooooXXXXXoooooooooooX",
    "XoXXXoXXXXXoXXXXXoXXXXXoXXXoX",
    "XoXXXoXXXXXoXXXXXoXXXXXoXXXoX",
    "XoooooooooooooooooooooooooooX",
    "XoXXXoXXoXXXXXXXXXXXoXXoXXXoX",
    "XoooooXXoooooXXXoooooXXoooooX",
    "XoXXXoXXXXXXoXXXoXXXXXXoXXXoX",
    "XoXXXoXXoooooooooooooXXoXXXoX",
    "ooooooXXoXXXXXXXXXXXoXXoooooo",
    "XoXXXoXXoXXXXXXXXXXXoXXoXXXoX",
    "XoXXXoXXoooooooooooooXXoXXXoX",
    "XoXXXoXXXXXXoXXXoXXXXXXoXXXoX",
    "XoooooXXoooooXXXoooooXXoooooX",
    "XoXXXoXXoXXXXXXXXXXXoXXoXXXoX",
    "XoXXXoooooooooooooooooooXXXoX",
    "XoXXXoXXXXoXXXXXXXXoXXXoXXXoX",
    "XoXXXoXXXXooooooooooXXXoXXXoX",
    "XooooooooooXXXXXXXXoooooooooX",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

int main() 
{

    int wigth = 870;
    int height = 600;

    ALLEGRO_DISPLAY *display = NULL;

    al_init();
    al_init_image_addon();
    al_install_keyboard();

    display = al_create_display(wigth, height);

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER *FPS = al_create_timer(1.0 / 60);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(FPS));

    al_start_timer(FPS);

    PacMan* pacman = new PacMan();
    Fantasma* fantasma = new Fantasma();

    while (game_over())
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_D:
                pacman->mov_right();
                break;
            case ALLEGRO_KEY_A:
                pacman->mov_left();
                break;
            case ALLEGRO_KEY_W:
                pacman->mov_up();
                break;
            case ALLEGRO_KEY_S:
                pacman->mov_down();
                break;
            }
        }

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            pacman->animation();
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        dibujar_mapa(pacman->x, pacman->y);
        
        fantasma->draw();

        pacman->Draw();

        al_flip_display();
    }

    fantasma->~Fantasma();
    pacman->~PacMan();
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}

void dibujar_mapa (int x, int y)
{
    int row, col;

    ALLEGRO_BITMAP *roca = NULL;
    ALLEGRO_BITMAP *comida = NULL;

    roca = al_load_bitmap("imagenes/roca.jpg");
    comida = al_load_bitmap("imagenes/comida.png");

    for(row = 0; row < MAXFILAS; row++)
    {
        for(col = 0; col < MAXCOLUMNAS; col++)
        {
            if (mapa_1[row][col] == 'X')
            {
                al_draw_bitmap(roca, col*30, row*30, 0);  
            }
            else if (mapa_1[row][col] == 'o')
            {
                al_draw_bitmap(comida, col*30, row*30, 0);

                if (y/30 == row && x/30 == col)
                {
                    mapa_1[row][col] = ' ';
                }
            }
        }
    }
    al_destroy_bitmap(roca);
    al_destroy_bitmap(comida);
}

bool game_over ()
{
    int row, col;

    for(row = 0; row < MAXFILAS; row++)
    {
        for(col = 0; col < MAXCOLUMNAS; col++)
        {
            if (mapa_1[row][col] == 'o') return true;
        }
    }
    return false;
}

// g++ main.cpp -o PacManCE -lallegro -lallegro_image
// ./PacManCE
