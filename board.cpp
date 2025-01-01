#include "board.h" 
#include <cstdlib>
#include <ctime> // for seeding random number generator

void fisherYatesShuffle(std::vector<Piece *>& elements) {
    // seed the random number generator
    std::srand(std::time(nullptr));

    for (size_t i = elements.size() - 1; i > 0; --i) {
        // generate a random index in the range [0, i]
        size_t j = std::rand() % (i + 1);

        // swap elements[i] with elements[j]
        std::swap(elements[i], elements[j]);
    }
}

Board::Board() : _width(10), _height(20), countOnRow(20), gameBoard(_height, std::vector<int>(_width)) {}

void Board::refillQueue() {
    if(_next.size() < 7){
        // generate identity permutation
        std::vector<Piece *> vec = {new TPiece(), new OPiece(), new IPiece(), new SPiece(), new LPiece(), new ZPiece(), new JPiece()};
        //fisherYatesShuffle(vec);
        for(Piece *p: vec) _next.push_back(p);
    }
}

void Board::addT() {
    _next.push_back(new TPiece());
}

int Board::get(int row, int col) {
    return gameBoard[row][col];
}

// deprecated
void Board::clearLine(int row) {
    for(int j = 0; j<_width; j++){
        gameBoard[row][j] = 0;
    }
    countOnRow[row] = 0;
}

void Board::clearLines() {
    std::vector<std::vector<int>> newGameBoard(_height, std::vector<int>(_width, 0));
    std::vector<int> newCountOnRow(_height);
    int curr = _height - 1;
    for(int i = _height - 1; i>=0; i--){
        std::cout << i << " " << countOnRow[i] << " " << _width << '\n';
        if(countOnRow[i] < _width){
            newCountOnRow[curr] = countOnRow[i];
            newGameBoard[curr] = gameBoard[i];
            curr--;
        }
    }
    for(int i = _height - 1; i>=0; i--){
        gameBoard[i] = newGameBoard[i]; 
        countOnRow[i] = newCountOnRow[i];
    }
    std::cout << "new countonrow: ";
    for(int i = 0; i<_height; i++){
        std::cout << countOnRow[i] << " ";
    }
    std::cout << '\n';
}

// draws the board on a pixel canvas.
void Board::render() {
}

void Board::display(std::vector<std::vector<char>>& sc) {
    std::vector<std::vector<char>> screen(20, std::vector<char>(10));
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            //std::cout << i << " " << j << '\n';
            if (gameBoard[i][j]) screen[i][j] = gameBoard[i][j];
            else screen[i][j] = '_';
        }
    }
    Piece *p = getCurrentPiece();
    for(int i = 0; i<p->getSize(); i++){
        for(int j = 0; j<p->getSize(); j++){
            if(p->getMaskAt(i, j)) screen[i+p->getPosX()][j+p->getPosY()] = 'o';
        }
    }
    sc = screen;
}

bool Board::isInsideBoard(int i, int j) {
    return (i >= 0 && i < _height && j >= 0 && j < _width);
}

bool Board::canPlace(Piece *p) {
    int sz = p->getSize();
    for(int i = 0; i<sz; i++){
        for(int j = 0; j<sz; j++){
            int ii = p->getPosX() + i;
            int jj = p->getPosY() + j;
            if(p->getMaskAt(i, j)){ // only check blocks
                // case 1: out of bounds
                // case 2: block used
                if(!isInsideBoard(ii, jj)) return 0;
                if(gameBoard[ii][jj]) return 0;
            }
        }
    }
    return 1;
}

void Board::placeCurrent() {
    Piece *p = _next.front();
    if(!canPlace(p)) return; // cant place => do nothing
    int sz = p->getSize();
    bool isAnyLineCleared = 0;
    for(int i = 0; i<sz; i++){
        for(int j = 0; j<sz; j++){
            int ii = p->getPosX() + i;
            int jj = p->getPosY() + j;
            if(p->getMaskAt(i, j)){
                gameBoard[ii][jj] = p->getId();
                countOnRow[ii]++;
                if(countOnRow[ii] == 10){
                    isAnyLineCleared = 1;
                }
            }
        }
    }
    std::cout << "countOnRow: ";
    for(int x: countOnRow){
        std::cout << x << " ";
    }
    std::cout << '\n';
    if(isAnyLineCleared){
        std::cout << "clearLines() called" << '\n';
        clearLines();
    }
    _next.pop_front();
    refillQueue();
    _canHold = 1;
}

// piece handling methods
// returns 1 if movement was successful
bool Board::moveCurrent(char dir){
    Piece *p = _next.front(); // get current piece
    int dx = 0;
    int dy = 0;
    // change coords
    switch(dir){
        case 'L':
            dy = -1;
            break;
        case 'U':
            dx = -1;
            break;
        case 'R':
            dy = 1;
            break;
        case 'D':
            dx = 1;
            break;
        default:
            return 0;
    }
    p->setPosX(p->getPosX() + dx);
    p->setPosY(p->getPosY() + dy);
    // if we can't move, undo the movement
    if(canPlace(p) == 0){
        p->setPosX(p->getPosX() - dx);
        p->setPosY(p->getPosY() - dy);
        return 0;
    }
    // else, we're done
    return 1;
}

void Board::hardDropCurrent(){
    while(moveCurrent('D')){}
    placeCurrent();
}

void Board::rotateR(){
    Piece *p = _next.front();
    p->rotateR();
    if(canPlace(p) == 0){
        p->rotateL();
        return;
    }
}

void Board::rotateL(){
    Piece *p = _next.front();
    p->rotateL();
    if(canPlace(p) == 0){
        p->rotateR();
        return;
    }
}

Piece *Board::getCurrentPiece(){
    return _next.front();
}

void Board::init(){
    refillQueue();
}

void Board::hold(){
    if(_canHold == 0) return;
    Piece *u = getCurrentPiece();
    _next.pop_front();
    Piece *v = getCurrentPiece();
    _next.pop_front();
    _next.push_front(u);
    _next.push_front(v);
    _canHold = 0;
}

int Board::getWidth(){
    return _width;
}

int Board::getHeight(){
    return _height;
}