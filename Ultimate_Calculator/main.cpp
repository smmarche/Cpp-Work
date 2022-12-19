#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout; using std::endl; using std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    // TODO(student): implement the UI

    while (true){
        //PROBLEM:infinite loop
        string first_number;
        string sign;
        string second_number;
        cin >> first_number;
        if ((first_number == "q") || (first_number == "quit")){
            break;
        }
        cin >> sign >> second_number;

        if (sign == "+"){

            cout << ">> " << endl;
            cout << "ans =" << endl;
            cout << "\n";
            cout << "    " << add(first_number,second_number) << endl;
            cout << "\n";            
        }
        else if(sign == "*"){
         
            cout << ">> " << endl;
            cout << "ans =" << endl;
            cout << "\n";
            cout << "    " << multiply(first_number,second_number) << endl;
            cout << "\n";
        }

    }
    // cout << "\n" << endl;
    cout << ">> " << endl;
    cout << "farvel!" << endl;
    return 0;
}

