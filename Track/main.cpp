

#include <iostream>
#include <fstream>
#include "parallel_tracks.h"

using std::cin; using std::cout; using std::endl;
using std::string; using std::invalid_argument;
using std::domain_error; using std::getline;

int main()
{
    // TODO: create arrays needed

	double timeArray[SIZE];
    unsigned int numberArray[SIZE];
    string countryArray[SIZE];
    string lastnameArray[SIZE];
    unsigned int rankArray[SIZE];

    // TODO: prep all arrays
	
    prep_double_array(timeArray);
    prep_unsigned_int_array(numberArray);
    prep_string_array(countryArray);
    prep_string_array(lastnameArray);

    // TODO: load the runner's data into the array

    // if unable to load runner data
    //   1) output "Bad input" to standard out
    //   2) exit program by returning 1


    if (get_runner_data(timeArray, countryArray, numberArray, lastnameArray) == false){
        cout << "Bad input"<<endl;
        return 1;
    }

    // TODO: determine ranking, notice the rank array receives the results
    get_ranking(timeArray, rankArray);
    // TODO: Output results
    print_results(timeArray, countryArray, lastnameArray, rankArray);
    // this is not required in C++ but many people still explitly add it
    return 0; 
}


