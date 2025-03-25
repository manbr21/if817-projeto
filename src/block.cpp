#include "block.h"
//#include <cstdlib>
#include <raylib.h>

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
        WaitTime(0.001);
    }
}

void Block::Move(bool occupied[10][20]){
	int data=0x0;
	
	int fd = open("/dev/mydev", O_RDWR);
	
	ioctl(fd, RD_PBUTTONS);
	read(fd, &data, 1);
	
	bool press_a = (data & 0b1000) == 0;
	bool press_d = (data & 0b0010) == 0; 
	bool press_s = (data & 0b0100) == 0; 
	bool press_w = (data & 0b0001) == 0; 
	
    if(IsKeyPressed(KEY_A) || press_a){
        for(int i = 0; i < size; i++){
            coord.at(i).first--;
        }
    }
    if(IsKeyPressed(KEY_D) || press_d){
        for(int i = 0; i < size; i++){
            coord.at(i).first++;
        }
    }
    if (IsKeyDown(KEY_S) || press_s){
        Fall();
    }
    if (IsKeyPressed(KEY_W) || press_w) {
        if (CanRotate(occupied)) {
            Rotate();
        }
    }
    
    close(fd);
}

void Block::Rotate() {
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
                if (OutOfBounds(occupied,coord[0].first+1,coord[0].second-1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first-1,coord[2].second+1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first-1,coord[3].second-1)) {
                    return false;
                }
            }
            else if (state == 1) {
                if (OutOfBounds(occupied,coord[0].first+1,coord[0].second+1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first-1,coord[2].second-1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first+1,coord[2].second-1)) {
                    return false;
                }
            }
            else if (state == 2) {
                if (OutOfBounds(occupied,coord[0].first-1,coord[0].second+1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first+1,coord[2].second-1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first+1,coord[2].second+1)) {
                    return false;
                }
            }
            else {
                if (OutOfBounds(occupied,coord[0].first-1,coord[0].second-1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first+1,coord[2].second+1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first-1,coord[2].second+1)) {
                    return false;
                }
            }
            break;
        case 1:
            if (state == 0 || state == 2) {
                if (OutOfBounds(occupied,coord[0].first+2,coord[0].second-1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first+1,coord[1].second-1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first,coord[2].second-1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first-1,coord[3].second)) {
                    return false;
                }
            }
            else {
                if (OutOfBounds(occupied,coord[0].first-2,coord[0].second+1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first-1,coord[1].second)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first,coord[2].second+1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first+1,coord[3].second)){
                    return false;
                }
            }
            break;
        case 2:
            if (state == 0 || state == 2) {
                if (OutOfBounds(occupied,coord[0].first+2,coord[0].second-2)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first+1,coord[1].second-1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first-1,coord[3].second+1)) {
                    return false;
                }
            }
            else {
                if (OutOfBounds(occupied,coord[0].first-2,coord[0].second+2)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first-1,coord[1].second+1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first+1,coord[3].second-1)){
                    return false;
                }
            }
            break;
        case 3:
            if (state == 0) {
                if (OutOfBounds(occupied,coord[0].first+2,coord[0].second-1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first+1,coord[1].second)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first,coord[2].second+1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first+1,coord[3].second-2)) {
                    return false;
                }
            }
            else if (state == 1) {
                if (OutOfBounds(occupied,coord[0].first,coord[0].second+2)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first-1,coord[1].second+1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first-2,coord[2].second)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first+1,coord[3].second+1)) {
                    return false;
                }
            }
            else if (state == 2) {
                if (OutOfBounds(occupied,coord[0].first-2,coord[0].second+1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first-1,coord[1].second)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first,coord[2].second-1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first-1,coord[3].second+2)) {
                    return false;
                }
            }
            else {
                if (OutOfBounds(occupied,coord[0].first,coord[0].second-2)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first+1,coord[1].second-1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first+2,coord[2].second)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first-1,coord[3].second-1)) {
                    return false;
                }
            }
            break;
        case 4:
            if (state == 0) {
                if (OutOfBounds(occupied,coord[0].first + 2,coord[0].second-1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first+1,coord[1].second)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first,coord[2].second+1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first-1,coord[3].second)) {
                    return false;
                }
            }
            else if (state == 1) {
                if (OutOfBounds(occupied,coord[0].first,coord[0].second+2)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first-1,coord[1].second+1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first-2,coord[2].second)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first-1,coord[3].second-1)) {
                    return false;
                }
            }
            else if (state == 2) {
                if (OutOfBounds(occupied,coord[0].first-2,coord[0].second)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first-1,coord[1].second-1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first,coord[2].second-2)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first+1,coord[3].second-1)) {
                    return false;
                }
            }
            else {
                if (OutOfBounds(occupied,coord[0].first,coord[0].second-1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first+1,coord[1].second)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first+2,coord[2].second+1)) {
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first+1,coord[3].second+2)) {
                    return false;
                }
            }
            break;
        case 5:
            if (state == 0 || state == 2) {
                if (OutOfBounds(occupied,coord[0].first+1,coord[0].second)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first,coord[1].second+1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first+1,coord[2].second-2)){

                }
                if (OutOfBounds(occupied,coord[3].first,coord[3].second-1)) {
                    return false;
                }
            }
            else {
                if (OutOfBounds(occupied,coord[0].first-1,coord[0].second)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[1].first,coord[1].second-1)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[2].first-1,coord[2].second+2)){
                    return false;
                }
                if (OutOfBounds(occupied,coord[3].first,coord[3].second+1)){
                    return false;
                }
            }
            break;
    }
    return true;
}

bool Block::CanFall(){
    for(int i = 0; i < size; i++){
        if(coord.at(i).second == 19){
            coord.at(i).second = 19;
            end = true;
            return false;
        }
    }
    return true;
}

bool Block::OutOfBounds(bool occupied[10][20],int x, int y) {
    if (x < 0 || x >= 10 || y < 0 || y >= 20 || occupied[x][y]){
        return true;
    }

    return false;
}


bool Block::CanMove(bool &end, bool occupied[10][20]){

	int data=0x0;
	
	int fd = open("/dev/mydev", O_RDWR);
	
	ioctl(fd, RD_PBUTTONS);
	read(fd, &data, 1);
	
	bool press_a = (data & 0b1000) == 0;
	bool press_d = (data & 0b0010) == 0; 
	bool press_s = (data & 0b0100) == 0; 
	bool press_w = (data & 0b0001) == 0; 

    if(IsKeyPressed(KEY_A) || press_a){
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
    if(IsKeyPressed(KEY_D) || press_d ){
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
    
    close(fd);
    
    return true;
}

