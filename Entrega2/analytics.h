#ifndef _ANALYTICS_H
#define _ANALYTICS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stack>
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

    std::string get_computer_name(std::string ip);
    std::stack<std::string> get_entry_connections(std::string ip);
    std::queue<std::string> get_exit_connections(std::string ip);


};


#endif