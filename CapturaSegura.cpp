#include <limits>
#include <windows.h>
#include <iostream>

using std::cout;
using std::cin;
using std::numeric_limits;

//  Función capturarEntero *************************************************************
int capturarEntero(const char solicitud[])
{
    int n;
    while(true){
        cout << solicitud;
        cin >> n;

        if(cin.bad()){
            cout << "Ocurri\242 un error irrecuperable en el flujo de entrada. \n";
            system("pause");
            return 0;
        }
        if(cin.fail()){
            system("CLS");
            cout << "Error: no es un n\243mero. Intentelo de nuevo. \n\n";
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            continue;
        }
        return n;
    }
}
//  Fin Función capturarEntero *********************************************************


//  Función capturarReal *************************************************************
double capturarReal(const char solicitud[])
{
    double n;
    while(true){
        cout << solicitud;
        cin >> n;

        if(cin.bad()){
            cout << "Ocurri\242 un error irrecuperable en el flijo de entrada. \n";
            system("pause");
            return 0;
        }
        if(cin.fail()){
            cout << "Error: no es un n\243mero. Intentelo de nuevo. \n\n";
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            continue;
        }
        return n;
    }
}

//  Fin Función capturarReal *******************************************************