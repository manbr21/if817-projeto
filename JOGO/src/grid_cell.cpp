#include "grid_cell.h"
#include <raylib.h>

#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 40

Grid_Cell::Grid_Cell()
{
    x = 0;
    y = 0;
    width = BLOCK_WIDTH;
    height = BLOCK_HEIGHT;
    falling = true;

}

void Grid_Cell::Draw() const
{
    DrawRectangle(x, y, width, height, BLACK);
}

