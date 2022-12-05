#include <fstream>
#include <string>
#include "Movie.h"
#include "sort.h"
#include <iomanip>
#include <regex>
#include <chrono>
#include <map>
#include <unordered_map>
#include "progressbar.hpp"

using namespace chrono;

set<string> genres;
regex regGenre = regex("(\\d$)");
regex regWeight = regex("(\\d{1,}) (\\d{1,}) (\\d{1,}$)");

vector<Movie*> inputMovies()
{
    vector<Movie*> movieList;
    ifstream movieData("data/merged_data_new.csv");
    if (movieData.is_open())
    {
        int completed_count = 0;
        int percentage = 0;
        const int total_movies = 220310; //Note this value is slightly smaller than the actual count to properly display loading bar
        progressbar bar(100);
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
            genres.insert(genre);
            if (percentage < ((100*completed_count)/total_movies))
            {
                percentage = ((100*completed_count)/total_movies);
                bar.update();
            }
            movieList.push_back(new Movie(id, title, startYear, stoi(runtime), genre, stod(avgRating), stoi(numVotes), stod(runTimeNorm), stod(avgRatingNorm), stod(numVotesNorm)));
            completed_count++;
        }
        bar.update();
        cout << "\n";
    }
    movieData.close();
    return movieList; //Returns list of movie objects
}

int main()
{
    vector<Movie*> movieList = inputMovies();
    Movie* first = movieList[0];
    string jimbo = "";
    vector<string> genre_v;

    auto it = genres.begin();
    int genre_count = 1;
    cout << "What genre do you want?" << endl; 
    cout << "0. None\n";
    while (it != genres.end())
    {
        cout << genre_count << ". " << *it << "\n";
        genre_v.push_back(*it);
        genre_count++;
        it++;
    }

    string selected_genre = "";
    bool filter_genre = false;
    bool genre_loop = true;
    while (genre_loop)
    {
        string genre_input = "";
        getline(cin, genre_input);
        smatch matchGenre = smatch();
        regex_match(genre_input, matchGenre, regGenre);
        if (matchGenre.empty() != true)
        {
            int input_val = stoi(matchGenre.str(1));
            if (input_val == 0) break;
            else if (input_val > 0 && input_val <= genres.size())
            {
                filter_genre = true;
                selected_genre = genre_v[input_val-1];
                break;
            }
        }
        cout << "Invalid choice. Please select again\n";
    }

    int runtime_weight;
    int vote_count_weight;
    int rating_weight;
    
    cout << "Enter your weights for runtime, vote_count, and rating weight using this format without quotes\n";
    cout << "\"1 2 3\"\n";

    bool weight_loop = true;
    while(weight_loop)
    {
        string weight_input = "";
        getline(cin, weight_input);
        smatch matchWeight = smatch();
        regex_match(weight_input, matchWeight, regWeight);
        if (matchWeight.empty() != true)
        {
            runtime_weight = stoi(matchWeight.str(1));
            vote_count_weight = stoi(matchWeight.str(2));
            rating_weight = stoi(matchWeight.str(3));
            break;
        }
        cout << "Invalid weights. Please select again\n";
    }

    cout << "runtime weight: " << runtime_weight << " count weight: " << vote_count_weight << " rating weight: " << rating_weight << "\n";

    vector<Movie*> merge_list;
    if(filter_genre)
    {
        for (int i=0; i<movieList.size(); i++)
        {
            if(movieList[i]->genre == selected_genre)
            {
                movieList[i]->score = ( ((movieList[i]->runtime/60)*runtime_weight) + ((movieList[i]->numVotes/1000*vote_count_weight)) + ((movieList[i]->avgRating)*(rating_weight)) );
                //cout << movieList[i]->score << "\n";
                merge_list.push_back(movieList[i]);
            }
        }
    }
    else
    {
        for (int i=0; i<movieList.size(); i++)
        {
            movieList[i]->score = ( ((movieList[i]->runtime/60)*runtime_weight) + ((movieList[i]->numVotes/100*vote_count_weight)) + ((movieList[i]->avgRating)*(rating_weight)) );
            merge_list.push_back(movieList[i]);
        }
    }

    vector<Movie*> quick_list = merge_list;



    steady_clock::time_point merge_begin = chrono::steady_clock::now();
    mergeSort(merge_list, 0, merge_list.size()-1);
    steady_clock::time_point merge_end = chrono::steady_clock::now();

    steady_clock::time_point quick_begin = chrono::steady_clock::now();
    quickSort(quick_list, 0, quick_list.size()-1);
    steady_clock::time_point quick_end = chrono::steady_clock::now();

    cout << "Merge Sort Time: " << chrono::duration_cast<chrono::microseconds>(merge_end - merge_begin).count() << " nanoseconds\n";
    cout << "Quick Sort Time: " << chrono::duration_cast<chrono::microseconds>(quick_end - quick_begin).count() << " nanoseconds\n";

    for (int i=0; i<merge_list.size(); i++)
    {
        if(merge_list[i]->title == quick_list[i]->title)
        {
            //cout << "Title: " << merge_list[i]->title << " Score: " << merge_list[i]->score << " Genre: " << merge_list[i]->genre << "\n";
        }
        else
        {
            cout << "mTitle: " << merge_list[i]->title << " Score: " << merge_list[i]->score << " Genre: " << merge_list[i]->genre << "\n";
            cout << "qTitle: " << quick_list[i]->title << " Score: " << quick_list[i]->score << " Genre: " << quick_list[i]->genre << "\n";
            cout << "ERROR: Mismatched movies at index " << i << "\n";
        }
    }

    cin >> jimbo;

    // vector<Movie*> movieList = inputMovies();
    // int genre, year;
    
    // // Interface
    // ////Get genre
    // cout << "Welcome to Movie Mappers etc." << endl;
    // cout << "|| ------------------------||" << endl;
    // cout << "What genre do you want?" << endl;
    // cout << "1. Action\n2. Comedy\n3. Drama\n4. Horror\n"; //Update, alphabetical?
    // cin >> genre; cout << endl;
    // // If statement for edge cases on choosing the genre
    
    // cin.clear();
    // ////Get year
    // cout << "What genre do you want?" << endl;
    // cout << "1. Before 1970\n2. 1970-1979\n3. 1980-1989\n4. 1990-1999\n5. 2000-2009\n6. 2010-2019\n7. 2020-Present\n" << endl; //Update, alphabetical?
    // cin >> year; cout << endl;
    // // If statement for edge cases on choosing the year
}