#pragma once
#include <vector>

using namespace std;

void mergeSort(vector<int>& list, int beginning, int end)
{
    if (begining != end)
    {
        int middle = beginning + ((end - beginning)/2);
        mergeSort(list, beginning, middle);
        mergeSort(list, middle, end);
        merge(list, beginning, middle, end);
    }   
}

void merge(vector<int> list, int beginning, int middle, int end)
{
    vector<int> tempLeft;
    vector<int> tempRight;
    //Place List values in new vectors
    for (int i = 0; i < (end - middle); i++)
    {
        tempLeft.push_back(list[middle + 1 + i]);
    }
    for (int j = 0; j < ((middle + 1) - beginning); j++)
    {
        tempLeft.push_back(list[beginning + j]);
    }
    //Merge vectors and store on original vector
    int posOne = 0;
    int posTwo = 0;
    int realPos = beginning;
    while (posOne < (end - middle) && posTwo < ((middle + 1) - beginning))
    {
        if (tempLeft[posOne] <= tempRight[posTwo])
        {
            list[realPos] = tempLeft[posOne];
        }
        else
        {
            list[realPos] = tempRight[posTwo];
        }
    realPos++;
    }
    //Add existing values
    while (posOne < (end - middle))
    {
        list[realPos] = tempLeft[posOne];
        posOne++;
        realPos++;
    }
    while (posTwo < ((middle + 1) - beginning))
    {
        list[realPos] = tempRight[posTwo];
        posTwo++;
        realPos++;
    }
}