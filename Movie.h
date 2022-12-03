#include <iostream>
#include <string>
#include <vector>
#include <set>
#pragma once

using namespace std;

class Movie
{
    private:
    public:
        string id;
        string title;
        string startYear;
        int runtime;
        string genre;
        double avgRating;
        int numVotes;
        double runTimeNorm;
        double avgRatingNorm;
        double numVotesNorm;
        double score;

        Movie(string _id, string _title, string _startYear, int _runtime, string _genre, double _avgRating, int _numVotes, double _runTimeNorm, double _avgRatingNorm, double _numVotesNorm);
        string getId();
        string getType();
        string getTitle();
        string getStartYear();
        int getRuntime();
        string getGenre();
};