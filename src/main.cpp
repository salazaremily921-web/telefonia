#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

string fechaActual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char fecha[11];
    sprintf(fecha, "%02d/%02d/%04d",
            ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
    return fecha;
}

bool cedulaExiste(string cedula) {
    ifstream archivo("data/clientes.csv");
    string linea;
    while (getline(archivo, linea)) {
        if (linea.find(cedula) == 0) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

void registrarHistorial(string accion) {
    ofstream hist("data/historial.txt", ios::app);
    hist << fechaActual() << " - " << accion << endl;
    hist.close();
}

void mostrarClientes() {
    ifstream archivo("data/clientes.csv");
    string linea;
    int contador = 0;

    cout << "\n--- LISTA DE CLIENTES ---\n";
    while (getline(archivo, linea)) {
        cout << linea << endl;
        contador++;
    }
    archivo.close();

    cout << "\nTotal de clientes: " << contador << endl;
}

void clientesActivos() {
    ifstream archivo("data/clientes.csv");
    string linea;

    cout << "\n--- CLIENTES ACTIVOS ---\n";
    while (getline(archivo, linea)) {
        if (linea.find(",Activo,") != string::npos) {
            cout << linea << endl;
        }
    }
    archivo.close();
}

void agregarCliente() {
    string cedula, nombre, apellido, telefono, email, direccion, plan;
    double consumo;

    cout << "Cedula: ";
    getline(cin, cedula);

    if (cedulaExiste(cedula)) {
        cout << "ERROR: La cedula ya existe.\n";
        return;
    }

    cout << "Nombre: "; getline(cin, nombre);
    cout << "Apellido: "; getline(cin, apellido);
    cout << "Telefono: "; getline(cin, telefono);
    cout << "Email: "; getline(cin, email);
    cout << "Direccion: "; getline(cin, direccion);
    cout << "Plan: "; getline(cin, plan);
    cout << "Consumo mensual ($): ";
    cin >> consumo;
    cin.ignore();

    double saldo = consumo * 1.12; // impuesto automático
    string estado = "Activo";
    string fecha = fechaActual();

    ofstream archivo("data/clientes.csv", ios::app);
    archivo << cedula << "," << nombre << "," << apellido << ","
            << telefono << "," << email << "," << direccion << ","
            << plan << "," << estado << "," << saldo << "," << fecha << endl;
    archivo.close();

    registrarHistorial("Cliente agregado: " + cedula);
    cout << "Cliente registrado correctamente.\n";
}

void buscarCliente() {
    ifstream archivo("data/clientes.csv");
    string cedula, linea;
    bool encontrado = false;

    cout << "Cedula a buscar: ";
    getline(cin, cedula);

    while (getline(archivo, linea)) {
        if (linea.find(cedula) == 0) {
            cout << "\nCliente encontrado:\n" << linea << endl;
            encontrado = true;
            break;
        }
    }
    archivo.close();

    if (!encontrado)
        cout << "Cliente no encontrado.\n";
}

void actualizarCliente() {
    ifstream archivo("data/clientes.csv");
    ofstream temp("data/temp.csv");
    string cedula, linea;
    bool actualizado = false;

    cout << "Cedula a actualizar: ";
    getline(cin, cedula);

    while (getline(archivo, linea)) {
        if (linea.find(cedula) == 0) {
            string nombre, apellido, telefono, email, direccion, plan, estado;
            double saldo;

            cout << "Nuevo nombre: "; getline(cin, nombre);
            cout << "Nuevo apellido: "; getline(cin, apellido);
            cout << "Nuevo telefono: "; getline(cin, telefono);
            cout << "Nuevo email: "; getline(cin, email);
            cout << "Nueva direccion: "; getline(cin, direccion);
            cout << "Nuevo plan: "; getline(cin, plan);
            cout << "Estado (Activo/Inactivo): "; getline(cin, estado);
            cout << "Nuevo saldo: ";
            cin >> saldo;
            cin.ignore();

            temp << cedula << "," << nombre << "," << apellido << ","
                 << telefono << "," << email << "," << direccion << ","
                 << plan << "," << estado << "," << saldo << "," << fechaActual() << endl;

            actualizado = true;
            registrarHistorial("Cliente actualizado: " + cedula);
        } else {
            temp << linea << endl;
        }
    }

    archivo.close();
    temp.close();
    remove("data/clientes.csv");
    rename("data/temp.csv", "data/clientes.csv");

    if (actualizado)
        cout << "Cliente actualizado.\n";
    else
        cout << "Cliente no encontrado.\n";
}

void eliminarCliente() {
    ifstream archivo("data/clientes.csv");
    ofstream temp("data/temp.csv");
    string cedula, linea;
    bool eliminado = false;

    cout << "Cedula a eliminar: ";
    getline(cin, cedula);

    while (getline(archivo, linea)) {
        if (linea.find(cedula) != 0) {
            temp << linea << endl;
        } else {
            eliminado = true;
            registrarHistorial("Cliente eliminado: " + cedula);
        }
    }

    archivo.close();
    temp.close();
    remove("data/clientes.csv");
    rename("data/temp.csv", "data/clientes.csv");

    if (eliminado)
        cout << "Cliente eliminado.\n";
    else
        cout << "Cliente no encontrado.\n";
}

int main() {
    int op;
    do {
        cout << "\n Sistema de telefonia\n";
        cout << "1. Mostrar clientes\n";
        cout << "2. Agregar cliente\n";
        cout << "3. Buscar cliente\n";
        cout << "4. Actualizar cliente\n";
        cout << "5. Eliminar cliente\n";
        cout << "6. Reporte clientes activos\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1: mostrarClientes(); break;
            case 2: agregarCliente(); break;
            case 3: buscarCliente(); break;
            case 4: actualizarCliente(); break;
            case 5: eliminarCliente(); break;
            case 6: clientesActivos(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (op != 0);

    return 0;
}


