#ifndef PLATO_H_INCLUDED
#define PLATO_H_INCLUDED

#include "funciones.h"
#include "cuadro.h"

// Declaraciones

struct plato{

    int id;
    char nombre[50];
    float costoPrep;
    float valorVenta;
    int tiempoPrep;
    int idRest;
    int comRest;
    int idCat;
    bool estado;

};

const char *PATH_PLATO = "platos.dat";

void menuPlatos();
void nuevo_plato();
void editar_plato();
void listar_plato_id();
void platos_resto();
void listar_plato(plato);
void listar_todos();
bool eliminar_plato();
bool cargar_plato(plato *);
bool guardar_plato(plato);
int buscar_plato(int);
plato leer_plato(int);
int cantidad_platos();
bool sobrescribir_plato(plato, int);
int buscar_plato_resto(int);

// Definiciones

void platos(){

        int opc;
        system("COLOR 1B");

        while(true){
        cls();
        menuPlatos();

        cout << "Ingresar opci\242n: ";
        cin >> opc;

        switch(opc){
            case 1:
                nuevo_plato();
            break;
            case 2:
                editar_plato();
            break;
            case 3:
                listar_plato_id();
            break;
            case 4:
                platos_resto();
            break;
            case 5:
                listar_todos();
            break;
            case 6:
                eliminar_plato();
            break;
            case 0:
                return;
            break;
            default:
                error();
            break;
        }
    }
}

// Layout Manú Platos
void menuPlatos(){
    cuadro(4, 1, 38, 15);
    gotoxy(18,3);
    cout << "MENU PLATOS" << endl;
    gotoxy(8,5);
    cout << "1) Nuevo Plato" << endl;
    gotoxy(8,6);
    cout << "2) Modificar Plato" << endl;
    gotoxy(8,7);
    cout << "3) Listar Plato por ID" << endl;
    gotoxy(8,8);
    cout << "4) Platos por Restaurant" << endl;
    gotoxy(8,9);
    cout << "5) Listar todos los Platos" << endl;
    gotoxy(8,10);
    cout << "6) Eliminar Plato" << endl;
    gotoxy(8,12);
    cout << "0) Volver al Menu Principal" << endl << endl;
    gotoxy(8,14);
}

// Cargar nuevo plato
void nuevo_plato(){
    cls();
    plato reg;
    if (cargar_plato(&reg)){
        if (guardar_plato(reg)){
            cout << "Plato cargado correctamente."<<endl;
            system("pause");
        }
        else{
            cout << "No se pudo guardar el plato en el archivo."<<endl;
            system("pause");
        }
    }
    else{
        cout << "No se pudo cargar el plato." <<endl;
        system("pause");
        return;
    }
}

// Solicitar datos del plato
bool cargar_plato(plato *p){

    cout << "ID: ";
    cin >> p->id;

    int i;
    i = buscar_plato(p->id);
    if (i>=0){
        cout<<"Plato ya existente."<<endl;
        return false;
    }

    if (p->id < 0){
        cout<<"El ID no puede ser negativo."<<endl;
        return false;
    }

    cout << "Nombre: ";
    cin.ignore();
    cin.getline(p->nombre, 50);

    cout << "Costo de Preparaci\242n: ";
    cin  >> p->costoPrep;

    if (p->costoPrep < 0){
        cout<<"El costo de preparacion no puede ser negativo."<<endl;
        return false;
    }

    cout << "Valor de Venta: ";
    cin  >> p->valorVenta;

    if (p->valorVenta < 0){
        cout<<"El Valor de Venta no puede ser negativo."<<endl;
        return false;
    }
    else if (p->valorVenta < p->costoPrep){
        cout<<"El Valor de Venta no puede ser menor al costo de la preparacion."<<endl;
        return false;
    }

    cout << "Tiempo de Preparaci\242n: ";
    cin  >> p->tiempoPrep;

    if (p->tiempoPrep < 0){
        cout<<"El Tiempo de Preparacion no puede ser negativo."<<endl;
        return false;
    }

    cout << "ID de Restaurante: ";
    cin  >> p->idRest;

    if (p->tiempoPrep < 0){
        cout<<"El ID de restaurante no puede ser negativo."<<endl;
        return false;
    }

    cout << "Comisi\242n de Restaurante: %";
    cin  >> p->comRest;

    if (p->comRest < 0 || p->comRest > 100){
        cout<<"La comision de restaurante ndebe ser un numero entre 0 y 100."<<endl;
        return false;
    }

    cout << "ID de la Categoria: ";
    cin  >> p->idCat;

    if (p->idCat < 0){
        cout<<"El ID de la Categoria no puede ser negativo."<<endl;
        return false;
    }

    p->estado = true;

    return true;
}

// Guardar plato en archivo - Si no existe el archivo se crea
bool guardar_plato(plato reg){
    bool guardo;
    FILE *p;
    p = fopen(PATH_PLATO, "ab");
    if (p == NULL){
        return false;
    }
    guardo = fwrite(&reg, sizeof(plato), 1, p);
    fclose(p);
    return guardo;
}

