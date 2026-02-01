#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void mostrarClientes() {
    ifstream archivo("data/clientes.csv");
    string linea;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    cout << "\n Lista de clientes ---\n";
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
    cout << "Fecha de registro: "; getline(cin, fecha);

    archivo << cedula << "," << nombre << "," << apellido << ","
            << telefono << "," << email << "," << direccion << ","
            << plan << "," << estado << "," << saldo << "," << fecha << endl;

    archivo.close();
    cout << "Cliente agregado correctamente.\n";
}

void buscarCliente() {
    ifstream archivo("data/clientes.csv");
    string cedulaBuscar, linea;

    cout << "Ingrese cedula a buscar: ";
    getline(cin, cedulaBuscar);

    bool encontrado = false;

    while (getline(archivo, linea)) {
        if (linea.find(cedulaBuscar) == 0) {
            cout << "Cliente encontrado:\n" << linea << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Cliente no encontrado.\n";
    }

    archivo.close();
}

void actualizarCliente() {
    ifstream archivo("data/clientes.csv");
    ofstream temp("data/temp.csv");

    string cedulaBuscar, linea;

    cout << "Cedula del cliente a actualizar: ";
    getline(cin, cedulaBuscar);

    bool actualizado = false;

    while (getline(archivo, linea)) {
        if (linea.find(cedulaBuscar) == 0) {
            string nombre, apellido, telefono, email, direccion, plan, estado, saldo, fecha;

            cout << "Nuevo nombre: "; getline(cin, nombre);
            cout << "Nuevo apellido: "; getline(cin, apellido);
            cout << "Nuevo telefono: "; getline(cin, telefono);
            cout << "Nuevo email: "; getline(cin, email);
            cout << "Nueva direccion: "; getline(cin, direccion);
            cout << "Nuevo plan: "; getline(cin, plan);
            cout << "Nuevo estado: "; getline(cin, estado);
            cout << "Nuevo saldo: "; getline(cin, saldo);
            cout << "Nueva fecha: "; getline(cin, fecha);

            temp << cedulaBuscar << "," << nombre << "," << apellido << ","
                 << telefono << "," << email << "," << direccion << ","
                 << plan << "," << estado << "," << saldo << "," << fecha << endl;

            actualizado = true;
        } else {
            temp << linea << endl;
        }
    }

    archivo.close();
    temp.close();

    remove("data/clientes.csv");
    rename("data/temp.csv", "data/clientes.csv");

    if (actualizado)
        cout << "Cliente actualizado correctamente.\n";
    else
        cout << "Cliente no encontrado.\n";
}

void eliminarCliente() {
    ifstream archivo("data/clientes.csv");
    ofstream temp("data/temp.csv");

    string cedulaBuscar, linea;
    bool eliminado = false;

    cout << "Cedula del cliente a eliminar: ";
    getline(cin, cedulaBuscar);

    while (getline(archivo, linea)) {
        if (linea.find(cedulaBuscar) != 0) {
            temp << linea << endl;
        } else {
            eliminado = true;
        }
    }

    archivo.close();
    temp.close();

    remove("data/clientes.csv");
    rename("data/temp.csv", "data/clientes.csv");

    if (eliminado)
        cout << "Cliente eliminado correctamente.\n";
    else
        cout << "Cliente no encontrado.\n";
}

int main() {
    int opcion;

    do {
        cout << "\n Sistema de Telefonia\n";
        cout << "1. Mostrar clientes\n";
        cout << "2. Agregar cliente\n";
        cout << "3. Buscar cliente\n";
        cout << "4. Actualizar cliente\n";
        cout << "5. Eliminar cliente\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: mostrarClientes(); break;
            case 2: agregarCliente(); break;
            case 3: buscarCliente(); break;
            case 4: actualizarCliente(); break;
            case 5: eliminarCliente(); break;
            case 0: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);

    return 0;
}


