#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "main.h"
#include <SDL/SDL_image.h>

/* ***** Declaration des variables de SDL ***** */
SDL_Surface *ecran = NULL, *caseBlanche = NULL, *caseNoire = NULL, *caseRouge = NULL, *caseColoree = NULL;
SDL_Surface *message = NULL, *messageIndicateur = NULL,*texte=NULL;
SDL_Surface *piecePionBlanc = NULL, *piecePionNoir = NULL, *pieceRoiNoir = NULL, *pieceRoiBlanc = NULL;
SDL_Surface *pieceTourBlanc = NULL, *pieceTourNoir = NULL, *pieceFouBlanc = NULL, *pieceFouNoir = NULL;
SDL_Surface *pieceCavalierNoir = NULL, *pieceCavalierBlanc = NULL, *pieceDameNoir = NULL, *pieceDameBlanc = NULL;
SDL_Surface *curseur = NULL;
SDL_Surface *pageouv=NULL;

SDL_Rect positionMessage, positionMessageIndicateur,positionecr;
SDL_Rect position0;
SDL_Rect positionCaseBlanche, positionCaseNoire, coordonneeCaseSelectionnee, position, position2, positionCaseColoree;
SDL_Rect positionCurseur;
/* */SDL_Rect positionTB1,positionTB2,positionFB1,positionFB2,positionCB1,positionCB2,positionDB1;
/* */SDL_Rect positionPB1,positionPB2,positionPB3,positionPB4,positionPB5,positionPB6,positionPB7,positionPB0;
/* */SDL_Rect positionTN1,positionTN2,positionFN1,positionFN2,positionCN1,positionCN2,positionDN1;
/* */SDL_Rect positionPN1,positionPN2,positionPN3,positionPN4,positionPN5,positionPN6,positionPN7,positionPN0;


SDL_Event event;

SDL_Color textColor = { 0, 0, 0 };

TTF_Font *font, *font2,*police;
/* *****                                  ***** */


/* ***** Declaration des variables globales ***** */
int continuer=1,i,j,w=0;
long destinationX, destinationY, mouseX, mouseY;   //coordonnées de la souris au moment du clic.
int caseSelectionnee = 0; // 0 = pas de case Selectionnée,  la case est Selectionnée = 1;
int aQuiDeJouer = 0; // 0 = Aux blancs de jouer, 1 = Aux noirs de jouer.
int positionRoiNX,positionRoiNY,positionRoiBX,positionRoiBY;
int roiBlanc = 1, roiNoir = 1;  // si les rois sont encore là.
/*  */
int tourBlanc=0,tourNoir=0;
int fouBlanc=0,fouNoir=0;
int cavBlanc=0,cavNoir=0;
int dameBlanc=0,dameNoir=0;
int pionBlanc=0,pionNoir=0;
/*   */
SDL_Rect positionB,positionN;

/*     changer pion       */
SDL_Surface *message1=NULL;
int x=0;
int choisieN=0,choisieB=0,selection=0;
SDL_Surface *choixDameN=NULL,*choixCavalierN=NULL,*choixTourN=NULL,*choixFouN=NULL;
SDL_Surface *choixDameB=NULL,*choixCavalierB=NULL,*choixTourB=NULL,*choixFouB=NULL;
SDL_Rect positionchoix;


/*                       */


struct Piece echiquier[8][8];
/* *****                                    ***** */


/* ***** Declarations des fonction à utiliser ***** */

void afficheIndicateurPosition() // Affiche quel joueur doit jouer
{
    positionMessageIndicateur.x = 960;
    positionMessageIndicateur.y = 420;
    if (aQuiDeJouer == 0)
    {
        messageIndicateur = TTF_RenderText_Blended(font2, "Aux Blancs de jouer !", textColor);
    }
    else
    {
        messageIndicateur = TTF_RenderText_Blended(font2, "Aux Noirs de jouer !", textColor);
    }

    if(x==0)
    {
        SDL_BlitSurface(messageIndicateur, NULL, ecran, &positionMessageIndicateur);
        SDL_FreeSurface(messageIndicateur);
    }
}


void coloreCase(int abscisse, int ordonnee)  // Colore la case d'abscisse X et d'ordonnée Y
{
    positionCaseColoree.x = abscisse * 96;
    positionCaseColoree.y = ordonnee * 96;
    SDL_BlitSurface(caseColoree, NULL, ecran, &positionCaseColoree);
}



void affichePieces(struct Piece echiquier[8][8])
{
    j = 0;
    for (j=0; j<8; j=j+1)
    {
        for (i=0; i<8; i=i+1)
        {
            if (j==2&&w==0) j=6;
            if (echiquier[i][j].couleurPiece == 'N')
            {

                if (echiquier[i][j].typePiece == 'F')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    SDL_BlitSurface(pieceFouNoir, NULL, ecran, &position2);
                }

                if (echiquier[i][j].typePiece == 'T')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    SDL_BlitSurface(pieceTourNoir, NULL, ecran, &position2);
                }

                if (echiquier[i][j].typePiece =='P')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    if(echiquier[i][7].typePiece=='P')
                    {
                        if(!choisieN)
                        {
                          x=1;
                            positionchoix.x=800+96/2;
                            positionchoix.y=276;
                            message1 = TTF_RenderText_Blended(font, "choisir l evolution de votre pion", textColor);
                            SDL_BlitSurface(message1,NULL,ecran,&positionchoix);
                            positionchoix.x=840;
                            positionchoix.y=330;
                            SDL_BlitSurface(choixDameN,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            SDL_BlitSurface(choixFouN,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            SDL_BlitSurface(choixCavalierN,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            SDL_BlitSurface(choixTourN,NULL,ecran,&positionchoix);
                            positionchoix.x=830+96/2;
                            positionchoix.y+=110;
                            message1 = TTF_RenderText_Blended(font, "D", textColor);
                            SDL_BlitSurface(message1,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            message1 = TTF_RenderText_Blended(font, "F", textColor);
                            SDL_BlitSurface(message1,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            message1 = TTF_RenderText_Blended(font, "C", textColor);
                            SDL_BlitSurface(message1,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            message1 = TTF_RenderText_Blended(font, "T", textColor);
                            SDL_BlitSurface(message1,NULL,ecran,&positionchoix);

                            SDL_Flip(ecran);
                            choisieN=0;
                            choisieB=0;
                        }

                        if(event.key.keysym.sym==SDLK_d)
                        {
                            echiquier[i][7].typePiece='D';

                        }
                        else if(event.key.keysym.sym==SDLK_f)
                        {
                            echiquier[i][7].typePiece='F';

                        }
                        else if(event.key.keysym.sym==SDLK_t)
                        {
                            echiquier[i][7].typePiece='T';

                        }
                        else if(event.key.keysym.sym==SDLK_c)
                        {
                            echiquier[i][7].typePiece='C';

                        }

                    }

                    else
                        {
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &position2);
                        x=0;
                        }


                }

                if (echiquier[i][j].typePiece == 'C')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    SDL_BlitSurface(pieceCavalierNoir, NULL, ecran, &position2);
                }

                if (echiquier[i][j].typePiece == 'D')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    SDL_BlitSurface(pieceDameNoir, NULL, ecran, &position2);
                }

                if (echiquier[i][j].typePiece == 'R')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    SDL_BlitSurface(pieceRoiNoir, NULL, ecran, &position2);
                }
            }

            if (echiquier[i][j].couleurPiece == 'B')
            {

                if (echiquier[i][j].typePiece == 'F')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    SDL_BlitSurface(pieceFouBlanc, NULL, ecran, &position2);
                }

                if (echiquier[i][j].typePiece == 'T')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    SDL_BlitSurface(pieceTourBlanc, NULL, ecran, &position2);
                }

                 if (echiquier[i][j].typePiece == 'P')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    if(echiquier[i][0].typePiece=='P')
                    {
                        if(!choisieB)
                        {
                            x=1;

                            positionchoix.x=800+96/2;
                            positionchoix.y=276;
                            message1 = TTF_RenderText_Blended(font, "choisir l evolution de votre pion", textColor);
                            SDL_BlitSurface(message1,NULL,ecran,&positionchoix);
                            positionchoix.x=840;
                            positionchoix.y=330;
                            SDL_BlitSurface(choixDameB,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            SDL_BlitSurface(choixFouB,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            SDL_BlitSurface(choixCavalierB,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            SDL_BlitSurface(choixTourB,NULL,ecran,&positionchoix);
                            positionchoix.x=830+96/2;
                            positionchoix.y+=110;
                            message1 = TTF_RenderText_Blended(font, "D", textColor);
                            SDL_BlitSurface(message1,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            message1 = TTF_RenderText_Blended(font, "F", textColor);
                            SDL_BlitSurface(message1,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            message1 = TTF_RenderText_Blended(font, "C", textColor);
                            SDL_BlitSurface(message1,NULL,ecran,&positionchoix);
                            positionchoix.x+=96;
                            message1 = TTF_RenderText_Blended(font, "T", textColor);
                            SDL_BlitSurface(message1,NULL,ecran,&positionchoix);

                            SDL_Flip(ecran);
                            choisieB=0;
                            choisieN=0;

                        }


                        if(event.key.keysym.sym==SDLK_d)
                        {
                            echiquier[i][0].typePiece='D';
                        }
                        else if(event.key.keysym.sym==SDLK_f)
                        {
                            echiquier[i][0].typePiece='F';
                        }
                        else if(event.key.keysym.sym==SDLK_t)
                        {
                            echiquier[i][0].typePiece='T';
                        }
                        else if(event.key.keysym.sym==SDLK_c)
                        {
                            echiquier[i][0].typePiece='C';
                        }

                    }

                    else
                    {
                    SDL_BlitSurface(piecePionBlanc, NULL, ecran, &position2);
                    x=0;
                    }

                }

                if (echiquier[i][j].typePiece == 'C')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    SDL_BlitSurface(pieceCavalierBlanc, NULL, ecran, &position2);
                }

                if (echiquier[i][j].typePiece == 'D')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    SDL_BlitSurface(pieceDameBlanc, NULL, ecran, &position2);
                }

                if (echiquier[i][j].typePiece == 'R')
                {
                    position2.x = i*96;
                    position2.y = j*96;
                    SDL_BlitSurface(pieceRoiBlanc, NULL, ecran, &position2);
                }
            }
            if(w==0)
            {
                SDL_Flip(ecran);
                SDL_Delay(100);
            }
        }
    }
    w=1;
}


