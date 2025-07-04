#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

// Enumerations
enum class MachineType { TRACTOR = 1, SEEDER, SPRAYER, HARVESTER };
enum class MachineState { OPERATIONAL = 1, UNDER_REPAIR, OUT_OF_SERVICE };

// Global messages errors and confirmations
const string MSG_INVALID_OPTION = "Opcion Invalida. Intente nuevamente con un caracter tipo numero.";
const string MSG_INVALID_DATE = "Fecha invalida. Debe tener formato DD/MM/AAAA y valores validos de tipo numero.";
const string MSG_REGISTER_OK = "Maquinaria registrada correctamente.";

// Función para convertir MachineType a string
string machineTypeToString(MachineType type) {
    switch(type) {
        case MachineType::TRACTOR: return "Tractor";
        case MachineType::SEEDER: return "Sembradora";
        case MachineType::SPRAYER: return "Pulverizadora";
        case MachineType::HARVESTER: return "Cosechadora";
        default: return "Desconocido";
    }
}

// Función para convertir MachineState a string
string machineStateToString(MachineState state) {
    switch(state) {
        case MachineState::OPERATIONAL: return "Operativa";
        case MachineState::UNDER_REPAIR: return "En reparacion";
        case MachineState::OUT_OF_SERVICE: return "Fuera de servicio";
        default: return "Desconocido";
    }
}

class Machinery {
protected:
    int id;
    MachineType type;
    MachineState state;
    string acquisitionDate;
    double cost;
public:
    Machinery(int id, MachineType type, MachineState state, const string& date, double cost)
        : id(id), type(type), state(state), acquisitionDate(date), cost(cost) {}

    virtual void show() const {
        cout << "Id: " << id << endl;
        cout << "Tipo: " << machineTypeToString(type) << endl;
        cout << "Fecha de adquisicion: " << acquisitionDate << endl;
        cout << "Estado: " << machineStateToString(state) << endl;
        cout << "Costo unitario: $" << cost << endl;
    }

    MachineType getType() const { return type; }
    double getCost() const { return cost; }
    MachineState getState() const { return state; }
    string getAcquisitionDate() const { return acquisitionDate; }
};

class TractorHarvester : public Machinery {
    int horsepower;
    int maintenanceCount;
    string fuel;
public:
    TractorHarvester(int id, MachineType type, MachineState state, const string& date, double cost,
                     int horsepower, int maintenanceCount, const string& fuel)
        : Machinery(id, type, state, date, cost),
          horsepower(horsepower), maintenanceCount(maintenanceCount), fuel(fuel) {}

    void show() const override {
        Machinery::show();
        cout << "Potencia: " << horsepower << " HP" << endl;
        cout << "Mantenimientos realizados: " << maintenanceCount << endl;
        cout << "Combustible: " << fuel << endl;
    }

    int getMaintenanceCount() const { return maintenanceCount; }

    string getFuel() const { return fuel; }

};

class SeederSprayer : public Machinery {
    double capacity;
    int usageCount;
public:
    SeederSprayer(int id, MachineType type, MachineState state, const string& date, double cost,
                  double capacity, int usageCount)
        : Machinery(id, type, state, date, cost), capacity(capacity), usageCount(usageCount) {}

    void show() const override {
        Machinery::show();
        cout << "Capacidad: " << capacity << endl;
        cout << "Usos: " << usageCount << endl;
    }

    int getUsageCount() const { return usageCount; }

};

vector<Machinery*> inventory;

// TODO: functions of validations

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

// Compara fechas en formato DD/MM/AAAA, devuelve true si a < b
bool minorDate(const string& a, const string& b) {
    int dayA = stoi(a.substr(0, 2));
    int monthA = stoi(a.substr(3, 2));
    int yearA = stoi(a.substr(6, 4));

    int dayB = stoi(b.substr(0, 2));
    int monthB = stoi(b.substr(3, 2));
    int yearB = stoi(b.substr(6, 4));

    if (yearA != yearB) return yearA < yearB;
    if (monthA != monthB) return monthA < monthB;
    return dayA < dayB;
}

// Pide un int validado
int getValidatedInt(const string& prompt) {
    int value;
    string line;
    bool valid = false;
    do {
        cout << prompt;
        getline(cin, line);

        try {
            size_t pos;
            value = stoi(line, &pos);
            if (pos != line.size() || value < 0) {
                throw invalid_argument("no entero");
            }
            valid = true;
        } catch (...) {
            cout << MSG_INVALID_OPTION << endl;
        }
    } while (!valid);
    return value;
}

