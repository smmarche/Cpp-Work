#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {

	cout << "Enter numbers 10 <= a <= b < 10000: ";

	int a;
	int b;
	cin >> a;
	cin >> b;

	// validate input (and reprompt on invalid input)
while (is_valid_range(a,b) == false) {
	cout << "Invalid Input" << endl;
	cout << "Enter numbers 10 <= a <= b < 10000: ";
	cin >> a;
	cin >> b;
	is_valid_range(a,b);
}
	// compute and display solution
	count_valid_mv_numbers(a,b);
	
	return 0;
}