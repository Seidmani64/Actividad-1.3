#include "ADT.h"
#include "sorter.h"
#include "search.h"
#include "mytimer.h"
#include <vector>
#include<regex>
#include <fstream>

using namespace std;

//Funcion para comparar valores de IP (A menor que B)
template <typename T>
bool compareIPLessThan(T &a, T &b)
{
    if(a == "-" && b != "-"){return true;}
    else if(a != "-" && b == "-"){return false;}
    else if(a == "-" && b == "-"){return false;}

    string f1 = regex_replace(a, regex(R"([\D])"),"");
    string f2 = regex_replace(b, regex(R"([\D])"),"");

    int firstIP = stoi(f1);
    int secondIP = stoi(f2);

    if(firstIP < secondIP){return true;}
    return false;
}


//Funcion para comparar nombres (A menor que B)
template <typename T>
bool compareNameLessThan(T &a, T &b)
{
    if(a == "-" && b != "-"){return true;}
    else if(a != "-" && b == "-"){return false;}
    else if(a == "-" && b == "-"){return false;}

    if(a<b)
    {
        return true;
    }
    return false;
}


//Funcion para comparar valores de IP (A menor o igual que B)
template <typename T>
bool compareIPLessOrEqual(T &a, T &b)
{
    if(a == "-" && b != "-"){return true;}
    else if(a != "-" && b == "-"){return false;}
    else if(a == "-" && b == "-"){return true;}

    string f1 = regex_replace(a, regex(R"([\D])"),"");
    string f2 = regex_replace(b, regex(R"([\D])"),"");

    int firstIP = stoi(f1);
    int secondIP = stoi(f2);

    if(firstIP <= secondIP){return true;}
    return false;
}


//Funcion para comparar nombres (A menor o igual que B)
template <typename T>
bool compareNameLessOrEqual(T &a, T &b)
{
    if(a == "-" && b != "-"){return true;}
    else if(a != "-" && b == "-"){return false;}
    else if(a == "-" && b == "-"){return true;}

    if(a<=b)
    {
        return true;
    }
    return false;
}

//Funcion para contar numero de registros por dia.
template <typename T>
void countDays(vector<T> &ADT, int numberDay)
{
    string day = ADT[0].getDate();
    int count = 1;
    int currentNumberDay = 1;
    for(int i = 0; i < ADT.size(); i++)
    {
        if(day == ADT[i].getDate())
        {
            count++;
        }
        else
        {
            if(currentNumberDay == numberDay)
            {
                 cout << "Number of records for day " << day << ": " << count << endl;
                 break;
            }
            currentNumberDay++;
            day = ADT[i].getDate();
            count = 1;
        }
    }
}

