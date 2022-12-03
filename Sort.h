#include "Movie.h"
#include <vector>
#pragma once

using namespace std;

//Merge Sort

void merge(vector<Movie*>& list, int beginning, int middle, int end) //Inspired by Sorting Module - Slide 90
{
    vector<Movie*> tempLeft;
    vector<Movie*> tempRight;
    int countOne = (middle + 1) - beginning;
    int countTwo = end - middle;
    //Place List values in two temporary vectors
    for (int i = 0; i < countOne; i++)
    {
        tempLeft.push_back(list[beginning + i]);
    }
    for (int j = 0; j < countTwo; j++)
    {
        tempRight.push_back(list[middle + 1 + j]);
    }
    //Merge and sort vectors and store on original vector
    int posOne = 0;
    int posTwo = 0;
    int realPos = beginning;
    while (posOne < countOne && posTwo < countTwo)
    {
        if (tempLeft[posOne]->score <= tempRight[posTwo]->score)
        {
            list[realPos] = tempLeft[posOne];
            posOne++;
        }
        else
        {
            list[realPos] = tempRight[posTwo];
            posTwo++;
        }
    realPos++;
    }
    //Add remaining values in sorted order after either temp array is traveresed
    while (posOne < countOne)
    {
        list[realPos] = tempLeft[posOne];
        posOne++;
        realPos++;
    }
    while (posTwo < countTwo)
    {
        list[realPos] = tempRight[posTwo];
        posTwo++;
        realPos++;
    }
}

void mergeSort(vector<Movie*>& list, int beginning, int end)
{
    if (beginning != end)
    {
        int middle = beginning + ((end - beginning) / 2);
        mergeSort(list, beginning, middle);
        mergeSort(list, middle + 1, end);
        merge(list, beginning, middle, end);
    }
}

//Quick Sort

void swap(vector<Movie*>& list, int indexOne, int indexTwo)
{
    Movie* tempIndex;
    tempIndex = list[indexOne];
    list[indexOne] = list[indexTwo];
    list[indexTwo] = tempIndex;
}

double partition(vector<Movie*>& list, int low, int high)
{
    double pivot = list[high]->score; //Using end value of vector as pivot
    double up = low, down = high;

    while (up < down)
    {
        while (list[up]->score < pivot && up < list.size() - 1) //Iterates until value higher than pivot found
        {
            up++;
        }
        while (down >= 0 && list[down]->score >= pivot) //Iterates until value lower than pivot found
        {
            down--;
        }
        if (up < down)
            swap(list, up, down);
    }
    swap(list, up, high);
    return up;
}

void quickSort(vector<Movie*>& list, int low, int high) //Inspired From Sorting Module Slide 122
{
    if (low < high)
    {
        double pivot = partition(list, low, high);
        quickSort(list, low, pivot - 1);
        quickSort(list, pivot + 1, high);
    }
}