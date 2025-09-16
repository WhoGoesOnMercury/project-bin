#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>

#define DEBUG

#ifndef DEBUG 
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed", #n); \
printf("On %s ", __DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif

typedef unsigned long long U64; //Unsigned long long == 32 bits + 32 bits = 64 bits

#define NAME "ChEngine"
#define BRD_SQ_NUM 120

#define MAXGAMEMOVES 2048 

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/pppppppp/RNBQKBNR w KQkq - 0 1"

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK }; // Existing piece
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };
enum { WHITE, BLACK, BOTH };

enum {
    A1 = 21, B1, C1 ,D1 ,E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

enum { TRUE, FALSE };


// 1 0 0 1 || (WKCA || BQCA) && !(WQCA || BKCA)
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 }; // Castling permissions


typedef struct {
    int move;
    int castlePerm;
    int enPassantSq;
    int fiftyMoveRule;
    U64 posKey;

} S_UNDO;

typedef struct {
    int pieces[BRD_SQ_NUM];
    U64 pawns[3];
    int KingSq[2];

    int side;
    int enPassantSq;
    int fiftyMoveRule;

    int castlePerm;

    int ply; // Half-moves
    int historyPly; // How many half-moves have been made || to determine repetitions

    U64 posKey;

    int pieceNum[13]; // To get count of pieces on board using Existing Piece
    int bigPieces[2]; // Anything that is not a pawn
    int majorPieces[2];
    int minorPieces[2];
    int material[2];

    S_UNDO history[MAXGAMEMOVES];

    // Piece List
    int pieceList[13][10];

    // pieceList[wN][0] = E1;
    // pieceList[wN][1] = D4;


} S_BOARD;

/* MACROS */
#define FR2SQ(f,r) ( (21 + (f) ) + ( (r) * 10 ) ) 
#define SQ64(sq120) Sq120ToSq64[sq120]
#define SQ120(sq64) (Sq64ToSq120[(sq64)])
#define POP(b) PopBit(b)
#define CNT(b) CountBits(b)
#define CLRBIT(bb, sq) ((bb) &= ClearMask[(sq)])
#define SETBIT(bb, sq) ((bb) |= SetMask[(sq)])

/* GLOBALS */

extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16]; 
extern char PieceChar[];
extern char SideChar[];
extern char FileChar[];
extern char RankChar[];

extern int PieceBig[13]; 
extern int PieceMaj[13];
extern int PieceMin[13];
extern int PieceVal[13];
extern int PieceCol[13];

extern int FilesBrd[BRD_SQ_NUM];
extern int RanksBrd[BRD_SQ_NUM];

/* FUNCTIONS */

extern void AllInit();
extern void InitSq120To64(); 

// bitboards.c 
extern void PrintBitBoard(U64 bb);
extern int PopBit(U64 *bb);
extern int CountBits(U64 bb);

// hashkeys.c
extern U64 GeneratePosKey (const S_BOARD *pos);

// boards.c
extern void ResetBoard(S_BOARD *pos);
extern int ParseFen(char *fen, S_BOARD *pos);
extern void PrintBoard(const S_BOARD *pos);
extern void UpdateListMaterials(S_BOARD *pos);

#endif