#include "grid.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 920
#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 40

Grid::Grid(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20; j++){
            occupied[i][j] = false;
        }
    }
    index = 0; //first block
    start_x =  SCREEN_WIDTH / 2 - 230;
    start_y = 50;
    size_x = BLOCK_WIDTH * 10;
    size_y =BLOCK_HEIGHT * 20;

    vector_size = 0;
    blocks_at_grid.push_back(cur);
    vector_size++;

    score = 0;
}

void Grid::FillGrid(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20;j++){
            Grid_Cell temp;
            temp.x = start_x + i * BLOCK_WIDTH;
            temp.y = start_y + j * BLOCK_WIDTH;
            grid_cells[i][j] = temp;
        }
    }
}

void Grid::DrawGrid(){
     //drawing real grid
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20;j++){
            grid_cells[i][j].Draw();
        }
    }
}

void Grid::DrawBlocks(){
    //drawing the blocks
    for(int j = 0; j < vector_size; j++){
        for(int i = 0; i < blocks_at_grid.at(j).size; i++){
            int coord_x = grid_cells[blocks_at_grid.at(j).coord.at(i).first][blocks_at_grid.at(j).coord.at(i).second].x;
            int coord_y = grid_cells[blocks_at_grid.at(j).coord.at(i).first][blocks_at_grid.at(j).coord.at(i).second].y;
            DrawRectangle(coord_x, coord_y, BLOCK_WIDTH, BLOCK_HEIGHT, blocks_at_grid.at(j).color);
        }
    }

    DrawText("NEXT",start_x + size_x + 110, start_y + 50, 30, BLACK);
    DrawRectangle(start_x + size_x + 50, start_y + 80, 200, 100, BLACK);
    for(int i = 0; i < nxt.size; i++){
        int coord_x = grid_cells[nxt.coord.at(i).first][nxt.coord.at(i).second].x + size_x - 50;
        int coord_y = grid_cells[nxt.coord.at(i).first][nxt.coord.at(i).second + 2].y + 10;
        DrawRectangle(coord_x, coord_y, BLOCK_WIDTH, BLOCK_HEIGHT, nxt.color);
    }
}

void Grid::DrawLines(){
    //drawing grid lines
    for(int i = start_x; i <= size_x + start_x; i+=BLOCK_WIDTH){
        DrawLine(i, start_y, i, size_y + start_y, WHITE);
    }
    for(int i = start_y; i <= size_y + start_y; i+=BLOCK_HEIGHT){
        DrawLine(start_x, i, size_x + start_x, i, WHITE);
    }
}

std::vector<int> Grid::IsLinecomplete(){
    int cont = 0;
    std::vector<int> lines_completed; 
    for(int linha = 19; linha >= 0; linha--){
        for(int coluna = 0; coluna < 10; coluna++){
            if(occupied[coluna][linha]){
                cont++;
            }
        }
        if(cont == 10){
            lines_completed.push_back(linha);
        }
        cont = 0;
    }
    
    return lines_completed; 
}