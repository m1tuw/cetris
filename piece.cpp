#include "piece.h"
#include <bits/stdc++.h>

void rotateCCW(std::vector<std::vector<bool>>& mat){
    int n = mat.size();
    for(int i = 0; i<n; i++){
        reverse(mat[i].begin(), mat[i].end());
    }
    for(int i = 0; i<n; i++){
        for(int j = i; j<n; j++){
            std::swap(mat[i][j], mat[j][i]);
        }
    }
}

void Piece::loadRotations(){
    for(int i = 0; i<4; i++){
        _rotatedMasks[i] = _mask;
        rotateCCW(_mask);
    }
    return;
}

void Piece::rotateR(){_rotation+=3; _rotation%=4; _mask = _rotatedMasks[_rotation];}
void Piece::rotateL(){_rotation++; _rotation%=4; _mask = _rotatedMasks[_rotation];}

// Setters
void Piece::setPosX(int x){_posX = x;}
void Piece::setPosY(int y){_posY = y;}
void Piece::setRotation(int angle){_rotation = angle%4;}

// Getters
int Piece::getPosX(){return _posX;}
int Piece::getPosY(){return _posY;}
int Piece::getRotation(){return _rotation;}
int Piece::getSize(){return _size;}
int Piece::getId(){return _id;}
ColorRGB Piece::getColor(){return _color;}
bool Piece::getMaskAt(int i, int j){return _mask[i][j];}
void Piece::displayMask(){
    for(int i = 0; i<_size; i++){
        for(int j = 0; j<_size; j++){
            std::cout << _mask[i][j];
        }
        std::cout << '\n';
    }
}