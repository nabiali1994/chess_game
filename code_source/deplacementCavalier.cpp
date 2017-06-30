#include "main.h"

int deplacementCavalier(int pieceX, int pieceY, int destinationpX, int destinationpY, struct Piece echiquier[8][8])
{
    if  (echiquier[pieceX][pieceY].couleurPiece == 'N')
    {
        if ((pieceX - destinationpX)*(pieceX - destinationpX) + (pieceY - destinationpY)*(pieceY - destinationpY) == 5)
        {
            if (echiquier[destinationpX][destinationpY].couleurPiece != 'N')
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }

    }

    if  (echiquier[pieceX][pieceY].couleurPiece == 'B')
    {
        if ((pieceX - destinationpX)*(pieceX - destinationpX) + (pieceY - destinationpY)*(pieceY - destinationpY) == 5)
        {
            if (echiquier[destinationpX][destinationpY].couleurPiece != 'B')
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }

    }
}



