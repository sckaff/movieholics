#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Actor
{
    private:
    int id;
    string name;
    vector <int> relevantFilms;
    public:
    Actor(int _id, string _name, vector<int> _relevantFilms);
    int getId();
    string getName();
    vector <int> getRelevantFilms();
    int setId(int id);
    string setName(string name);
    vector<int> setRelevantFilms(vector <int> relevantFilms);
};