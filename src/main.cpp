#include <raylib.h>
#include <bits/stdc++.h>
#include "grid_cell.h"
#include "block.h"

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 920
#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 40

int main() 
{   

    srand(time(0));
    int frames = 0;

    const int grid_start_x = SCREEN_WIDTH / 2 - 230, grid_size_x = BLOCK_WIDTH * 10, grid_start_y = 50, grid_size_y = BLOCK_HEIGHT * 20;

    Grid_Cell grid[10][20]; //matriz

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20;j++){
            Grid_Cell temp;
            temp.x = grid_start_x + i * BLOCK_WIDTH;
            temp.y = grid_start_y + j * BLOCK_WIDTH;
            grid[i][j] = temp;
        }
    }

    queue<Block> blocks;
    Block cur, nxt;
    blocks.push(cur);
    blocks.push(nxt);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {   
        
        frames++;
        
        if((frames * 1.0) / 60 == 0.5 and blocks.front().CheckBoundaries()){ //0.5 seg
            blocks.front().Fall();
            frames = 0;
        }
        
        if(blocks.front().CheckBoundaries())
            blocks.front().Move();
        
        BeginDrawing();

            ClearBackground(GRAY); //blackground color
            DrawRectangle(grid_start_x, grid_start_y, grid_size_x, grid_size_y, BLACK); //first layer grid
            
            //drawing real grid
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 20;j++){
                    grid[i][j].Draw();
                }
            }
            //DrawRectangle(grid_hitbox.x, grid_hitbox.y, grid_hitbox.width, grid_hitbox.height, GREEN);
            //drawing the blocks
            for(int i = 0; i < blocks.front().size; i++){
                DrawRectangle(grid[blocks.front().coord.at(i).first][blocks.front().coord.at(i).second].x, grid[blocks.front().coord.at(i).first][blocks.front().coord.at(i).second].y, BLOCK_WIDTH, BLOCK_HEIGHT, blocks.front().color);
            }
            
            //drawing grid lines
            for(int i = grid_start_x; i <= grid_size_x + grid_start_x; i+=BLOCK_WIDTH){
                DrawLine(i, grid_start_y, i, grid_size_y + grid_start_y, WHITE);
            }
            for(int i = grid_start_y; i <= grid_size_y + grid_start_y; i+=BLOCK_HEIGHT){
                DrawLine(grid_start_x, i, grid_size_x + grid_start_x, i, WHITE);
            }
        EndDrawing();
    }
    
    CloseWindow();
}