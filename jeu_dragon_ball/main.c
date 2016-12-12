#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "const.h"
#include "play.h"

int main(int argc, char*argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(SDL_LoadBMP("dragon_ball.bmp"), NULL); //icon doit etre charge avant SDL_SetVideoMode
    ecran = SDL_SetVideoMode(WIDTH_WINDOW, LENGTH_WINDOW, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Dragon Ball", NULL);

    menu = SDL_LoadBMP("logo_dragon.bmp");
    positionMenu.x = 0;
    positionMenu.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_KP1: //demande à jouer
                        play(ecran);
                        break;
                    case SDLK_KP2: //demande niveaux
                        continuer = 0;
                        break;
		    default: break;
                }
                break;
        }
        //Effacement de l'ecran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;

}
