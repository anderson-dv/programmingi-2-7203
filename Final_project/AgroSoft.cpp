#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct fecha {
    int dia, mes, anio;
    
    // Constructor por defecto
    fecha() : dia(0), mes(0), anio(0) {}
    fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}
};

class maquinaria {
    protected:
        string tipo; // Tractor, Cosechadora, Arado, Sembradora
        int id;
        fecha fecha_inicio;
        string estado; // Operativa, En reparación, Fuera de servicio
        double costo_unitario;
    public:
        maquinaria(string tipo, int id, fecha fi, string estado, double c)
            : tipo(tipo), id(id), fecha_inicio(fi), estado(estado), costo_unitario(c) {}

        // Getters
        string getTipo() const { return tipo; }
        int getId() const { return id; }
        fecha getFechaInicio() const { return fecha_inicio; }
        string getEstado() const { return estado; }
        double getCostoUnitario() const { return costo_unitario; }

        // Setters
        void setTipo(const string& t) { tipo = t; }
        void setId(int i) { id = i; }
        void setFechaInicio(const fecha& fi) { fecha_inicio = fi; }
        void setEstado(const string& e) { estado = e; }
        void setCostoUnitario(double c) { costo_unitario = c; }

        // Método virtual para calcular costo total
        virtual double calcularCostoTotal() const {
            return costo_unitario;
        }

        // Método virtual para mostrar información
        virtual void mostrarInfo() const {
            cout << "ID: " << id << endl;
            cout << "Tipo: " << tipo << endl;
            cout << "Fecha de inicio: " << fecha_inicio.dia << "/" 
                << fecha_inicio.mes << "/" << fecha_inicio.anio << endl;
            cout << "Estado: " << estado << endl;
            cout << "Costo unitario: $" << costo_unitario << endl;
        }

        // Método virtual para guardar en archivo
        virtual string toFileString() const {
            return to_string(id) + "," + tipo + "," + 
                to_string(fecha_inicio.dia) + "," + 
                to_string(fecha_inicio.mes) + "," + 
                to_string(fecha_inicio.anio) + "," + 
                estado + "," + to_string(costo_unitario);
        }

};

class tractor : public maquinaria {
    private:
        double potencia;
        int mantenimientos; // Número de mantenimientos realizados
        string combustible; // Diesel, Gasolina, Eléctrico
    public:
        tractor(int id, fecha fi, string estado, double c, double potencia, 
                int mantenimientos, const string& combustible)
            : maquinaria("Tractor", id, fi, estado, c), potencia(potencia), 
            mantenimientos(mantenimientos), combustible(combustible) {}

        // Getters
        double getPotencia() const { return potencia; }
        int getMantenimientos() const { return mantenimientos; }
        string getCombustible() const { return combustible; }

        // Setters
        void setPotencia(double p) { potencia = p; }
        void setMantenimientos(int m) { mantenimientos = m; }
        void setCombustible(const string& c) { combustible = c; }

        // Método para mostrar información
        void mostrarInfo() const override {
            maquinaria::mostrarInfo();
            cout << "Potencia: " << potencia << " HP" << endl;
            cout << "Mantenimientos realizados: " << mantenimientos << endl;
            cout << "Combustible: " << combustible << endl;
        }
};

class cosechadora : public maquinaria {
    private:
        double potencia;
        int mantenimientos; // Número de mantenimientos realizados
        string combustible; // Diesel, Gasolina, Eléctrico
    public:
        cosechadora(int id, fecha fi, string estado, double c, double potencia, 
                    int mantenimientos, const string& combustible)
            : maquinaria("Cosechadora", id, fi, estado, c), potencia(potencia), 
            mantenimientos(mantenimientos), combustible(combustible) {}

        // Getters
        double getPotencia() const { return potencia; }
        int getMantenimientos() const { return mantenimientos; }
        string getCombustible() const { return combustible; }

        // Setters
        void setPotencia(double p) { potencia = p; }
        void setMantenimientos(int m) { mantenimientos = m; }
        void setCombustible(const string& c) { combustible = c; }

        // Método para mostrar información
        void mostrarInfo() const override {
            maquinaria::mostrarInfo();
            cout << "Potencia: " << potencia << " HP" << endl;
            cout << "Mantenimientos realizados: " << mantenimientos << endl;
            cout << "Combustible: " << combustible << endl;
        }
};

class sembradora : public maquinaria {
    private:
        double capacidad; // litros o hectareas
        int usos; // Número de veces que se ha utilizado
    public:
        sembradora(int id, fecha fi, string estado, double c, double capacidad, int usos)
            : maquinaria("Sembradora", id, fi, estado, c), capacidad(capacidad), usos(usos) {}

        // Getters
        double getCapacidad() const { return capacidad; }
        int getUsos() const { return usos; }

        // Setters
        void setCapacidad(double c) { capacidad = c; }
        void setUsos(int u) { usos = u; }

        // Método para mostrar información
        void mostrarInfo() const override {
            maquinaria::mostrarInfo();
            cout << "Capacidad: " << capacidad << " hectareas" << endl;
            cout << "Usos: " << usos << endl;
        }
};

