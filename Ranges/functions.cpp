#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {

	if ((10 <= a) && (a <= b) && (b < 10000) && (a < 10000 && b >= 10 )) {
		return true;
	}
	else {
	return false;
	}
}

char classify_mv_range_type(int number) {

	// return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	int remainingNumber = number;
	char status = 'X';

	// getting the end digit of the number

	int endNumber = remainingNumber % 10;
	// getting the digit(s) before the end digit of the number

	remainingNumber = remainingNumber / 10;

	// this should run while there are still more numbers to the left of the current number were on
	while (remainingNumber > 0) {

		// getting only the number before the number we are currently on
		int secondNumber;
		secondNumber = remainingNumber % 10;

		// comparisons adjacent numbers and if it preceeded a M or a V value

		if (endNumber > secondNumber){
			if (status == 'M') {
				return 'N';
			}
			status = 'M';
		}
		else if (endNumber < secondNumber){
			if (status == 'V') {
				return 'N' ;
			}
			status = 'V';
		}	
		
		else{
			return 'N';
			//move one digit over
		}
		endNumber = secondNumber;
		remainingNumber /= 10;
	}
	return status;
}

void count_valid_mv_numbers(int a, int b) {
	// count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out
	int counter;
	int mountain = 0;
	int valley = 0;

	//loop through the interval
	//loops starts at the beginning of the interval, increases by one integer, and stops when the number is greater than the max number
	for (counter = a; counter <= b; ++counter){
		if (classify_mv_range_type(counter) == 'M') {
			mountain += 1;
		}
		else if (classify_mv_range_type(counter) == 'V') {
			valley += 1;
		} 
	}
	cout << "There are " << mountain << " mountain ranges and " << valley << " valley ranges between " << a << " and " << b << "." << endl; 
}