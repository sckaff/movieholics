#include "Actor.h"

Actor::Actor(int _id, string _name, vector <int> _relevantFilms)
{
    this->id = _id;
    this->name = _name;
    this->relevantFilms = _relevantFilms;
}

int Actor::getId()
{
    return this->id;
}

string Actor::getName()
{
    return this->name;
}

vector <int> Actor::getRelevantFilms()
{
    return this->relevantFilms;
}

int Actor::setId(int id)
{
    this->id = id;
}

string Actor::setName(string name)
{
    this->name = name;
}

vector<int> Actor::setRelevantFilms(vector <int> relevantFilms)
{
    this->relevantFilms = relevantFilms;
}