void coloreCaseSelectionne()
{
    int             mouseX = event.button.x; // On récupere la position du curseur de la souris
    int             mouseY = event.button.y;

    mouseX = mouseX / 96;    //On regarde sur quelle case de l'échiquier il se trouve en abscisse

    if (mouseY>=0)         //On regarde sur quelle case de l'échiquier il se trouve en ordonnée
    {
        mouseY = mouseY / 96;
    }
    else
    {
        mouseY = -1; //Le curseur de la souris est au dessus de l'échiquier.
    }

    /* Si le clic est dans la zone de l'échiquier, caseSelectionnee passe a 1 pour colorer la case Selectionnée.
       voir juste avant le flipecran. */

    if ((mouseX < 8) && (mouseX >= 0) && (mouseY < 8) && (mouseY >= 0)) //si on est sur l'échiquier par rapport aux X et aux Y

    {
        caseSelectionnee = 1;
        coordonneeCaseSelectionnee.x = mouseX * 96;
        coordonneeCaseSelectionnee.y = (mouseY * 96);

    }
    else
    {
        caseSelectionnee = 0;
    }
}





int echecN()  // Renvoi 1 si le roi noir est en échec et 0 s'il ne l'est pas.
{
    int a,b,echecNoir = 0;
    for (b=0; b<8; b++)
    {
        for (a=0; a<8; a++)
        {
            if (echiquier[a][b].couleurPiece == 'B')
            {
                if (echiquier[a][b].typePiece == 'T')
                {
                    if (deplacementTour(a,b,positionRoiNX,positionRoiNY, echiquier) == 0) // La tour peut aller sur le roi
                    {
                        echecNoir = 1;
                    }
                }
                if (echiquier[a][b].typePiece == 'C')
                {
                    if (deplacementCavalier(a,b,positionRoiNX,positionRoiNY, echiquier) == 0) // Le cavalier peut aller sur le roi
                    {
                        echecNoir = 1;
                    }
                }
                if (echiquier[a][b].typePiece == 'D')
                {
                    if (deplacementTour(a,b,positionRoiNX,positionRoiNY, echiquier) == 0) // La dame peut aller sur le roi
                    {
                        echecNoir = 1;
                    }
                    if (deplacementFou(a,b,positionRoiNX,positionRoiNY, echiquier) == 0)
                    {
                        echecNoir = 1;
                    }
                }
                if (echiquier[a][b].typePiece == 'P')
                {
                    if (deplacementPion(a,b,positionRoiNX,positionRoiNY, echiquier) == 0) // La tour peut aller sur le roi
                    {
                        echecNoir = 1;
                    }
                }
                if (echiquier[a][b].typePiece == 'F')
                {
                    if (deplacementFou(a,b,positionRoiNX,positionRoiNY, echiquier) == 0) // Le fou peut aller sur le roi
                    {
                        echecNoir = 1;
                    }
                }

            }
        }
    }

    if (echecNoir == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

int echecB()  // Renvoi 0 si le roi blanc est en échec et 1 s'il ne l'est pas.
{
    int a,b,echecBlanc = 0;
    for (b=0; b<8; b++)
    {
        for (a=0; a<8; a++)
        {
            if (echiquier[a][b].couleurPiece == 'N')
            {
                if (echiquier[a][b].typePiece == 'T')
                {
                    if (deplacementTour(a,b,positionRoiBX,positionRoiBY, echiquier) == 0) // La tour peut aller sur le roi
                    {
                        echecBlanc = 1;
                    }
                }
                if (echiquier[a][b].typePiece == 'C')
                {
                    if (deplacementCavalier(a,b,positionRoiBX,positionRoiBY, echiquier) == 0) // Le cavalier peut aller sur le roi
                    {
                        echecBlanc = 1;
                    }
                }
                if (echiquier[a][b].typePiece == 'D')
                {
                    if (deplacementTour(a,b,positionRoiBX,positionRoiBY, echiquier) == 0) // La dame peut aller sur le roi
                    {
                        echecBlanc = 1;
                    }
                    if (deplacementFou(a,b,positionRoiBX,positionRoiBY, echiquier) == 0)
                    {
                        echecBlanc = 1;
                    }
                }
                if (echiquier[a][b].typePiece == 'P')
                {
                    if (deplacementPion(a,b,positionRoiBX,positionRoiBY, echiquier) == 0) // La tour peut aller sur le roi
                    {
                        echecBlanc = 1;
                    }
                }
                if (echiquier[a][b].typePiece == 'F')
                {
                    if (deplacementFou(a,b,positionRoiBX,positionRoiBY, echiquier) == 0) // Le fou peut aller sur le roi
                    {
                        echecBlanc = 1;
                    }
                }

            }
        }
    }

    if (echecBlanc == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}




void deplacement()
{
    destinationX = event.button.x; // On récupere la position du curseur de la souris
    destinationY = event.button.y;

    destinationX = destinationX / 96;    //On regarde sur quelle case de l'échiquier il se trouve en abscisse

    if (destinationY>=0)         //On regarde sur quelle case de l'échiquier il se trouve en ordonnée
    {
        destinationY = destinationY / 96;
    }
    else
    {
        destinationY = -1;
    }

    if (caseSelectionnee == 1) // Si le joueur a bien sélectionné une case avant de clic-droit
    {
        if ((destinationX < 8) && (destinationX >= 0) && (destinationY < 8) && (destinationY >= 0)) //si on est sur l'échiquier par rapport aux X et aux Y
        {
            int x = coordonneeCaseSelectionnee.x / 96;
            int y = coordonneeCaseSelectionnee.y / 96;

            if (((echiquier[x][y].couleurPiece == 'N') && (aQuiDeJouer == 1)) || ((echiquier[x][y].couleurPiece == 'B') && (aQuiDeJouer == 0)))
            {
                if (echiquier[x][y].typePiece == 'T')
                {
                    if (deplacementTour(x,y,destinationX,destinationY, echiquier) == 0) // Si le déplacement est possible.
                    {

                        if (echiquier[x][y].couleurPiece == 'N')
                        {
                            /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourBlanc == 1) {positionTB2.x=positionB.x;positionTB2.y=positionB.y;positionB.x+=96;tourBlanc=2;}
                                if(tourBlanc == 0) {positionTB1.x=positionB.x;positionTB1.y=positionB.y;positionB.x+=96;tourBlanc=1;}
                            }
                             /* */
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouBlanc == 1) {positionFB2.x=positionB.x;positionFB2.y=positionB.y;positionB.x+=96;fouBlanc=2;}
                                if(fouBlanc == 0) {positionFB1.x=positionB.x;positionFB1.y=positionB.y;positionB.x+=96;fouBlanc=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavBlanc == 1) {positionCB2.x=positionB.x;positionCB2.y=positionB.y;positionB.x+=96;cavBlanc=2;}
                                if(cavBlanc == 0) {positionCB1.x=positionB.x;positionCB1.y=positionB.y;positionB.x+=96;cavBlanc=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameBlanc == 0) {positionDB1.x=positionB.x;positionDB1.y=positionB.y;positionB.x+=96;dameBlanc=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionBlanc == 7) {positionPB7.x=positionB.x;positionPB7.y=positionB.y;positionB.x+=96;pionBlanc=8;}
                                if(pionBlanc == 6) {positionPB6.x=positionB.x;positionPB6.y=positionB.y;positionB.x+=96;pionBlanc=7;}
                                if(pionBlanc == 5) {positionPB5.x=positionB.x;positionPB5.y=positionB.y;positionB.x+=96;pionBlanc=6;}
                                if(pionBlanc == 4) {positionPB4.x=positionB.x;positionPB4.y=positionB.y;positionB.x+=96;pionBlanc=5;}
                                if(pionBlanc == 3) {positionPB3.x=positionB.x;positionPB3.y=positionB.y;positionB.x+=96;pionBlanc=4;}
                                if(pionBlanc == 2) {positionPB2.x=positionB.x;positionPB2.y=positionB.y;positionB.x+=96;pionBlanc=3;}
                                if(pionBlanc == 1) {positionPB1.x=positionB.x;positionPB1.y=positionB.y;positionB.x+=96;pionBlanc=2;}
                                if(pionBlanc == 0) {positionPB0.x=positionB.x;positionPB0.y=positionB.y;positionB.x+=96;pionBlanc=1;}
                            }
                             /* */

                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiBlanc = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'N';
                        }
                        else
                        {
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourNoir == 1) {positionTN2.x=positionN.x;positionTN2.y=positionN.y;positionN.x+=96;tourNoir=2;}
                                if(tourNoir == 0) {positionTN1.x=positionN.x;positionTN1.y=positionN.y;positionN.x+=96;tourNoir=1;}
                            }
                             /* */
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouNoir == 1) {positionFN2.x=positionN.x;positionFN2.y=positionN.y;positionN.x+=96;fouNoir=2;}
                                if(fouNoir == 0) {positionFN1.x=positionN.x;positionFN1.y=positionN.y;positionN.x+=96;fouNoir=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavNoir == 1) {positionCN2.x=positionN.x;positionCN2.y=positionN.y;positionN.x+=96;cavNoir=2;}
                                if(cavNoir == 0) {positionCN1.x=positionN.x;positionCN1.y=positionN.y;positionN.x+=96;cavNoir=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameNoir == 0) {positionDN1.x=positionN.x;positionDN1.y=positionN.y;positionN.x+=96;dameNoir=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionNoir == 7) {positionPN7.x=positionN.x;positionPN7.y=positionN.y;positionN.x+=96;pionNoir=8;}
                                if(pionNoir == 6) {positionPN6.x=positionN.x;positionPN6.y=positionN.y;positionN.x+=96;pionNoir=7;}
                                if(pionNoir == 5) {positionPN5.x=positionN.x;positionPN5.y=positionN.y;positionN.x+=96;pionNoir=6;}
                                if(pionNoir == 4) {positionPN4.x=positionN.x;positionPN4.y=positionN.y;positionN.x+=96;pionNoir=5;}
                                if(pionNoir == 3) {positionPN3.x=positionN.x;positionPN3.y=positionN.y;positionN.x+=96;pionNoir=4;}
                                if(pionNoir == 2) {positionPN2.x=positionN.x;positionPN2.y=positionN.y;positionN.x+=96;pionNoir=3;}
                                if(pionNoir == 1) {positionPN1.x=positionN.x;positionPN1.y=positionN.y;positionN.x+=96;pionNoir=2;}
                                if(pionNoir == 0) {positionPN0.x=positionN.x;positionPN0.y=positionN.y;positionN.x+=96;pionNoir=1;}
                            }
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiNoir = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'B';
                        }

                        echiquier[destinationX][destinationY].typePiece = 'T';
                        echiquier[x][y].couleurPiece = ' ';
                        echiquier[x][y].typePiece = ' ';
                        if (aQuiDeJouer == 0)  // A l'autre de jouer maintenant.
                        {
                            aQuiDeJouer = 1;
                        }
                        else
                        {
                            aQuiDeJouer = 0;
                        }
                    }
                }

                if (echiquier[x][y].typePiece == 'P')
                {
                    if (deplacementPion(x,y,destinationX,destinationY, echiquier) == 0) // Si le déplacement est possible.
                    {
                        if (echiquier[x][y].couleurPiece == 'N')
                        {
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourBlanc == 1) {positionTB2.x=positionB.x;positionTB2.y=positionB.y;positionB.x+=96;tourBlanc=2;}
                                if(tourBlanc == 0) {positionTB1.x=positionB.x;positionTB1.y=positionB.y;positionB.x+=96;tourBlanc=1;}
                            }
                            /*  */
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouBlanc == 1) {positionFB2.x=positionB.x;positionFB2.y=positionB.y;positionB.x+=96;fouBlanc=2;}
                                if(fouBlanc == 0) {positionFB1.x=positionB.x;positionFB1.y=positionB.y;positionB.x+=96;fouBlanc=1;}
                            }
                            /*  */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavBlanc == 1) {positionCB2.x=positionB.x;positionCB2.y=positionB.y;positionB.x+=96;cavBlanc=2;}
                                if(cavBlanc == 0) {positionCB1.x=positionB.x;positionCB1.y=positionB.y;positionB.x+=96;cavBlanc=1;}
                            }
                             /* */
                                 /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameBlanc == 0) {positionDB1.x=positionB.x;positionDB1.y=positionB.y;positionB.x+=96;dameBlanc=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionBlanc == 7) {positionPB7.x=positionB.x;positionPB7.y=positionB.y;positionB.x+=96;pionBlanc=8;}
                                if(pionBlanc == 6) {positionPB6.x=positionB.x;positionPB6.y=positionB.y;positionB.x+=96;pionBlanc=7;}
                                if(pionBlanc == 5) {positionPB5.x=positionB.x;positionPB5.y=positionB.y;positionB.x+=96;pionBlanc=6;}
                                if(pionBlanc == 4) {positionPB4.x=positionB.x;positionPB4.y=positionB.y;positionB.x+=96;pionBlanc=5;}
                                if(pionBlanc == 3) {positionPB3.x=positionB.x;positionPB3.y=positionB.y;positionB.x+=96;pionBlanc=4;}
                                if(pionBlanc == 2) {positionPB2.x=positionB.x;positionPB2.y=positionB.y;positionB.x+=96;pionBlanc=3;}
                                if(pionBlanc == 1) {positionPB1.x=positionB.x;positionPB1.y=positionB.y;positionB.x+=96;pionBlanc=2;}
                                if(pionBlanc == 0) {positionPB0.x=positionB.x;positionPB0.y=positionB.y;positionB.x+=96;pionBlanc=1;}
                            }
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiBlanc = 0;
                            }

                            echiquier[destinationX][destinationY].couleurPiece = 'N';
                        }
                        else
                        {
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourNoir == 1) {positionTN2.x=positionN.x;positionTN2.y=positionN.y;positionN.x+=96;tourNoir=2;}
                                if(tourNoir == 0) {positionTN1.x=positionN.x;positionTN1.y=positionN.y;positionN.x+=96;tourNoir=1;}
                            }
                            /*  */
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouNoir == 1) {positionFN2.x=positionN.x;positionFN2.y=positionN.y;positionN.x+=96;fouNoir=2;}
                                if(fouNoir == 0) {positionFN1.x=positionN.x;positionFN1.y=positionN.y;positionN.x+=96;fouNoir=1;}
                            }
                            /*  */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavNoir == 1) {positionCN2.x=positionN.x;positionCN2.y=positionN.y;positionN.x+=96;cavNoir=2;}
                                if(cavNoir == 0) {positionCN1.x=positionN.x;positionCN1.y=positionN.y;positionN.x+=96;cavNoir=1;}
                            }
                             /* */
                                 /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameNoir == 0) {positionDN1.x=positionN.x;positionDN1.y=positionN.y;positionN.x+=96;dameNoir=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionNoir == 7) {positionPN7.x=positionN.x;positionPN7.y=positionN.y;positionN.x+=96;pionNoir=8;}
                                if(pionNoir == 6) {positionPN6.x=positionN.x;positionPN6.y=positionN.y;positionN.x+=96;pionNoir=7;}
                                if(pionNoir == 5) {positionPN5.x=positionN.x;positionPN5.y=positionN.y;positionN.x+=96;pionNoir=6;}
                                if(pionNoir == 4) {positionPN4.x=positionN.x;positionPN4.y=positionN.y;positionN.x+=96;pionNoir=5;}
                                if(pionNoir == 3) {positionPN3.x=positionN.x;positionPN3.y=positionN.y;positionN.x+=96;pionNoir=4;}
                                if(pionNoir == 2) {positionPN2.x=positionN.x;positionPN2.y=positionN.y;positionN.x+=96;pionNoir=3;}
                                if(pionNoir == 1) {positionPN1.x=positionN.x;positionPN1.y=positionN.y;positionN.x+=96;pionNoir=2;}
                                if(pionNoir == 0) {positionPN0.x=positionN.x;positionPN0.y=positionN.y;positionN.x+=96;pionNoir=1;}
                            }
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiNoir = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'B';
                        }
                        echiquier[destinationX][destinationY].typePiece = 'P';
                        echiquier[x][y].couleurPiece = ' ';
                        echiquier[x][y].typePiece = ' ';
                        if (aQuiDeJouer == 0)  // A l'autre de jouer maintenant.
                        {
                            aQuiDeJouer = 1;
                        }
                        else
                        {
                            aQuiDeJouer = 0;
                        }
                    }
                }

                if (echiquier[x][y].typePiece == 'C')
                {
                    if (deplacementCavalier(x,y,destinationX,destinationY, echiquier) == 0) // Si le déplacement est possible.
                    {

                        if (echiquier[x][y].couleurPiece == 'N')
                        {
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourBlanc == 1) {positionTB2.x=positionB.x;positionTB2.y=positionB.y;positionB.x+=96;tourBlanc=2;}
                                if(tourBlanc == 0) {positionTB1.x=positionB.x;positionTB1.y=positionB.y;positionB.x+=96;tourBlanc=1;}
                            }
                            /*  */
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouBlanc == 1) {positionFB2.x=positionB.x;positionFB2.y=positionB.y;positionB.x+=96;fouBlanc=2;}
                                if(fouBlanc == 0) {positionFB1.x=positionB.x;positionFB1.y=positionB.y;positionB.x+=96;fouBlanc=1;}
                            }
                            /*  */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavBlanc == 1) {positionCB2.x=positionB.x;positionCB2.y=positionB.y;positionB.x+=96;cavBlanc=2;}
                                if(cavBlanc == 0) {positionCB1.x=positionB.x;positionCB1.y=positionB.y;positionB.x+=96;cavBlanc=1;}
                            }
                             /* */
                                 /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameBlanc == 0) {positionDB1.x=positionB.x;positionDB1.y=positionB.y;positionB.x+=96;dameBlanc=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionBlanc == 7) {positionPB7.x=positionB.x;positionPB7.y=positionB.y;positionB.x+=96;pionBlanc=8;}
                                if(pionBlanc == 6) {positionPB6.x=positionB.x;positionPB6.y=positionB.y;positionB.x+=96;pionBlanc=7;}
                                if(pionBlanc == 5) {positionPB5.x=positionB.x;positionPB5.y=positionB.y;positionB.x+=96;pionBlanc=6;}
                                if(pionBlanc == 4) {positionPB4.x=positionB.x;positionPB4.y=positionB.y;positionB.x+=96;pionBlanc=5;}
                                if(pionBlanc == 3) {positionPB3.x=positionB.x;positionPB3.y=positionB.y;positionB.x+=96;pionBlanc=4;}
                                if(pionBlanc == 2) {positionPB2.x=positionB.x;positionPB2.y=positionB.y;positionB.x+=96;pionBlanc=3;}
                                if(pionBlanc == 1) {positionPB1.x=positionB.x;positionPB1.y=positionB.y;positionB.x+=96;pionBlanc=2;}
                                if(pionBlanc == 0) {positionPB0.x=positionB.x;positionPB0.y=positionB.y;positionB.x+=96;pionBlanc=1;}
                            }
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiBlanc = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'N';
                        }
                        else
                        {
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourNoir == 1) {positionTN2.x=positionN.x;positionTN2.y=positionN.y;positionN.x+=96;tourNoir=2;}
                                if(tourNoir == 0) {positionTN1.x=positionN.x;positionTN1.y=positionN.y;positionN.x+=96;tourNoir=1;}
                            }
                            /*  */
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouNoir == 1) {positionFN2.x=positionN.x;positionFN2.y=positionN.y;positionN.x+=96;fouNoir=2;}
                                if(fouNoir == 0) {positionFN1.x=positionN.x;positionFN1.y=positionN.y;positionN.x+=96;fouNoir=1;}
                            }
                            /*  */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavNoir == 1) {positionCN2.x=positionN.x;positionCN2.y=positionN.y;positionN.x+=96;cavNoir=2;}
                                if(cavNoir == 0) {positionCN1.x=positionN.x;positionCN1.y=positionN.y;positionN.x+=96;cavNoir=1;}
                            }
                             /* */
                                 /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameNoir == 0) {positionDN1.x=positionN.x;positionDN1.y=positionN.y;positionN.x+=96;dameNoir=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionNoir == 7) {positionPN7.x=positionN.x;positionPN7.y=positionN.y;positionN.x+=96;pionNoir=8;}
                                if(pionNoir == 6) {positionPN6.x=positionN.x;positionPN6.y=positionN.y;positionN.x+=96;pionNoir=7;}
                                if(pionNoir == 5) {positionPN5.x=positionN.x;positionPN5.y=positionN.y;positionN.x+=96;pionNoir=6;}
                                if(pionNoir == 4) {positionPN4.x=positionN.x;positionPN4.y=positionN.y;positionN.x+=96;pionNoir=5;}
                                if(pionNoir == 3) {positionPN3.x=positionN.x;positionPN3.y=positionN.y;positionN.x+=96;pionNoir=4;}
                                if(pionNoir == 2) {positionPN2.x=positionN.x;positionPN2.y=positionN.y;positionN.x+=96;pionNoir=3;}
                                if(pionNoir == 1) {positionPN1.x=positionN.x;positionPN1.y=positionN.y;positionN.x+=96;pionNoir=2;}
                                if(pionNoir == 0) {positionPN0.x=positionN.x;positionPN0.y=positionN.y;positionN.x+=96;pionNoir=1;}
                            }
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiNoir = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'B';
                        }
                        echiquier[destinationX][destinationY].typePiece = 'C';
                        echiquier[x][y].couleurPiece = ' ';
                        echiquier[x][y].typePiece = ' ';
                        if (aQuiDeJouer == 0)  // A l'autre de jouer maintenant.
                        {
                            aQuiDeJouer = 1;
                        }
                        else
                        {
                            aQuiDeJouer = 0;
                        }
                    }

                }

                if (echiquier[x][y].typePiece == 'F')
                {
                    if (deplacementFou(x,y,destinationX,destinationY, echiquier) == 0&&(x!=destinationX&&y!=destinationY)) // Si le déplacement est possible.
                    {

                        if (echiquier[x][y].couleurPiece == 'N')
                        {
                             /*  */
                             if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourBlanc == 1) {positionTB2.x=positionB.x;positionTB2.y=positionB.y;positionB.x+=96;tourBlanc=2;}
                                if(tourBlanc == 0) {positionTB1.x=positionB.x;positionTB1.y=positionB.y;positionB.x+=96;tourBlanc=1;}
                            }
                            /*   */
                            /*  */
                             if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouBlanc == 1) {positionFB2.x=positionB.x;positionFB2.y=positionB.y;positionB.x+=96;fouBlanc=2;}
                                if(fouBlanc == 0) {positionFB1.x=positionB.x;positionFB1.y=positionB.y;positionB.x+=96;fouBlanc=1;}
                            }
                            /*   */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavBlanc == 1) {positionCB2.x=positionB.x;positionCB2.y=positionB.y;positionB.x+=96;cavBlanc=2;}
                                if(cavBlanc == 0) {positionCB1.x=positionB.x;positionCB1.y=positionB.y;positionB.x+=96;cavBlanc=1;}
                            }
                             /* */
                                 /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameBlanc == 0) {positionDB1.x=positionB.x;positionDB1.y=positionB.y;positionB.x+=96;dameBlanc=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionBlanc == 7) {positionPB7.x=positionB.x;positionPB7.y=positionB.y;positionB.x+=96;pionBlanc=8;}
                                if(pionBlanc == 6) {positionPB6.x=positionB.x;positionPB6.y=positionB.y;positionB.x+=96;pionBlanc=7;}
                                if(pionBlanc == 5) {positionPB5.x=positionB.x;positionPB5.y=positionB.y;positionB.x+=96;pionBlanc=6;}
                                if(pionBlanc == 4) {positionPB4.x=positionB.x;positionPB4.y=positionB.y;positionB.x+=96;pionBlanc=5;}
                                if(pionBlanc == 3) {positionPB3.x=positionB.x;positionPB3.y=positionB.y;positionB.x+=96;pionBlanc=4;}
                                if(pionBlanc == 2) {positionPB2.x=positionB.x;positionPB2.y=positionB.y;positionB.x+=96;pionBlanc=3;}
                                if(pionBlanc == 1) {positionPB1.x=positionB.x;positionPB1.y=positionB.y;positionB.x+=96;pionBlanc=2;}
                                if(pionBlanc == 0) {positionPB0.x=positionB.x;positionPB0.y=positionB.y;positionB.x+=96;pionBlanc=1;}
                            }
                             /* */
                            echiquier[destinationX][destinationY].couleurPiece = 'N';

                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiBlanc = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'N';
                        }
                        else
                        {
                            /*  */
                             if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourNoir == 1) {positionTN2.x=positionN.x;positionTN2.y=positionN.y;positionN.x+=96;tourNoir=2;}
                                if(tourNoir == 0) {positionTN1.x=positionN.x;positionTN1.y=positionN.y;positionN.x+=96;tourNoir=1;}
                            }
                            /*   */
                            /*  */
                             if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouNoir == 1) {positionFN2.x=positionN.x;positionFN2.y=positionN.y;positionN.x+=96;fouNoir=2;}
                                if(fouNoir == 0) {positionFN1.x=positionN.x;positionFN1.y=positionN.y;positionN.x+=96;fouNoir=1;}
                            }
                            /*   */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavNoir == 1) {positionCN2.x=positionN.x;positionCN2.y=positionN.y;positionN.x+=96;cavNoir=2;}
                                if(cavNoir == 0) {positionCN1.x=positionN.x;positionCN1.y=positionN.y;positionN.x+=96;cavNoir=1;}
                            }
                             /* */
                                 /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameNoir == 0) {positionDN1.x=positionN.x;positionDN1.y=positionN.y;positionN.x+=96;dameNoir=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionNoir == 7) {positionPN7.x=positionN.x;positionPN7.y=positionN.y;positionN.x+=96;pionNoir=8;}
                                if(pionNoir == 6) {positionPN6.x=positionN.x;positionPN6.y=positionN.y;positionN.x+=96;pionNoir=7;}
                                if(pionNoir == 5) {positionPN5.x=positionN.x;positionPN5.y=positionN.y;positionN.x+=96;pionNoir=6;}
                                if(pionNoir == 4) {positionPN4.x=positionN.x;positionPN4.y=positionN.y;positionN.x+=96;pionNoir=5;}
                                if(pionNoir == 3) {positionPN3.x=positionN.x;positionPN3.y=positionN.y;positionN.x+=96;pionNoir=4;}
                                if(pionNoir == 2) {positionPN2.x=positionN.x;positionPN2.y=positionN.y;positionN.x+=96;pionNoir=3;}
                                if(pionNoir == 1) {positionPN1.x=positionN.x;positionPN1.y=positionN.y;positionN.x+=96;pionNoir=2;}
                                if(pionNoir == 0) {positionPN0.x=positionN.x;positionPN0.y=positionN.y;positionN.x+=96;pionNoir=1;}
                            }
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiNoir = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'B';
                        }
                        echiquier[destinationX][destinationY].typePiece = 'F';
                        echiquier[x][y].couleurPiece = ' ';
                        echiquier[x][y].typePiece = ' ';
                        if (aQuiDeJouer == 0)  // A l'autre de jouer maintenant.
                        {
                            aQuiDeJouer = 1;
                        }
                        else
                        {
                            aQuiDeJouer = 0;
                        }
                    }
                }

                if (echiquier[x][y].typePiece == 'D')
                {
                    if ((deplacementFou(x,y,destinationX,destinationY, echiquier) == 0&&(x!=destinationX&&y!=destinationY)) || (deplacementTour(x,y,destinationX,destinationY, echiquier) == 0))// Si le déplacement est possible.
                    {

                        if (echiquier[x][y].couleurPiece == 'N')
                        {
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourBlanc == 1) {positionTB2.x=positionB.x;positionTB2.y=positionB.y;positionB.x+=96;tourBlanc=2;}
                                if(tourBlanc == 0) {positionTB1.x=positionB.x;positionTB1.y=positionB.y;positionB.x+=96;tourBlanc=1;}
                            }
                            /*  */
                             /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouBlanc == 1) {positionFB2.x=positionB.x;positionFB2.y=positionB.y;positionB.x+=96;fouBlanc=2;}
                                if(fouBlanc == 0) {positionFB1.x=positionB.x;positionFB1.y=positionB.y;positionB.x+=96;fouBlanc=1;}
                            }
                            /*  */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavBlanc == 1) {positionCB2.x=positionB.x;positionCB2.y=positionB.y;positionB.x+=96;cavBlanc=2;}
                                if(cavBlanc == 0) {positionCB1.x=positionB.x;positionCB1.y=positionB.y;positionB.x+=96;cavBlanc=1;}
                            }
                             /* */
                                 /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameBlanc == 0) {positionDB1.x=positionB.x;positionDB1.y=positionB.y;positionB.x+=96;dameBlanc=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionBlanc == 7) {positionPB7.x=positionB.x;positionPB7.y=positionB.y;positionB.x+=96;pionBlanc=8;}
                                if(pionBlanc == 6) {positionPB6.x=positionB.x;positionPB6.y=positionB.y;positionB.x+=96;pionBlanc=7;}
                                if(pionBlanc == 5) {positionPB5.x=positionB.x;positionPB5.y=positionB.y;positionB.x+=96;pionBlanc=6;}
                                if(pionBlanc == 4) {positionPB4.x=positionB.x;positionPB4.y=positionB.y;positionB.x+=96;pionBlanc=5;}
                                if(pionBlanc == 3) {positionPB3.x=positionB.x;positionPB3.y=positionB.y;positionB.x+=96;pionBlanc=4;}
                                if(pionBlanc == 2) {positionPB2.x=positionB.x;positionPB2.y=positionB.y;positionB.x+=96;pionBlanc=3;}
                                if(pionBlanc == 1) {positionPB1.x=positionB.x;positionPB1.y=positionB.y;positionB.x+=96;pionBlanc=2;}
                                if(pionBlanc == 0) {positionPB0.x=positionB.x;positionPB0.y=positionB.y;positionB.x+=96;pionBlanc=1;}
                            }
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiBlanc = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'N';
                        }
                        else
                        {
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourNoir == 1) {positionTN2.x=positionN.x;positionTN2.y=positionN.y;positionN.x+=96;tourNoir=2;}
                                if(tourNoir == 0) {positionTN1.x=positionN.x;positionTN1.y=positionN.y;positionN.x+=96;tourNoir=1;}
                            }
                            /*  */
                             /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouNoir == 1) {positionFN2.x=positionN.x;positionFN2.y=positionN.y;positionN.x+=96;fouNoir=2;}
                                if(fouNoir == 0) {positionFN1.x=positionN.x;positionFN1.y=positionN.y;positionN.x+=96;fouNoir=1;}
                            }
                            /*  */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavNoir == 1) {positionCN2.x=positionN.x;positionCN2.y=positionN.y;positionN.x+=96;cavNoir=2;}
                                if(cavNoir == 0) {positionCN1.x=positionN.x;positionCN1.y=positionN.y;positionN.x+=96;cavNoir=1;}
                            }
                             /* */
                                 /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameNoir == 0) {positionDN1.x=positionN.x;positionDN1.y=positionN.y;positionN.x+=96;dameNoir=1;}
                            }
                             /* */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionNoir == 7) {positionPN7.x=positionN.x;positionPN7.y=positionN.y;positionN.x+=96;pionNoir=8;}
                                if(pionNoir == 6) {positionPN6.x=positionN.x;positionPN6.y=positionN.y;positionN.x+=96;pionNoir=7;}
                                if(pionNoir == 5) {positionPN5.x=positionN.x;positionPN5.y=positionN.y;positionN.x+=96;pionNoir=6;}
                                if(pionNoir == 4) {positionPN4.x=positionN.x;positionPN4.y=positionN.y;positionN.x+=96;pionNoir=5;}
                                if(pionNoir == 3) {positionPN3.x=positionN.x;positionPN3.y=positionN.y;positionN.x+=96;pionNoir=4;}
                                if(pionNoir == 2) {positionPN2.x=positionN.x;positionPN2.y=positionN.y;positionN.x+=96;pionNoir=3;}
                                if(pionNoir == 1) {positionPN1.x=positionN.x;positionPN1.y=positionN.y;positionN.x+=96;pionNoir=2;}
                                if(pionNoir == 0) {positionPN0.x=positionN.x;positionPN0.y=positionN.y;positionN.x+=96;pionNoir=1;}
                            }
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiNoir = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'B';
                        }
                        echiquier[destinationX][destinationY].typePiece = 'D';
                        echiquier[x][y].couleurPiece = ' ';
                        echiquier[x][y].typePiece = ' ';
                        if (aQuiDeJouer == 0)  // A l'autre de jouer maintenant.
                        {
                            aQuiDeJouer = 1;
                        }
                        else
                        {
                            aQuiDeJouer = 0;
                        }
                    }
                }

                if (echiquier[x][y].typePiece == 'R')
                {
                    if (deplacementRoi(x,y,destinationX,destinationY, echiquier) == 0)
                    {

                        if (echiquier[x][y].couleurPiece == 'N')
                        {
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourBlanc == 1) {positionTB2.x=positionB.x;positionTB2.y=positionB.y;positionB.x+=96;tourBlanc=2;}
                                if(tourBlanc == 0) {positionTB1.x=positionB.x;positionTB1.y=positionB.y;positionB.x+=96;tourBlanc=1;}
                            }
                            /*  */
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouBlanc == 1) {positionFB2.x=positionB.x;positionFB2.y=positionB.y;positionB.x+=96;fouBlanc=2;}
                                if(fouBlanc == 0) {positionFB1.x=positionB.x;positionFB1.y=positionB.y;positionB.x+=96;fouBlanc=1;}
                            }
                            /*  */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavBlanc == 1) {positionCB2.x=positionB.x;positionCB2.y=positionB.y;positionB.x+=96;cavBlanc=2;}
                                if(cavBlanc == 0) {positionCB1.x=positionB.x;positionCB1.y=positionB.y;positionB.x+=96;cavBlanc=1;}
                            }
                             /* */
                             /*  */
                             if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameBlanc == 0) {positionDB1.x=positionB.x;positionDB1.y=positionB.y;positionB.x+=96;dameBlanc=1;}
                            }
                              /* */
                              /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionBlanc == 7) {positionPB7.x=positionB.x;positionPB7.y=positionB.y;positionB.x+=96;pionBlanc=8;}
                                if(pionBlanc == 6) {positionPB6.x=positionB.x;positionPB6.y=positionB.y;positionB.x+=96;pionBlanc=7;}
                                if(pionBlanc == 5) {positionPB5.x=positionB.x;positionPB5.y=positionB.y;positionB.x+=96;pionBlanc=6;}
                                if(pionBlanc == 4) {positionPB4.x=positionB.x;positionPB4.y=positionB.y;positionB.x+=96;pionBlanc=5;}
                                if(pionBlanc == 3) {positionPB3.x=positionB.x;positionPB3.y=positionB.y;positionB.x+=96;pionBlanc=4;}
                                if(pionBlanc == 2) {positionPB2.x=positionB.x;positionPB2.y=positionB.y;positionB.x+=96;pionBlanc=3;}
                                if(pionBlanc == 1) {positionPB1.x=positionB.x;positionPB1.y=positionB.y;positionB.x+=96;pionBlanc=2;}
                                if(pionBlanc == 0) {positionPB0.x=positionB.x;positionPB0.y=positionB.y;positionB.x+=96;pionBlanc=1;}
                            }
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiBlanc = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'N';
                            positionRoiNY = destinationY;
                            positionRoiNX = destinationX;
                        }

                        else
                        {
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'T')
                            {
                                if(tourNoir == 1) {positionTN2.x=positionN.x;positionTN2.y=positionN.y;positionN.x+=96;tourNoir=2;}
                                if(tourNoir == 0) {positionTN1.x=positionN.x;positionTN1.y=positionN.y;positionN.x+=96;tourNoir=1;}
                            }
                            /*  */
                            /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'F')
                            {
                                if(fouNoir == 1) {positionFN2.x=positionN.x;positionFN2.y=positionN.y;positionN.x+=96;fouNoir=2;}
                                if(fouNoir == 0) {positionFN1.x=positionN.x;positionFN1.y=positionN.y;positionN.x+=96;fouNoir=1;}
                            }
                            /*  */
                              /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'C')
                            {
                                if(cavNoir == 1) {positionCN2.x=positionN.x;positionCN2.y=positionN.y;positionN.x+=96;cavNoir=2;}
                                if(cavNoir == 0) {positionCN1.x=positionN.x;positionCN1.y=positionN.y;positionN.x+=96;cavNoir=1;}
                            }
                             /* */
                             /*  */
                             if (echiquier[destinationX][destinationY].typePiece == 'D')
                            {
                                if(dameNoir == 0) {positionDN1.x=positionN.x;positionDN1.y=positionN.y;positionN.x+=96;dameNoir=1;}
                            }
                              /* */
                              /*  */
                            if (echiquier[destinationX][destinationY].typePiece == 'P')
                            {
                                if(pionNoir == 7) {positionPN7.x=positionN.x;positionPN7.y=positionN.y;positionN.x+=96;pionNoir=8;}
                                if(pionNoir == 6) {positionPN6.x=positionN.x;positionPN6.y=positionN.y;positionN.x+=96;pionNoir=7;}
                                if(pionNoir == 5) {positionPN5.x=positionN.x;positionPN5.y=positionN.y;positionN.x+=96;pionNoir=6;}
                                if(pionNoir == 4) {positionPN4.x=positionN.x;positionPN4.y=positionN.y;positionN.x+=96;pionNoir=5;}
                                if(pionNoir == 3) {positionPN3.x=positionN.x;positionPN3.y=positionN.y;positionN.x+=96;pionNoir=4;}
                                if(pionNoir == 2) {positionPN2.x=positionN.x;positionPN2.y=positionN.y;positionN.x+=96;pionNoir=3;}
                                if(pionNoir == 1) {positionPN1.x=positionN.x;positionPN1.y=positionN.y;positionN.x+=96;pionNoir=2;}
                                if(pionNoir == 0) {positionPN0.x=positionN.x;positionPN0.y=positionN.y;positionN.x+=96;pionNoir=1;}
                            }
                             /* */
                            if (echiquier[destinationX][destinationY].typePiece == 'R')
                            {
                                roiNoir = 0;
                            }
                            echiquier[destinationX][destinationY].couleurPiece = 'B';
                            positionRoiBY = destinationY;
                            positionRoiBX = destinationX;
                        }
                        echiquier[destinationX][destinationY].typePiece = 'R';
                        echiquier[x][y].couleurPiece = ' ';
                        echiquier[x][y].typePiece = ' ';
                        if (aQuiDeJouer == 0)  // A l'autre de jouer maintenant.
                        {
                            aQuiDeJouer = 1;
                        }
                        else
                        {
                            aQuiDeJouer = 0;
                        }
                    }
                }
            }
        }
    }
 if(positionB.x>=1344) {positionB.x=768;positionB.y+=96;}
 if(positionN.x>=1344) {positionN.x=768;positionN.y-=96;}
}

