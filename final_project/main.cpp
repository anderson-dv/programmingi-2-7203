#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Enumerations
enum class MachineType { TRACTOR = 1, SEEDER, SPRAYER, HARVESTER };
enum class MachineState { OPERATIONAL = 1, UNDER_REPAIR, OUT_OF_SERVICE };

// Global messages errors and confirmations
const string MSG_INVALID_OPTION = "Opcion Invalida. Intente nuevamente con un caracter tipo numero.";
const string MSG_INVALID_DATE = "Fecha invalida. Debe tener formato DD/MM/AAAA y valores validos de tipo numero.";
const string MSG_REGISTER_OK = "Maquinaria registrada correctamente.";

// Validar fecha
bool validateDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;

    int day, month, year;
    try {
        day = stoi(date.substr(0, 2));
        month = stoi(date.substr(3, 2));
        year = stoi(date.substr(6, 4));
    } catch (...) {
        return false;
    }

    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < 1900 || year > 2100) return false;

    return true;
}

// Pide un int validado
int getValidatedInt(const string& prompt) {
    int value;
    bool valid = false;
    do {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << MSG_INVALID_OPTION << endl;
        } else if (value < 0) {
            cout << MSG_INVALID_OPTION << endl;
        } else {
            valid = true;
        }
    } while (!valid);
    return value;
}

// Pide un double validado
double getValidatedDouble(const string& prompt) {
    double value;
    bool valid = false;
    do {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << MSG_INVALID_OPTION << endl;
        } else {
            valid = true;
        }
    } while (!valid);
    return value;
}

// Pide una fecha validada
string getValidatedDate(const string& prompt) {
    string date;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia buffer antes de pedir la fecha
    bool valid = false;
    do {
        cout << prompt;
        getline(cin, date);
        valid = validateDate(date);
        if (!valid) {
            cout << MSG_INVALID_DATE << endl;
        }
    } while (!valid);
    return date;
}

int getValidatedOption(const string& prompt, int min, int max) {
    int value;
    bool valid = false;
    do {
        value = getValidatedInt(prompt);
        if (value < min || value > max) {
            cout << MSG_INVALID_OPTION << endl;
        } else {
            valid = true;
        }
    } while (!valid);
    return value;
}

int main() {
    int option = -1;

    do {
        bool validOption = false;
        do {
            cout << "\n----- Menu AgroSoft -----\n";
            cout << "1. Registrar nueva maquinaria\n";
            cout << "0. Salir\n";
            cout << "Seleccione una opcion: ";
            cin >> option;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << MSG_INVALID_OPTION << endl;
            } else if (option != 0 && option != 1) {
                cout << MSG_INVALID_OPTION << endl;
            } else {
                validOption = true;
            }

        } while (!validOption);

        switch (option) {
            case 1: {
                cout << "\n--- Registro de nueva maquinaria ---\n";

                int id = getValidatedInt("Ingrese ID para la maquinaria: ");

                cout << "Seleccione tipo:\n";
                cout << "1. Tractor\n2. Sembradora\n3. Pulverizadora\n4. Cosechadora\n";
                int typeOption = getValidatedOption("Opcion: ", 1, 4);

                cout << "Seleccione estado:\n";
                cout << "1. Operativa\n2. En reparacion\n3. Fuera de servicio\n";
                int stateOption = getValidatedOption("Opcion: ", 1, 3);

                string acquisitionDate = getValidatedDate("Fecha de adquisicion (DD/MM/AAAA): ");
                double cost = getValidatedDouble("Costo unitario: $");

                // En proceso...
                cout << MSG_REGISTER_OK << endl;

                break;
            }
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << MSG_INVALID_OPTION << endl;
        }
    } while (option != 0);

    return 0;
}

