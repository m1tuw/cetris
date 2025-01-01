#include <bits/stdc++.h>
#include <ncurses.h>
#include <GL/glut.h>

#include "board.cpp"

#define EXIT_GAME 113 // Q
#define SOFT_DROP KEY_DOWN
#define HARD_DROP 32 // SPACE
#define ROTATE_LEFT 122 // Z
#define ROTATE_RIGHT 120 // X
#define MOVE_LEFT KEY_LEFT
#define MOVE_RIGHT KEY_RIGHT
#define HOLD_CURRENT 99 // C

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
GLubyte pixels[SCREEN_HEIGHT * SCREEN_WIDTH * 3];
std::vector<ColorRGB> pieceColors(256, {100, 100, 100}); // default color

Board board;
std::vector<std::vector<char>> sc(20, std::vector<char>(10));

void loadColors(){
    pieceColors[(int)('T')] = T_COLOR;
    pieceColors[(int)('S')] = S_COLOR;
    pieceColors[(int)('O')] = O_COLOR;
    pieceColors[(int)('Z')] = Z_COLOR;
    pieceColors[(int)('L')] = L_COLOR;
    pieceColors[(int)('J')] = J_COLOR;
    pieceColors[(int)('I')] = I_COLOR;
}

void clearScreen() {
    clear();
    refresh();
    return;
}

void displayHelp() {
    printw("Instructions: enter q to exit. Other commands:\n\n");
    printw("  l: move left\n");
    printw("  r: move right\n");
    printw("  d: soft drop\n");
    printw("  h: hard drop / place tetromino\n");
    printw("  rr: rotate right\n");
    printw("  ll: rotate left\n");
    printw("\nInput anything to resume...\n");
    refresh();

    std::string tmp;
    std:: cin >> tmp;
}

void initPixels() {
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            int index = (y * SCREEN_WIDTH + x) * 3;
            pixels[index] = (GLubyte)((x + y) % 256); // Red
            pixels[index + 1] = (GLubyte)(x % 256);   // Green
            pixels[index + 2] = (GLubyte)(y % 256);   // Blue
        }
    }
}

void colorPixel(int x, int y, ColorRGB col){
    int index = (y*SCREEN_WIDTH + x)*3;
    pixels[index] = (GLubyte)(col.r);
    pixels[index+1] = (GLubyte)(col.g);
    pixels[index+2] = (GLubyte)(col.b);
}

void drawBlock(int x, int y, ColorRGB col, int sz){
    for(int i = 0; i<sz; i++){
        for(int j = 0; j<sz; j++){
            colorPixel(x+i, y-j, col);
        }
    }
}

// assuming board is a global variable
void drawBoard(){
    int block_size = 20;
    int gap = 2;
    ColorRGB dark_grey = {30, 30, 30};
    ColorRGB blue = {0, 0, 200};
    ColorRGB red = {200, 0, 0};
    
    for(int i = 0; i<20; i++){
        for(int j = 0; j<10; j++){
            char c = sc[i][j];
            ColorRGB selected_color = board.getCurrentPiece()->getColor();
            ColorRGB placed_color = pieceColors[(int)c % 256];
            if(c != '_' && c != 'o') drawBlock(j*(block_size + gap), SCREEN_HEIGHT - 1 - i*(block_size + gap), placed_color, block_size);
            else if(c == 'o') drawBlock(j*(block_size + gap), SCREEN_HEIGHT - 1 - i*(block_size + gap), selected_color, block_size);
            else drawBlock(j*(block_size + gap), SCREEN_HEIGHT - 1 - i*(block_size + gap), dark_grey, block_size);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // rotate 90deg right
    glRasterPos2i(-1, -1); 
    glDrawPixels(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    
    glFlush();
}

void keyPress(unsigned char key, int x, int y) {
    switch (key) {
        case EXIT_GAME:
            exit(0);
            break;
        case HARD_DROP:
            board.hardDropCurrent();
            break;
        case ROTATE_LEFT:
            board.rotateL();
            break;
        case ROTATE_RIGHT:
            board.rotateR();
            break;
        case HOLD_CURRENT:
            board.hold();
            break;
    }
}

void specialKeyPress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            board.moveCurrent('L');
            break;
        case GLUT_KEY_RIGHT:
            board.moveCurrent('R');
            break;
        case GLUT_KEY_DOWN:
            board.moveCurrent('D');
            break;
    }
}

void update(){
    drawBoard();
    board.display(sc);
    glutPostRedisplay();
}

int main(int argc, char** argv){
    loadColors();
    // initialize opengl
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_HEIGHT, SCREEN_WIDTH);
    glutCreateWindow("OpenGL Example");

    board.init();
    drawBoard();

    glutDisplayFunc(display);
    glutIdleFunc(update);

    // kb callbacks
    glutKeyboardFunc(keyPress);
    glutSpecialFunc(specialKeyPress);

    glutMainLoop(); // Enter the event loop

    return 0;
}
