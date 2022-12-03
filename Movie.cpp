#include "Movie.h"

Movie::Movie(string _id, string _title, string _startYear, int _runtime, string _genre, double _avgRating, int _numVotes, double _runTimeNorm, double _avgRatingNorm, double _numVotesNorm) {
    this->id = _id;
    this->title = _title;
    this->startYear = _startYear;
    this->runtime = _runtime;
    this->genre = _genre;
    this->avgRating = _avgRating;
    this->numVotes = _numVotes;
    this->runTimeNorm = _runTimeNorm;
    this->avgRatingNorm = avgRatingNorm;
    this->numVotesNorm = _numVotesNorm;
}

string Movie::getId() {
    return this->id;
}

string Movie::getTitle() {
    return this->title;
}

string Movie::getStartYear() {
    return this->startYear;
}

int Movie::getRuntime() {
    return this->runtime;
}

string Movie::getGenre() {
    return this->genre;
}
