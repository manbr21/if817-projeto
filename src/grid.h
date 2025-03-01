#pragma once
#include "grid_cell.h"
#include "block.h"
#include <raylib.h>
#include <vector>
#include <iostream>

class Grid
{
    public:
        int start_x, start_y;
        int size_x, size_y;
        int vector_size;
        int index;
        Block cur, nxt;
        std::vector<Block> blocks_at_grid;
        Grid_Cell grid_cells[10][20];
        bool occupied[10][20];
        Grid();
        void FillGrid();
        void DrawGrid();
        void DrawBlocks();
        void DrawLines();
        std::vector<int> IsLinecomplete();
};