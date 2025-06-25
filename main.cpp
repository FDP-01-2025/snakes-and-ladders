#include "./src/definitions.cpp"

int main(){
    srand(time(NULL));
    int dado;

    celda tablero[10][10];
    read_board(tablero, 10);

    conexion conexiones[32];
    read_connections(conexiones, 32);

    jugar(tablero, 10, conexiones, 32);

    mostrar_tablero(tablero, 10);
    cout << "Gracias por jugar! Vuelva pronto!!\n";

    return 0;
}