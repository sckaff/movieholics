#include "Movie.h"

Movie::Movie(int _id, string _type, string _title, bool _adult, string _startYear, string _endYear, int _runtime, vector<string> _genres) {
    this->id = _id;
    this->type = _type;
    this->title = _title;
    this->adult = _adult;
    this->startYear = _startYear;
    this->endYear = _endYear;
    this->runtime = _runtime;
    this->genres = _genres;
}

int Movie::getId() {
    return this->id;
}

string Movie::getType() {
    return this->type;
}

string Movie::getTitle() {
    return this->title;
}

bool Movie::getAdult() {
    return this->adult;
}

string Movie::getStartYear() {
    return this->startYear;
}

string Movie::getEndYear() {
    return this->endYear;
}

int Movie::getRuntime() {
    return this->runtime;
}

vector<string> Movie::getGenres() {
    return this->genres;
}

int Movie::setId(int _id) {
    this->id = _id;
}

string Movie::setType(string _type) {
    this->type = _type;
}

string Movie::setTitle(string _title) {
    this->title = _title;
}

bool Movie::setAdult(bool _adult) {
    this->adult = _adult;
}

string Movie::setStartYear(string _startYear) {
    this->startYear = _startYear;
}

string Movie::setEndYear(string _endYear) {
    this->endYear = _endYear;
}

int Movie::setRuntime(int _runtime) {
    this->runtime = _runtime;
}

vector<string> Movie::setGenres(vector<string> _genres) {
    this->genres = _genres;
}