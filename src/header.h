#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

typedef struct {
    char c1;
    char c2;
} celda;

typedef struct {
    string item;
    int fila;
    int columna;
} conexion;

typedef struct {
    int fila;
    int columna;
    char direccion;
    char c1_substituted;
    char c2_substituted;
} posicion;

posicion jugador;

void dormir(int time_ms);
void read_board(celda tablero[][10], int nfilas);
void read_connections(conexion conexiones[], int tam);
void colocar_jugador(celda tablero[][10]);
void restaurar_celda(celda tablero[][10]);
void mostrar_tablero(celda tablero[][10], int nfilas);
int gestionar_turno();
void avanzar(int dado);
void encontrar_conexion(string text, conexion conexiones[], int tam);
void procesar_nueva_posicion(celda tablero[][10], int nfilas, conexion conexiones[], int nconex);
bool verificar_victoria();
void jugar(celda tablero[][10], int nfilas, conexion conexiones[], int nconex);
