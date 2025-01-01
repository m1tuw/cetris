#include <bits/stdc++.h>
#include <deque>

struct ColorRGB{
    int r, g, b;
};

ColorRGB T_COLOR = {153, 51, 153};
ColorRGB S_COLOR = {119, 179, 0};
ColorRGB O_COLOR = {255, 204, 0};
ColorRGB Z_COLOR = {204, 0, 0};
ColorRGB L_COLOR = {0, 0, 204};
ColorRGB J_COLOR = {255, 153, 0};
ColorRGB I_COLOR = {153, 204, 255};

class Piece{
    protected:
        int _size;
        int _rotation;
        int _posX = 0;
        int _posY = 0;
        int _id = 0;
        ColorRGB _color = {100, 100, 100};
        std::vector<std::vector<bool>> _mask;
        std::vector<std::vector<bool>> _rotatedMasks[4];
        void loadRotations();

    public:
        virtual ~Piece() = default;
        void rotateR();
        void rotateL();
        void setPosX(int x);
        void setPosY(int y);
        void setRotation(int angle);
        int getPosX();
        int getPosY();
        int getRotation();
        int getSize();
        int getId();
        ColorRGB getColor();
        bool getMaskAt(int i, int j);
        void displayMask();
};

class TPiece: public Piece {
    public:
        TPiece(){
            _color = T_COLOR;
            _size = 3;
            _id = (int)('T');
            _mask = {{0, 1, 0},
                     {1, 1, 1},
                     {0, 0, 0}};
            loadRotations();
        }
};

class SPiece: public Piece {
    public:
        SPiece(){
            _color = S_COLOR;
            _size = 3;
            _id = (int)('S');
            _mask = {{0, 0, 0},
                     {0, 1, 1},
                     {1, 1, 0}};
            loadRotations();
        }
};

class OPiece: public Piece {
    public:
        OPiece(){
            _color = O_COLOR;
            _size = 2;
            _id = (int)('O');
            _mask = {{1, 1},
                     {1, 1}};
            loadRotations();
        }
};

class IPiece: public Piece {
    public:
        IPiece(){
            _color = I_COLOR;
            _size = 4;
            _id = (int)('I');
            _mask = {{0, 0, 0, 0},
                     {1, 1, 1, 1},
                     {0, 0, 0, 0},
                     {0, 0, 0, 0}};
            loadRotations();
        }
};

class LPiece: public Piece {
    public:
        LPiece(){
            _color = L_COLOR;
            _size = 3;
            _id = (int)('L');
            _mask = {{0, 0, 0},
                     {1, 0, 0},
                     {1, 1, 1}};
            loadRotations();
        }
};

class ZPiece: public Piece {
    public:
        ZPiece(){
            _color = Z_COLOR;
            _size = 3;
            _id = (int)('Z');
            _mask = {{0, 0, 0},
                     {1, 1, 0},
                     {0, 1, 1}};
            loadRotations();
        }
};

class JPiece: public Piece {
    public:
        JPiece(){
            _color = J_COLOR;
            _size = 3;
            _id = (int)('J');
            _mask = {{0, 0, 0},
                     {0, 0, 1},
                     {1, 1, 1}};
            loadRotations();
        }
};