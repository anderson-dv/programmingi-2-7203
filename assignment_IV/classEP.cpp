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



#include <map>
#include <string>
#include <utility>
using namespace std;

// Función 1: Contar por tipo y marca
void contarPorTipoYMarca(vector<Electrodomestico>& lista) {
    map<string, map<string, int>> conteo;

    for (auto& equipo : lista) {
        conteo[equipo.getTipo()][equipo.getMarca()]++;
    }

    cout << "\nCantidad por tipo y marca:\n";
    for (auto& tipo : conteo) {
        cout << "- Tipo: " << tipo.first << endl;
        for (auto& marca : tipo.second) {
            cout << "  Marca: " << marca.first << " -> " << marca.second << " unidades\n";
        }
    }
}

// Función 2: Contar en mal estado por tipo
void contarMalEstadoPorTipo(vector<Electrodomestico>& lista) {
    map<string, int> conteo;

    for (auto& equipo : lista) {
        if (equipo.getEstado() == "mal") {
            conteo[equipo.getTipo()]++;
        }
    }

    cout << "\nEquipos en mal estado por tipo:\n";
    for (auto& item : conteo) {
        cout << "- " << item.first << ": " << item.second << " equipos\n";
    }
}

// Función 3: Buscar equipo con mayor y menor garantía
void buscarMayorMenorGarantia(vector<Electrodomestico>& lista) {
    if (lista.empty()) return;

    Electrodomestico* mayor = &lista[0];
    Electrodomestico* menor = &lista[0];

    for (auto& equipo : lista) {
        if (equipo.getGarantia() > mayor->getGarantia()) mayor = &equipo;
        if (equipo.getGarantia() < menor->getGarantia()) menor = &equipo;
    }

    cout << "\nEquipo con MAYOR garantía:\n";
    cout << "- Tipo: " << mayor->getTipo() << ", Marca: " << mayor->getMarca() << ", Años: " << mayor->getGarantia() << "\n";

    cout << "\nEquipo con MENOR garantía:\n";
    cout << "- Tipo: " << menor->getTipo() << ", Marca: " << menor->getMarca() << ", Años: " << menor->getGarantia() << "\n";
}

// Función 4: Costo promedio por tipo
void costoPromedioPorTipo(vector<Electrodomestico>& lista) {
    map<string, pair<double, int>> acumulado;

    for (auto& equipo : lista) {
        acumulado[equipo.getTipo()].first += equipo.getCostoUnitario();
        acumulado[equipo.getTipo()].second += 1;
    }

    cout << "\nCosto promedio por tipo de equipo:\n";
    for (auto& item : acumulado) {
        double promedio = item.second.first / item.second.second;
        cout << "- " << item.first << ": $" << promedio << endl;
    }
}

//MAIN PARA PROBAR
int main() {
    Proveedor proveedor;
    proveedor.setNombre("ElectroCaribe");

    Electrodomestico e1, e2, e3, e4;

    e1.setId(1); e1.setTipo("TV"); e1.setMarca("Samsung"); e1.setEstado("bien");
    e1.setCostoUnitario(400); e1.setGarantia(2); e1.setProveedorPrincipal(proveedor); e1.calcularCostoTotal();

    e2.setId(2); e2.setTipo("Nevera"); e2.setMarca("LG"); e2.setEstado("mal");
    e2.setCostoUnitario(500); e2.setGarantia(3); e2.setProveedorPrincipal(proveedor); e2.calcularCostoTotal();

    e3.setId(3); e3.setTipo("PC"); e3.setMarca("HP"); e3.setEstado("mal");
    e3.setCostoUnitario(600); e3.setGarantia(4); e3.setProveedorPrincipal(proveedor); e3.calcularCostoTotal();

    e4.setId(4); e4.setTipo("TV"); e4.setMarca("Samsung"); e4.setEstado("bien");
    e4.setCostoUnitario(450); e4.setGarantia(1); e4.setProveedorPrincipal(proveedor); e4.calcularCostoTotal();

    vector<Electrodomestico> lista = {e1, e2, e3, e4};

    contarPorTipoYMarca(lista);
    contarMalEstadoPorTipo(lista);
    buscarMayorMenorGarantia(lista);
    costoPromedioPorTipo(lista);

    return 0;
}
