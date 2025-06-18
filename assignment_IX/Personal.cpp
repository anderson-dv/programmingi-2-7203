#include <iostream> 
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct fecha {
    int dia;
    int mes;
    int anio;
    
    // Constructor por defecto
    fecha() : dia(0), mes(0), anio(0) {}
    fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}
};

class Empleado {
    protected:
        string nombre;
        int id;
        int anios_industria;
        string tipo; // Para distinguir entre Empleado y Director
    public:
        Empleado(string n, int i, int ai) : nombre(n), id(i), anios_industria(ai), tipo("Empleado") {};

        // Getters
        string getNombre() const { return nombre; }
        int getId() const { return id; }
        int getAniosIndustria() const { return anios_industria; }
        string getTipo() const { return tipo; }

        // Setters
        void setNombre(const string& n) { nombre = n; }
        void setId(int i) { id = i; }
        void setAniosIndustria(int ai) { anios_industria = ai; }

        // Destructor virtual para manejo adecuado de polimorfismo
        virtual ~Empleado() = default;

        virtual void mostrarDatos() const { // Método virtual para mostrar los datos del empleado
            cout << "Tipo: " << tipo << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "ID: " << id << endl;
            cout << "Anios en la industria: " << anios_industria << endl;
        }

        // Métodos virtuales para guardar y cargar datos
        virtual string toFileString() const {
            return "E," + nombre + "," + to_string(id) + "," + to_string(anios_industria);
        }

        virtual void fromFileString(const string& data) {
            // Este método se implementa en las clases derivadas
        }
};

class Director : public Empleado { 
    private:
        string beeper;
        fecha fecha_inicio;
    public:
        Director(string n, int i, int ai, string b, fecha fi) : Empleado(n, i, ai) {
            beeper = b;
            fecha_inicio = fi;
            tipo = "Director"; // Cambiar el tipo
        }

        // Getters para Director
        string getBeeper() const { return beeper; }
        fecha getFechaInicio() const { return fecha_inicio; }

        // Setters para Director
        void setBeeper(const string& b) { beeper = b; }
        void setFechaInicio(const fecha& fi) { fecha_inicio = fi; }

        void mostrarDatos() const override {
            Empleado::mostrarDatos();
            cout << "Beeper: " << beeper << endl;
            cout << "Fecha de inicio: " << fecha_inicio.dia << "/" << fecha_inicio.mes << "/" << fecha_inicio.anio << endl;
        }

        string toFileString() const override {
            return "D," + nombre + "," + to_string(id) + "," + to_string(anios_industria) + "," + 
            beeper + "," + to_string(fecha_inicio.dia) + "," + to_string(fecha_inicio.mes) + "," + to_string(fecha_inicio.anio);
        }
};

vector<Empleado*> empleados; // Vector global para almacenar empleados

// Función para guardar datos en archivo
void guardarDatos() {
    ofstream archivo("empleados.txt");
    if (archivo.is_open()) {
        for (const auto& emp : empleados) {
            archivo << emp->toFileString() << endl;
        }
        archivo.close();
        cout << "Datos guardados correctamente." << endl;
    } else {
        cout << "Error al guardar los datos." << endl;
    }
}

// Función para cargar datos desde archivo
void cargarDatos() {
    ifstream archivo("empleados.txt");
    string linea;
    
    // Limpiar datos existentes
    for (auto& emp : empleados) {
        delete emp;
    }
    empleados.clear();
    
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            
            stringstream ss(linea);
            string tipo, nombre, beeper;
            int id, anios, dia, mes, anio;
            
            getline(ss, tipo, ',');
            getline(ss, nombre, ',');
            ss >> id;
            ss.ignore(); // ignorar la coma
            ss >> anios;
            ss.ignore();
            
            if (tipo == "E") {
                empleados.push_back(new Empleado(nombre, id, anios));
            } else if (tipo == "D") {
                getline(ss, beeper, ',');
                ss >> dia;
                ss.ignore();
                ss >> mes;
                ss.ignore();
                ss >> anio;
                
                fecha fi(dia, mes, anio);
                empleados.push_back(new Director(nombre, id, anios, beeper, fi));
            }
        }
        archivo.close();
        cout << "Datos cargados correctamente. (" << empleados.size() << " registros)" << endl;
    } else {
        cout << "No se encontro archivo de datos previo." << endl;
    }
}

