struct Piece
{
    char couleurPiece;  // Couleur = N ou B ou ' ' (s'il n'y a pas de piece)
    char typePiece;     //Type = T(our), C(avalier), D(ame), R(oi), P(ion), F(ou)  ou ' ' (s'il n'y a pas de piece)
};

int deplacementTour(int pieceX, int pieceY, int destinationpX, int destinationpY, struct Piece echiquier[8][8]);
int deplacementFou(int pieceX, int pieceY, int destinationpX, int destinationpY, struct Piece echiquier[8][8]);
int deplacementPion(int pieceX, int pieceY, int destinationpX, int destinationpY,  struct Piece echiquier[8][8]);
int deplacementRoi(int pieceX, int pieceY, int destinationpX, int destinationpY, struct Piece echiquier[8][8]);
int deplacementCavalier(int pieceX, int pieceY, int destinationpX, int destinationpY, struct Piece echiquier[8][8]);



