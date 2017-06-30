#include "main.h"

int deplacementTour(int pieceX, int pieceY, int destinationpX, int destinationpY, struct Piece echiquier[8][8])
{
   int tmp2;
   int tmp, possible = 1;



                        if ((pieceY != destinationpY) && (pieceX != destinationpX))
                            {
                                possible = 0;
                            }


                        if (pieceX == destinationpX) // On regarde si elle se d�place en abscisse ou en ordonn�e, ici en ordonn�e.
                            {
                                if (pieceY > destinationpY) // Alors elle va vers le haut
                                    {
                                  tmp2 = pieceY - destinationpY; //Tmp2 = nombre de cases � parcourir.
                                  tmp = 1;
                                    while ((tmp<=tmp2)&&(possible==1))
                                        {
                                            if (echiquier[pieceX][pieceY].couleurPiece == 'B')
                                            {
                                                if((tmp==tmp2) && (echiquier[pieceX][pieceY - tmp].couleurPiece == 'N'))
                                                {
                                                tmp++;
                                                }
                                            }

                                            if (echiquier[pieceX][pieceY].couleurPiece == 'N')
                                            {
                                                if((tmp==tmp2) && (echiquier[pieceX][pieceY - tmp].couleurPiece == 'B'))
                                                {
                                                tmp++;
                                                }
                                            }



                                            if((echiquier[pieceX][pieceY - tmp].typePiece != ' ') && (tmp<=tmp2))
                                                {possible = 0;}
                                                tmp++;
                                        }
                                    }

                                if (pieceY < destinationpY) // Alors elle va vers le bas
                                    {
                                  tmp2 = destinationpY - pieceY; //Tmp2 = nombre de cases � parcourir.
                                  tmp = 1;
                                    while ((tmp<=tmp2)&&(possible==1))
                                        {

                                             if (echiquier[pieceX][pieceY].couleurPiece == 'B')  // Si la case d'arriv�e est un ennemi, on peut le manger.
                                             {
                                                if((tmp==tmp2) && (echiquier[pieceX][pieceY + tmp].couleurPiece == 'N'))
                                                {
                                                tmp++;
                                                }
                                            }

                                             if (echiquier[pieceX][pieceY].couleurPiece == 'N')  // Si la case d'arriv�e est un ennemi, on peut le manger.
                                             {
                                                if((tmp==tmp2) && (echiquier[pieceX][pieceY + tmp].couleurPiece == 'B'))
                                                {
                                                tmp++;
                                                }
                                            }




                                            if((echiquier[pieceX][pieceY + tmp].typePiece != ' ') && (tmp<=tmp2))
                                                {possible = 0;}
                                                tmp++;
                                        }
                                    }

                                if (pieceY == destinationpY) // ELle ne bouge pas du tout, il faut �viter de compter un coup pour rien.
                                    {
                                        possible = 0;
                                    }
                            }


                        if (pieceY == destinationpY) // On regarde si elle se d�place en abscisse ou en ordonn�e.
                            {
                                if (pieceX > destinationpX) // Alors elle va vers la gauche
                                    {
                                  tmp2 = pieceX - destinationpX; //Tmp2 = nombre de cases � parcourir.
                                  tmp = 1;
                                    while ((tmp<=tmp2)&&(possible==1))
                                        {
                                            if (echiquier[pieceX][pieceY].couleurPiece == 'B')
                                            {
                                                if((tmp==tmp2) && (echiquier[pieceX - tmp][pieceY].couleurPiece == 'N'))
                                                {
                                                tmp++;
                                                }
                                            }

                                            if (echiquier[pieceX][pieceY].couleurPiece == 'N')
                                            {
                                                if((tmp==tmp2) && (echiquier[pieceX - tmp][pieceY].couleurPiece == 'B'))
                                                {
                                                tmp++;
                                                }
                                            }


                                            if((echiquier[pieceX - tmp][pieceY].typePiece != ' ') && (tmp<=tmp2))
                                                {possible = 0;}
                                                tmp++;
                                        }
                                    }

                                if (pieceX < destinationpX) // Alors elle va vers la droite.
                                    {
                                  tmp2 = destinationpX - pieceX; //Tmp2 = nombre de cases � parcourir.
                                  tmp = 1;
                                    while ((tmp<=tmp2)&&(possible==1))
                                        {

                                            if (echiquier[pieceX][pieceY].couleurPiece == 'B')
                                            {
                                                if((tmp==tmp2) && (echiquier[pieceX + tmp][pieceY].couleurPiece == 'N'))
                                                {
                                                tmp++;
                                                }
                                            }

                                            if (echiquier[pieceX][pieceY].couleurPiece == 'N')
                                            {
                                                if((tmp==tmp2) && (echiquier[pieceX + tmp][pieceY].couleurPiece == 'B'))
                                                {
                                                tmp++;
                                                }
                                            }


                                            if((echiquier[pieceX + tmp][pieceY].typePiece != ' ') && (tmp<=tmp2))
                                                {possible = 0;}
                                                tmp++;
                                        }
                                    }

                                if (pieceX == destinationpX) // ELle ne bouge pas du tout, il faut �viter de compter un coup pour rien.
                                    {
                                        possible = 0;
                                    }
                            }

                        if (possible == 1)
                        {
                            return 0;
                        }
                        else
                        {
                            return 1;
                        }

}


