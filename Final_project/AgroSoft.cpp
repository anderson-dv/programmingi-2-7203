#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct fecha {
    int dia, mes, anio;
    
    fecha() : dia(0), mes(0), anio(0) {}
    fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}
};

class maquinaria {
    protected:
        string tipo;
        int id;
        fecha fecha_inicio;
        string estado;
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

        virtual double calcularCostoTotal() const {
            return costo_unitario;
        }

        virtual void mostrarInfo() const {
            cout << "ID: " << id << endl;
            cout << "Tipo: " << tipo << endl;
            cout << "Fecha de inicio: " << fecha_inicio.dia << "/" 
                << fecha_inicio.mes << "/" << fecha_inicio.anio << endl;
            cout << "Estado: " << estado << endl;
            cout << "Costo unitario: $" << costo_unitario << endl;
        }

        // Método virtual puro para que cada clase defina su formato
        virtual string toFileString() const = 0;
        
        // Destructor virtual
        virtual ~maquinaria() {}
};

class tractor : public maquinaria {
    private:
        double potencia;
        int mantenimientos;
        string combustible;
    public:
        tractor(int id, fecha fi, string estado, double c, double potencia, 
                int mantenimientos, const string& combustible)
            : maquinaria("Tractor", id, fi, estado, c), potencia(potencia), 
            mantenimientos(mantenimientos), combustible(combustible) {}

        double getPotencia() const { return potencia; }
        int getMantenimientos() const { return mantenimientos; }
        string getCombustible() const { return combustible; }

        void setPotencia(double p) { potencia = p; }
        void setMantenimientos(int m) { mantenimientos = m; }
        void setCombustible(const string& c) { combustible = c; }

        void mostrarInfo() const override {
            maquinaria::mostrarInfo();
            cout << "Potencia: " << potencia << " HP" << endl;
            cout << "Mantenimientos realizados: " << mantenimientos << endl;
            cout << "Combustible: " << combustible << endl;
        }

        // Formato: tipo,id,dia,mes,anio,estado,costo,potencia,mantenimientos,combustible
        string toFileString() const override {
            return tipo + "," + to_string(id) + "," + 
                to_string(fecha_inicio.dia) + "," + 
                to_string(fecha_inicio.mes) + "," + 
                to_string(fecha_inicio.anio) + "," + 
                estado + "," + to_string(costo_unitario) + "," +
                to_string(potencia) + "," + to_string(mantenimientos) + "," + combustible;
        }
};

class cosechadora : public maquinaria {
    private:
        double potencia;
        int mantenimientos;
        string combustible;
    public:
        cosechadora(int id, fecha fi, string estado, double c, double potencia, 
                    int mantenimientos, const string& combustible)
            : maquinaria("Cosechadora", id, fi, estado, c), potencia(potencia), 
            mantenimientos(mantenimientos), combustible(combustible) {}

        double getPotencia() const { return potencia; }
        int getMantenimientos() const { return mantenimientos; }
        string getCombustible() const { return combustible; }

        void setPotencia(double p) { potencia = p; }
        void setMantenimientos(int m) { mantenimientos = m; }
        void setCombustible(const string& c) { combustible = c; }

        void mostrarInfo() const override {
            maquinaria::mostrarInfo();
            cout << "Potencia: " << potencia << " HP" << endl;
            cout << "Mantenimientos realizados: " << mantenimientos << endl;
            cout << "Combustible: " << combustible << endl;
        }

        string toFileString() const override {
            return tipo + "," + to_string(id) + "," + 
                to_string(fecha_inicio.dia) + "," + 
                to_string(fecha_inicio.mes) + "," + 
                to_string(fecha_inicio.anio) + "," + 
                estado + "," + to_string(costo_unitario) + "," +
                to_string(potencia) + "," + to_string(mantenimientos) + "," + combustible;
        }
};

class sembradora : public maquinaria {
    private:
        double capacidad;
        int usos;
    public:
        sembradora(int id, fecha fi, string estado, double c, double capacidad, int usos)
            : maquinaria("Sembradora", id, fi, estado, c), capacidad(capacidad), usos(usos) {}

        double getCapacidad() const { return capacidad; }
        int getUsos() const { return usos; }

        void setCapacidad(double c) { capacidad = c; }
        void setUsos(int u) { usos = u; }

        void mostrarInfo() const override {
            maquinaria::mostrarInfo();
            cout << "Capacidad: " << capacidad << " hectareas" << endl;
            cout << "Usos: " << usos << endl;
        }

        string toFileString() const override {
            return tipo + "," + to_string(id) + "," + 
                to_string(fecha_inicio.dia) + "," + 
                to_string(fecha_inicio.mes) + "," + 
                to_string(fecha_inicio.anio) + "," + 
                estado + "," + to_string(costo_unitario) + "," +
                to_string(capacidad) + "," + to_string(usos);
        }
};

class pulverizadora : public maquinaria {
    private:
        double capacidad;
        int usos;
    public:
        pulverizadora(int id, fecha fi, string estado, double c, double capacidad, int usos)
            : maquinaria("Pulverizadora", id, fi, estado, c), capacidad(capacidad), usos(usos) {}

        double getCapacidad() const { return capacidad; }
        int getUsos() const { return usos; }

