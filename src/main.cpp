#include <raylib.h>
#include <bits/stdc++.h>
#include "grid_cell.h"
#include "block.h"
#include "grid.h"

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 920
#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 40

int main() 
{   

    srand(time(0));
    int frames = 0;

    Grid grid;
    grid.FillGrid();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {   
        
        if((frames * 1.0) / 60 == 0.5 && !grid.blocks_at_grid.at(grid.index).end){ //cai a cada 0.5s se estiver nos limites
            grid.blocks_at_grid.at(grid.index).Fall();
            frames = 0;
        }

        if(grid.blocks_at_grid.at(grid.index).CheckBoundaries(grid.blocks_at_grid.at(grid.index).end, grid.occupied)) //checa se o bloco está nos limites do jogo
            grid.blocks_at_grid.at(grid.index).Move(grid.occupied);

        if(grid.blocks_at_grid.at(grid.index).end){ //se bloco que está caindo chegou no fim
            for(int i = 0; i < grid.blocks_at_grid.at(grid.index).size; i++){ //seta vetor de ocupados
                grid.occupied[grid.blocks_at_grid.at(grid.index).coord.at(i).first][grid.blocks_at_grid.at(grid.index).coord.at(i).second] = true;
            }
            grid.blocks_at_grid.push_back(grid.nxt); //aciciona o novo bloco no vetor
            grid.vector_size++;
            Block new_nxt;
            grid.nxt = new_nxt; //cria proximo bloco
            grid.index++; //proximo bloco
        }

        // if(grid.IsLinecomplete() != -1){
        //     for(int coluna = 0; coluna)
        // }
        
        BeginDrawing();

            ClearBackground(GRAY); //blackground color
            DrawRectangle(grid.start_x, grid.start_y, grid.size_x, grid.size_y, BLACK); //first layer grid
            
            grid.DrawGrid();
            grid.DrawBlocks();
            grid.DrawLines();

            if(grid.IsLinecomplete() != -1){
                std::cout << "LINHA COMPLETA" << endl;
            }
    
        EndDrawing();

        frames++;
    }
    
    CloseWindow();
}