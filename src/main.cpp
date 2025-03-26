#include <raylib.h>
#include <vector>
#include "grid_cell.h"
#include "block.h"
#include "grid.h"

#include <stdio.h>	/* printf */
#include <stdlib.h>	/* malloc, atoi, rand... */
#include <string.h>	/* memcpy, strlen... */
#include <stdint.h>	/* uints types */
#include <sys/types.h>	/* size_t ,ssize_t, off_t... */
#include <unistd.h>	/* close() read() write() */
#include <fcntl.h>	/* open() */
#include <sys/ioctl.h>	/* ioctl() */
#include <errno.h>	/* error codes */

#include "ioctl_cmds.h"
#include "display.h"

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
    
    bool isPaused = false;
    
    int driver_file = open("/dev/mydev", O_RDWR);
    
    unsigned int data = 0xFFFFFFFF;
    
    ioctl(driver_file, WR_L_DISPLAY);
	write(driver_file, &data, sizeof(data));
	
	ioctl(driver_file, WR_R_DISPLAY);
	write(driver_file, &data, sizeof(data));

    data = data ^ data;

    ioctl(driver_file, WR_GREEN_LEDS);
    write(driver_file, &data, sizeof(data));
	
	close(driver_file);
    
    while (!WindowShouldClose())
    {   
        if((frames * 1.0) / 60 == 0.25 && grid.blocks_at_grid.at(grid.index).CanFall() && !isPaused){ //cai a cada 0.5s se estiver nos limites
            grid.blocks_at_grid.at(grid.index).Fall();
            frames = 0;
        }

        if(grid.blocks_at_grid.at(grid.index).CanMove(grid.blocks_at_grid.at(grid.index).end, grid.occupied) && !isPaused) //checa se o bloco está nos limites do jogo
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
            if(isPaused){
                DrawText("PAUSADO", (grid.start_x + grid.size_x) / 2 + 6, grid.start_y + 200, 83, WHITE);
            }
    
        EndDrawing();
        
    	int fd, retval;
    	unsigned data = 0x0;
		
		fd = open("/dev/mydev", O_RDWR);
		char vet[5];
		
		vet[0] = (grid.score / 1000) + 48;
		vet[1] = (grid.score % 1000) / 100 + 48;
		vet[2] = (grid.score % 100) / 10 + 48;
		vet[3] = (grid.score % 10) + 48;
		
		//printf("%s\n", vet);
		int posi = 0;
		for(int i=3;i>=0;i--){
			switch (vet[i]){
				case '0':
					data |= (HEX_0 & 0xff) << posi;
					break;
				case '1':
					data |= (HEX_1 & 0xff) << posi;
					break;
				case '2':
					data |= (HEX_2 & 0xff) << posi;
					break;
				case '3':
					data |= (HEX_3 & 0xff) << posi;
					break;
				case '4':
					data |= (HEX_4 & 0xff) << posi;
					break;
				case '5':
					data |= (HEX_5 & 0xff) << posi;
					break;
				case '6':
					data |= (HEX_6 & 0xff) << posi;
					break;
				case '7':
					data |= (HEX_7 & 0xff) << posi;
					break;
				case '8':
					data |= (HEX_8 & 0xff) << posi;
					break;
				case '9':
					data |= (HEX_9 & 0xff) << posi;
					break;
				default:
					data |= 0xc0 << posi;
					break;
			}
			posi += 8;
		}
		
		ioctl(fd, WR_4_DISPLAY);
		retval = write(fd, &data, sizeof(data));

        switch(grid.score / 250){
            case 0:
                data = 0b000000000;
                break;
            case 1:
                data = 0b000000001;
                break;
            case 2:
                data = 0b000000011;
                break;
            case 3:
                data = 0b000000111;
                break;
            case 4:
                data = 0b000001111;
                break;
            case 5:
                data = 0b000011111;
                break;
            case 6:
                data = 0b000111111;
                break;
            case 7:
                data = 0b001111111;
                break;
            case 8:
                data = 0b011111111;
                break;
            default:
                data = 0b111111111;
                break;
        }

        ioctl(fd, WR_GREEN_LEDS);
        write(fd, &data, sizeof(data));

        data = data ^ data;

        ioctl(fd, RD_SWITCHES);
        read(fd, &data, 4);
		
		close(fd);
	
        if((frames * 1.0) / 60 != 0.25 && !isPaused)
            frames++;

        isPaused = (data & 0xf) == 0b1;
    }
    
    CloseWindow();
}
