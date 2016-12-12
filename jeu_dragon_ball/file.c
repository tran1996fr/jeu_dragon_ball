#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "const.h"
#include "file.h"

int chargerNiveau(int niveau[NB_SQUARES_LENGTH][NB_SQUARES_WIDTH])
{
    FILE* fichier = NULL;
    char ligneFichier[NB_SQUARES_LENGTH * NB_SQUARES_WIDTH + 1] = {0};
    int i = 0, j = 0;

    fichier = fopen("blabla.txt", "r");
    if (fichier == NULL)
        return 0;

    fgets(ligneFichier, NB_SQUARES_LENGTH * NB_SQUARES_WIDTH + 1, fichier);

    for (i = 0 ; i < NB_SQUARES_LENGTH ; i++)
    {
        for (j = 0 ; j < NB_SQUARES_WIDTH ; j++)
        {
            switch (ligneFichier[(i * NB_SQUARES_LENGTH) + j])
            {
                case '0':
                    niveau[j][i] = 0;
                    break;
                case '1':
                    niveau[j][i] = 1;
                    break;
                case '2':
                    niveau[j][i] = 2;
                    break;
                case '3':
                    niveau[j][i] = 3;
                    break;
                case '4':
                    niveau[j][i] = 4;
                    break;
            }
        }
    }

    fclose(fichier);
    return 1;
}
