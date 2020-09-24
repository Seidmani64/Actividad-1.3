#ifndef _READ_RECORD_FROM_FILE_H
#define _READ_RECORD_FROM_FILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class ADT
{
    private:
        string file_name; // Nombre del csv.

        void readData() // Funcion encargada de guardar info en vector.
        {
            ifstream file; // Crear  ifstream, biblioteca fstream.
            file.open(file_name); // Abrir csv.

            while(file.peek() != EOF) // Iterar hasta llegar al final del csv.
            {
                vector <string> fields(8); // Vector temporal para guardar todo un renglon.
                getline(file, fields[0], ',');
                getline(file, fields[1], ','); // getline(nombre del archivo, variable en la que se guarda el valor, limitante para guardar cada campo)
                getline(file, fields[2], ',');
                getline(file, fields[3], ',');
                getline(file, fields[4], ',');
                getline(file, fields[5], ',');
                getline(file, fields[6], ',');
                getline(file, fields[7], '\n');

                data.push_back(fields); // Guardar renglon en vector principal
            }
        }
    public:
        vector <vector<T>> data; // Vector donde se guardara toda la info del csv.
        ADT(string _file_name) // Constructor
        {
            file_name = _file_name;
            readData(); // Test para probar si funciona.
        }
        ~ADT() {};
};

#endif