void NotreProgramme()
{
    while (continuer)  //Boucle infinie qui fait le jeu en quelque sorte
    {
        SDL_Delay(20);
        SDL_WaitEvent(&event); //attente d'un évenement.
        switch(event.type) // Choix de l'action à réaliser suivant l'évenement.
        {
        case SDL_QUIT:  // Cas du clic sur la croix rouge (en haut a droite)
            continuer = 0;
            break;

        case SDL_KEYDOWN:     // Cas d'une touche appuyé
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE: // Cas de la touche ECHAP
                continuer = 0;
                break;
            }
       case SDL_MOUSEMOTION:
            positionCurseur.x=event.motion.x;
            positionCurseur.y=event.motion.y;

        case SDL_MOUSEBUTTONUP:  // Cas du clic de la souris ..
            if (event.button.button == SDL_BUTTON_LEFT) // gauche !
            {
                coloreCaseSelectionne();
            }

            if (event.button.button == SDL_BUTTON_RIGHT) // droit !
            {
                deplacement(); //gestion du déplacement (pas forcément possible)
            }
            break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

////////////////////////////////////////////////////////////////////////////////
////////////////////// AFFICHAGE DES CASES NOIRES //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

        for (i=0; i<8; i=i+2)
        {
            for (j=0; j<8; j=j+2)
            {
                positionCaseNoire.x = i*96;
                positionCaseNoire.y = j*96 + 96;
                SDL_BlitSurface(caseNoire, NULL, ecran, &positionCaseNoire);
                positionCaseNoire.x = i*96 + 96;
                positionCaseNoire.y = j*96;
                SDL_BlitSurface(caseNoire, NULL, ecran, &positionCaseNoire);
            }
        }

////////////////////////////////////////////////////////////////////////////////
////////////////////// AFFICHAGE DES CASES BLANCHES ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

        for (i=0; i<8; i=i+2)
        {
            for (j=0; j<8; j=j+2)
            {
                positionCaseBlanche.x = i*96 ;
                positionCaseBlanche.y = j*96;
                SDL_BlitSurface(caseBlanche, NULL, ecran, &positionCaseBlanche);
                positionCaseBlanche.x = i*96 + 96;
                positionCaseBlanche.y = j*96 + 96;
                SDL_BlitSurface(caseBlanche, NULL, ecran, &positionCaseBlanche);
            }
        }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

if (tourBlanc==1)
{
                        SDL_BlitSurface(pieceTourBlanc, NULL, ecran, &positionTB1);
}
if (tourBlanc==2)
{
                        SDL_BlitSurface(pieceTourBlanc, NULL, ecran, &positionTB1);
                        SDL_BlitSurface(pieceTourBlanc, NULL, ecran, &positionTB2);
}
if (fouBlanc==1)
{
                        SDL_BlitSurface(pieceFouBlanc, NULL, ecran, &positionFB1);
}
if (fouBlanc==2)
{
                        SDL_BlitSurface(pieceFouBlanc, NULL, ecran, &positionFB1);
                        SDL_BlitSurface(pieceFouBlanc, NULL, ecran, &positionFB2);
}
if (cavBlanc==1)
{
                        SDL_BlitSurface(pieceCavalierBlanc, NULL, ecran, &positionCB1);
}
if (cavBlanc==2)
{
                        SDL_BlitSurface(pieceCavalierBlanc, NULL, ecran, &positionCB1);
                        SDL_BlitSurface(pieceCavalierBlanc, NULL, ecran, &positionCB2);
}
if (dameBlanc==1)
{
                        SDL_BlitSurface(pieceDameBlanc, NULL, ecran, &positionDB1);
}
if (pionBlanc==8)
{
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB7);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB6);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB5);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB4);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB3);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB2);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB1);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB0);
}
if (pionBlanc==7)
{
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB6);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB5);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB4);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB3);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB2);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB1);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB0);
}
if (pionBlanc==6)
{
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB5);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB4);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB3);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB2);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB1);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB0);
}
if (pionBlanc==5)
{
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB4);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB3);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB2);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB1);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB0);
}
if (pionBlanc==4)
{
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB3);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB2);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB1);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB0);
}
if (pionBlanc==3)
{
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB2);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB1);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB0);
}
if (pionBlanc==2)
{
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB1);
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB0);
}
if (pionBlanc==1)
{
                        SDL_BlitSurface(piecePionBlanc, NULL, ecran, &positionPB0);
}

