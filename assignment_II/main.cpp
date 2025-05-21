#include <iostream>
using namespace std;

// int entero = 100;
// float flotante = 9.5;
// double doble = 12353.6543;


// return 1; Se retorna 1 cuando el programa termina por una condición no válida o por un error 

int main() {

    double y, a, x, b;

    cout << "Ingrese el valor para la variable a: ";
    cin >> a;
    cout << "Ingrese el valor para la variable x: ";
    cin >> x;
    cout << "Ingrese el valor para la variable b: ";
    cin >> b;

    if( x + b == 0) {
        cout << "División entre cero no permitida, reinicie e ingrese los valores para (x) y (b) nuevamente" << endl;
        return 1; // Si la expresión es false, se muestra el error y se retorna 1 para evitar que el código continúe ejecutándose.
    }
    
    y = a / (x + b);

    cout << "El resultado de la proporcionalidad inversa es:" << endl;
    cout << "y = " << a << " / (" << x << " + " << b << ")" << endl;
    cout << "y = " << y << endl;
    
    return 0;
}