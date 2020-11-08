#ifndef _ANALYTICS_H
#define _ANALYTICS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stack>
#include <map>
#include "log.h"
#include "../sorter.h"
#include "../search.h"

class Analytics
{
private:
    std::vector<Log> data;

public:
    ~Analytics();
    Analytics();

    int load_data_from_csv(std::string path);
    void print_data();
    int length();
    Log get_registry(int idx);

    std::vector<std::string> get_non_domain_names();
    std::string get_domain_ip(std::string domain);
    std::vector<std::string> get_entry_connections(std::string ip);
    std::map<std::string,int> conexionesPorDia(std::string date);

};


#endif