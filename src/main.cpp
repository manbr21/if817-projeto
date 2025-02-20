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
    bool occupied[10][20]; //falta implementar 

    //preenche o 
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20;j++){
            Grid_Cell temp;
            temp.x = grid_start_x + i * BLOCK_WIDTH;
            temp.y = grid_start_y + j * BLOCK_WIDTH;
            grid[i][j] = temp;
            occupied[i][j] = false;
        }
    }

    vector<Block> blocks_at_grid;
    int vector_size = 0;
    queue<Block> cur_and_nxt_blocks;
    Block cur, nxt;
    blocks_at_grid.push_back(cur);
    vector_size++;
    cur_and_nxt_blocks.push(cur);
    cur_and_nxt_blocks.push(nxt);
    
    int index = 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {   
        if(blocks_at_grid.at(index).end){ //se bloco que está caindo chegou no fim
            for(int i = 0; i < blocks_at_grid.at(index).size; i++){ //seta vetor de ocupados
                occupied[blocks_at_grid.at(index).coord.at(i).first][blocks_at_grid.at(index).coord.at(i).second] = true;
            }
            //cur_and_nxt_blocks.pop(); //da pop na fila
            blocks_at_grid.push_back(nxt); //aciciona o novo bloco no vetor
            vector_size++;
            Block new_nxt;
            nxt = new_nxt; //cria proximo bloco
            //cur_and_nxt_blocks.push(nxt); //coloca na fila do atual e do prox
            index++; //proximo bloco
        }

        if(blocks_at_grid.at(index).CheckBoundaries(blocks_at_grid.at(index).end, occupied)) //checa se o bloco está nos limites do jogo
            blocks_at_grid.at(index).Move(occupied);

        frames++;

        if((frames * 1.0) / 60 == 0.5 && !blocks_at_grid.at(index).end){ //cai a cada 0.5s se estiver nos limites
            blocks_at_grid.at(index).Fall();
            frames = 0;
        }
        
        BeginDrawing();

            ClearBackground(GRAY); //blackground color
            DrawRectangle(grid_start_x, grid_start_y, grid_size_x, grid_size_y, BLACK); //first layer grid
            
            //drawing real grid
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 20;j++){
                    grid[i][j].Draw();
                }
            }
            
            //drawing the blocks
            for(int j = 0; j < vector_size; j++){
                for(int i = 0; i < blocks_at_grid.at(j).size; i++){
                    int coord_x = grid[blocks_at_grid.at(j).coord.at(i).first][blocks_at_grid.at(j).coord.at(i).second].x;
                    int coord_y = grid[blocks_at_grid.at(j).coord.at(i).first][blocks_at_grid.at(j).coord.at(i).second].y;
                    DrawRectangle(coord_x, coord_y, BLOCK_WIDTH, BLOCK_HEIGHT, blocks_at_grid.at(j).color);
                }
            }
            
            //desenhando a próxima peça e box dela
            DrawText("NEXT",grid_start_x + grid_size_x + 110, grid_start_y + 50, 30, BLACK);
            DrawRectangle(grid_start_x + grid_size_x + 50, grid_start_y + 80, 200, 100, BLACK);
            for(int i = 0; i < nxt.size; i++){
                int coord_x = grid[nxt.coord.at(i).first][nxt.coord.at(i).second].x + grid_size_x - 50;
                int coord_y = grid[nxt.coord.at(i).first][nxt.coord.at(i).second + 2].y + 10;
                DrawRectangle(coord_x, coord_y, BLOCK_WIDTH, BLOCK_HEIGHT, nxt.color);
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