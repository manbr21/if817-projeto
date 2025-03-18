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
        if((frames * 1.0) / 60 == 0.5 && grid.blocks_at_grid.at(grid.index).CanFall()){ //cai a cada 0.5s se estiver nos limites
            grid.blocks_at_grid.at(grid.index).Fall();
            frames = 0;
        }

        if(grid.blocks_at_grid.at(grid.index).CanMove(grid.blocks_at_grid.at(grid.index).end, grid.occupied)) //checa se o bloco está nos limites do jogo
            grid.blocks_at_grid.at(grid.index).Move(grid.occupied);

        if(grid.blocks_at_grid.at(grid.index).end){ //se bloco que está caindo chegou no fim

            for(int i = 0; i < grid.blocks_at_grid.at(grid.index).size; i++){ //seta vetor de ocupados
                grid.occupied[grid.blocks_at_grid.at(grid.index).coord.at(i).first][grid.blocks_at_grid.at(grid.index).coord.at(i).second] = true;
            }

            std::vector<int> line_index = grid.IsLinecomplete(); //checando linhas completas
            int cont = 0, sub_lines = 0;
            for(auto index : line_index){
                if(index != -1){
                    index += sub_lines;
                
                    //procura objetos na linha e exclui a linha
                    for(int b_index = 0; b_index < grid.vector_size; b_index++){
                        for(int coord_index = 0; coord_index < grid.blocks_at_grid.at(b_index).size; coord_index++){
                            if(grid.blocks_at_grid.at(b_index).coord.at(coord_index).second == index){
                                grid.occupied[grid.blocks_at_grid.at(b_index).coord.at(coord_index).first][grid.blocks_at_grid.at(b_index).coord.at(coord_index).second] = false;
                                grid.blocks_at_grid.at(b_index).coord.erase((grid.blocks_at_grid.at(b_index).coord.begin() + coord_index));
                                grid.blocks_at_grid.at(b_index).size--;
                                coord_index--;
                            }
                        }
                    }
                    
                    //caindo as peças
                    for(int b_index = 0; b_index < grid.vector_size; b_index++){
                        for(int coord_index = 0; coord_index < grid.blocks_at_grid.at(b_index).size; coord_index++){
                            if(grid.blocks_at_grid.at(b_index).coord.at(coord_index).second < index){
                                grid.blocks_at_grid.at(b_index).coord.at(coord_index).second++;
                            }
                        }
                    }

                    //atualizando matriz de ocupados
                    for(int i = 0; i < 10; i++){
                        for(int j = 0; j < 20; j++){
                            grid.occupied[i][j] = false;
                        }
                    }
                    for(int blocks = 0; blocks < grid.vector_size; blocks++){
                        for(int i = 0; i < grid.blocks_at_grid.at(blocks).size; i++){ //seta matriz de ocupados
                            grid.occupied[grid.blocks_at_grid.at(blocks).coord.at(i).first][grid.blocks_at_grid.at(blocks).coord.at(i).second] = true;
                        }
                    }
                    
                    line_index.erase(line_index.begin() + cont);
                    cont++;
                    sub_lines++;
                }
            }

            switch (cont)
            {
            case 1:
                grid.score += 100;
                break;
            case 2:
                grid.score += 300;
                break;
            case 3:
                grid.score += 500;
                break;
            case 4: //tetris
                grid.score += 800;
                break;
            default:
                grid.score += 10;
                break;
            }

            grid.blocks_at_grid.push_back(grid.nxt); //aciciona o novo bloco no vetor
            grid.vector_size++;

            Block new_nxt;
            grid.nxt = new_nxt; //cria proximo bloco
            grid.index++; //proximo bloco
        }
        
        BeginDrawing();

            ClearBackground(GRAY); //blackground color
            DrawRectangle(grid.start_x, grid.start_y, grid.size_x, grid.size_y, BLACK); //first layer grid
            
            grid.DrawGrid();
            grid.DrawBlocks();
            grid.DrawLines();

            DrawText(TextFormat("Score: %d", grid.score), grid.start_x + grid.size_x + 50, grid.start_y + 200, 50, BLACK);
    
        EndDrawing();

        if((frames * 1.0) / 60 != 0.5)
            frames++;
    }
    
    CloseWindow();
}