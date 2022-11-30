#include <fstream>
#include "Movie.h"
int main()
{
    int genre, year;
    
    // Interface
    ////Get genre
    cout << "Welcome to Movie Mappers etc." << endl;
    cout << "|| ------------------------||" << endl;
    cout << "What genre do you want?" << endl;
    cout << "1. Action\n2. Comedy\n3. Drama\n4. Horror\n"; //Update, alphabetical?
    cin >> genre; cout << endl;
    // If statement for edge cases on choosing the genre
    
    cin.clear();
    ////Get year
    cout << "What genre do you want?" << endl;
    cout << "1. Before 1970\n2. 1970-1979\n3. 1980-1989\n4. 1990-1999\n5. 2000-2009\n6. 2010-2019\n7. 2020-Present\n" << endl; //Update, alphabetical?
    cin >> year; cout << endl;
    // If statement for edge cases on choosing the year
}


/*
Assignments:
* Create Movie Objects (Read File input and stream into movie objects) - Christian 
* Polish menu to accept "would you rather pop, length, rating" and account edge cases
* Ask how many movies in the rank (top 3, 10, 100, etc)
* Loop through .csv and make objects
* Sort with merge/quick
 - Input: vector array of movie objects
 - Output: sorted list of movies
* Print sorted list of movies (based on user input for rank amount)
* Work on output (How to display output)
* Show how much time it took to sort with quick sort and merge sort
*/