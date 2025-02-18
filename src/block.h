#pragma once
#include <vector>
#include "grid_cell.h"
#include <raylib.h>

class Block{
    public:
        Block();
        int shape;
        int size;
        int right_limit, left_limit, down_limit;
        std::vector<std::pair<int,int>> coord;
        Color color;
        void Fall();
        void Move();
        bool CheckBoundaries();
    
};