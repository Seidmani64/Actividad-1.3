#ifndef sorter_h
#define sorter_h

#include <iostream>
#include <vector>


template <typename T>
class Sorter
{
    public:
    Sorter() {};
    ~Sorter() {};

    void swap(int i, int j, std::vector<T> &arr)
    {
        T aux = arr[i];
        arr[i] = arr[j];
        arr[j] = aux;
    };

    virtual void sort(std::vector<T> &arr) {};
};

template <typename T>
class SelectionSort:public Sorter<T>
{
    public:
    SelectionSort(){};
    ~SelectionSort(){};

    void sort(std::vector<T> &arr, bool (*compare)(T &a, T &b))
    {
        for (size_t i = 0; i < arr.size() - 1; i++)
        {
            size_t min = i;
            for (size_t j = i+1; j < arr.size(); j++)
            {
                if ((*compare)(arr[j],arr[min]))
                    min = j;
            }
            Sorter<T>::swap(i, min, arr);
        }        
    };
};


template <typename T>
class BubbleSort:public Sorter<T>
{
    public:
    BubbleSort(){};
    ~BubbleSort(){};

    void sort(std::vector<T> &arr, bool (*compare)(T &a, T &b))
    {
        bool noSwap = true;
        for(size_t i = 0; i < arr.size(); i++)
        {
            noSwap = true;
            for(size_t j = i+1; j < arr.size(); j++)
                if((*compare)(arr[j], arr[i]))
                {
                    Sorter<T>::swap(j,i,arr);
                    noSwap = false;
                }
            if(noSwap == true)
                break;
        }    
    };
};

template <typename T>
class InsertionSort:public Sorter<T>
{
    public:
    InsertionSort(){};
    ~InsertionSort(){};

    void sort(std::vector<T> &arr, bool (*compare)(T &a, T &b))
    {
        T key;
        for (size_t i = 1; i < arr.size(); i++)
        {
            key = arr[i];
            int j = i - 1;
            while (j >= 0 && (*compare)(key, arr[j]))
            {
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
        }        
    };
};

template <typename T>
class MergeSort : public Sorter<T>
{
    public:
    MergeSort() {};
    ~MergeSort() {};

    void sort(std::vector<T> &arr)
    {
        mergesort(arr, 0, arr.size()-1);
    };


    void mergesort(std::vector<T> &arr, int l, int r)
    {
        if (l < r) {
            int m = l + (r-l) / 2;
            
            mergesort(arr, l, m);
            mergesort(arr, m+1, r);

            merge(arr, l, m, r);
        }
    }

    void merge(std::vector<T> &arr, int l, int m, int r)
    {
        std::vector<T> left;
        std::vector<T> right;
        int i,j,k;
        int leftMax = m - l + 1;
        int rightMax = r - m;

        for(i = 0; i < leftMax; i++)
            left.push_back(arr[l+i]);
        for(j = 0; j < rightMax; j++)
            right.push_back(arr[m+1+j]);
        
        i = 0;
        j = 0;
        k = l;

        while(i < leftMax && j < rightMax)
        {
            if(left[i] <= right[j])
            {
                arr[k] = left[i];
                i++;
            }
            else
            {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while(i < leftMax)
        {
            arr[k] = left[i];
            k++;
            i++;
        }

        while(j < rightMax)
        {
            arr[k] = right[j];
            k++;
            j++;
        }
    }
};

template <typename T>
class QuickSort : public Sorter<T>
{
    public:
    QuickSort(){};
    ~QuickSort(){};

    void sort(std::vector<T> &arr, bool (*compare)(T &a, T &b))
    {
        quicksort(arr, 0, arr.size()-1, compare);
    };

    void quicksort(std::vector<T> &arr, int low, int high, bool (*compare)(T &a, T &b))
    {
        if((*compare)(low, high))
        {
            int piv = partition(arr, low, high, compare);

            quicksort(arr, low, piv - 1, compare);
            quicksort(arr, piv + 1, high, compare);
        }
    };

    int partition(std::vector<T> &arr, int low, int high, bool (*compare)(T &a, T &b))
    {
        T pivot = arr[high];
        int i = low - 1;
        for (size_t j = low; j <= high-1; j++)
        {
            if((*compare)(arr[j], pivot))
            {
                i++;
                Sorter<T>::swap(i, j, arr);
            }
        }
        Sorter<T>::swap(i+1, high, arr);
        return(i+1);
    };
};


#endif
