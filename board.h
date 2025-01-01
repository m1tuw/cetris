#include <bits/stdc++.h>
#include <deque>
#include "piece.cpp"

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

// interface
class Board{
    protected:
        int _width;
        int _height;
        std::vector<std::vector<int>> gameBoard;
        std::deque<Piece*> _next;
        Piece current;
        bool _canHold = 1;
        void refillQueue();
        void clearLines(); // drop floating pieces
        void clearLine(int row);

    public:
        std::vector<int> countOnRow; // optimization
        Board();
        void addT();

        // getters
        int get(int i, int j);
        int getWidth();
        int getHeight();
        Piece *getCurrentPiece();

        // board mechanics and game logic
        void render();
        void display(std::vector<std::vector<char>>& sc);
        bool canPlace(Piece *p);
        bool isInsideBoard(int i, int j);

        // game initialization
        void init();

        // piece handling methods
        void hold();
        void placeCurrent();
        bool moveCurrent(char dir);
        void hardDropCurrent();
        void rotateR();
        void rotateL();

};