        void setCapacidad(double c) { capacidad = c; }
        void setUsos(int u) { usos = u; }

        void mostrarInfo() const override {
            maquinaria::mostrarInfo();
            cout << "Capacidad: " << capacidad << " hectareas" << endl;
            cout << "Usos: " << usos << endl;
        }

        string toFileString() const override {
            return tipo + "," + to_string(id) + "," + 
                to_string(fecha_inicio.dia) + "," + 
                to_string(fecha_inicio.mes) + "," + 
                to_string(fecha_inicio.anio) + "," + 
                estado + "," + to_string(costo_unitario) + "," +
                to_string(capacidad) + "," + to_string(usos);
        }
};

vector<maquinaria*> maquinas;

// Función para dividir string por comas
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void guardarDatos() {
    ofstream archivo("maquinas.txt");
    if (archivo.is_open()) {
        for (const auto& m : maquinas) {
            archivo << m->toFileString() << endl;
        }
        archivo.close();
        cout << "Datos guardados correctamente en 'maquinas.txt'." << endl;
    } else {
        cout << "Error al abrir el archivo para guardar los datos." << endl;
    }
}

void cargarDatos() {
    ifstream archivo("maquinas.txt");
    if (archivo.is_open()) {
        string linea;
        int contador = 0;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue; // Saltar líneas vacías
            
            vector<string> datos = split(linea, ',');
            
            if (datos.size() < 7) {
                cout << "Error en línea: datos insuficientes" << endl;
                continue;
            }

            try {
                string tipo = datos[0];
                int id = stoi(datos[1]);
                fecha fi(stoi(datos[2]), stoi(datos[3]), stoi(datos[4]));
                string estado = datos[5];
                double costo = stod(datos[6]);

                if (tipo == "Tractor" && datos.size() >= 10) {
                    double potencia = stod(datos[7]);
                    int mantenimientos = stoi(datos[8]);
                    string combustible = datos[9];
                    maquinas.push_back(new tractor(id, fi, estado, costo, potencia, mantenimientos, combustible));
                    contador++;
                } else if (tipo == "Cosechadora" && datos.size() >= 10) {
                    double potencia = stod(datos[7]);
                    int mantenimientos = stoi(datos[8]);
                    string combustible = datos[9];
                    maquinas.push_back(new cosechadora(id, fi, estado, costo, potencia, mantenimientos, combustible));
                    contador++;
                } else if (tipo == "Sembradora" && datos.size() >= 9) {
                    double capacidad = stod(datos[7]);
                    int usos = stoi(datos[8]);
                    maquinas.push_back(new sembradora(id, fi, estado, costo, capacidad, usos));
                    contador++;
                } else if (tipo == "Pulverizadora" && datos.size() >= 9) {
                    double capacidad = stod(datos[7]);
                    int usos = stoi(datos[8]);
                    maquinas.push_back(new pulverizadora(id, fi, estado, costo, capacidad, usos));
                    contador++;
                }
            } catch (const exception& e) {
                cout << "Error al procesar línea: " << linea << endl;
            }
        }
        archivo.close();
        cout << "Datos cargados correctamente. (" << contador << " registros)" << endl;
    } else {
        cout << "No se encontró archivo de datos previo." << endl;
    }
}

void aniadirMaquinaria() {
    cout << "¿Cuántas máquinas desea añadir? ";
    int cantidadm;
    cin >> cantidadm;
    cin.ignore();

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
        cin.ignore();

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
            case 1: {
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
            case 2: {
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
            case 3: {
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
            case 4: {
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
                i--;
                break;
        }
    }
    
    cout << "\nTodas las máquinas han sido agregadas exitosamente." << endl;
    cout << "Total de máquinas en el sistema: " << maquinas.size() << endl;
    
    // Guardar automáticamente después de agregar
    guardarDatos();
}

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
                delete *it;
                maquinas.erase(it);
                cout << "Máquina eliminada correctamente." << endl;
                guardarDatos();
            } else {
                cout << "Eliminación cancelada." << endl;
            }
            return;
        }
    }

    cout << "No se encontró máquina con ID: " << id << endl;
}

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

void costoActivas() {
    double total = 0.0;
    int count = 0;
    for (const auto& m : maquinas) {
        if (m->getEstado() == "Operativa") {
            total += m->calcularCostoTotal();
            count++;
        }
    }
    cout << "Máquinas operativas: " << count << endl;
    cout << "Costo total de máquinas operativas: $" << total << endl;
}

int main() {
    cargarDatos();
    int opcion;
    do {
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Añadir maquinaria" << endl;
        cout << "2. Eliminar maquinaria" << endl;
        cout << "3. Mostrar maquinaria" << endl;
        cout << "4. Calcular costo total de máquinas operativas" << endl;
        cout << "5. Costo de maquinarias activas" << endl;
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
            case 5:
                costoActivas(); 
                break;
            case 0:
                cout << "Guardando datos y saliendo del programa..." << endl;
                guardarDatos();
                // Limpiar memoria
                for (auto& m : maquinas) {
                    delete m;
                }
                maquinas.clear();
                break;
            default:
                cout << "Opción no válida" << endl;
        }
    } while (opcion != 0);
    
    return 0;
}