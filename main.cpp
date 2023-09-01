#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void Merge(vector<string> horasIngreso, vector<string> horasSalida, vector<string> &horasResultado){
    int tamanho = horasIngreso.size();
    
    horasResultado.push_back(horasIngreso[0]);
    for (int i = 0; i < tamanho-1; i++){
        if (horasSalida[i] != horasIngreso[i+1]){
            horasResultado.push_back(horasSalida[i]);
            horasResultado.push_back(horasIngreso[i+1]);
        }
    }
    horasResultado.push_back(horasSalida[tamanho-1]);
}

int main(){

    vector<string> horasResultado(0);
    vector<string> horasIngreso(0);
    vector<string> horasSalida(0);

    string nombreArchivo;
    cout << "Ingrese el nombre del archivo CSV: ";
    cin >> nombreArchivo;

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string primeraLinea;
    getline(archivo, primeraLinea);

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string horaAux;

        bool esHoraIngreso = true;
        while (getline(ss, horaAux, ',')) {
            if (esHoraIngreso){
                horasIngreso.push_back(horaAux);
                esHoraIngreso = false;
            } else {
                horasSalida.push_back(horaAux);
                esHoraIngreso = true;
            }
        }

    }

    archivo.close();

    Merge(horasIngreso, horasSalida, horasResultado);

    ofstream archivoCSV("tabla2.csv");
    if (archivoCSV.is_open()) {
        archivoCSV << "INGRESO,SALIDA\n";
        for (int i = 0; i < horasResultado.size(); i += 2) {
            archivoCSV << horasResultado[i] << "," << horasResultado[i + 1] << "\n";
        }
        archivoCSV.close();
        cout << "Archivo CSV 'tabla2.csv' creado exitosamente." << endl;
    } else {
        cout << "No se pudo crear el archivo CSV." << endl;
    }

    return 0;
}
