#ifndef __TETRISAI_H__
#define __TETRISAI_H__

#include <iostream>
using namespace std;

typedef struct
{
    int transpose;
    int block[4][4];
    int typenum;
    int pose[4][4];
}tetris_block;

class TetrisAI {
    private:
        int maxValue;
        int map[15][10];
        int map_copy[15][10];
        int bestblock[4][4];
        int currentblock[4][4];

    public:
        int RowTransitions();
        int ColumnTransitions();
        int NumberofHoles();
        int WellSums();
        int RowsEliminated;
        int PierreDellacherie();
        bool collisionJudge(int x, int y);
        void addtomapcopy(int x, int y);
        void inittetris(int type);
        void AIrun();
        void copymap();
        void tetrisrotate();
        void addbesttomap();
        int nowpose[4][4];
        int bestX, bestY, besttrans;
        tetris_block tetris;

};

#endif // __TETRISAI_H__