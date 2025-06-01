#include <iostream>
#include <cctype>
using namespace std;

int main() {
    const string errorMessage = "Please enter only letters from the alphabet";
    char letter1, letter2;

    cout << "Enter two letters of the alphabet \n";

    cout << "First letter: ";
    cin >> letter1;
    if (!isalpha(letter1)) {
        cout << errorMessage << endl;
        return 1;
    }

    cout << "Second letter: ";
    cin >> letter2;
    if (!isalpha(letter2)) {
        cout << errorMessage << endl;
        return 1;
    }

    letter1 = toupper(letter1);
    letter2 = toupper(letter2);

    if (letter1 > letter2) swap(letter1, letter2);

    cout << "The uppercase letters of the alphabet between '" << letter1 << "' and '" << letter2 << "' are:\n";

    for (char c = letter1; c <= letter2; c++) {
        cout << static_cast<char>(toupper(c)) << " ";
    }
    cout << endl;

    return 0;
}

//! LO QUE RALIZANMOS EN ESTE CODIGO:

// # Importamos #include <cctype> para trabajar con caracteres de tipo char.
// # Luego declaramos una variable global errorMessage que contiene un mensaje de error para mostrar si el usuario ingresa un carácter no alfabético.
// # En la función main, solicitamos al usuario que ingrese dos letras del alfabeto y en la misma validamo que su valor sea el indicado a isalpha() .
// # Si ambas letras son válidas, comparamos sus valores ASCII y las intercambiamos si letter1 es mayor que letter2 usando la función swap().
// # Después, mostramos un mensaje indicando las letras del alfabeto entre letter1 y letter2.
// # Utilizamos un ciclo for para iterar desde letter1 hasta letter2, convirtiendo cada letra a mayúscula con la función toupper() y mostrando el resultado.
// # Si las letras son válidas, mostramos las letras del alfabeto entre ellas en mayúsculas.

//* ASCII: American Standard Code for Information Interchange (Código Estándar Americano para el Intercambio de Información).