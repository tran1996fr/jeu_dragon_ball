#ifndef PLAY_H_INCLUDED
#define PLAY_H_INCLUDED

void play(SDL_Surface* ecran);
void deplacerPlayer(int carte[NB_SQUARES_LENGTH][NB_SQUARES_WIDTH], SDL_Rect *pos, int direction);
void deplacerball(int *premiereCaisse, int *secondeCaisse);

#endif // PLAY_H_INCLUDED
