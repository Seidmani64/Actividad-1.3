#ifndef search_h
#define search_h

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>


class Search
{
    public:
    Search(){}



    int sequenceSearch(std::vector<T> arr, T toFind, bool (*compare)(T &a, T &b))
    {
        for(int i = 0; i<arr.size();i++)
        {
            if(arr[i]==toFind)
                return i;
            if((*compare)(toFind,arr[i]))
                break;
        }
        return -1;
    }

    int sequenceSearch2(std::vector<T> arr, T toFind, bool (*compare)(T &a, T &b))
    {
        int p = arr.size()/1000;
        
        for(int i = 0; i<arr.size();i+=p)
        {
            if(arr[i]==toFind)
                return i;
            if((*compare)(arr[i-p],toFind)&&(*compare)(toFind,arr[i]))
            {
                p = 100;
                continue;
            }
            if((*compare)(arr[i],toFind)&&(*compare)(toFind,arr[i+p]))
            {
                p = 100;
                continue;
            }
        }
        

        return -1;
    }
 
    int binarySearch(std::vector<T> arr, int f, int l, T toFind, bool (*compare)(T &a, T &b))
    {
        int h = (f+l)/2;
        if(arr[h]==toFind)
            return h;
        if((*compare)(toFind,arr[h]))
            return binarySearch(arr, f, h-1, toFind, (*compare));
        if((*compare)(arr[h],toFind))
            return binarySearch(arr, h+1, l, toFind, (*compare));
        return -1;
    }

};

#endif