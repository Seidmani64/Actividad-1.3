#include <vector>
#include <algorithm>
#include <map>
#include "analytics.h"
#include "log.h"
#include "analytics.cpp"
#include "log.cpp"

using namespace std;

void pregunta1(vector<vector<string>> &topFives)
{
    bool everyDay = false;
    string everyDayDomain = "";
    int counter = 0;
    for (size_t i = 0; i < topFives[0].size(); i++)
    {
        string current = topFives[0][i];
        for (size_t j = 0; j < topFives.size(); j++)
        {
            if (count(topFives[j].begin(), topFives[j].end(), current))
               counter++;
            else
                counter = 0;
        }
        if (counter == topFives.size())
        {
            everyDayDomain = current;
            everyDay = true;
            cout << everyDayDomain << " appears on the top five of all dates!" << endl;
            return;
        }
    }
}



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
    

    vector<vector<string>> topFives;
    vector<pair<string, int>> currentTop;
    vector<string> temp;
    string prevDate = "";
    string currentDate = "";
    
    for (size_t i = 0; i < my_analitic.length(); i++)
    {
        currentDate = my_analitic.get_registry(i).get_date();
        if (prevDate == currentDate)
            continue;
            
        cout << "Date: " << currentDate << endl;
        currentTop = my_analitic.top(5, currentDate);
        for (auto& j : currentTop)
        {
            temp.push_back(j.first);
        }
        topFives.push_back(temp);

        prevDate = currentDate;
    }

    /////////////////////////////////// Pregunta 1 ///////////////////////////////
    
    pregunta1(topFives);

    /////////////////////////////////// Pregunta 2 ///////////////////////////////
   
    cout << "El sitio anomalo 249krwpsl2ciatl5u8nb.ru aparece en el top 5 desde el día 6." << endl;

    /////////////////////////////////// Pregunta 3 ///////////////////////////////
    cout << "El sitio protonmail.com tiene una cantidad mucho más alta de tráfico que lo normal" << endl;
    

    return 0;
}