class pulverizadora : public maquinaria {
    private:
        double capacidad; // litros o hectareas
        int usos; // Número de veces que se ha utilizado
    public:
        pulverizadora(int id, fecha fi, string estado, double c, double capacidad, int usos)
            : maquinaria("Pulverizadora", id, fi, estado, c), capacidad(capacidad), usos(usos) {}

        // Getters
        double getCapacidad() const { return capacidad; }
        int getUsos() const { return usos; }

        // Setters
        void setCapacidad(double c) { capacidad = c; }
        void setUsos(int u) { usos = u; }

        // Método para mostrar información
        void mostrarInfo() const override {
            maquinaria::mostrarInfo();
            cout << "Capacidad: " << capacidad << " hectareas" << endl;
            cout << "Usos: " << usos << endl;
        }
};

vector<maquinaria*> maquinas; // Vector para almacenar las máquinas

// Función para cargar datos desde archivo
void guardarDatos() {
    ofstream archivo("maquinas.txt");
    if (archivo.is_open()) {
        for (const auto& m : maquinas) {
            archivo << m->toFileString() << endl;
        }
        archivo.close();
        cout << "Datos guardados correctamente." << endl;
    } else {
        cout << "Error al guardar los datos." << endl;
    }
};

// Función para cargar datos desde archivo
void cargarDatos() {
    ifstream archivo("maquinas.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            // Parsear la línea
            size_t pos = 0;
            vector<string> datos;
            while ((pos = linea.find(',')) != string::npos) {
                datos.push_back(linea.substr(0, pos));
                linea.erase(0, pos + 1);
            }
            datos.push_back(linea); // Agregar el último dato

            // Crear la máquina según el tipo
            if (datos[1] == "Tractor") {
                maquinas.push_back(new tractor(stoi(datos[0]), 
                    fecha(stoi(datos[2]), stoi(datos[3]), stoi(datos[4])), 
                    datos[5], stod(datos[6]), stod(datos[7]), 
                    stoi(datos[8]), datos[9]));
            } else if (datos[1] == "Cosechadora") {
                maquinas.push_back(new cosechadora(stoi(datos[0]), 
                    fecha(stoi(datos[2]), stoi(datos[3]), stoi(datos[4])), 
                    datos[5], stod(datos[6]), stod(datos[7]), 
                    stoi(datos[8]), datos[9]));
            } else if (datos[1] == "Sembradora") {
                maquinas.push_back(new sembradora(stoi(datos[0]), 
                    fecha(stoi(datos[2]), stoi(datos[3]), stoi(datos[4])), 
                    datos[5], stod(datos[6]), stod(datos[7]), 
                    stoi(datos[8])));
            } else if (datos[1] == "Pulverizadora") {
                maquinas.push_back(new pulverizadora(stoi(datos[0]), 
                    fecha(stoi(datos[2]), stoi(datos[3]), stoi(datos[4])), 
                    datos[5], stod(datos[6]), stod(datos[7]), 
                    stoi(datos[8])));
            }
        }
        archivo.close();
        cout << "Datos cargados correctamente. (" << maquinas.size() << " registros)" << endl;
    } else {
        cout << "No se encontró archivo de datos previo." << endl;
    }
}

