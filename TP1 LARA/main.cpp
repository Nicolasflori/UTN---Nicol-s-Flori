/*------------------------------------

Trabajo Práctico N°1
Archivos
Laboratorio de Computación II - 2020

Alumno: Nicolás Flori

------------------------------------*/

#include <iostream>
using namespace std;
#include <cstdio>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "rlutil.h"
using namespace rlutil;

#include "funciones.h"
#include "plato.h"
#include "cuadro.h"

int main(){

    int opc;
    bool continuar = true;
    system("COLOR 5e");
    cuadro(4, 2, 58, 15);
    presentacion();

    while (continuar == true){

        system("COLOR 3B");
        cuadro(4, 1, 38, 15);
        menuPrincipal();
        ShowConsoleCursor(true);

        cout << "Ingresar opci\242n: ";
        cin >> opc;

        switch (opc){
            case 1:
                system("cls");
                platos();
                system("cls");
            break;
            case 2:

            break;
            case 3:

            break;
            case 4:

            break;
            case 5:

            break;
            case 6:

            break;
            case 0:
                system("cls");
                continuar = fsalir(continuar);
                system("cls");
            break;
            default:
                error();
            break;
        }
    }
    pantalla_fin();
    return 0;
}
