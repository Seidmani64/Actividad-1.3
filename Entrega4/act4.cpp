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

/////////////////////// Pregunta 3 //////////////////////////////////////
    map<string,int> conexiones;
    conexiones = my_analitic.conexionesTotal();
    
    vector<pair<string,int>> pairs;
    for(auto i = conexiones.begin(); i != conexiones.end(); i++)
        pairs.push_back(*i);

    sort(pairs.begin(),pairs.end(), [=](pair<string,int>& a, pair<string,int>& b)
    {
        return a.second < b.second;
    }
    );

    for (int i = pairs.size()-1; i >= 0; i--)
    {
    cout << pairs[i].first << ":" << pairs[i].second << endl;
    }



    return 0;
}