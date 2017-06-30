#include "main.h"



int deplacementRoi(int pieceX, int pieceY, int destinationpX, int destinationpY, struct Piece echiquier[8][8])
{
    if ((destinationpX - pieceX)*(destinationpX - pieceX) == 1)
    {
        if (destinationpY == pieceY + 1)                 //En bas a droite ou a gauche.
        {
           if (echiquier[pieceX][pieceY].couleurPiece == 'N')
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
           if (echiquier[pieceX][pieceY].couleurPiece == 'B')
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

        }

        if (destinationpY == pieceY - 1)                 //En haut a droite ou a gauche
        {
           if (echiquier[pieceX][pieceY].couleurPiece == 'N')
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
           if (echiquier[pieceX][pieceY].couleurPiece == 'B')
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

        }

        if (destinationpY == pieceY)                 // a droite ou a gauche
        {
           if (echiquier[pieceX][pieceY].couleurPiece == 'N')
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
           if (echiquier[pieceX][pieceY].couleurPiece == 'B')
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

        }

    }

    else if (((destinationpY - pieceY)*(destinationpY - pieceY) == 1) && (pieceX == destinationpX)) // en haut ou en bas.
    {
           if (echiquier[pieceX][pieceY].couleurPiece == 'N')
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
           if (echiquier[pieceX][pieceY].couleurPiece == 'B')
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

    }

    else
    {
        return 1;
    }
}




