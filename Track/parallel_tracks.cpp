#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "parallel_tracks.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;


bool get_runner_data( double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
  int i = 0;

  // Update function to return the correct boolean values based on the parameters

  //Get input and store into the arrays
  for (i = 0; i < 9; ++i) {
	//taking in each line input
		cin >> timeArray[i] >> countryArray[i] >> numberArray[i] >> lastnameArray[i];
		//check if the time is less than 0
		if (timeArray[i] <= 0){
			// cout << "time bad " << timeArray[i]<< endl;
			return false;
		}
		//check if the country has less than 3 letters
		if (countryArray[i].size() != 3){
			// cout << "country bad " << countryArray[i]<< endl;
			return false;
		}
		// if (numberArray[i].size()!= 1 || numberArray[i].size()!= 2){
		// 	return false;
		// } trying to check the how many digits
		if(lastnameArray[i].size() <= 1){
			// cout << "lastname bad " << lastnameArray[i]<< endl;
			return false;
		}
		//check if all 3 letters in country are all caps and letters
		
		for (unsigned int j = 0; j < countryArray[i].size(); ++j){
			if (!isupper(countryArray[i].at(j)))
			{
				// cout << "country bad " << countryArray[i]<< endl;
				return false;
			}
			// if(!isalpha(countryArray[i].at(j)))
			// {
			// 	return false;
			// }
			
		}
		
		// if (!isdigit(numberArray[i]) ){
		// 	return false;
		// }
		for (unsigned int l = 0; l < lastnameArray[i].size(); ++l){
			if(!isalpha(lastnameArray[i].at(l))){
				// cout << "lastname bad " << lastnameArray[i]<< endl;
				return false;
			}
  		}
		if(numberArray[i] >= 100){
		// cout << "number bad" << numberArray[i] << endl;
		return false;
		}

  	}

  //TODO


  return true; // set so it will compile
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an array of doubles is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
{
	// making sure all values within the array are set to 0.0;
  	//TODO
  int i;
  for (i = 0; i <= 8; ++i){
	ary[i] = 0.0;
  }
}

//-------------------------------------------------------
// Name: prep_unsigned_int_array
// PreCondition:  an array of unsigned ints is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	//TODO
	int i = 0;
	for (i = 0; i <= 8; ++i){
	ary[i] = 0;
  }
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  an array of strings is passed in
// PostCondition: each element in the array is set to "N/A"
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	//TODO
	int i = 0;
	for (i = 0; i <= 8; ++i){
	ary[i] = "N/A";
  }
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	//TODO
	int quickestIndex = -1;
	double quickestTime = INT32_MAX;
	for(int i = 0; i <= 8; ++i){
		quickestIndex = -1;
		quickestTime = INT32_MAX;
		for(int j = 0; j <= 8; ++j){
			if (rankArray[j] != 0)
				continue;
			if(quickestTime > timeArray[j]){
				quickestTime = timeArray[j];
  				quickestIndex = j;
			}
		}
		rankArray[quickestIndex] = i + 1;
	}

}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays them along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(std::string ret) {
	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}