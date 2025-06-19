#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

struct fecha {
    int dia, mes, anio;
    
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

        virtual void mostrarDatos() const { // Metodo virtual para mostrar los datos del empleado
            cout << "Tipo: " << tipo << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "ID: " << id << endl;
            cout << "Anios en la industria: " << anios_industria << endl;
        }

        // Metodos virtuales para guardar y cargar datos
        virtual string toFileString() const {
            return "E," + nombre + "," + to_string(id) + "," + to_string(anios_industria);
        }

        virtual void fromFileString(const string& data) {
            // Este metodo se implementa en las clases derivadas
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

class Equipo {
protected:
    int numInv;
    float costo;
public:
    Equipo(int ni, float c) : numInv(ni), costo(c) {}
    virtual ~Equipo() = default;
    virtual float calcularConsumo() const = 0;
    virtual string getTipo() const = 0;
    int getNumInv() const { return numInv; }
    float getCosto() const { return costo; }
};


class Bomba : public Equipo {
protected:
    float ps, pd, f;
public:
    Bomba(int ni, float c, float ps, float pd, float f)
        : Equipo(ni, c), ps(ps), pd(pd), f(f) {}

    float getPs() const { return ps; }
    float getPd() const { return pd; }
    float getF() const { return f; }
};


class Centrifuga : public Bomba {
    float der;
    int np;
public:
    Centrifuga(int ni, float c, float ps, float pd, float f, float der, int np) 
        : Bomba(ni, c, ps, pd, f), der(der), np(np) {}

    float calcularConsumo() const override {
        return 0.38 * (ps + pd) + 2.3 * f + 3.4 * (der + np);
    }

    string getTipo() const override {
        return "Centrifuga";
    }

    float getDer() const { return der; }
    int getNp() const { return np; }

    float getPs() const { return ps; }
    float getPd() const { return pd; }
    float getF() const { return f; }
};


class Embolo : public Bomba {
    float l, d;
public:
    Embolo(int ni, float c, float ps, float pd, float f, float l, float d) 
        : Bomba(ni, c, ps, pd, f), l(l), d(d) {}

    float calcularConsumo() const override {
        return 0.38 * (ps + pd) + 2.3 * f;
    }

    string getTipo() const override {
        return "Embolo";
    }

    float getL() const { return l; }
    float getD() const { return d; }

    float getPs() const { return ps; }
    float getPd() const { return pd; }
    float getF() const { return f; }
};


class Intercambiador : public Equipo {
    float a, ptc, d;
public:
    Intercambiador(int ni, float c, float a, float ptc, float d) 
        : Equipo(ni, c), a(a), ptc(ptc), d(d) {}

    float calcularConsumo() const override {
        return 0.25 * ptc + log(d);
    }

    string getTipo() const override {
        return "Intercambiador";
    }

    float getA() const { return a; }
    float getPtc() const { return ptc; }
    float getD() const { return d; }
};


vector<Empleado*> empleados; // Vector global para almacenar empleados

vector<Equipo*> equipos;
float consumoAlumbrado = 0; 

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
    guardarDatos(); // Guardar automaticamente
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
    guardarDatos(); // Guardar automaticamente
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

void aniadirEquipo() {
    int tipo;
    cout << "Seleccione tipo de equipo (1=Centrifuga, 2=Embolo, 3=Intercambiador): ";
    cin >> tipo;

    if (tipo == 1) {
        int ni, np;
        float c, ps, pd, f, der;
        cout << "Ingrese numero de inventario: "; cin >> ni;
        cout << "Ingrese costo: "; cin >> c;
        cout << "Ingrese presion de succion: "; cin >> ps;
        cout << "Ingrese presion de descarga: "; cin >> pd;
        cout << "Ingrese flujo: "; cin >> f;
        cout << "Ingrese diametro del eje de rotacion: "; cin >> der;
        cout << "Ingrese numero de paletas: "; cin >> np;

        equipos.push_back(new Centrifuga(ni, c, ps, pd, f, der, np));
        cout << "Centrifuga anadida correctamente." << endl;
    } 
    else if (tipo == 2) {
        int ni;
        float c, ps, pd, f, l, d;
        cout << "Ingrese numero de inventario: "; cin >> ni;
        cout << "Ingrese costo: "; cin >> c;
        cout << "Ingrese presion de succion: "; cin >> ps;
        cout << "Ingrese presion de descarga: "; cin >> pd;
        cout << "Ingrese flujo: "; cin >> f;
        cout << "Ingrese largo: "; cin >> l;
        cout << "Ingrese diametro: "; cin >> d;

        equipos.push_back(new Embolo(ni, c, ps, pd, f, l, d));
        cout << "embolo anadido correctamente." << endl;
    } 
    else if (tipo == 3) {
        int ni;
        float c, a, ptc, d;
        cout << "Ingrese numero de inventario: "; cin >> ni;
        cout << "Ingrese costo: "; cin >> c;
        cout << "Ingrese area: "; cin >> a;
        cout << "Ingrese presion del tubo central: "; cin >> ptc;
        cout << "Ingrese diametro: "; cin >> d;

        equipos.push_back(new Intercambiador(ni, c, a, ptc, d));
        cout << "Intercambiador anadido correctamente." << endl;
    } 
    else {
        cout << "Tipo de equipo no valido." << endl;
    }
}


float calcularConsumoTotal() {
    float total = consumoAlumbrado;
    for (auto eq : equipos) {
        total += eq->calcularConsumo();
    }
    return total;
}

void equipoMayorConsumo() {
    if (equipos.empty()) {
        cout << "No hay equipos registrados." << endl;
        return;
    }
    auto mayor = max_element(equipos.begin(), equipos.end(),
        [](Equipo* a, Equipo* b) { return a->calcularConsumo() < b->calcularConsumo(); });
    cout << "Equipo de mayor consumo: #" << (*mayor)->getNumInv()
         << " (" << (*mayor)->getTipo() << ") Consumo: "
         << (*mayor)->calcularConsumo() << endl;
}

void listarCentrifugasOrdenadas() {
    vector<Centrifuga*> centrifugas;
    for (auto eq : equipos) {
        if (auto c = dynamic_cast<Centrifuga*>(eq)) {
            centrifugas.push_back(c);
        }
    }
    sort(centrifugas.begin(), centrifugas.end(),
         [](Centrifuga* a, Centrifuga* b) { return a->getDer() > b->getDer(); });

    cout << "Centrifugas ordenadas por diametro descendente:\n";
    for (auto c : centrifugas) {
        cout << "NumInv: " << c->getNumInv() << ", Der: " << c->getDer()
             << ", Consumo: " << c->calcularConsumo() << endl;
    }
}

void contarEquipos() {
    int nc = 0, ne = 0, ni = 0;
    for (auto eq : equipos) {
        if (eq->getTipo() == "Centrifuga") nc++;
        else if (eq->getTipo() == "Embolo") ne++;
        else if (eq->getTipo() == "Intercambiador") ni++;
    }
    cout << "Centrifugas: " << nc << ", Embolos: " << ne << ", Intercambiadores: " << ni << endl;
}

void trabajadorMasAntiguo() {
    if (empleados.empty()) {
        cout << "No hay empleados." << endl;
        return;
    }
    auto mayor = max_element(empleados.begin(), empleados.end(),
        [](Empleado* a, Empleado* b) { return a->getAniosIndustria() < b->getAniosIndustria(); });
    cout << "Trabajador mas antiguo: " << (*mayor)->getNombre()
         << " con " << (*mayor)->getAniosIndustria() << " anos." << endl;
}

void guardarEquipos() {
    ofstream archivo("equipos.txt");
    if (archivo.is_open()) {
        for (auto eq : equipos) {
            archivo << eq->getTipo() << " ";
            archivo << eq->getNumInv() << " " << eq->getCosto() << " ";

            if (eq->getTipo() == "Centrifuga") {
                Centrifuga* c = dynamic_cast<Centrifuga*>(eq);
                archivo << c->getPs() << " " << c->getPd() << " " << c->getF() 
                        << " " << c->getDer() << " " << c->getNp();
            }
            else if (eq->getTipo() == "Embolo") {
                Embolo* e = dynamic_cast<Embolo*>(eq);
                archivo << e->getPs() << " " << e->getPd() << " " << e->getF() 
                        << " " << e->getL() << " " << e->getD();
            }
            else if (eq->getTipo() == "Intercambiador") {
                Intercambiador* i = dynamic_cast<Intercambiador*>(eq);
                archivo << i->getA() << " " << i->getPtc() << " " << i->getD();
            }

            archivo << endl;
        }
        archivo.close();
        cout << "Equipos guardados correctamente." << endl;
    } else {
        cout << "Error al guardar los equipos." << endl;
    }
}


void cargarEquipos() {
    ifstream archivo("equipos.txt");
    if (!archivo.is_open()) {
        cout << "No se encontraron equipos guardados." << endl;
        return;
    }

    // Limpiar vector
    for (auto e : equipos) delete e;
    equipos.clear();

    string tipo;
    while (archivo >> tipo) {
        if (tipo == "Centrifuga") {
            int ni, np;
            float c, ps, pd, f, der;
            archivo >> ni >> c >> ps >> pd >> f >> der >> np;
            equipos.push_back(new Centrifuga(ni, c, ps, pd, f, der, np));
        }
        else if (tipo == "Embolo") {
            int ni;
            float c, ps, pd, f, l, d;
            archivo >> ni >> c >> ps >> pd >> f >> l >> d;
            equipos.push_back(new Embolo(ni, c, ps, pd, f, l, d));
        }
        else if (tipo == "Intercambiador") {
            int ni;
            float c, a, ptc, d;
            archivo >> ni >> c >> a >> ptc >> d;
            equipos.push_back(new Intercambiador(ni, c, a, ptc, d));
        }
    }

    archivo.close();
    cout << "Equipos cargados correctamente. (" << equipos.size() << " registros)" << endl;
}



int main() {
    cout << "=== PROGRAMA DE GESTION DE PERSONAL ===" << endl;
    
    // Cargar datos al iniciar
    cargarDatos();
    cargarEquipos();
    
    int opcion;
    do {
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Aniadir empleados" << endl;
        cout << "2. Aniadir directores" << endl;
        cout << "3. Mostrar todos los empleados" << endl;
        cout << "4. Eliminar empleado" << endl;
        cout << "5. Aniadir equipo" << endl;
        cout << "6. Mostrar consumo total" << endl;
        cout << "7. Mostrar equipo mayor consumo" << endl;
        cout << "8. Listar centrifugas ordenadas" << endl;
        cout << "9. Contar equipos por tipo" << endl;
        cout << "10. Trabajador mas antiguo" << endl;
        cout << "0. Salir" << endl;
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
                aniadirEquipo();
                break;
            case 6: 
                cout << "Consumo total: " << calcularConsumoTotal() << endl; 
                break;
            case 7: 
                equipoMayorConsumo(); 
                break;
            case 8: 
                listarCentrifugasOrdenadas(); 
                break;
            case 9: 
                contarEquipos(); 
                break;
            case 10: 
                trabajadorMasAntiguo(); 
                break;
            case 0:
                cout << "Guardando datos y saliendo del programa..." << endl;
                guardarDatos();
                guardarEquipos(); // Guardar antes de salir
                break;
            default:
                cout << "Opcion no valida" << endl;
        }
    } while(opcion != 0); // mientras no sea la opción 5, muestra el menú

    for (auto eq : equipos) delete eq;
    equipos.clear();

    // Liberar memoria al salir
    for(Empleado* emp : empleados) {
        delete emp;
    }
    empleados.clear();

    return 0;
}