void aniadirEmpleado() {
    cout << "Cuantos empleados desea aniadir? ";
    int cantidadEmpleados;
    cin >> cantidadEmpleados;
    
    for (int i = 0; i < cantidadEmpleados; i++) {
        Empleado* nuevoEmpleado = new Empleado("", 0, 0);
        
        cout << "Ingrese el nombre del empleado " << i + 1 << ": ";
        string nombre;
        cin >> nombre;
        nuevoEmpleado->setNombre(nombre);
        
        cout << "Ingrese el ID del empleado " << i + 1 << ": ";
        int id;
        cin >> id;
        nuevoEmpleado->setId(id);
        
        cout << "Ingrese los anios de industria del empleado " << i + 1 << ": ";
        int anios_industria;
        cin >> anios_industria;
        nuevoEmpleado->setAniosIndustria(anios_industria);

        empleados.push_back(nuevoEmpleado);
    }
    guardarDatos(); // Guardar automáticamente
}

void aniadirDirector() {
    cout << "Cuantos directores desea aniadir? ";
    int cantidadDirectores;
    cin >> cantidadDirectores;
    
    for (int i = 0; i < cantidadDirectores; i++) {
        Director* nuevoDirector = new Director("", 0, 0, "", fecha());
        
        cout << "Ingrese el nombre del director " << i + 1 << ": ";
        string nombre;
        cin >> nombre;
        nuevoDirector->setNombre(nombre);
        
        cout << "Ingrese el ID del director " << i + 1 << ": ";
        int id;
        cin >> id;
        nuevoDirector->setId(id);
        
        cout << "Ingrese los anios de industria del director " << i + 1 << ": ";
        int anios_industria;
        cin >> anios_industria;
        nuevoDirector->setAniosIndustria(anios_industria);
        
        cout << "Ingrese el beeper del director " << i + 1 << ": ";
        string beeper;
        cin >> beeper;
        nuevoDirector->setBeeper(beeper);
        
        cout << "Ingrese la fecha de inicio (dia mes anio) del director " << i + 1 << ": ";
        fecha fi;
        cin >> fi.dia >> fi.mes >> fi.anio;
        nuevoDirector->setFechaInicio(fi);

        empleados.push_back(nuevoDirector);
    }
    guardarDatos(); // Guardar automáticamente
}

void mostrarEmpleados() {
    if (empleados.empty()) {
        cout << "No hay empleados registrados." << endl;
        return;
    }
    
    cout << "\n=== LISTA DE EMPLEADOS ===" << endl;
    for (size_t i = 0; i < empleados.size(); i++) {
        cout << "\n------------------------" << endl;
        cout << "Registro " << i + 1 << ":" << endl;
        empleados[i]->mostrarDatos();
    }
}

void eliminarEmpleado() {
    if (empleados.empty()) {
        cout << "No hay empleados registrados." << endl;
        return;
    }
    
    cout << "Ingrese el ID del empleado a eliminar: ";
    int id;
    cin >> id;
    
    for (auto it = empleados.begin(); it != empleados.end(); ++it) {
        if ((*it)->getId() == id) {
            cout << "\n=== EMPLEADO A ELIMINAR ===" << endl;
            (*it)->mostrarDatos();
            
            cout << "\nEsta seguro de eliminar este empleado? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            
            if (confirmacion == 's' || confirmacion == 'S') {
                delete *it; // Liberar memoria
                empleados.erase(it); // Eliminar del vector
                cout << "Empleado eliminado correctamente." << endl;
                guardarDatos();
            } else {
                cout << "Eliminacion cancelada." << endl;
            }
            return;
        }
    }
    
    cout << "No se encontro empleado con ID: " << id << endl;
}

int main() {
    cout << "=== PROGRAMA DE GESTION DE PERSONAL ===" << endl;
    
    // Cargar datos al iniciar
    cargarDatos();
    
    int opcion;
    do {
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Aniadir empleados" << endl;
        cout << "2. Aniadir directores" << endl;
        cout << "3. Mostrar todos los empleados" << endl;
        cout << "4. Eliminar empleado" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                aniadirEmpleado();
                break;
            case 2:
                aniadirDirector();
                break;
            case 3:
                mostrarEmpleados();
                break;
            case 4:
                eliminarEmpleado();
                break;
            case 5:
                cout << "Guardando datos y saliendo del programa..." << endl;
                guardarDatos(); // Guardar antes de salir
                break;
            default:
                cout << "Opcion no valida" << endl;
        }
    } while(opcion != 5); // mientras no sea la opción 5, muestra el menú

    // Liberar memoria al salir
    for(Empleado* emp : empleados) {
        delete emp;
    }
    empleados.clear();

    return 0;
}