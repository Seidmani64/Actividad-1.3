#ifndef search_h
#define search_h

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>

//Search class includes all search methods and constructor
//Constructor generates vector with 100,000 whole numbers between 0 and 1000
class Search
{
    public:
    Search(){}

//First search method
//Finds element in unordered array using linear sequence search
    int seqSearch(std::vector<T> arr, T toFind, bool (*compare)(T &a, T &b))
    {
        for(int i = 0; i<arr.size();i++)
        {
            if(arr[i]==toFind)
                return i;
        }
        return -1;
    }


//Second search method
//Finds element in ordered array using linear sequence search
//Stops process if vector value is larger than objective
    int orderedSeq1(std::vector<T> arr, T toFind, bool (*compare)(T &a, T &b))
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


//Third search method
//Finds element in ordered array using sequence search with steps
//Checks vector value p-steps forward and back
//If larger and smaller than objective, lowers p to 1 and searches one at a time
    int orderedSeq2(std::vector<T> arr, T toFind, bool (*compare)(T &a, T &b))
    {
        int p = arr.size()/10;
        
        for(int i = 0; i<arr.size();i+=p)
        {
            if(arr[i]==toFind)
                return i;
            if((arr[i-p]<toFind)&&(arr[i]>toFind))
            {
                p = 1;
                continue;
            }
            if((arr[i]<toFind)&&(arr[i+p]>toFind))
            {
                p = 1;
                continue;
            }
        }
        

        return -1;
    }


//Final search method
//Finds elements in ordered array using binary search through recursion
//Checks first and last indexes of vector
//If halfway index is less than objective, begin method with halfway point as first extreme
//If halfway index is more than objective, begin method with halfway point as last extreme 
    int binSearch(std::vector<T> arr, int f, int l, T toFind, bool (*compare)(T &a, T &b))
    {
        int h = (f+l)/2;
        if(arr[h]==toFind)
            return h;
        if((*compare)(toFind,arr[h]))
            return binSearch(arr,f,h-1,toFind,compare);
        if((*compare)(arr[h],toFind))
            return binSearch(arr,h+1,l,toFind,compare);
        return -1;
    }

};

#endif