#include "header.h"

void dormir(int time_ms){
    this_thread::sleep_for(std::chrono::milliseconds(time_ms));
}

void read_board(celda tablero[][10], int nfilas){
    ifstream board_file("resources/board.snake");

    char c1, c2;
    for(int i = 0; i < nfilas; i++){
        for(int j = 0; j < 10; j++){
            board_file >> tablero[i][j].c1 >> tablero[i][j].c2;
        }
    }

    board_file.close();
}

void read_connections(conexion conexiones[], int tam){
    ifstream connection_file("resources/connections.snake");
    
    for(int i = 0; i < tam; i++){
        connection_file >> conexiones[i].item >> conexiones[i].fila >> conexiones[i].columna;
    }

    connection_file.close();
}

void colocar_jugador(celda tablero[][10]){
    jugador.c1_substituted = tablero[jugador.fila][jugador.columna].c1;
    jugador.c2_substituted = tablero[jugador.fila][jugador.columna].c2;
    tablero[jugador.fila][jugador.columna].c1 = 'p';
    tablero[jugador.fila][jugador.columna].c2 = 'p';
}

void restaurar_celda(celda tablero[][10]){
    tablero[jugador.fila][jugador.columna].c1 = jugador.c1_substituted;
    tablero[jugador.fila][jugador.columna].c2 = jugador.c2_substituted;
}

void mostrar_tablero(celda tablero[][10], int nfilas){
    cout << "  --  --  --  --  --  --  --  --  --  --  \n";
    for(int i = 0; i < nfilas; i++){
        cout << "|";
        for(int j = 0; j < 10; j++){
            cout << " " << tablero[i][j].c1 << tablero[i][j].c2 << " ";
        }
        cout << "|\n| --  --  --  --  --  --  --  --  --  -- |\n";
    }
}

int gestionar_turno(){
    int op, dado;

    do{
        cout << "Opciones:\n\t1. Tirar dado\n\t2. Salir\n";
        cout << "Selecciona una opción: ";
        cin >> op;
        switch(op){
            case 1:
                cout << "Tirando dado...\n";
                dormir(1000);
                dado = rand() % 6 + 1;
                cout << "Has obtenido un " << dado << "!\n";
                dormir(1000);
                return dado;
            case 2:
                return -1;
            default:
                cout << "Opción inválida!\n";
        }
    }while(true);
}

void avanzar(int dado){
    for(int i = 0; i < dado; i++){
        switch(jugador.direccion){
            case 'R':
                if( jugador.columna + 1 <= 9 ){
                    jugador.fila = jugador.fila;
                    jugador.columna = jugador.columna + 1;
                    jugador.direccion = jugador.direccion;
                }else{
                    jugador.fila = jugador.fila - 1;
                    jugador.columna = jugador.columna;
                    jugador.direccion = 'L';
                }
                break;
            case 'L':
                if( jugador.columna - 1 >= 0 ){
                    jugador.fila = jugador.fila;
                    jugador.columna = jugador.columna - 1;
                    jugador.direccion = jugador.direccion;
                }else{
                    if( !(jugador.fila == 0 && jugador.columna == 0) ){
                        jugador.fila = jugador.fila - 1;
                        jugador.columna = jugador.columna;
                        jugador.direccion = 'R';
                    }
                }
                break;
        }
    }
}

void encontrar_conexion(string text, conexion conexiones[], int tam){
    for(int i = 0; i < tam; i++){
        if( conexiones[i].item == text ){
            jugador.fila = conexiones[i].fila;
            jugador.columna = conexiones[i].columna;
            jugador.direccion = ((jugador.fila % 2 == 0)?'L':'R');
            return;
        }
    }
}

void procesar_nueva_posicion(celda tablero[][10], int nfilas, conexion conexiones[], int nconex){
    string celda_actual = string(1,jugador.c1_substituted) + string(1, jugador.c2_substituted);

    if( celda_actual == ".." || celda_actual == "gu"){
        return;
    }
    if( celda_actual[0] == 's' ){
        cout << "Te picó una culebra!!!!!\n";
        dormir(3000);
        string str_a_buscar = "t" + string(1,celda_actual[1]);
        restaurar_celda(tablero);
        encontrar_conexion(str_a_buscar, conexiones, nconex);
        colocar_jugador(tablero);
        return;
    }
    if( celda_actual[1] == 'd' ){
        cout << "Subiste por una escalera!\n";
        dormir(3000);
        string str_a_buscar = string(1, celda_actual[0]) + string(1,'u');
        restaurar_celda(tablero);
        encontrar_conexion(str_a_buscar, conexiones, nconex);
        colocar_jugador(tablero);
        return;
    }
}

bool verificar_victoria(){
    if( jugador.fila == 0 && jugador.columna == 0 ){
        cout << "Felicidades! Has llegado a la meta!!!!\n";
        return true;
    }
    return false;
}

void jugar(celda tablero[][10], int nfilas, conexion conexiones[], int nconex){
    int dado;

    jugador.fila = 9;
    jugador.columna = 0;
    jugador.direccion = 'R';
    colocar_jugador(tablero);
    do{
        mostrar_tablero(tablero, 10);
        dado = gestionar_turno();
        if( dado == -1 ){
            break;
        }

        restaurar_celda(tablero);
        avanzar(dado);
        colocar_jugador(tablero);
        procesar_nueva_posicion(tablero, 10, conexiones, 32);
    }while(!verificar_victoria());
}