if (tourNoir==1)
{
                        SDL_BlitSurface(pieceTourNoir, NULL, ecran, &positionTN1);
}
if (tourNoir==2)
{
                        SDL_BlitSurface(pieceTourNoir, NULL, ecran, &positionTN1);
                        SDL_BlitSurface(pieceTourNoir, NULL, ecran, &positionTN2);
}
if (fouNoir==1)
{
                        SDL_BlitSurface(pieceFouNoir, NULL, ecran, &positionFN1);
}
if (fouNoir==2)
{
                        SDL_BlitSurface(pieceFouNoir, NULL, ecran, &positionFN1);
                        SDL_BlitSurface(pieceFouNoir, NULL, ecran, &positionFN2);
}
if (cavNoir==1)
{
                        SDL_BlitSurface(pieceCavalierNoir, NULL, ecran, &positionCN1);
}
if (cavNoir==2)
{
                        SDL_BlitSurface(pieceCavalierNoir, NULL, ecran, &positionCN1);
                        SDL_BlitSurface(pieceCavalierNoir, NULL, ecran, &positionCN2);
}
if (dameNoir==1)
{
                        SDL_BlitSurface(pieceDameNoir, NULL, ecran, &positionDN1);
}
if (pionNoir==8)
{
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN7);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN6);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN5);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN4);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN3);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN2);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN1);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN0);
}
if (pionNoir==7)
{
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN6);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN5);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN4);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN3);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN2);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN1);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN0);
}
if (pionNoir==6)
{
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN5);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN4);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN3);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN2);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN1);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN0);
}
if (pionNoir==5)
{
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN4);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN3);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN2);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN1);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN0);
}
if (pionNoir==4)
{
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN3);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN2);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN1);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN0);
}
if (pionNoir==3)
{
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN2);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN1);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN0);
}
if (pionNoir==2)
{
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN1);
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN0);
}
if (pionNoir==1)
{
                        SDL_BlitSurface(piecePionNoir, NULL, ecran, &positionPN0);
}


        affichePieces(echiquier);
        if (caseSelectionnee)   ////// Affichage du couleur different autour de la case selectionnée, si l'utilisateur a cliqué sur une case.
        {
            SDL_BlitSurface(caseRouge, NULL, ecran, &coordonneeCaseSelectionnee);
        }
        else
        {
            message = TTF_RenderText_Blended(font, "Selectionnez la pièce avec le clic gauche", textColor);
            SDL_BlitSurface(message, NULL, ecran, &positionMessage);
            message = TTF_RenderText_Blended(font, "      et déplacez la avec le clic droit", textColor);
            positionMessage.y+=50;
            SDL_BlitSurface(message, NULL, ecran, &positionMessage);
            positionMessage.y-=50;
            SDL_FreeSurface(message);
        }
        afficheIndicateurPosition();
        //SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur); //Afin d'afficher l'autre curseur.
        SDL_Flip(ecran); //Mise à jour de l'écran.

        if ((roiNoir == 0) || (roiBlanc == 0))
        {
            continuer = 0;
        }
    }
}

