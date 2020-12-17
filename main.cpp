//AUTOR: Jesús Armando Báez Camacho
#include "window.h"
#include "CapturaSegura.h"
#include <iostream>

using std::cout;
using std::cin;

const int WIDTH = 800, HEIGHT = 600;

int menu();

#undef main
int main(int argv, char** args)
{
    int opcion,xi,xf,yi,yf,p,a,b,r;
    Window window("Plotter", 800, 800);
    window.StartWindow();
    window.poolEvents();
    window.clear();
    window.Draw();
    do{ 
        cout<<"Graficas.\n\n"<<"Select an option\n\n"<<"0.Exit.\n"<<"1.Line\n"<<"2.Circumference\n"<<"3.Ellipse\n"<<"4.Parabola\n"<<"5.Hyperbola\n";
        opcion = menu();
        window.poolEvents();
        window.clear();
        switch(opcion){
            
            case 1:
                xi = capturarEntero("\nWrite the initial x: ");
                yi = capturarEntero("\nWrite the initial y: ");
                xf = capturarEntero("\nWrite the final x: ");
                yf = capturarEntero("\nWrite the final y: ");
                window.Line(xi,yi,xf,yf);
                break;
            case 2:
                r = capturarEntero("\nWrite the radius: ");
                while (r < 0){
                    cout << "\nThe radius can't be negative. Try Again. ";
                    r = capturarReal("\nWrite the radius: ");
                }
                window.Circumference(r);
                break;
            case 3:
                a = capturarEntero("\nWrite a: ");
                b = capturarEntero("\nWrite b: ");
                window.Ellipse(a,b);
                break;
            case 4:
                p = capturarEntero("\nWrite p: ");
                while (p < 0){
                    cout << "\np Can't be negative. ";
                    p = capturarReal("\nWrite p: ");
                }
                window.Parabola(p);
                break;
            case 5:  
                a = capturarEntero("\nWrite a: ");
                b = capturarEntero("\nWrite b: ");
                window.Hyperbola(a,b);
                break;
        }
        window.Draw();
    }while(opcion != 0);
    
    return EXIT_SUCCESS;
}

//  Función menú *************************************************************
int menu()
{
    int opcion;
    do{
        opcion = capturarEntero("Number Option: ");

        if(opcion < 0 || opcion > 5)
            cout << "Error: you must select an option from the menu.\n";

    }while(opcion < 0 || opcion > 5);

    return opcion;
}
//  Fin Función menú *********************************************************
/*
g++ main.cpp -o prog -I C:\\libSDL\\include -L C:\\libSDL\\lib -lmingw32 -lSDL2main -lSDL2
*/