#include <iostream>
#include "board.h"

Board *board;

// runs on each frame
void update(){
    // get command input
    board->render();
}

int main(){
    std::cout << "hola mundo" << '\n';
    return 0;
}