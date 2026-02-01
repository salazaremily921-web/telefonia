#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void mostrarClientes() {
    ifstream archivo("data/clientes.csv");
    string linea;

    if (!archivo.is_open()) {
        cout << "Error al abrir clientes.csv" << endl;
        return;
    }

    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}

void agregarCliente() {
    ofstream archivo("data/clientes.csv", ios::app);

    string cedula, nombre, apellido, telefono, email, direccion, plan, estado, saldo, fecha;

    cout << "Cedula: "; getline(cin, cedula);
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Apellido: "; getline(cin, apellido);
    cout << "Telefono: "; getline(cin, telefono);
    cout << "Email: "; getline(cin, email);
    cout << "Direccion: "; getline(cin, direccion);
    cout << "Plan: "; getline(cin, plan);
    cout << "Estado: "; getline(cin, estado);
    cout << "Saldo: "; getline(cin, saldo);
    cout << "Fecha registro: "; getline(cin, fecha);

    archivo << cedula << "," << nombre << "," << apellido << ","
            << telefono << "," << email << "," << direccion << ","
            << plan << "," << estado << "," << saldo << "," << fecha << endl;

    archivo.close();
    cout << "Cliente agregado correctamente." << endl;
}

int main() {
    int opcion;

    do {
        cout << "\n--- SISTEMA DE TELEFONIA ---\n";
        cout << "1. Mostrar clientes\n";
        cout << "2. Agregar cliente\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                mostrarClientes();
                break;
            case 2:
                agregarCliente();
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }

    } while (opcion != 0);

    return 0;
}


