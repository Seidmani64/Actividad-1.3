#include "ADT.h"
#include "sorter.h"
#include "search.h"
#include <vector>
#include<regex>

using namespace std;

template <typename T>
bool compareIP(T &a, T &b)
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

template <typename T>
bool compareName(T &a, T &b)
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

//Main utilizado para hacer pruebas y encontrar las respuestas de las preguntas
int main() 
{
    //Inicializacion
    ADT<string> test("equipo9.csv");

    cout<<"La cantidad de registros es de: "<<test.data.size()<<endl;


    //Establecer y llenar vector con la columna de hostnames
    vector<string> hostnames;
    for(size_t i = 0; i < test.data.size(); i++)
    {
        hostnames.push_back(test.data[i][4]);
    }

    //Hacer Objetos de Sort y Search y organizar el vector de hostnames
    InsertionSort<string> nameSort;
    nameSort.sort(hostnames,&compareName);
    Search<string> find;

    //Imprimir indice del termino buscado y si no es -1 imprimir el termino
    int elementIdx = find.orderedSeq1(hostnames,"server.reto.com", &compareName); 
    cout<<elementIdx<<endl;
    if(elementIdx >= 0){cout<<hostnames[elementIdx]<<endl;}

    //Repetir lo anterior para la columna de destination names
    vector<string> destnames;
    
    for(size_t i = 0; i < test.data.size(); i++)
    {
        destnames.push_back(test.data[i][7]);
    }

    nameSort.sort(destnames, &compareName);
    int elementIdx2 = find.orderedSeq1(destnames,"protonmail.com", &compareName); 
    cout<<elementIdx2<<endl;
    if(elementIdx2 >= 0){cout<<destnames[elementIdx2]<<endl;}



    return 0;
}