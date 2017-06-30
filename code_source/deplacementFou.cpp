#include "main.h"


int deplacementFou(int pieceX, int pieceY, int destinationpX, int destinationpY, struct Piece echiquier[8][8])
{
    int tmp, tmp2;
    if (((destinationpX - pieceX) == (destinationpY - pieceY)) && ((destinationpX - pieceX)>0)) //Bonne position si le fou va vers en bas a droite.
    {
        tmp2 = destinationpX - pieceX;
        tmp = 1;

        while (tmp<=tmp2)
        {

            if (echiquier[pieceX][pieceY].couleurPiece == 'B')
            {
                if ((tmp==tmp2) && echiquier[pieceX + tmp][pieceY + tmp].couleurPiece == 'N')
                {
                    return 0;
                }
            }

            if (echiquier[pieceX][pieceY].couleurPiece == 'N')
            {
                if ((tmp==tmp2) && echiquier[pieceX + tmp][pieceY + tmp].couleurPiece == 'B')
                {
                    return 0;
                }
            }



            if (echiquier[pieceX + tmp][pieceY + tmp].typePiece != ' ')
            {
                return 1;
            }
            tmp++;
        }
        return 0;
    }

    if (((destinationpX - pieceX) == (0 -(destinationpY - pieceY))) && ((destinationpX - pieceX)>0)) //Bonne position si le fou va vers en haut a droite.
    {
        tmp2 = destinationpX - pieceX;
        tmp = 1;

        while (tmp<=tmp2)
        {

            if (echiquier[pieceX][pieceY].couleurPiece == 'B')
            {
                if ((tmp==tmp2) && echiquier[pieceX + tmp][pieceY - tmp].couleurPiece == 'N')
                {
                    return 0;
                }
            }

            if (echiquier[pieceX][pieceY].couleurPiece == 'N')
            {
                if ((tmp==tmp2) && echiquier[pieceX + tmp][pieceY - tmp].couleurPiece == 'B')
                {
                    return 0;
                }
            }

            if (echiquier[pieceX + tmp][pieceY - tmp].typePiece != ' ')
            {
                return 1;
            }
            tmp++;
        }
        return 0;
    }

    if (((destinationpX - pieceX) == (destinationpY - pieceY)) && ((destinationpX - pieceX)<0)) //Bonne position si le fou va vers en haut a gauche.
    {
        tmp2 = pieceX - destinationpX ;
        tmp = 1;

        while (tmp<=tmp2)
        {

            if (echiquier[pieceX][pieceY].couleurPiece == 'B')
            {
                if ((tmp==tmp2) && echiquier[pieceX - tmp][pieceY - tmp].couleurPiece == 'N')
                {
                    return 0;
                }
            }

            if (echiquier[pieceX][pieceY].couleurPiece == 'N')
            {
                if ((tmp==tmp2) && echiquier[pieceX - tmp][pieceY - tmp].couleurPiece == 'B')
                {
                    return 0;
                }
            }

            if (echiquier[pieceX - tmp][pieceY - tmp].typePiece != ' ')
            {
                return 1;
            }
            tmp++;
        }
        return 0;
    }

    if (((destinationpX - pieceX) == (0 -(destinationpY - pieceY))) && ((destinationpX - pieceX)<0)) //Bonne position si le fou va vers en bas a gauche.
    {
        tmp2 = pieceX - destinationpX ;
        tmp = 1;

        while (tmp<=tmp2)
        {

            if (echiquier[pieceX][pieceY].couleurPiece == 'B')
            {
                if ((tmp==tmp2) && echiquier[pieceX - tmp][pieceY + tmp].couleurPiece == 'N')
                {
                    return 0;
                }
            }

            if (echiquier[pieceX][pieceY].couleurPiece == 'N')
            {
                if ((tmp==tmp2) && echiquier[pieceX - tmp][pieceY + tmp].couleurPiece == 'B')
                {
                    return 0;
                }
            }

            if (echiquier[pieceX - tmp][pieceY + tmp].typePiece != ' ')
            {
                return 1;
            }
            tmp++;
        }
        return 0;
    }


    }

