#pragma once
#include <vector>
#include "grid_cell.h"
#include <raylib.h>

class Block{
    public:
        Block();
        int shape;
        int state;
        int size;
        std::vector<std::pair<int,int>> coord;
        Color color;
        bool end;

        void Fall();
        void Move(bool occupied[10][20]);
        void Rotate();
        bool CanFall();
        bool CanMove(bool &end, bool occupied[10][20]);
        bool CanRotate(bool occupied[10][20]);
    
};