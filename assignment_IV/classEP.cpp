#include <iostream>
#include <vector>
using namespace std;

// Clase Proveedor
class Proveedor {
private:
    string nombre;

public:
    // Constructor 
    Proveedor() : nombre("") {}

    // Setter
    void setNombre(string _nombre) {
        nombre = _nombre;
    }

    // Getter
    string getNombre() {
        return nombre;
    }
};

// Clase Electrodomestico
class Electrodomestico {
private:
    int id, garantia;
    double costo_unitario, costo_total;
    string tipo, marca, estado;
    Proveedor proveedor_principal;
    vector<Proveedor> proveedores_secundarios; // Lista de proveedores secundarios

public:
    // Constructor 
    Electrodomestico() {
        id = 0;
        garantia = 0;
        costo_unitario = 0.0;
        costo_total = 0.0;
        tipo = "";
        marca = "";
        estado = "";
    }

    // Setters
    void setId(int _id) {
        id = _id;
    }

    void setGarantia(int _garantia) {
        garantia = _garantia;
    }

    void setCostoUnitario(double _costo_unitario) {
        costo_unitario = _costo_unitario;
    }

    void setTipo(string _tipo) {
        tipo = _tipo;
    }

    void setMarca(string _marca) {
        marca = _marca;
    }

    void setEstado(string _estado) {
        estado = _estado;
    }

    void setProveedorPrincipal(Proveedor _proveedor) {
        proveedor_principal = _proveedor;
    }

    // Método que agrega un proveedor al vector
    void agregarProveedorSecundario(Proveedor _proveedor) {
        // push_back() agrega un elemento al final del vector
        proveedores_secundarios.push_back(_proveedor);
    }

    // Getters
    int getId() {
        return id;
    }

    int getGarantia() {
        return garantia;
    }

    double getCostoUnitario() {
        return costo_unitario;
    }

    string getTipo() {
        return tipo;
    }

    string getMarca() {
        return marca;
    }

    string getEstado() {
        return estado;
    }

    Proveedor getProveedorPrincipal() {
        return proveedor_principal;
    }

    vector<Proveedor> getProveedoresSecundarios() {
        return proveedores_secundarios;
    }

    // Método que calcula el costo total del producto
    void calcularCostoTotal() {
        costo_total = costo_unitario * garantia;
    }

    double getCostoTotal() {
        return costo_total;
    }
};



int main(){
}