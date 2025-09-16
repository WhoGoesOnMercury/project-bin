#include <stdio.h>
#include "defs.h"

U64 GeneratePosKey (const S_BOARD *pos) {
    int sq = 0;
    U64 finalKey = 0;
    int piece = EMPTY;

    for(sq = 0; sq < BRD_SQ_NUM; sq++) {
        piece = pos->pieces[sq];
        if(piece != NO_SQ && piece != EMPTY && piece != OFFBOARD) {
            ASSERT(piece>=wP && piece<=bK);
            finalKey ^= PieceKeys[piece][sq];
        }
    }

    if(pos->side ==WHITE) {
        finalKey ^= SideKey;
    }

    if(pos->enPassantSq != NO_SQ) {
        ASSERT(pos->enPassantSq>=0 && pos->enPassantSq<BRD_SQ_NUM);
        finalKey ^= PieceKeys[EMPTY][pos->enPassantSq];
    }

    ASSERT(pos->castlePerm>=0 && pos->castlePerm<=15);

    finalKey ^= CastleKeys[pos->castlePerm];

    return finalKey;
}