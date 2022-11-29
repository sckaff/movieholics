#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Movie
{
    private:
        int id;
        string type;
        string title;
        bool adult;
        string startYear;
        string endYear;
        int runtime;
        vector<string> genres;
    public:
        Movie(int _id, string _type, string _title, bool _adult, string _startYear, string _endYear, int _runtime, vector<string> _genres);
        int getId();
        string getType();
        string getTitle();
        bool getAdult();
        string getStartYear();
        string getEndYear();
        int getRuntime();
        vector<string> getGenres();
        int setId(int _id);
        string setType(string _type);
        string setTitle(string _title);
        bool setAdult(bool _adult);
        string setStartYear(string _startYear);
        string setEndYear(string _endYear);
        int setRuntime(int _runtime);
        vector<string> setGenres(vector<string> _genres);
};