#include <vector>
#include <algorithm>
#include <map>
#include "analytics.h"
#include "log.h"
#include "analytics.cpp"
#include "log.cpp"

using namespace std;



int main()
{
    //Load Files
    Analytics my_analitic;
    
    if (my_analitic.load_data_from_csv("nuevo9.csv") > 0)
        cout << "Loaded data." << endl;
    else
    {
        cout << "ERROR loading input file... Exiting program...";
        return 0;
    }


    map<string,int> conexiones;
    conexiones = my_analitic.conexionesPorDia("10-8-2020");
    
    for (auto& x: conexiones) {
    cout << x.first << ": " << x.second << '\n';
  }

    


    return 0;
}