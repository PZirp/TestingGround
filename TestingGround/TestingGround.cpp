// TestingGround.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Point.h"
#include <vector>
#include "OpenGLInit2.h"

int goGetter(int a);

int main()
{
    std::cout << "Hello World!\n\n Dammi un numero: ";

    /*int a = 0;
    //std::cin >> a;
    goGetter(a);

    if (a >= 4) {
        std::cout << "Alla grande!\n";
    }
    else {
        std::cout << "YEET!\n";
    }*/

    int arr[5];

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    int* posUno = &arr[1];

    //std::cout << "Puntatore posUno " << *posUno << " array 1 " << arr[1] << "\n";
    //std::cout << "Puntatore posUno++ " << (*posUno)++ << " array 2 " << arr[2] << "\n";

    Point prova(1, 2);

    std::cout << "X: " << prova.getX() << " Y: " << prova.getY() << "\n";   

    prova.setX(122);
    prova.setY(2300);

    std::cout << "X: " << prova.getX() << " Y: " << prova.getY() << "\n";

   // int *coords = prova.getCoordinates();

   // std::cout << "Coords X: " << *coords << " X: " << prova.getX() << " Coords Y: " << *(coords++)<< " Y " << prova.getY() << "\n";

    std::vector<int> c = prova.getCoordinates();
    std::cout << "Bubi X: " << c[0] << " Y: " << c[1] << "\n"; 

    OpenGLInit2::openGLInit2();
    return 0;
}

int goGetter(int a) {
    std::cin >> a;
    return a;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
