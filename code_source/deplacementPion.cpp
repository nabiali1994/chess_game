#include "main.h"


int deplacementPion(int pieceX, int pieceY, int destinationpX, int destinationpY,  struct Piece echiquier[8][8])
{
if (echiquier[pieceX][pieceY].couleurPiece == 'N')
{
  if (destinationpX == pieceX)
    {

    if ((pieceY == 1) &&(destinationpY == 3)) //Alors le pion Noir peut avancer de 2 cases
    {
        if ((echiquier[pieceX][pieceY +1].typePiece == ' ') && (echiquier[pieceX][pieceY + 2].typePiece == ' '))
        {
            return 0;
        }

        else
        {
            return 1;
        }

    }
    if (destinationpY == pieceY + 1)
    {
        if (echiquier[destinationpX][destinationpY].typePiece == ' ')
        {
            return 0;
        }
        else
        {
            return 1;
        }

    }
    }
    if ((destinationpX == pieceX +1) && (destinationpY == pieceY + 1)) // L'Attaque du pion vers la droite.
    {
        if  (echiquier[pieceX+1][pieceY+1].couleurPiece == 'B')
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

    if ((destinationpX == pieceX -1) && (destinationpY == pieceY + 1)) // L'Attaque du pion vers la gauche.
    {
        if(echiquier[pieceX-1][pieceY+1].couleurPiece == 'B')
        {
            return 0;
        }
        else
        {
            return 1;
        }
}
}

if (echiquier[pieceX][pieceY].couleurPiece == 'B')
{
  if (destinationpX == pieceX)
    {

    if ((pieceY == 6) &&(destinationpY == 4)) //Alors le pion Noir peut avancer de 2 cases
    {
        if ((echiquier[pieceX][pieceY -1].typePiece == ' ') && (echiquier[pieceX][pieceY - 1].typePiece == ' '))
        {
            return 0;
        }

        else
        {
            return 1;
        }

    }
    if (destinationpY == pieceY - 1)
    {
        if (echiquier[destinationpX][destinationpY].typePiece == ' ')
        {
            return 0;
        }
        else
        {
            return 1;
        }

    }
    }

     if ((destinationpX == pieceX +1) && (destinationpY == pieceY - 1)) // L'Attaque du pion vers la droite.
    {
        if  (echiquier[pieceX+1][pieceY-1].couleurPiece == 'N')
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

    if ((destinationpX == pieceX -1) && (destinationpY == pieceY - 1)) // L'Attaque du pion vers la gauche.
    {
        if(echiquier[pieceX-1][pieceY-1].couleurPiece == 'N')
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


