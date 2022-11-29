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

* Download title.ratings.tsv.gz and title.basics.tsv.gz from https://datasets.imdbws.com/

* Get columns FROM title.basics.tsv.gz
    tconst (string) - alphanumeric unique identifier of the title
    titleType (string) – the type/format of the title (e.g. movie, short, tvseries, tvepisode, video, etc)
    primaryTitle (string) – the more popular title / the title used by the filmmakers on promotional materials at the point of release
    isAdult (boolean) - 0: non-adult title; 1: adult title
    startYear (YYYY) – represents the release year of a title. In the case of TV Series, it is the series start year
    runtimeMinutes – primary runtime of the title, in minutes
    genres (string array) – includes up to three genres associated with the title

* Get columns FROM title.ratings.tsv.gz    
    tconst (string) - alphanumeric unique identifier of the title
    averageRating – weighted average of all the individual user ratings
    numVotes - number of votes the title has received 

Assignments:
1. Create Movie Objects (Read File input and stream into movie objects) - Christian 
2. Create total weight based on desired input - Fernando
3. Load movie pointers into vector
4. Sort with merge/quick
5. Output sorted vector
6. Work on user input (What categories to be more weighted/how much output desired to be seen)
7. Work on output (How to display output)




Christian: FILTER - isAdult and titleType == "movie" (from title.basics.tsv.gz)
Fernando: 
Brian: 

*/