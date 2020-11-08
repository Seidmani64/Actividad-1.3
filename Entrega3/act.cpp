#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include "analytics.h"
#include "log.h"
#include "analytics.cpp"
#include "log.cpp"
#include "conexiones.h"

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

    ///////////////////////// Pregunta 1 ///////////////////////////////////
    vector<string> names;
    names = my_analitic.get_non_domain_names();
    string anomaly = "249krwpsl2ciatl5u8nb.ru";

    //////////////////////// Pregunta 2 ////////////////////////////////////
    string anomalyIP = my_analitic.get_domain_ip(anomaly);
    cout << "The anomaly's IP address is: " << anomalyIP << endl;

    vector<string> eC;
    eC = my_analitic.get_entry_connections(anomalyIP);
    std::sort(eC.begin(), eC.end());
    eC.erase(std::unique(eC.begin(), eC.end()), eC.end());
    int computerNum = eC.size();
    // cout<<"The amount of computers that connected to the anomaly is: "<<computerNum<<endl;

    /////////////////////// Pregunta 3 //////////////////////////////////////
    map<string, ConexionesComputadora<string>> dataDict;
    map<string, ConexionesComputadora<string>>::iterator it;
    for (size_t i = 0; i < my_analitic.length(); i++)
    {
        string srcHostname = my_analitic.get_registry(i).get_src_hostname();
        string ip = my_analitic.get_registry(i).get_src_ip();
        it = dataDict.find(srcHostname);
        if (it == dataDict.end() and srcHostname != "-" and ip != "-")
        {
            ConexionesComputadora<string> conexionComp(my_analitic.get_registry(i).get_src_ip(), &my_analitic);
            dataDict.insert(pair<string, ConexionesComputadora<string>>(srcHostname, conexionComp));
        }

        string dstHostname = my_analitic.get_registry(i).get_dst_hostname();
        ip = my_analitic.get_registry(i).get_dst_ip();
        it = dataDict.find(dstHostname);
        if (it == dataDict.end() and dstHostname != "-" and ip != "-")
        {
            ConexionesComputadora<string> conexionComp(my_analitic.get_registry(i).get_dst_ip(), &my_analitic);
            dataDict.insert(pair<string, ConexionesComputadora<string>>(dstHostname, conexionComp));
        }
    }

    int count = 0;
    for (auto i : dataDict)
    {
        size_t index = i.first.find_first_of(".");
        string tempName = i.first.substr(index + 1, i.first.size());
        int conexionesSize = i.second.conexionEntranteSize();
        if (conexionesSize > 0 and tempName == "reto.com")
        {
            count++;
        }
    }
    cout << "Ip's with at least one connection: " << count << endl;

    /////////////////////// Pregunta 4 //////////////////////////////////////
    set<string> ipUnica;

    for (size_t i = 0; i < my_analitic.length(); i++)
    {
        if (my_analitic.get_registry(i).get_src_port() != "68" and my_analitic.get_registry(i).get_dst_hostname() != "server.reto.com")
            ipUnica.insert(my_analitic.get_registry(i).get_src_ip());
    }

    /////////////////////// Pregunta 6 //////////////////////////////////////
    count = 0;
    for (auto i : dataDict)
    {
        size_t index = i.first.find_first_of(".");
        string tempName = i.first.substr(index + 1, i.first.size());
        int conexionesSize = i.second.conexionEntranteSize();

        if (conexionesSize > 0 and tempName == "reto.com")
        {
            while (i.second.conexionSalienteSize() != 0)
            {
                string conexionSaliente = i.second.getConexionSaliente();
                if (conexionSaliente == "123.22.79.224" or conexionSaliente == "33.50.66.90")
                    count++;
            }
        }
    }

    if (count > 0)
        cout << "Number of times connected to anomalies: " << count << endl;

    return 0;
}