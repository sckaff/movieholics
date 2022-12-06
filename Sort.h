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
        if (tempLeft[posOne]->score < tempRight[posTwo]->score)
        {
            list[realPos] = tempLeft[posOne];
            posOne++;
        }
        else if (tempLeft[posOne]->score > tempRight[posTwo]->score)
        {
            list[realPos] = tempRight[posTwo];
            posTwo++;
        }
        else
        {
            if (tempLeft[posOne]->title.compare(tempRight[posTwo]->title) < 0)
            {
                list[realPos] = tempLeft[posOne];
                posOne++;
            }
            else
            {
                list[realPos] = tempRight[posTwo];
                posTwo++;
            }
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

bool comp(int a1, string a2, int b1, string b2)
{
    if (a1 < b1)
    {
        return false;
    }
    else if (a1 > b1)
    {
        return true;
    }
    else if (a1 == b1)
    {
        if (a2.compare(b2) < 0)
        {
            return false;
        }
        else return true;
    }
}

void swap(vector<Movie*>& list, int indexOne, int indexTwo)
{
    Movie* tempIndexValue;
    tempIndexValue = list[indexOne];
    list[indexOne] = list[indexTwo];
    list[indexTwo] = tempIndexValue;
}

int partition(vector<Movie*>& list, int low, int high)
{
    double pivot = list[high]->score; //Using end value of vector as pivot
    string pivotB = list[high]->title; //Using end value of vector as pivot
    bool isDupliate = false;
    int up = low, down = high;

    while (up < down)
    {
        while (!comp(list[up]->score, list[up]->title, pivot, pivotB) && up < high && !isDupliate) //Iterates until value higher than pivot found
        {
            up++;
        }
        isDupliate = false;
        while (down > low && comp(list[down]->score, list[down]->title, pivot, pivotB) && !isDupliate) //Iterates until value lower than pivot found
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
        int pivot = partition(list, low, high);
        quickSort(list, low, pivot - 1);
        quickSort(list, pivot + 1, high);
    }
}