// Función para añadir maquinaria
void aniadirMaquinaria() {
    cout << "¿Cuántas máquinas desea añadir? ";
    int cantidadm;
    cin >> cantidadm;
    cin.ignore(); // Limpiar buffer

    for (int i = 0; i < cantidadm; i++) {
        cout << "\n--- Máquina " << (i + 1) << " de " << cantidadm << " ---" << endl;
        cout << "Seleccione el tipo de maquinaria a añadir:" << endl;
        cout << "1. Tractor" << endl;
        cout << "2. Cosechadora" << endl;   
        cout << "3. Sembradora" << endl;
        cout << "4. Pulverizadora" << endl;
        cout << "Opción: ";
        
        int tipo;
        cin >> tipo;
        cin.ignore(); // Limpiar buffer

        // Datos comunes para todas las máquinas
        int id;
        fecha fechaInicio;
        string estado;
        double costoUnitario;

        cout << "Ingrese el ID de la máquina: ";
        cin >> id;
        cin.ignore();

        cout << "Ingrese la fecha de inicio (día mes año): ";
        cin >> fechaInicio.dia >> fechaInicio.mes >> fechaInicio.anio;
        cin.ignore();

        cout << "Ingrese el estado (Operativa/En reparación/Fuera de servicio): ";
        getline(cin, estado);

        cout << "Ingrese el costo unitario: $";
        cin >> costoUnitario;
        cin.ignore();

        switch (tipo) {
            case 1: { // Tractor
                double potencia;
                int mantenimientos;
                string combustible;

                cout << "Ingrese la potencia (HP): ";
                cin >> potencia;
                cin.ignore();

                cout << "Ingrese el número de mantenimientos realizados: ";
                cin >> mantenimientos;
                cin.ignore();

                cout << "Ingrese el tipo de combustible (Diesel/Gasolina/Eléctrico): ";
                getline(cin, combustible);

                maquinas.push_back(new tractor(id, fechaInicio, estado, costoUnitario, 
                                            potencia, mantenimientos, combustible));
                cout << "Tractor agregado exitosamente." << endl;
                break;
            }
            case 2: { // Cosechadora
                double potencia;
                int mantenimientos;
                string combustible;

                cout << "Ingrese la potencia (HP): ";
                cin >> potencia;
                cin.ignore();

                cout << "Ingrese el número de mantenimientos realizados: ";
                cin >> mantenimientos;
                cin.ignore();

                cout << "Ingrese el tipo de combustible (Diesel/Gasolina/Eléctrico): ";
                getline(cin, combustible);

                maquinas.push_back(new cosechadora(id, fechaInicio, estado, costoUnitario, 
                                                potencia, mantenimientos, combustible));
                cout << "Cosechadora agregada exitosamente." << endl;
                break;
            }
            case 3: { // Sembradora
                double capacidad;
                int usos;

                cout << "Ingrese la capacidad (hectáreas): ";
                cin >> capacidad;
                cin.ignore();

                cout << "Ingrese el número de usos: ";
                cin >> usos;
                cin.ignore();

                maquinas.push_back(new sembradora(id, fechaInicio, estado, costoUnitario, 
                                                capacidad, usos));
                cout << "Sembradora agregada exitosamente." << endl;
                break;
            }
            case 4: { // Pulverizadora
                double capacidad;
                int usos;

                cout << "Ingrese la capacidad (hectáreas): ";
                cin >> capacidad;
                cin.ignore();

                cout << "Ingrese el número de usos: ";
                cin >> usos;
                cin.ignore();

                maquinas.push_back(new pulverizadora(id, fechaInicio, estado, costoUnitario, 
                                                capacidad, usos));
                cout << "Pulverizadora agregada exitosamente." << endl;
                break;
            }
            default:
                cout << "Opción inválida. Máquina no agregada." << endl;
                i--; // Decrementar para repetir esta iteración
                break;
        }
    }
    
    cout << "\nTodas las máquinas han sido agregadas exitosamente." << endl;
    cout << "Total de máquinas en el sistema: " << maquinas.size() << endl;
}

// Función para eliminar una máquina
void eliminarMaquina() {
    if (maquinas.empty()) {
        cout << "No hay máquinas registradas." << endl;
        return;
    }

    cout << "Ingrese el ID de la máquina a eliminar: ";
    int id;
    cin >> id;

    for (auto it = maquinas.begin(); it != maquinas.end(); ++it) {
        if ((*it)->getId() == id) {
            cout << "\n=== MÁQUINA A ELIMINAR ===" << endl;
            (*it)->mostrarInfo();

            cout << "\n¿Está seguro de eliminar esta máquina? (s/n): ";
            char confirmacion;
            cin >> confirmacion;

            if (confirmacion == 's' || confirmacion == 'S') {
                delete *it; // Liberar memoria
                maquinas.erase(it); // Eliminar del vector
                cout << "Máquina eliminada correctamente." << endl;
                guardarDatos(); // Guardar cambios
            } else {
                cout << "Eliminación cancelada." << endl;
            }
            return;
        }
    }

    cout << "No se encontró máquina con ID: " << id << endl;
}

// Función para mostrar todas las máquinas registradas
void mostrarMaquinas() {
    if (maquinas.empty()) {
        cout << "No hay máquinas registradas." << endl;
        return;
    }

    cout << "\n=== LISTA DE MÁQUINAS ===" << endl;
    for (size_t i = 0; i < maquinas.size(); i++) {
        cout << "\n------------------------" << endl;
        cout << "Registro " << (i + 1) << ":" << endl;
        maquinas[i]->mostrarInfo();
    }
}

// Función para calcular el costo total de máquinas operativas
void costoActivas () {
    double total = 0.0;
    for (const auto& m : maquinas) {
        if (m->getEstado() == "Operativa") {
            total += m->calcularCostoTotal();
        }
    }
    cout << "Costo total de máquinas operativas: $" << total << endl;
}

void mantenimientos() {
    if (maquinas.empty()) {
        cout << "No hay máquinas registradas." << endl;
        return;
    }

    

}

int main() {

    cargarDatos(); // Cargar datos al iniciar
    int opcion;
    do
    { 
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Añadir maquinaria" << endl;
        cout << "2. Eliminar maquinaria" << endl;
        cout << "3. Mostrar maquinaria" << endl;
        cout << "4. Calcular costo total de máquinas operativas" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                aniadirMaquinaria();
                break;
            case 2:
                eliminarMaquina();
                break;
            case 3:
                mostrarMaquinas();
                break;
            case 4:
                costoActivas();
                break;
            case 0:
                cout << "Guardando datos y saliendo del programa..." << endl;
                guardarDatos();
                break;
            default:
                cout << "Opción no válida" << endl;
        }
    } while (opcion != 0);
    
    return 0;
}