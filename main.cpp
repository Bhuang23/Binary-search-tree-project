//
// <<Brian Huang>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"
using namespace std;
//Movie data structure
struct MovieData
{
		int PubYear;
		string MovieName;
		int Num5Stars;
		int Num4Stars;
		int Num3Stars;
		int Num2Stars;
		int Num1Star;
};
//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}


//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//
void InputMovies(string moviesFilename)
{
  ifstream moviesFile(moviesFilename);
  int      id, pubYear;
  string   name;

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    name = trim(name);  

    // debugging:
    cout << id << "," << pubYear << "," << name << endl;

    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
  }
}
//isInteger function returns 1 if the input is a integer and 0 if it is not
int isInteger(string input)
{
	for(int i =0; i < (int)input.size(); i++)
	{
		if(isdigit(input[i]) == 0 )
		{
			return 0;
		}
	}
	return 1;
}
//
// main
//
int main()
{
  string moviesFilename;
  string reviewsFilename;
  binarysearchtree<int, MovieData> bstMoviesByID;
  binarysearchtree<string, int> bstMoviesByName;
  int nummovies = 0;
  int numreviews = 0;
  cout << "movies file?> ";
  cin >> moviesFilename;

  cout << "reviews file?> ";
  cin >> reviewsFilename;
  //create all the movie variables and struct
  ifstream moviesFile(moviesFilename);
  int      id, pubYear;
  string   name;
  MovieData md;

  if (!moviesFile.good())//check if file can be opened
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
	return 0;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())//check if reached end of file
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    name = trim(name);  

    // debugging:
	md.PubYear = pubYear;
	md.MovieName = name;
	md.Num5Stars =0;
	md.Num4Stars =0;
	md.Num3Stars =0;
	md.Num2Stars =0;
	md.Num1Star = 0;
	bstMoviesByID.insert(id, md);
	bstMoviesByName.insert(name, id);
	nummovies++;
    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
  }
  //created review variables
  ifstream reviewsFile(reviewsFilename);
  int reviewid, ID, rating;

  if (!reviewsFile.good())//check if file can be opened
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
  }

  reviewsFile >> reviewid;  // get first review ID, or set EOF flag if file empty:

  while (!reviewsFile.eof())//check if reached end of file
  {
    // we have more data, so input id and rating:
    reviewsFile >> ID;
    reviewsFile >> rating;  // movie rating fills rest of input line:
    //add 1 to the struct Moviedata's rating variables for each of the ratings in the review file
	if(rating == 1)
		{
			//add 1 to Num1Star in moviedata structure
			(bstMoviesByID.search(ID)->Num1Star)+=1;
		}
		else if(rating == 2)
		{
			//add 1 to Num2Stars in moviedata structure
			(bstMoviesByID.search(ID)->Num2Stars)+=1;
		}
		else if(rating == 3)
		{
			//add 1 to Num3Stars in moviedata structure
			(bstMoviesByID.search(ID)->Num3Stars)+=1;
		}
		else if(rating == 4)
		{
			//add 1 to Num4Stars in moviedata structure
			(bstMoviesByID.search(ID)->Num4Stars)+=1;
		}
		else if(rating == 5)
		{
			//add 1 to Num5Stars in moviedata structure
			(bstMoviesByID.search(ID)->Num5Stars)+=1;
		}
	numreviews++;//increment numreviews
    reviewsFile >> reviewid;  // get review ID, or set EOF flag if no more data:
  }
  //search for review movie id 
  cout << "Num movies: " << nummovies << endl;
  cout << "Num reviews: " << numreviews << endl;
  cout << endl;
  cout << "Tree by movie id: " << "size=" << bstMoviesByID.size() << ", " << "height=" << bstMoviesByID.height() << endl;
  cout << "Tree by movie name: " << "size=" << bstMoviesByName.size() << ", " << "height=" << bstMoviesByName.height() << endl;
  string junk;
  getline(cin, junk);
  string input;
  cout << endl;
  while(input != "#")//continue program is input isn't "#"
  {
	  //begin with prompt
	  cout << "Enter a movie id or name (or # to quit)> ";
	  getline(cin, input);
	// read entire input line
	// check if input is the movie name
	  if((bstMoviesByName.search(input) != nullptr))
	  {
		  cout << "Movie ID: " << *bstMoviesByName.search(input) << endl;
		  cout << "Movie Name: " << input << endl;
		  //check if there are no reviews by checking if the sum of all the reviews is 0
		  if(((bstMoviesByID.search(*bstMoviesByName.search(input))->Num1Star)
		  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num2Stars)
		  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num3Stars)
		  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num4Stars)
		  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num5Stars)) == 0)
		  {
			cout << "Avg rating: " << 0 << endl;
		  }
		  //divide the number of reviews by the sum of all the reviews
		  else
		  {
			  //add up all the reviews for the movie convert to double and then divide by the number 
			  //of reviews to get double avg
			  cout << "Avg rating: " << (double)((bstMoviesByID.search(*bstMoviesByName.search(input))->Num1Star)
			  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num2Stars)*2
			  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num3Stars)*3
			  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num4Stars)*4
			  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num5Stars)*5)
			  /((bstMoviesByID.search(*bstMoviesByName.search(input))->Num1Star)
			  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num2Stars)
			  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num3Stars)
			  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num4Stars)
			  +(bstMoviesByID.search(*bstMoviesByName.search(input))->Num5Stars)) << endl;
		  }
		  //print out the reviews
		  cout << "5 stars: " << ((bstMoviesByID.search(*bstMoviesByName.search(input)))->Num5Stars)<< endl;
		  cout << "4 stars: " << ((bstMoviesByID.search(*bstMoviesByName.search(input)))->Num4Stars)<< endl;
		  cout << "3 stars: " << ((bstMoviesByID.search(*bstMoviesByName.search(input)))->Num3Stars)<< endl;
		  cout << "2 stars: " << ((bstMoviesByID.search(*bstMoviesByName.search(input)))->Num2Stars)<< endl;
		  cout << "1 star: " <<  ((bstMoviesByID.search(*bstMoviesByName.search(input)))->Num1Star) << endl;
	  }
	  //check if input is an integer and if it is the movie id
	  else if((isInteger(input) == 1) && (bstMoviesByID.search(stoi(input)) != nullptr))
	  {
		  cout << "Movie ID: " << input << endl;
		  cout << "Movie Name: " << bstMoviesByID.search(stoi(input))->MovieName << endl;
		  //check if there are no reviews by checking if the sum of all the reviews is 0
		  if(((double)((bstMoviesByID.search(stoi(input))->Num1Star)
		  +(bstMoviesByID.search(stoi(input))->Num2Stars)
		  +(bstMoviesByID.search(stoi(input))->Num3Stars)
		  +(bstMoviesByID.search(stoi(input))->Num4Stars)
		  +(bstMoviesByID.search(stoi(input))->Num5Stars))) == 0)
		  {
			  cout << "Avg rating: " << 0 << endl;
		  }
		  //divide the number of reviews by the sum of all the reviews
		  else
		  {
			  
			  //add up all the reviews for the movie convert to double and then divide by the number 
			  //of reviews to get double avg
			  cout << "Avg rating: " << ((double)((bstMoviesByID.search(stoi(input))->Num1Star)
			  +(bstMoviesByID.search(stoi(input))->Num2Stars*2)
			  +(bstMoviesByID.search(stoi(input))->Num3Stars*3)
			  +(bstMoviesByID.search(stoi(input))->Num4Stars*4)
			  +(bstMoviesByID.search(stoi(input))->Num5Stars*5)))/
			((double)((bstMoviesByID.search(stoi(input))->Num1Star)
			  +(bstMoviesByID.search(stoi(input))->Num2Stars)
			  +(bstMoviesByID.search(stoi(input))->Num3Stars)
			  +(bstMoviesByID.search(stoi(input))->Num4Stars)
			  +(bstMoviesByID.search(stoi(input))->Num5Stars))) << endl;
		  }
		  //print out the reviews
		  cout << "5 stars: " << (bstMoviesByID.search(stoi(input))->Num5Stars)<< endl;
		  cout << "4 stars: " << (bstMoviesByID.search(stoi(input))->Num4Stars)<< endl;
		  cout << "3 stars: " << (bstMoviesByID.search(stoi(input))->Num3Stars)<< endl;
		  cout << "2 stars: " << (bstMoviesByID.search(stoi(input))->Num2Stars)<< endl;
		  cout << "1 star: " <<  (bstMoviesByID.search(stoi(input))->Num1Star) << endl;
	  }
	  else if(input == "#")//do nothing
	  {
	  }
	  else//input is not movie name or movie id
	  {
		  cout << "not found..." << endl;
      }
	  cout << endl;
  }
  
  return 0;
}
