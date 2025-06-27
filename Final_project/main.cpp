#include <iostream>
#include <string>
using namespace std;


class medios {
    protected:
        string tipo, estado;
        int ni; //numero de inventario
        float c; //costo
    public:
        medios(int ni, string tipo, string estado, float c) // Constructor
            : ni(ni), tipo(tipo), estado(estado), c(c) {}

        //getters
        string getTipo() const { return tipo; }
        string getEstado() const { return estado; }
        int getNi() const { return ni; }
        float getCosto() const { return c; }

        //setters
        void setTipo(const string& tipo) { this->tipo = tipo; }
        void setEstado(const string& estado) { this->estado = estado; }
        void setNi(int ni) { this->ni = ni; }
        void setCosto(float c) { this->c = c; }

        // Destructor virtual para herencia
        virtual ~medios() = default;

        // Método virtual puro para calcular costo total
        virtual float calcularCostoTotal() const = 0;

        // Método virtual para mostrar información
        virtual void mostrarInfo() const {
            cout << "Numero de inventario: " << ni << endl;
            cout << "Tipo: " << tipo << endl;
            cout << "Estado: " << estado << endl;
            cout << "Costo unitario: $" << c << endl;
        }

        // Método virtual para guardar en archivo
        virtual string toFileString() const {
        return to_string(ni) + "," + tipo + "," + estado + "," + to_string(c);
        }
    };    



int main() {
    return 0;
}