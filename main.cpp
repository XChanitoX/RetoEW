#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    int cantidadHoras;
    string horaAux;
    vector<string> horas(0);

    do {
        cout << "Ingrese la cantidad de horas a ingresar: " << endl;
        cin >> cantidadHoras;
    } while (cantidadHoras <= 0);

    for (int i = 0; i < cantidadHoras * 2; i++) {
        if (i % 2 == 0)
            cout << "Ingrese la hora de ingreso: " << endl;
        else
            cout << "Ingrese la hora de salida: " << endl;

        cin >> horaAux;
        bool horaRepetida = false;
        for (int j = 0; j < horas.size(); j++) {
            if (horaAux == horas[j]) {
                horaRepetida = true;
                horas.erase(horas.begin() + j);
                break;
            }
        }

        if (!horaRepetida) {
            horas.push_back(horaAux);
        }
    }

    ofstream archivoCSV("horas.csv");
    if (archivoCSV.is_open()) {
        archivoCSV << "INGRESO,SALIDA\n";
        for (int i = 0; i < horas.size(); i += 2) {
            archivoCSV << horas[i] << "," << horas[i + 1] << "\n";
        }
        archivoCSV.close();
        cout << "Archivo CSV 'horas.csv' creado exitosamente." << endl;
    } else {
        cout << "No se pudo crear el archivo CSV." << endl;
    }

    return 0;
}
