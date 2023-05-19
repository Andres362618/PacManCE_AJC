#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "pacman.h"
#include "fantasmas.h"

using namespace std;

#define MAXFILAS 20
#define MAXCOLUMNAS 31

void dibujar_mapa_1 (int x, int y);
void dibujar_mapa_2 (int x, int y);
bool game_over ();
int nivel_2 ();

char mapa_1[MAXFILAS][MAXCOLUMNAS] = 
{
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "XoooooooooooXXXXXXoooooooooooX",
    "XoXXXoXXXXXoXXXXXXoXXXXXoXXXoX",
    "XoXXXoXXXXXoXXXXXXoXXXXXoXXXoX",
    "XooooooooooooooooooooooooooooX",
    "XoXXXoXXoXXXXXXXXXXXXoXXoXXXoX",
    "XoooooXXoooooXXXXoooooXXoooooX",
    "XoXXXoXXXXXXoXXXXoXXXXXXoXXXoX",
    "XoXXXoXXooooooooooooooXXoXXXoX",
    "ooooooXXoXXXXXXXXXXXXoXXoooooo",
    "XoXXXoXXoXXXXXXXXXXXXoXXoXXXoX",
    "XoXXXoXXooooooooooooooXXoXXXoX",
    "XoXXXoXXXXXXoXXXXoXXXXXXoXXXoX",
    "XoooooXXoooooXXXXoooooXXoooooX",
    "XoXXXoXXoXXXXXXXXXXXXoXXoXXXoX",
    "XoXXXooooooooooooooooooooXXXoX",
    "XoXXXoXXXXoXXXXXXXXXoXXXoXXXoX",
    "XoXXXoXXXXoooooooooooXXXoXXXoX",
    "XooooooooooXXXXXXXXXoooooooooX",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

char mapa_2[MAXFILAS][MAXCOLUMNAS] = 
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

int main() 
{
    int vidas = 3;
    int puntuacion = 0;

    int wigth = 1010;
    int height = 600;

    ALLEGRO_DISPLAY *display = NULL;

    ALLEGRO_FONT* minecraft = NULL;

    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();

    display = al_create_display(wigth, height);

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER *FPS = al_create_timer(1.0 / 60);

    ALLEGRO_BITMAP *corazon = al_load_bitmap("imagenes/corazon.png");
    ALLEGRO_BITMAP *vida_1 = al_load_bitmap("imagenes/1.png");
    ALLEGRO_BITMAP *vida_2 = al_load_bitmap("imagenes/2.png");
    ALLEGRO_BITMAP *vida_3 = al_load_bitmap("imagenes/3.png");
    ALLEGRO_BITMAP *muro = al_load_bitmap("imagenes/muro.png");
    ALLEGRO_BITMAP *puntos = al_load_bitmap("imagenes/comida.png");
    ALLEGRO_BITMAP *vida = vida_3;

    minecraft = al_load_font("fuentes/Minecraft.ttf", 30, 0);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(FPS));

    al_start_timer(FPS);

    PacMan* pacman = new PacMan();
    Fantasma* fantasma = new Fantasma();

    bool play = true;

    while (play)
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

        if (mapa_1[pacman->y/30][pacman->x/30] == 'o')
        {
            puntuacion += 10;
        }
        
        if ((pacman->x)/30 == (fantasma->x)/30 && 
            (pacman->y)/30 == (fantasma->y)/30)
        {
            pacman->x = 15*30;
            pacman->y = 17*30;
            pacman->dir = 4;

            vidas--;           

            fantasma->x = 2*30;
            fantasma->y = 2*30;
        }

        if (vidas == 2)
        {
            vida = vida_2;
        }
        
        if (vidas == 1)
        {
            vida = vida_1;
        }
        
        if (vidas == 0)
            {
                fantasma->~Fantasma();
                pacman->~PacMan();
                al_destroy_bitmap(vida);
                al_destroy_bitmap(vida_1);
                al_destroy_bitmap(vida_2);
                al_destroy_bitmap(vida_3);
                al_destroy_bitmap(muro);
                al_destroy_bitmap(corazon);
                al_destroy_bitmap(puntos);
                al_destroy_event_queue(queue);
                al_destroy_display(display);
                play = false;
            }

        if (game_over() == false)
        {
            fantasma->~Fantasma();
            pacman->~PacMan();
            al_destroy_bitmap(vida);
            al_destroy_bitmap(vida_1);
            al_destroy_bitmap(vida_2);
            al_destroy_bitmap(vida_3);
            al_destroy_bitmap(muro);
            al_destroy_bitmap(corazon);
            al_destroy_bitmap(puntos);
            al_destroy_event_queue(queue);
            al_destroy_display(display);

            nivel_2 ();
        }
        
        al_clear_to_color(al_map_rgb(0, 0, 0));

        dibujar_mapa_1(pacman->x, pacman->y);

        al_draw_text(minecraft, al_map_rgb(255, 255, 255), 30*30 + 10, 1*30, NULL, "Nivel 1");

        al_draw_bitmap(muro, 30*30, 0, 0);

        al_draw_bitmap(corazon, 30*30 + 10, 3*30, 0);
        al_draw_bitmap(vida, 31*30 + 20, 3*30, 0);

        al_draw_bitmap(puntos, 30*30 + 10, 5*30, 0);
        al_draw_text(minecraft, al_map_rgb(255, 255, 255), 31*30 + 10, 5*30, NULL, to_string(puntuacion).c_str());

        
        fantasma->draw();

        pacman->Draw_1();

        al_flip_display();
    }   

    fantasma->~Fantasma();
    pacman->~PacMan();
    al_destroy_bitmap(vida);
    al_destroy_bitmap(vida_1);
    al_destroy_bitmap(vida_2);
    al_destroy_bitmap(vida_3);
    al_destroy_bitmap(muro);
    al_destroy_bitmap(corazon);
    al_destroy_bitmap(puntos);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}

int nivel_2() 
{
    int wigth = 900;
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
    Fantasma* a = new Fantasma();
    Fantasma* b = new Fantasma();

    while (true)
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

        if ((pacman->x)/30 == (a->x)/30 && 
            (pacman->y)/30 == (a->y)/30 ||
            (pacman->x)/30 == (b->x)/30 && 
            (pacman->y)/30 == (b->y)/30)
        {
            pacman->x = 15*30;
            pacman->y = 17*30;
            pacman->dir = 4;

            a->x = 2*30;
            a->y = 2*30;

            b->x = 29*30;
            b->y = 2*30;
        }
/*
        if (game_over() == false)
        {
            al_destroy_display(display);
            al_destroy_event_queue(queue);

            nivel_3 ();
        }*/
        
        al_clear_to_color(al_map_rgb(0, 0, 0));

        dibujar_mapa_2(pacman->x, pacman->y);
        
        a->draw_2();
        b->draw_2();

        pacman->Draw_2();

        al_flip_display();
    }   

    a->~Fantasma();
    b->~Fantasma();
    pacman->~PacMan();
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}

void dibujar_mapa_1 (int x, int y)
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

void dibujar_mapa_2 (int x, int y)
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
            if (mapa_2[row][col] == 'X')
            {
                al_draw_bitmap(roca, col*30, row*30, 0);  
            }
            else if (mapa_2[row][col] == 'o')
            {
                al_draw_bitmap(comida, col*30, row*30, 0);

                if (y/30 == row && x/30 == col)
                {
                    mapa_2[row][col] = ' ';
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

// g++ main.cpp -o PacManCE -lallegro -lallegro_image -lallegro_font -lallegro_ttf
// ./PacManCE