// Buscar producto por ID
int buscar_plato(int id_buscado){
    plato reg;
    int i=0;
    FILE *p;
    p = fopen(PATH_PLATO, "rb");
    if (p == NULL){
        return -2;
    }
    while (fread(&reg, sizeof(plato), 1, p)){
        if (reg.id == id_buscado){
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

// Solicitar ID y modificar un lplato existente
void editar_plato(){
    system("cls");
    int id_buscado, pos;
    cout << "ID a modificar: ";
    cin >> id_buscado;
    pos = buscar_plato(id_buscado);
    if (pos >= 0){
        plato reg = leer_plato(pos);
        cout << endl;
        listar_plato(reg);
        cout << endl << "Nuevo Valor de Venta: ";
        cin >> reg.valorVenta;
        cout << endl << "Nuevo Tiempo de Preparacion: ";
        cin >> reg.tiempoPrep;
        if (sobrescribir_plato(reg, pos)){
            cout << "Plato modificado."<<endl;
            system("pause");
        }
        else {
            cout << "No se modific\242 el plato."<<endl;
            system("pause");
        }
    }
    else {
        cout << "No existe el plato."<<endl;
        system("pause");
    }
}

//Reemplazar registro
bool sobrescribir_plato(plato reg, int pos){
    bool escribio;
    FILE *p;
    p = fopen(PATH_PLATO, "rb+");
    if (p == NULL){
        return false;
    }
    fseek(p, pos * sizeof(plato), SEEK_SET);
    escribio = fwrite(&reg, sizeof(plato), 1, p);
    fclose(p);
    return escribio;
}

// Soilicitar ID y listar platos por ID
void listar_plato_id(){
    system("cls");
    int id_buscado, pos;
    cout << "ID a buscar: ";
    cin >> id_buscado;
    pos = buscar_plato(id_buscado);
    if (pos >= 0){
        plato reg = leer_plato(pos);
        system("cls");
        cout<<"--------- ID: "<<reg.id<<" ---------"<<endl;
        listar_plato(reg);
        cout<<"-------------------------"<<endl;
        cout<<endl;
        system("pause");
    }
    else{
        system("cls");
        cout << "No existe el ID buscado" << endl;
        system("pause");
    }
}

// Solicitar ID de Restaurant y listar platos de dicho ID Restaurant
void platos_resto(){
system("cls");
    int id_buscado, pos,i;
    cout << "ID del restaurante a buscar: ";
    cin >> id_buscado;
    if (pos >= 0){
        plato reg;
        FILE *p;
        p = fopen(PATH_PLATO, "rb");
        system("cls");
    while (fread(&reg, sizeof(plato), 1, p)){
        if (reg.idRest == id_buscado){
            cout<<"--------- ID Restaurante: "<<id_buscado<<" ---------"<<endl;
            listar_plato(reg);
            cout<<"------------------------------------"<<endl;
            cout<<endl;
        }
            i++;
        }
        system("pause");
    }
    else{
        system("cls");
        cout << "No existe el ID del restaurante buscado" << endl;
        system("pause");
    }
}

plato leer_plato(int pos){
    plato reg;
    FILE *p;
    p = fopen(PATH_PLATO, "rb");
    if (p == NULL){
        reg.id = -1;
        return reg;
    }
    fseek(p, pos * sizeof(plato),SEEK_SET);
    fread(&reg, sizeof(plato), 1, p);
    fclose(p);
    return reg;
}

//Obtener cantidad de registros
int cantidad_platos(){
    int bytes, cr;
    FILE *p;
    p = fopen(PATH_PLATO, "rb");
    if (p == NULL){
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cr = bytes / sizeof(plato);
    fclose(p);
    return cr;
}

//Listar todos los registros del archivo
void listar_todos(){
    cls();
    plato reg;
    int cant = cantidad_platos(), i;
    for(i=0; i<cant; i++){
        cout << "------- Plato Numero: " << i+1 << "-------------"<< endl;
        reg = leer_plato(i);
        listar_plato(reg);
        cout << endl;
    }
    system("pause");
}

// Layout de listado de platos
void listar_plato(plato reg){

    if (reg.estado == true){

    cout << "ID: " << reg.id << endl;
    cout << "Nombre: " << reg.nombre << endl;
    cout << "Costo de Preparaci\242n: " << reg.costoPrep << endl;
    cout << "Valor de Venta: $" << reg.valorVenta << endl;
    cout << "Tiempo de Preparaci\242n: " << reg.tiempoPrep << endl;
    cout << "ID de Restaurante: " << reg.idRest << endl;
    cout << "Comisi\242n de Restaurante: %" << reg.comRest << endl;
    cout << "ID de la Categoria: " << reg.idCat << endl;
    }
}

// Solicitar ID y realizar baja lógica del plato
bool eliminar_plato(){
    system("cls");
    int id_buscado, pos;
    char borrar;

    cout << "ID del plato a eliminar: ";
    cin >> id_buscado;
    pos = buscar_plato(id_buscado);
    if (pos >= 0){
        plato reg = leer_plato(pos);
        cout << endl;
        listar_plato(reg);
        cout << "Desea eliminar el plato seleccionado? (S/N): ";
        cin >> borrar;

        if (borrar=='S' or borrar=='s'){
            FILE *p;
            p = fopen(PATH_PLATO, "rb+");
            if (p == NULL){
                return false;
            }
            fread(&reg, sizeof(reg), 1, p);
            while(!feof(p)){
                if(reg.id == id_buscado){
                    fseek(p, ftell(p) - sizeof(reg), SEEK_SET);
                    reg.estado = false;
                    fwrite(&reg, sizeof(reg), 1, p);
                    break;
                }
                fread(&reg, sizeof(reg), 1, p);
            }
            fclose(p);
        cout << endl;
        cout << "Plato eliminado." << endl;
        system("pause");
        }

        else if (borrar=='N' or borrar=='n'){

            cout << endl;
            cout << "Acci\242n cancelada." << endl;;
            system("pause");
        }
        else {
            error();
        }
    }
    else{
    system("cls");
    cout << endl;
    cout << "El ID es incorrecto." << endl;;
    system("pause");
    }
}

#endif // PLATO_H_INCLUDED