/* ******************************** */


int main(int argc, char *argv[])
{
    positionB.x = 768;
    positionB.y = 0;
    positionN.x = 768;
    positionN.y = 672;
    position0.x=position0.y=0;
    positionecr.x=20,positionecr.y=50;

///////////////////////////////////////////////////////////////////////////////
//////////////////// DEFINITIONS DE l'ECHIQUIER ET DES PIECES /////////////////
///////////////////////////////////////////////////////////////////////////////

    for (i=0; i<8; i=i+1)     // Mise à zero de l'échiquier.
    {
        for (j=0; j<8; j=j+1)
        {
            echiquier[i][j].couleurPiece = ' ';
            echiquier[i][j].typePiece = ' ';
        }
    }

    for (i=0; i<8; i=i+1)    // Les 2 premieres et dernieres lignes sont décrites au niveaux de la couleur deja.
    {
        for (j=0; j<2; j=j+1)
        {
            echiquier[i][j].couleurPiece = 'N';
            echiquier[i][j+6].couleurPiece = 'B';
        }
    }

    echiquier[0][0].typePiece = 'T';   /////  Les tours ..
    echiquier[7][0].typePiece = 'T';
    echiquier[0][7].typePiece = 'T';
    echiquier[7][7].typePiece = 'T';

    echiquier[1][0].typePiece = 'C';   /////  Les cavaliers ...
    echiquier[6][0].typePiece = 'C';
    echiquier[1][7].typePiece = 'C';
    echiquier[6][7].typePiece = 'C';


    echiquier[2][0].typePiece = 'F';   ///// Les fous ....
    echiquier[5][0].typePiece = 'F';
    echiquier[2][7].typePiece = 'F';
    echiquier[5][7].typePiece = 'F';

    echiquier[3][0].typePiece = 'D';   ////// Les 2 dames...
    echiquier[3][7].typePiece = 'D';

    echiquier[4][0].typePiece = 'R';   ////// Les 2 rois ...
    positionRoiNX = 4;
    positionRoiNY = 0;
    echiquier[4][7].typePiece = 'R';
    positionRoiBX = 4;
    positionRoiBY = 7;

    for (i=0; i<8; i=i+1)               /////// Les pions...
    {
        echiquier[i][1].typePiece = 'P';
        echiquier[i][6].typePiece = 'P';
    }

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);

    /////////////////*************/////////////////

    SDL_Color couleur = {255, 0, 0};
    SDL_Color couleur1 = {0, 162, 232};
    SDL_Color couleur2 = {255, 255, 255};

    ecran =SDL_SetVideoMode(1366,768,32,SDL_HWSURFACE|SDL_RESIZABLE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Jeux d'echec -ALI", NULL);

    pageouv = IMG_Load("pageouv.jpg");
    SDL_SetAlpha(pageouv, SDL_SRCALPHA,120);
    SDL_BlitSurface(pageouv, NULL, ecran, &position0);
    font = TTF_OpenFont( "Dbbrnms.ttf", 34 );
    font2 = TTF_OpenFont( "Dbbrnms.ttf", 22 );

    police = TTF_OpenFont("angelina.ttf",100);
    texte= TTF_RenderText_Blended(police,"Projet de fin d'Année II1",couleur);
    positionecr.x+=250;
    SDL_BlitSurface(texte, NULL, ecran, &positionecr);
    texte= TTF_RenderText_Blended(police, "Sujet: Implementation du jeu d'échec", couleur);
    positionecr.y+=100;
    positionecr.x-=250;
    SDL_BlitSurface(texte, NULL, ecran, &positionecr);
    texte= TTF_RenderText_Blended(police, "Réalisé par: ", couleur2);
    positionecr.y+=100;
    positionecr.x+=100;
    SDL_BlitSurface(texte, NULL, ecran, &positionecr);
    texte= TTF_RenderText_Blended(police, "Mohamed Ali NABI", couleur1);
    positionecr.y+=120;
    positionecr.x+=150;
    SDL_BlitSurface(texte, NULL, ecran, &positionecr);
    texte= TTF_RenderText_Blended(police, "Mohamed Ilyess BENZARTI", couleur1);
    positionecr.y+=100;
    SDL_BlitSurface(texte, NULL, ecran, &positionecr);
    texte= TTF_RenderText_Blended(police, "Encadré par:  Mr Béchir RADDAOUI", couleur2);
    positionecr.y+=150;
    positionecr.x-=250;
    SDL_BlitSurface(texte, NULL, ecran, &positionecr);
    SDL_Flip(ecran);
    SDL_Delay(5000);
    SDL_FreeSurface(pageouv);
    SDL_FreeSurface(texte);

    /////////////****************///////////////

    ecran = SDL_SetVideoMode(1366, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN );

    /////////////// Mise En mémoire des différentes images des cases ///////////

    //caseBlanche =SDL_CreateRGBSurface(SDL_HWSURFACE,96,96,32,0,0,0,0);
    //SDL_FillRect(caseBlanche,NULL,SDL_MapRGB(caseBlanche->format,231,231,198));
    caseBlanche=IMG_Load("casemaron.png");

    //caseNoire =SDL_CreateRGBSurface(SDL_HWSURFACE,96,96,32,0,0,0,0);
    //SDL_FillRect(caseNoire,NULL,SDL_MapRGB(caseBlanche->format,74,165,74));
    caseNoire=IMG_Load("casemaronf.png");

    caseRouge = SDL_LoadBMP("caseSelectionnee.bmp");////////////////////////////
    SDL_SetAlpha(caseRouge, SDL_SRCALPHA, 128); //permet de rendre la couleur du selectionnement un peu transparent.

    pieceFouNoir = IMG_Load("fouN.png");
    pieceFouBlanc = IMG_Load("fouB.png");
    pieceDameNoir = IMG_Load("dameN.png");
    pieceDameBlanc = IMG_Load("dameB.png");
    pieceCavalierNoir = IMG_Load("cavalierN.png");
    pieceCavalierBlanc = IMG_Load("cavalierB.png");
    pieceRoiNoir = IMG_Load("roiN.png");
    pieceRoiBlanc = IMG_Load("roiB.png");
    pieceTourNoir = IMG_Load("tourN.png");
    pieceTourBlanc = IMG_Load("tourB.png");
    piecePionNoir = IMG_Load("pionN.png");
    piecePionBlanc = IMG_Load("pionB.png");
    curseur = IMG_Load("curseur.bmp");
    /*   */
    choixDameN= IMG_Load("dameN.png");
    choixFouN= IMG_Load("fouN.png");
    choixCavalierN= IMG_Load("cavalierN.png");
    choixTourN= IMG_Load("tourN.png");
    choixDameB= IMG_Load("dameB.png");
    choixFouB= IMG_Load("fouB.png");
    choixCavalierB= IMG_Load("cavalierB.png");
    choixTourB= IMG_Load("tourB.png");


    /*    */
    SDL_SetColorKey(curseur,SDL_SRCCOLORKEY,SDL_MapRGB(curseur->format,255,0,255));

 ///////////////  *********************************************** ///////////

    SDL_EnableKeyRepeat(10, 10); /* Activation de la répétition des touches */
    //SDL_ShowCursor(SDL_DISABLE);

    SDL_WM_SetIcon(IMG_Load("icon.ico"), NULL);

    positionMessage.x = 800;
    positionMessage.y = 290;

    font = TTF_OpenFont( "Dbbrnms.ttf", 34 );
    font2 = TTF_OpenFont( "Dbbrnms.ttf", 22 );


    NotreProgramme();

    if ((roiNoir == 0) || (roiBlanc == 0))
    {
        SDL_Delay(1000);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        message = TTF_RenderText_Blended(font, "Fin de la partie", textColor);
        positionMessage.x = 550;
        positionMessage.y = 250;
        SDL_BlitSurface(message, NULL, ecran, &positionMessage);
        positionMessage.x = 500;
        positionMessage.y = 450;
        SDL_Flip(ecran);
        SDL_Delay(1000);
        if (roiNoir == 0)
        {
            message = TTF_RenderText_Blended(font, "Le joueur Blanc a gagné", textColor);
        }

        if (roiBlanc == 0)
        {
            message = TTF_RenderText_Blended(font, "Le joueur Noir a gagné", textColor);
        }
        SDL_BlitSurface(message, NULL, ecran, &positionMessage);
        SDL_Flip(ecran);
        SDL_Delay(2000);
    }

    //on libere les mémoires utilisée//

    SDL_FreeSurface(caseNoire);
    SDL_FreeSurface(caseBlanche);
    SDL_FreeSurface(caseRouge);
    SDL_FreeSurface(caseColoree);
    SDL_FreeSurface(pieceFouNoir);
    SDL_FreeSurface(pieceFouBlanc);
    SDL_FreeSurface(pieceDameNoir);
    SDL_FreeSurface(pieceDameBlanc);
    SDL_FreeSurface(pieceCavalierNoir);
    SDL_FreeSurface(pieceCavalierBlanc);
    SDL_FreeSurface(pieceRoiNoir);
    SDL_FreeSurface(pieceRoiBlanc);
    SDL_FreeSurface(pieceTourNoir);
    SDL_FreeSurface(pieceTourBlanc);
    SDL_FreeSurface(piecePionNoir);
    SDL_FreeSurface(piecePionBlanc);
    SDL_FreeSurface(message);
    SDL_FreeSurface(messageIndicateur);

    // *********************** //

    TTF_CloseFont(font);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();

    return 0;

}





