#include "block.h"
#include <cstdlib>

Block::Block(){
    shape = rand() % 7;
    state = 0;
    size = 4;
    end = false;
    
    switch (shape){
        // T
        case 0:
            color = PINK;
            coord.push_back({3,0});
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({4,1});
            break;
        // Cobrinha esquerda
        case 1:
            color = GREEN;
            coord.push_back({3,0});
            coord.push_back({4,0});
            coord.push_back({4,1});
            coord.push_back({5,1});
            break;
        // Retangulo
        case 2:
            color = RED;
            coord.push_back({3,0});
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({6,0});
            break;
        // L direita
        case 3:
            color = BLUE;
            coord.push_back({3,0});
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({3,1});
            break;
        // L esquerda
        case 4:
            color = YELLOW;
            coord.push_back({3,0});
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({5,1});
            break;
        // Cobrinha direita
        case 5:
            color = BROWN;
            coord.push_back({4,0});
            coord.push_back({5,0});
            coord.push_back({3,1});
            coord.push_back({4,1});
            break;
        // Quadrado
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

void Block::Move(bool occupied[10][20]){
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
    if (IsKeyDown(KEY_S)){
        Fall();
    }
    if (IsKeyPressed(KEY_W)) {
        if (CanRotate(occupied)) {
            Rotate();
        }
    }
}

void Block::Rotate() {
    // Verificar Se pode rotacionar

    switch (shape) {
        case 0:
            if(state == 0) {
                coord.at(0) = {coord.at(0).first + 1, coord.at(0).second - 1};
                coord.at(1) = {coord.at(1).first, coord.at(1).second};
                coord.at(2) = {coord.at(2).first - 1, coord.at(2).second + 1};
                coord.at(3) = {coord.at(3).first - 1, coord.at(2).second - 1};
            }
            else if(state == 1) {
                coord.at(0) = {coord.at(0).first + 1, coord.at(0).second + 1};
                coord.at(1) = {coord.at(1).first, coord.at(1).second};
                coord.at(2) = {coord.at(2).first - 1, coord.at(2).second - 1};
                coord.at(3) = {coord.at(3).first + 1, coord.at(2).second - 1};
            }
            else if(state == 2) {
                coord.at(0) = {coord.at(0).first - 1, coord.at(0).second + 1};
                coord.at(1) = {coord.at(1).first, coord.at(1).second};
                coord.at(2) = {coord.at(2).first + 1, coord.at(2).second - 1};
                coord.at(3) = {coord.at(3).first + 1, coord.at(2).second + 1};
            }
            else {
                coord.at(0) = {coord.at(0).first - 1, coord.at(0).second - 1};
                coord.at(1) = {coord.at(1).first, coord.at(1).second};
                coord.at(2) = {coord.at(2).first + 1, coord.at(2).second + 1};
                coord.at(3) = {coord.at(3).first - 1, coord.at(2).second + 1};
            }
            break;
        case 1:
            if (state == 0 || state == 2) {
                coord.at(0) = {coord.at(0).first + 2, coord.at(0).second - 1};
                coord.at(1) = {coord.at(1).first + 1, coord.at(1).second};
                coord.at(2) = {coord.at(2).first, coord.at(2).second - 1};
                coord.at(3) = {coord.at(3).first - 1, coord.at(3).second};
            }
            else {
                coord.at(0) = {coord.at(0).first - 2, coord.at(0).second + 1};
                coord.at(1) = {coord.at(1).first - 1, coord.at(1).second};
                coord.at(2) = {coord.at(2).first, coord.at(2).second + 1};
                coord.at(3) = {coord.at(3).first + 1, coord.at(3).second};
            }
            break;
        case 2:
            if (state == 0 || state == 2) {
                coord.at(0) = {coord.at(0).first + 2, coord.at(0).second - 2};
                coord.at(1) = {coord.at(1).first + 1, coord.at(1).second - 1};
                coord.at(2) = {coord.at(2).first, coord.at(2).second};
                coord.at(3) = {coord.at(3).first - 1, coord.at(3).second + 1};
            }
            else {
                coord.at(0) = {coord.at(0).first - 2, coord.at(0).second + 2};
                coord.at(1) = {coord.at(1).first - 1, coord.at(1).second + 1};
                coord.at(2) = {coord.at(2).first, coord.at(2).second};
                coord.at(3) = {coord.at(3).first + 1, coord.at(3).second - 1};
            }
            break;
        case 3:
            if (state == 0) {
                coord.at(0) = {coord.at(0).first + 2, coord.at(0).second - 1};
                coord.at(1) = {coord.at(1).first + 1, coord.at(1).second};
                coord.at(2) = {coord.at(2).first, coord.at(2).second + 1};
                coord.at(3) = {coord.at(3).first + 1, coord.at(3).second - 2};
            }
            else if (state == 1) {
                coord.at(0) = {coord.at(0).first, coord.at(0).second + 2};
                coord.at(1) = {coord.at(1).first - 1, coord.at(1).second + 1};
                coord.at(2) = {coord.at(2).first - 2, coord.at(2).second};
                coord.at(3) = {coord.at(3).first + 1, coord.at(3).second + 1};
            }
            else if (state == 2) {
                coord.at(0) = {coord.at(0).first - 2, coord.at(0).second + 1};
                coord.at(1) = {coord.at(1).first - 1, coord.at(1).second};
                coord.at(2) = {coord.at(2).first, coord.at(2).second - 1};
                coord.at(3) = {coord.at(3).first - 1, coord.at(3).second + 2};
            }
            else {
                coord.at(0) = {coord.at(0).first, coord.at(0).second - 2};
                coord.at(1) = {coord.at(1).first + 1, coord.at(1).second - 1};
                coord.at(2) = {coord.at(2).first + 2, coord.at(2).second};
                coord.at(3) = {coord.at(3).first - 1, coord.at(3).second - 1};
            }
            break;
        case 4:
            if (state == 0) {
                coord.at(0) = {coord.at(0).first + 2,coord.at(0).second - 1};
                coord.at(1) = {coord.at(1).first + 1,coord.at(1).second};
                coord.at(2) = {coord.at(2).first,coord.at(2).second + 1};
                coord.at(3) = {coord.at(3).first - 1,coord.at(3).second};
            }
            else if (state == 1) {
                coord.at(0) = {coord.at(0).first,coord.at(0).second + 2};
                coord.at(1) = {coord.at(1).first - 1, coord.at(1).second + 1};
                coord.at(2) = {coord.at(2).first - 2, coord.at(2).second};
                coord.at(3) = {coord.at(3).first - 1, coord.at(3).second - 1};
            }
            else if (state == 2) {
                coord.at(0) = {coord.at(0).first - 2, coord.at(0).second};
                coord.at(1) = {coord.at(1).first - 1, coord.at(0).second - 1};
                coord.at(2) = {coord.at(2).first, coord.at(2).second - 2};
                coord.at(3) = {coord.at(3).first + 1, coord.at(3).second - 1};
            }
            else {
                coord.at(0) = {coord.at(0).first,coord.at(0).second - 1};
                coord.at(1) = {coord.at(1).first + 1, coord.at(1).second};
                coord.at(2) = {coord.at(2).first + 2, coord.at(2).second + 1};
                coord.at(3) = {coord.at(3).first + 1, coord.at(3).second + 2};
            }
            break;
        case 5:
            if (state == 0 || state == 2) {
                coord.at(0) = {coord.at(0).first + 1, coord.at(0).second};
                coord.at(1) = {coord.at(1).first, coord.at(1).second + 1};
                coord.at(2) = {coord.at(2).first + 1, coord.at(2).second - 2};
                coord.at(3) = {coord.at(3).first, coord.at(3).second - 1};
            }
            else {
                coord.at(0) = {coord.at(0).first - 1, coord.at(0).second};
                coord.at(1) = {coord.at(1).first, coord.at(1).second - 1};
                coord.at(2) = {coord.at(2).first - 1, coord.at(2).second + 2};
                coord.at(3) = {coord.at(3).first, coord.at(3).second + 1};
            }
            break;
    }

    state = (state + 1) % 4;
}

bool Block::CanRotate(bool occupied[10][20]) {
    switch (shape) {
        case 0:
            if (state == 0) {

            }
            else if (state == 1) {

            }
            else if (state == 2) {
                
            }
            else {

            }
            break;
        case 1:
            if (state == 0 || state == 2) {
                if (occupied[coord[0].first+2][coord[0].second-1] || coord[0].first+2 >= 10 || coord[0].second-1 < 0){
                    return false;
                }
                if (occupied[coord[1].first+1][coord[1].second] || coord[1].first + 1 >= 10){
                    return false;
                }
                if (occupied[coord[2].first][coord[2].second-1] || coord[2].second - 1 < 0){

                }
                if (occupied[coord[3].first-1][coord[3].second] || coord[3].first - 1  < 0) {
                    return false;
                }
            }
            else {
                if (occupied[coord[0].first-1][coord[0].second] || coord[0].first-1 < 0){
                    return false;
                }
                if (occupied[coord[1].first][coord[1].second - 1] || coord[1].second - 1 < 0){
                    return false;
                }
                if (occupied[coord[2].first-1][coord[2].second+2] || coord[2].first-1 < 0 || coord[2].second + 2 >= 20){
                    return false;
                }
                if (occupied[coord[3].first][coord[3].second+1] || coord[3].second + 1 >= 20){
                    return false;
                }
            }
            break;
        case 2:
            if (state == 0 || state == 2) {
                if (occupied[coord[0].first+2][coord[0].second-2] || coord[0].first+2 >= 10 || coord[0].second - 2 < 0){
                    return false;
                }
                if (occupied[coord[1].first+1][coord[1].second-1] || coord[1].first+1 >= 10 || coord[1].second - 1 < 0){
                    return false;
                }
                if (occupied[coord[3].first - 1][coord[3].second+1] || coord[3].first - 1 < 0 || coord[3].second + 1 >= 20) {
                    return false;
                }
            }
            else {
                if (occupied[coord[0].first-2][coord[0].second+2] || coord[0].first-2 < 0 || coord[0].second + 2 >= 20){
                    return false;
                }
                if (occupied[coord[1].first - 1][coord[1].second + 1] || coord[1].first-1 < 0 || coord[1].second + 1 >= 20){
                    return false;
                }
                if (occupied[coord[3].first + 1][coord[3].second - 1] || coord[3].first+1 >= 10 || coord[3].second - 1 < 0){
                    return false;
                }
            }
            break;
        case 3:
            if (state == 0) {

            }
            else if (state == 1) {

            }
            else if (state == 2) {
                
            }
            else {
                
            }
            break;
        case 4:
            if (state == 0) {

            }
            else if (state == 1) {

            }
            else if (state == 2) {
                
            }
            else {
                
            }
            break;
        case 5:
            if (state == 0 || state == 2) {
                if (occupied[coord[0].first+1][coord[0].second] || coord[0].first+1 >= 10){
                    return false;
                }
                if (occupied[coord[1].first][coord[1].second+1] || coord[1].second + 1 >= 20){
                    return false;
                }
                if (occupied[coord[2].first+1][coord[2].second-2] || coord[2].first + 1 >= 10 || coord[2].second < 0){

                }
                if (occupied[coord[3].first][coord[3].second-1] || coord[3].second - 1  < 0) {
                    return false;
                }
            }
            else {
                if (occupied[coord[0].first-1][coord[0].second] || coord[0].first-1 < 0){
                    return false;
                }
                if (occupied[coord[1].first][coord[1].second - 1] || coord[1].second - 1 < 0){
                    return false;
                }
                if (occupied[coord[2].first-1][coord[2].second+2] || coord[2].first-1 < 0 || coord[2].second + 2 >= 20){
                    return false;
                }
                if (occupied[coord[3].first][coord[3].second+1] || coord[3].second + 1 >= 20){
                    return false;
                }
            }
            break;
    }
    return true;
}

bool Block::CheckBoundaries(bool &end, bool occupied[10][20]){
    if(IsKeyPressed(KEY_A)){
        for(int i = 0; i < size; i++){
            if(coord.at(i).first <= 0){
                coord.at(i).first = 0;
                end = false;
                return false;
            }
            if(occupied[coord.at(i).first-1][coord.at(i).second] == true){
                return false;
            }
        }
    }
    if(IsKeyPressed(KEY_D)){
        for(int i = 0; i < size; i++){
            if(coord.at(i).first >= 9){
                coord.at(i).first = 9;
                end = false;
                return false;
            }
            if(occupied[coord.at(i).first+1][coord.at(i).second] == true){
                return false;
            }
        }
    }

    for(int i = 0; i < size; i++){
        if(coord.at(i).second >= 19){
            coord.at(i).second = 19;
            end = true;
            return false;
        }
        if(occupied[coord.at(i).first][coord.at(i).second + 1] == true){
            end = true;
            return false;
        }
    }

    return true;
}

