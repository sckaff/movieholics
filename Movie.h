#include <iostream>
#include <string>
#include <vector>
#pragma once

using namespace std;

class Movie
{
    private:
        string id;
        string type;
        string title;
        bool adult;
        string startYear;
        int runtime;
        string genre;
        double avgRating;
        int numVotes;
        double runTimeNorm;
        double avgRatingNorm;
        double numVotesNorm;
        double score;
    public:
        Movie(string _id, string _title, string _startYear, int _runtime, string _genre, double _avgRating, int _numVotes, double _runTimeNorm, double _avgRatingNorm, double _numVotesNorm);
        string getId();
        string getType();
        string getTitle();
        string getStartYear();
        int getRuntime();
        string getGenre();
        double getScore();
};