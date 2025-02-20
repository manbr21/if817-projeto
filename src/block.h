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
        void Move();
        void Rotate();
        bool CheckBoundaries(bool &end, bool occupied[10][20]);
    
};