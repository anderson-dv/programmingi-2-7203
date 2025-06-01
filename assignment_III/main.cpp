#include <iostream>
#include <cctype> //necesaria para usar toupper
using namespace std;

int main () {
	char letra1, letra2, inicio, final, actual;
	
	cout << "Ingrese la primera letra \n";
	cin >> letra1;
	letra1 = toupper(letra1); //toupper convierte la letra dada en mayuscula en caso de no serlo
	
	cout << "Ingrese la segunda letra \n";
	cin >> letra2;
	cout << endl;
	
	letra2 = toupper(letra2);
		
	if (!(letra1 >= 'A' && letra1 <= 'Z')) {
		cout << "El primer valor ingresado no es valido";
		return 1;
	}
	if (!(letra2 >= 'A' && letra2 <= 'Z')) {
		cout << "El segundo valor ingresado no es valido";
		return 1;
	}
	
	if (letra1 < letra2) {  //usamos este if else para definir cual de las letras dadas, es la primera y cual la ultima del rango
        inicio = letra1;
        final = letra2;
    } else {
        inicio = letra2;
        final = letra1;
    }
	
	actual = inicio +1; //sirve para asignar un comienzo, el cual debe ser el siguiente a la primera letra
	while (actual < final) { //este ciclo while, mientras actual no haya llegado a final, escribe la variable siguiente
		cout << actual << " ";  
        actual++;
	}

	cin.ignore(); //para evitar que el programa se cierre inmediatamente al finalizar
	cin.get(); //para que el programa espere a que el usuario presione una tecla antes de finalizar
	
	return 0;
}