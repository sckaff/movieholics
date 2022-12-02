#include <fstream>
#include <string>
#include "Movie.h"
#include "sort.h"

vector<Movie*> inputMovies()
{
    vector<Movie*> movieList;
    ifstream movieData("data/merged_data.csv");
    if (movieData.is_open())
    {
        string buffer, id, title, startYear, runtime, genre, avgRating, numVotes, runTimeNorm, avgRatingNorm, numVotesNorm;
        getline(movieData, buffer); //Skips Initial Line of column titles
        while (getline(movieData, id, ',')) //Where an ID exists, read line
        {
            getline(movieData, title, ',');
            getline(movieData, startYear, ',');
            getline(movieData, runtime, ',');
            getline(movieData, genre, ',');
            getline(movieData, avgRating, ',');
            getline(movieData, numVotes, ',');
            getline(movieData, runTimeNorm, ',');
            getline(movieData, avgRatingNorm, ',');
            getline(movieData, numVotesNorm);
            movieList.push_back(new Movie(id, title, startYear, stoi(runtime), genre, stod(avgRating), stoi(numVotes), stod(runTimeNorm), stod(avgRatingNorm), stod(numVotesNorm)));
        }
    }
    movieData.close();
    return movieList; //Returns list of movie objects
}

int main()
{
    vector<Movie*> movieList = inputMovies();
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