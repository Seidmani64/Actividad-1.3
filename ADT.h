#ifndef _READ_RECORD_FROM_FILE_H
#define _READ_RECORD_FROM_FILE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Record
{
    public:
        vector<T> row;

        Record(vector<T> _row) // Constructor
        {
            row = _row;
        }
        ~Record() {};

        T getDate() {return row[0];}
        T getTime() {return row[1];}
        T getInerIp() {return row[2];}
        T getInerPort() {return row[3];}
        T getUser() {return row[4];}
        T getOuterIp() {return row[5];}
        T getOuterPort() {return row[6];}
        T getWebsite() {return row[7];}
};

#endif