//Main utilizado para hacer pruebas y encontrar las respuestas de las preguntas
int main() 
{
    string file_name = "equipo9.csv"; // Nombre del csv.
    ifstream file; // Crear  ifstream, biblioteca fstream.
    file.open(file_name); // Abrir csv.

    vector<string> fields(8);
    vector<Record<string>> data;
    
    while(file.peek() != EOF) // Iterar hasta llegar al final del csv.
    {
        getline(file, fields[0], ',');
        getline(file, fields[1], ','); // getline(nombre del archivo, variable en la que se guarda el valor, limitante para guardar cada campo)
        getline(file, fields[2], ',');
        getline(file, fields[3], ',');
        getline(file, fields[4], ',');
        getline(file, fields[5], ',');
        getline(file, fields[6], ',');
        getline(file, fields[7], '\n');

        Record<string> row(fields);
        data.push_back(row); // Guardar renglon en vector principal
    }


//PRUEBAS PRELIMINARES PARA DECIDIR CUALES METODOS DE BUSQUEDA Y SORTEO UTILIZAR

    //Establecer y llenar vector con la columna de hostnames
    vector<string> hostnames1;
    for(size_t i = 0; i < data.size(); i++)
    {
        hostnames1.push_back(data[i].getUser());
    }

    //Hacer Objeto de QuickSort y organizar el vector de hostnames
    DECLARE_TIMING(t1);
    START_TIMING(t1);
    QuickSort<string> qsort;
    qsort.sort(hostnames1,&compareNameLessThan);
    STOP_TIMING(t1);
    SHOW_TIMING(t1, "QuickSort");

    //Establecer y llenar vector con la columna de hostnames
    vector<string> hostnames2;
    for(size_t i = 0; i < data.size(); i++)
    {
        hostnames2.push_back(data[i].getUser());
    }

    //Hacer Objeto de MergeSort y organizar el vector de hostnames
    DECLARE_TIMING(t2);
    START_TIMING(t2);
    MergeSort<string> msort;
    msort.sort(hostnames2,&compareNameLessOrEqual);
    STOP_TIMING(t2);
    SHOW_TIMING(t2, "MergeSort");

//INSERTION SORT ESTA COMENTADO PORQUE TARDA 75 SEGUNDOS EN CARGAR
    // //Establecer y llenar vector con la columna de hostnames
    // vector<string> hostnames3;
    // for(size_t i = 0; i < data.size(); i++)
    // {
    //     hostnames3.push_back(data[i]getUser());
    // }

    // //Hacer Objeto de InsertionSort y organizar el vector de hostnames
    // DECLARE_TIMING(t3);
    // START_TIMING(t3);
    // InsertionSort<string> isort;
    // isort.sort(hostnames3,&compareNameLessThan);
    // STOP_TIMING(t3);
    // SHOW_TIMING(t3, "InsertionSort");

    //Hacer Objeto de search y buscar betty.reto.com usando sequenceSearch
    DECLARE_TIMING(t4);
    START_TIMING(t4);
    Search<string> find1;
    find1.sequenceSearch(hostnames2, "betty.reto.com", &compareNameLessThan);
    STOP_TIMING(t4);
    SHOW_TIMING(t4, "SequenceSearch");

    //Hacer Objeto de search y buscar betty.reto.com usando binarySearch
    DECLARE_TIMING(t5);
    START_TIMING(t5);
    Search<string> find2;
    find2.binarySearch(hostnames2, 0, hostnames2.size()-1, "betty.reto.com", &compareNameLessThan);
    STOP_TIMING(t5);
    SHOW_TIMING(t5, "BinarySearch");


//PRUEBAS PARA RESPONDER LAS PREGUNTAS

cout<<"La cantidad de registros es de: "<<data.size()<<endl;


    //Establecer y llenar vector con la columna de hostnames
    vector<string> hostnames;
    for(size_t i = 0; i < data.size(); i++)
    {
        hostnames.push_back(data[i].getUser());
    }

    //Hacer Objetos de Sort y Search y organizar el vector de hostnames
    MergeSort<string> nameSort;
    nameSort.sort(hostnames,&compareNameLessOrEqual);
    Search<string> find;

    //Imprimir indice del termino buscado y si no es -1 imprimir el termino
    int elementIdx = find.sequenceSearch(hostnames,"server.reto.com", &compareNameLessThan); 
    cout<<elementIdx<<endl;
    if(elementIdx >= 0){cout<<hostnames[elementIdx]<<endl;}
    else{cout<<"Element not found."<<endl;}

    //Repetir lo anterior para la columna de destination names
    vector<string> destnames;
    for(size_t i = 0; i < data.size(); i++)
    {
        destnames.push_back(data[i].getWebsite());
    }

    nameSort.sort(destnames, &compareNameLessOrEqual);
    int elementIdx2 = find.sequenceSearch(destnames,"protonmail.com", &compareNameLessThan); 
    cout<<elementIdx2<<endl;
    if(elementIdx2 >= 0){cout<<destnames[elementIdx2]<<endl;}

    // Llamar funcion para contar los registros de cierto dia.
    countDays(data, 2);

    return 0;
}