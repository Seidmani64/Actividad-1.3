#include <vector>
#include <algorithm>
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


    vector<string> names;
    names = my_analitic.get_non_domain_names();

    string anomaly = "249krwpsl2ciatl5u8nb.ru";
    string anomalyIP = my_analitic.get_domain_ip(anomaly);
    cout<<"The anomaly's IP address is: "<<anomalyIP<<endl;

    vector<string> eC;
    eC = my_analitic.get_entry_connections(anomalyIP);
    std::sort(eC.begin(), eC.end());
    eC.erase(std::unique(eC.begin(), eC.end()), eC.end());
    int computerNum = eC.size();
    cout<<"The amount of computers that connected to the anomaly is: "<<computerNum<<endl;


    return 0;
}