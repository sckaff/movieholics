#include <fstream>
#include <string>
#include <iomanip>
#include <regex>
#include <chrono>
#include <cmath>

#include "Sort.h"
#include "Movie.h"
#include "progressbar.hpp"

using namespace chrono;

set<string> genres;
regex regGenre = regex("(\\d$)");
regex regWeight = regex("(\\d{1,}) (\\d{1,}) (\\d{1,}$)");

vector<Movie*> inputMovies()
{
    vector<Movie*> movieList;
    ifstream movieData("Data/merged_data.csv");
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
    int popularity_weight;
    int rating_weight;

    char set_weight;
    bool not_done = true;
    while(not_done){
        cout << "Are you in the mood for a highly rated (h) or poorly rated (p) film?" << endl; //Determine sign +/-
        cin >> set_weight; cin.clear();

        switch (set_weight)
        {
        case 'h':
            rating_weight = 1;
            not_done = false;
            break;
        case 'p':
            rating_weight = -1;
            not_done = false;
            break;
        default:
            cout << "Invalid choice. Please select again\n";
            continue;
        }
    }

    not_done = true;
    while(not_done){
        cout << "Do you want a more (m) or less (l) popular film?" << endl; //Determine sign +/-
        cin >> set_weight; cin.clear();

        switch (set_weight)
        {
        case 'm':
            popularity_weight = 1;
            not_done = false;
            break;
        case 'l':
            popularity_weight = -1;
            not_done = false;
            break;
        default:
            cout << "Invalid choice. Please select again\n";
            continue;
        }
    }

    not_done = true;
    while(not_done){
        cout << "Would you like longer movies (l), shorter movies (s)? Type (x) to ignore length." << endl;
        cin >> set_weight; cin.clear();

        switch (set_weight)
        {
        case 'l':
            runtime_weight = 1;
            not_done = false;
            break;
        case 's':
            runtime_weight = -1;
            not_done = false;
            break;
        case 'x':
            runtime_weight = -3;
            not_done = false;
            break;
        default:
            cout << "Invalid choice. Please select again\n";
            continue;
        }
    }

    not_done = true;
    while(not_done){  
        cout << "Do you care more about rating (r) or popularity (p)?" << endl; //Determines weights
        cin >> set_weight; cin.clear();
        switch (set_weight)
        {
        case 'r':
            rating_weight *= 3;
            popularity_weight *= 1;
            not_done = false;
            break;
        case 'p':
            rating_weight *= 1;
            popularity_weight *= 3;
            not_done = false;
            break;
        default:
            cout << "Invalid choice. Please select again\n";
            continue;
        }
    }

    cout << "Calculating movie scores...\n";

    int movie_score;
    vector<Movie*> merge_list;
    if(filter_genre)
    {
        for (int i=0; i<movieList.size(); i++)
        {

            if(movieList[i]->genre == selected_genre)
            {

                movie_score = 100*(((movieList[i]->runTimeNorm)*exp(1+runtime_weight)) + 
                      ((movieList[i]->numVotesNorm)*exp(1+popularity_weight)) + 
                      ((movieList[i]->avgRatingNorm)*exp(1+rating_weight)));

                movieList[i]->score = movie_score;
                //cout << movieList[i]->score << "\n";
                merge_list.push_back(movieList[i]);
            }
        }
    }
    else
    {
        for (int i=0; i<movieList.size(); i++)
        {

            movie_score = 100*(((movieList[i]->runTimeNorm)*exp(1+runtime_weight)) + 
                      ((movieList[i]->numVotesNorm)*exp(1+popularity_weight)) + 
                      ((movieList[i]->avgRatingNorm)*exp(1+rating_weight)));

            movieList[i]->score = movie_score;
            merge_list.push_back(movieList[i]);
        }
    }

    vector<Movie*> quick_list = merge_list;

    cout << "Sorting movies...\n";

    steady_clock::time_point merge_begin = chrono::steady_clock::now();
    mergeSort(merge_list, 0, merge_list.size()-1);
    steady_clock::time_point merge_end = chrono::steady_clock::now();

    steady_clock::time_point quick_begin = chrono::steady_clock::now();
    quickSort(quick_list, 0, quick_list.size()-1);
    steady_clock::time_point quick_end = chrono::steady_clock::now();

    cout << "Completed\n";
    cout << "Merge Sort Time: " << chrono::duration_cast<chrono::microseconds>(merge_end - merge_begin).count() << " nanoseconds\n";
    cout << "Quick Sort Time: " << chrono::duration_cast<chrono::microseconds>(quick_end - quick_begin).count() << " nanoseconds\n";

    bool specific_movie = false;
    bool random_movie = false;
    char how_many_pick;
    not_done = true;
    while(not_done){  
        cout << "Display a list (l) of movies, a specific (s) movie, or a random movie (r)?" << endl;
        cin >> how_many_pick; cin.clear();
        switch (how_many_pick)
        {
        case 'l':
            specific_movie = false;
            not_done = false;
            break;
        case 's':
            specific_movie = true;
            not_done = false;
            break;
        case 'r':
            specific_movie = true;
            random_movie = true;
            not_done = false;
            break;
        default:
            cout << "Invalid choice. Please select again\n";
            continue;
        }
    }

    int chosen_movie_index;
    int how_many_movies = 1;
    if (specific_movie)
    {
        if(random_movie)
        {
            chosen_movie_index = (rand() % merge_list.size());
        }
        else
        {
            not_done = true;
            while(not_done)
            {
                cout << "What index do you want between (0-" << merge_list.size() - 1 << ")?\n";
                cin >> chosen_movie_index; cin.clear();
                if (chosen_movie_index >= 0 && chosen_movie_index < merge_list.size())
                {
                    not_done = false;
                }
                else
                {
                    cout << "Invalid choice. Please select again\n";
                }
            }
        }

        cout << "||============================================|| Popularity: " << merge_list[chosen_movie_index]->numVotes << " | Average Rating: " << merge_list[chosen_movie_index]->avgRating << " | Length: " << merge_list[chosen_movie_index]->runtime << "min" << endl
             << "  YOUR MOVIE #" << chosen_movie_index << ": " << merge_list[chosen_movie_index]->title << endl
             << "||============================================||" << endl
             << "MOVIEHOLICS SCORE: " << merge_list[chosen_movie_index]->score << endl;
    }
    else
    {
        not_done = true;
        while(not_done)
        {
            cout << "How many movies would you like to display between (1-" << merge_list.size() << ")?\n";
            cin >> how_many_movies; cin.clear();
            if (how_many_movies > 0 && how_many_movies <= merge_list.size())
            {
                int movie_number_label = 1;
                for (int i = merge_list.size() - 1; i > merge_list.size() - how_many_movies - 1; i--)
                {   
                    if (i == merge_list.size() - 1){
                        cout << "||============================================|| Popularity: " << merge_list[i]->numVotes << " | Average Rating: " << merge_list[i]->avgRating << " | Length: " << merge_list[i]->runtime << "min" << endl
                            << "  YOUR PERFECT MOVIE: " << merge_list[i]->title << endl
                            << "||============================================||" << endl
                            << "MOVIEHOLICS SCORE: " << merge_list[i]->score << endl << endl;
                            
                        
                        cout << "In case you're wondering, here are the next " << how_many_movies - 1 << " movies in the list: \n"; 
                    }    
                    else
                    {   
                        cout << "#" << movie_number_label << ": Title: " << merge_list[i]->title 
                            << " | Popularity: " << merge_list[i]->numVotes 
                            << " | Average Rating: " << merge_list[i]->avgRating 
                            << " | Length: " << merge_list[i]->runtime << "min"
                            << " | MOVIEHOLICS SCORE: " << merge_list[i]->score << endl;
                    }
                    movie_number_label++;
                }
                not_done = false;
            }
            else
            {
                cout << "Invalid choice. Please select again\n";
            }
        }
        
    }

    cout << "\nType anything to close the program\n";

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