// Pide un double validado
double getValidatedDouble(const string& prompt) {
    double value;
    string line;
    bool valid = false;
    do {
        cout << prompt;
        getline(cin, line);

        try {
            size_t pos;
            value = stod(line, &pos);
            if (pos != line.size() || value < 0) {
                throw invalid_argument("No es un numero válido");
            }
            valid = true;
        } catch (...) {
            cout << MSG_INVALID_OPTION << endl;
        }
    } while (!valid);
    return value;
}

// Pide una fecha validada
string getValidatedDate(const string& prompt) {
    string date;
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
            cout << "2. Mostrar el listado por tipo y estado\n";
            cout << "3. Costo total de maquinarias activas\n";
            cout << "4. Maquinaria con mas mantenimientos\n";
            cout << "5. Maquinaria con mayor uso o consumo\n";
            cout << "6. Costo promedio por tipo de maquinaria\n";
            cout << "7. Tipo de combustible mas comun\n";
            cout << "0. Salir\n";
            cout << "Seleccione una opcion: ";

            string line;
            getline(cin, line);
            try {
                size_t pos;
                option = stoi(line, &pos);
                if (pos != line.size() || option < 0 || option > 7) {
                    throw invalid_argument("fuera de rango");
                }
                validOption = true;
            } catch (...) {
                cout << MSG_INVALID_OPTION << endl;
            }

        } while (!validOption);

        switch (option) {
            case 1: {
                cout << "\n--- Registro de nueva maquinaria ---\n";

                int id = getValidatedInt("Ingrese ID para la maquinaria: ");

                cout << "Seleccione tipo:\n";
                cout << "1. Tractor\n2. Sembradora\n3. Pulverizadora\n4. Cosechadora\n";
                int typeOption = getValidatedOption("Opcion: ", 1, 4);
                MachineType type = static_cast<MachineType>(typeOption);

                cout << "Seleccione estado:\n";
                cout << "1. Operativa\n2. En reparacion\n3. Fuera de servicio\n";
                int stateOption = getValidatedOption("Opcion: ", 1, 3);
                MachineState state = static_cast<MachineState>(stateOption);

                string acquisitionDate = getValidatedDate("Fecha de adquisicion (DD/MM/AAAA): ");
                double cost = getValidatedDouble("Costo unitario: $");

                if (type == MachineType::TRACTOR || type == MachineType::HARVESTER) {
                    // tractor o cosechadora
                    int horsepower = getValidatedInt("Potencia en HP: ");
                    int maintenanceCount = getValidatedInt("Numero de mantenimientos realizados: ");
                    cout << "Seleccione combustible:\n";
                    cout << "1. Diesel\n2. Gasolina\n3. Electrico\n";
                    int fuelOption = getValidatedOption("Opcion: ", 1, 3);
                    string fuel;
                    switch(fuelOption) {
                        case 1: fuel = "Diesel"; break;
                        case 2: fuel = "Gasolina"; break;
                        case 3: fuel = "Electrico"; break;
                    }
                    inventory.push_back(
                        new TractorHarvester(id, type, state, acquisitionDate, cost, horsepower, maintenanceCount, fuel)
                    );
                } else {
                    // sembradora o pulverizadora
                    double capacity = getValidatedDouble("Capacidad en litros o hectareas: ");
                    int usageCount = getValidatedInt("Numero de veces utilizada: ");
                    inventory.push_back(
                        new SeederSprayer(id, type, state, acquisitionDate, cost, capacity, usageCount)
                    );
                }

                cout << MSG_REGISTER_OK << endl;

                break;
            }

            case 2: {
                if (inventory.empty()) {
                    cout << "No hay maquinarias registradas.\n";
                    break;
                }

                cout << "\nSeleccione el Tipo para filtrar:\n";
                cout << "1. Tractor\n2. Sembradora\n3. Pulverizadora\n4. Cosechadora\n";
                int typeFilter = getValidatedOption("Opcion: ", 1, 4);
                MachineType filterType = static_cast<MachineType>(typeFilter);

                cout << "Seleccione el Estado para filtrar:\n";
                cout << "1. Operativa\n2. En reparacion\n3. Fuera de servicio\n";
                int stateFilter = getValidatedOption("Opcion: ", 1, 3);
                MachineState filterState = static_cast<MachineState>(stateFilter);

                // Filtrar por tipo y estado
                vector<Machinery*> filtered;
                for (auto m : inventory) {
                    if (m->getType() == filterType && m->getState() == filterState) {
                        filtered.push_back(m);
                    }
                }

                if (filtered.empty()) {
                    cout << "No hay maquinarias que coincidan con el tipo y estado seleccionados.\n";
                    break;
                }

                // Ordenar filtrado por  fecha
                sort(filtered.begin(), filtered.end(), [](Machinery* a, Machinery* b) {
                    return minorDate(a->getAcquisitionDate(), b->getAcquisitionDate());
                });

                cout << "\n--- Listado de maquinarias por tipo y estado ---\n";
                for (auto m : filtered) {
                    m->show();
                    cout << "--------------------------\n";
                }
                break;
            }

            case 3: {
                if (inventory.empty()) {
                    cout << "No hay maquinarias registradas.\n";
                    break;
                }

                double totalCost = 0.0;
                for (auto m : inventory) {
                    if (m->getState() == MachineState::OPERATIONAL) {
                        totalCost += m->getCost();
                    }
                }

                cout << "Costo total en maquinarias activas: $" << totalCost << endl;

                break;
            }

            case 4: {
                if (inventory.empty()) {
                    cout << "No hay maquinarias registradas.\n";
                    break;
                }

                TractorHarvester* maxMaintenance = nullptr;
                int maxCount = -1;

                for (auto m : inventory) {
                    TractorHarvester* th = dynamic_cast<TractorHarvester*>(m);
                    if (th != nullptr) {
                        // downcast ok
                        if (th->getMaintenanceCount() > maxCount) {
                            maxCount = th->getMaintenanceCount();
                            maxMaintenance = th;
                        }
                    }
                }

                if (maxMaintenance != nullptr) {
                    cout << "\n--- Maquinaria con mas mantenimientos ---\n";
                    maxMaintenance->show();
                } else {
                    cout << "No hay tractores o cosechadoras registradas.\n";
                }
                break;
            }

            case 5: {
                if (inventory.empty()) {
                    cout << "No hay maquinarias registradas.\n";
                    break;
                }

                SeederSprayer* maxUsage = nullptr;
                int maxUses = -1;

                for (auto m : inventory) {
                    SeederSprayer* ss = dynamic_cast<SeederSprayer*>(m);
                    if (ss != nullptr) {
                        if (ss->getUsageCount() > maxUses) {
                            maxUses = ss->getUsageCount();
                            maxUsage = ss;
                        }
                    }
                }

                if (maxUsage != nullptr) {
                    cout << "\n--- Maquinaria con mayor uso o consumo ---\n";
                    maxUsage->show();
                } else {
                    cout << "No hay sembradoras o pulverizadoras registradas.\n";
                }
                break;
            }

            case 6: {
                if (inventory.empty()) {
                    cout << "No hay maquinarias registradas.\n";
                    break;
                }

                cout << "\n--- Costo promedio por tipo de maquinaria ---\n";
                for (int t = 1; t <= 4; t++) {
                    MachineType mt = static_cast<MachineType>(t);
                    double sum = 0.0;
                    int count = 0;
                    for (auto m : inventory) {
                        if (m->getType() == mt) {
                            sum += m->getCost();
                            count++;
                        }
                    }
                    if (count > 0) {
                        cout << machineTypeToString(mt) << ": $" << (sum / count) << endl;
                    } else {
                        cout << machineTypeToString(mt) << ": Sin registros.\n";
                    }
                }
                break;
            }

            case 7: {
                if (inventory.empty()) {
                    cout << "No hay maquinarias registradas.\n";
                    break;
                }

                int dieselCount = 0, gasolinaCount = 0, electricoCount = 0;

                for (auto m : inventory) {
                    TractorHarvester* th = dynamic_cast<TractorHarvester*>(m);
                    if (th != nullptr) {
                        string f = th->getFuel();
                        if (f == "Diesel") dieselCount++;
                        else if (f == "Gasolina") gasolinaCount++;
                        else if (f == "Electrico") electricoCount++;
                    }
                }

                if (dieselCount == 0 && gasolinaCount == 0 && electricoCount == 0) {
                    cout << "No hay tractores o cosechadoras registradas con combustible.\n";
                    break;
                }

                string commonFuel;
                int maxCount = dieselCount;
                commonFuel = "Diesel";

                if (gasolinaCount > maxCount) {
                    maxCount = gasolinaCount;
                    commonFuel = "Gasolina";
                }
                if (electricoCount > maxCount) {
                    maxCount = electricoCount;
                    commonFuel = "Electrico";
                }

                cout << "Tipo de combustible mas comun: " << commonFuel << " (" << maxCount << " maquinas)" << endl;

                break;
            }

            case 0:
                cout << "Saliendo del programa...\n";
                // liberar memoria
                for (auto m : inventory) delete m;

                inventory.clear();
                break;
            default:
                cout << MSG_INVALID_OPTION << endl;
        }
    } while (option != 0);

    return 0;
}

