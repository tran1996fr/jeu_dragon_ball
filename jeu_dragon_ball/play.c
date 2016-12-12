#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "const.h"
#include "play.h"


void play(SDL_Surface* ecran)
{
    SDL_Surface *songuku[4] = {NULL}; //4 surfaces pour 4 directions de songuku
    SDL_Surface *wall = NULL, *ball = NULL, *namek_red = NULL, *namek_green = NULL, *songukuActuel = NULL;
    SDL_Rect position, positionPlayer;

    SDL_Event event;

    int continuer = 1, objectifsRemaining = 0, i = 0, j = 0;
    int carte[NB_SQUARES_LENGTH][NB_SQUARES_WIDTH] = {0};

    //Chargement des sprites
    wall = SDL_LoadBMP("wall.bmp");
    ball = SDL_LoadBMP("dragon_ball.bmp");
    namek_red = SDL_LoadBMP("namek_red.bmp");
    namek_green = SDL_LoadBMP("namek_green.bmp");
    songuku[UP] = SDL_LoadBMP("songuku_up.bmp");
    songuku[DOWN] = SDL_LoadBMP("songuku_down.bmp");
    songuku[LEFT] = SDL_LoadBMP("songuku_left.bmp");
    songuku[RIGHT] = SDL_LoadBMP("songuku_right.bmp");

    songukuActuel = songuku[DOWN];

    // Chargement du niveau
    chargerNiveau(carte);

    //Cherche la position de songuku
    for(i = 0; i < NB_SQUARES_LENGTH; i++)
    {
        for(j = 0; j < NB_SQUARES_WIDTH; j++)
        {
            if (carte[i][j] == SONGUKU)
            {
                positionPlayer.x = i;
                positionPlayer.y = j;
                carte[i][j] = EMPTY;
            }
        }
    }

    //Activation  de la répétition de touche
    SDL_EnableKeyRepeat(100, 100);

    //Gestion de la déplacement de songuku
    while(continuer)
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
                    case SDLK_UP:
                        songukuActuel = songuku[UP];
                        deplacerPlayer(carte, &positionPlayer, UP);
                        break;
                    case SDLK_DOWN:
                        songukuActuel = songuku[DOWN];
                        deplacerPlayer(carte, &positionPlayer, DOWN);
                        break;
                    case SDLK_LEFT:
                        songukuActuel = songuku[LEFT];
                        deplacerPlayer(carte, &positionPlayer, LEFT);
                        break;
                    case SDLK_RIGHT:
                        songukuActuel = songuku[RIGHT];
                        deplacerPlayer(carte, &positionPlayer, RIGHT);
                        break;
		    default: break;
                }
                break;
        }
        /*Blitter*/
        //Mettre la couleur blanc pour le fond
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        // Placement des objets à l'écran
        objectifsRemaining = 0;

        //Blitter EMPTY, wall, ball, NAMEK_GREEN, songuku, ball_OK
        for(i = 0; i < NB_SQUARES_LENGTH; i++)
        {
            for(j = 0; j < NB_SQUARES_WIDTH; j++)
            {
                position.x = i * SIZE_BLOCK;
                position.y = j * SIZE_BLOCK;
                //On vérifie des cas(EMPTY, wall, ball, NAMEK_GREEN, songuku, namek_red)
                switch(carte[i][j])
                {
                    case WALL:
                        SDL_BlitSurface(wall, NULL, ecran, &position);
                        break;
                    case BALL:
                        SDL_BlitSurface(ball, NULL, ecran, &position);
                        break;
                    case NAMEK_GREEN:
                        SDL_BlitSurface(namek_green, NULL, ecran, &position);
                        objectifsRemaining = 1;
                        break;
                    case NAMEK_RED:
                        SDL_BlitSurface(namek_red, NULL, ecran, &position);
                        break;
                    case SONGUKU:
                        SDL_BlitSurface(songukuActuel, NULL, ecran, &position);
                        break;
                }

            }
        }
        // Si on n'a trouvé aucun NAMEK_GREEN sur la carte, c'est qu'on a gagné
        if (!objectifsRemaining)
            continuer = 0;

        // On place le Player à la bonne position
        position.x = positionPlayer.x * SIZE_BLOCK;
        position.y = positionPlayer.y * SIZE_BLOCK;
        SDL_BlitSurface(songukuActuel, NULL, ecran, &position);

        /*Après blit, on va faire flip*/
        SDL_Flip(ecran);

    }
    //Disable EnableKeyRepeat
    SDL_EnableKeyRepeat(0, 0);

    /*Free surface*/
    SDL_FreeSurface(wall);
    SDL_FreeSurface(ball);
    SDL_FreeSurface(namek_red);
    SDL_FreeSurface(namek_green);
    for (i = 0; i < 4; i++)
    {
        SDL_FreeSurface(songuku);
    }

}
void deplacerPlayer(int carte[NB_SQUARES_LENGTH][NB_SQUARES_WIDTH], SDL_Rect *pos, int direction)
{
    switch(direction)
    {
        case UP:
            if (carte[pos->x][pos->y - 1] == EMPTY)
            {
                pos->y--;
                break;
            }
            else if ((carte[pos->x][pos->y - 1] == BALL || carte[pos->x][pos->y - 1] == NAMEK_RED) && (carte[pos->x][pos->y - 2] == NAMEK_GREEN || carte[pos->x][pos->y - 2] == EMPTY))

                {
                    deplacerball(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);
                    pos->y--;
                    break;
                }
            else
                break;
        case DOWN:
            if (carte[pos->x][pos->y + 1] == EMPTY)
            {
                pos->y++;
                break;
            }
            else if ((carte[pos->x][pos->y + 1] == BALL || carte[pos->x][pos->y + 1] == NAMEK_RED) && (carte[pos->x][pos->y + 2] == NAMEK_GREEN || carte[pos->x][pos->y + 2] == EMPTY))

                {
                    deplacerball(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);
                    pos->y++;
                    break;
                }
            else
                break;
        case RIGHT:
            if (carte[pos->x+1][pos->y] == EMPTY)
            {
                pos->x++;
                break;
            }
            else if ((carte[pos->x+1][pos->y] == BALL || carte[pos->x+1][pos->y] == NAMEK_RED) && (carte[pos->x+2][pos->y] == NAMEK_GREEN || carte[pos->x+2][pos->y] == EMPTY))

                {
                    deplacerball(&carte[pos->x+1][pos->y], &carte[pos->x+2][pos->y]);
                    pos->x++;
                    break;
                }
            else
                break;
        case LEFT:
            if (carte[pos->x-1][pos->y] == EMPTY)
            {
                pos->x--;
                break;
            }
            else if ((carte[pos->x-1][pos->y] == BALL || carte[pos->x-1][pos->y] == NAMEK_RED) && (carte[pos->x-2][pos->y] == NAMEK_GREEN || carte[pos->x-2][pos->y] == EMPTY))

                {
                    deplacerball(&carte[pos->x-1][pos->y], &carte[pos->x-2][pos->y]);
                    pos->x--;
                    break;
                }
            else
                break;
    }
}
/*void deplacerball(int *premierball, int *secondeball)
{
    if (*premierball == ball)
    {
        if (*secondeball == EMPTY)
        {
            *secondeball == ball;
        }
        else // secondeCaise == NAMEK_GREEN
            *secondeball == ball_OK;
    }
    else // premier ball  == ball_OK
        {
            if (*secondeball == EMPTY)
            {
                *premierball == NAMEK_GREEN;
                *secondeball == ball;
            }
            else // secondeCaise == NAMEK_GREEN
            {
                *premierball == ball;
                *secondeball == ball_OK;
            }


        }

}*/

void deplacerball(int *premiereCaisse, int *secondeCaisse)
{
    if (*premiereCaisse == BALL || *premiereCaisse == NAMEK_RED)
    {
        if (*secondeCaisse == NAMEK_GREEN)
            *secondeCaisse = NAMEK_RED;
        else
            *secondeCaisse = BALL;

        if (*premiereCaisse == NAMEK_RED)
            *premiereCaisse = NAMEK_GREEN;
        else
            *premiereCaisse = EMPTY;
    }
}
