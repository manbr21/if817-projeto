#include "block.h"
#include <cstdlib>

Block::Block(){
    shape = rand() % 7;
    size = 4;
    
    switch (shape){
        case 0:
            color = PINK;
            coord.push_back({3,0});
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({5,1});
            break;
        case 1:
            color = GREEN;
            coord.push_back({3,0});
            coord.push_back({4,0});
            coord.push_back({4,1});
            coord.push_back({5,1});
            break;
        case 2:
            color = RED;
            coord.push_back({3,0});
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({6,0});
            break;
        case 3:
            color = BLUE;
            coord.push_back({3,0});
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({3,1});
            break;
        case 4:
            color = YELLOW;
            coord.push_back({3,0});
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({5,1});
            break;

        case 5:
            color = BROWN;
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({3,1});
            coord.push_back({4,1});
            break;

        case 6:
            color = PURPLE;
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({4,1});
            coord.push_back({5,1});
            break;
        
        default:
            break;
    }
};

void Block::Fall(){
    for(int i = 0; i < size; i++){
        coord.at(i).second++;
    }
}

void Block::Move(){
    if(IsKeyPressed(KEY_A)){
        for(int i = 0; i < size; i++){
            coord.at(i).first--;
        }
    }
    if(IsKeyPressed(KEY_D)){
        for(int i = 0; i < size; i++){
            coord.at(i).first++;
        }
    }
    if(IsKeyPressed(KEY_S)){
        Fall();
    }
}

bool Block::CheckBoundaries(){
    if(IsKeyPressed(KEY_A)){
        for(int i = 0; i < size; i++){
            if(coord.at(i).first - 1 < 0){
                coord.at(i).first = 0;
                return false;
            }
        }
    }
    if(IsKeyPressed(KEY_D)){
        for(int i = 0; i < size; i++){
            if(coord.at(i).first + 1 > 9){
                coord.at(i).first = 9;
                return false;
            }
        }
    }

    for(int i = 0; i < size; i++){
        if(coord.at(i).second + 1 > 19){
            coord.at(i).second = 19;
            return false;
        }
    }

    return true;
}

