#ifndef _ANALYTICS_H
#define _ANALYTICS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
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

    void day_nth(int day_idx, std::string &date, int &count);
    int find_computer_owner(std::vector<std::string> names);
    std::string get_computer_name(std::string ip);
    std::vector<int> dst_port_under_val(int threshold);
};


#endif