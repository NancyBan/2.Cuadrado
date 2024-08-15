#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cstdlib>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Cuadrado {
private:
    int lado;

public:
    Cuadrado(int lado) : lado(lado) {}

    int obtenerLado() const {
        return lado;
    }

    void Dibujar(int posX, int posY) const {
        for (int fila = 0; fila < lado; fila++) {
            gotoxy(posX, posY + fila);
            for (int columna = 0; columna < lado; columna++) {
                std::cout << "* ";
            }
        }
    }

    void Borrar(int posX, int posY) const {
        for (int fila = 0; fila < lado; fila++) {
            gotoxy(posX, posY + fila);
            for (int columna = 0; columna < lado; columna++) {
                std::cout << "  ";
            }
        }
    }
};


void Actualizar(Cuadrado& cuadro, int& posX, int& posY, int anchoMax, int altoMax) {
    if (_kbhit()) {
        char tecla = _getch();
        int deltaX = 0, deltaY = 0;

        switch (tecla) {
            case 'a':
                //si x no esta en el borde izquierdo, se mueve a  la izquierda
                deltaX = (posX > 0) ? -1 : 0;
                break;
            case 's':
                //si y es menor al borde superior considerando la altura deel cuadro, se mueve hacia arriba
                deltaY = (posY < altoMax - cuadro.obtenerLado()) ? 1 : 0;
                break;
            case 'd':
                //si x no esta en el borde derecho considerando el ancho del cuadrado, se mueve hacia la derecha
                deltaX = (posX < anchoMax - cuadro.obtenerLado() * 2) ? 1 : 0;
                break;
            case 'w':
                //si y no esta en el borde inferior, se mueve hacia arriba
                deltaY = (posY > 0) ? -1 : 0;
                break;
            case 27:
                exit(0);
        }

        if (deltaX != 0 || deltaY != 0) {
            cuadro.Borrar(posX, posY);
            posX += deltaX;
            posY += deltaY;
        }
    }
}

void Mostrar(const Cuadrado& cuadro, int posX, int posY) {
    cuadro.Dibujar(posX, posY);
}

int main() {
    int x = 0, y = 0, lado = 0;
    std::cout << "Ingrese la longitud del lado del cuadrado: ";
    std::cin >> lado;


    system("cls");

    Cuadrado cuadrado(lado);

    const int anchoMax = 80;
    const int altoMax = 25;

    while (true) {
        Actualizar(cuadrado, x, y, anchoMax, altoMax);
        Mostrar(cuadrado, x, y);
        Sleep(100);
    }

    return 0;
}