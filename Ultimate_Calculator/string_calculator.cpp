#include <iostream>
#include <string>

#include "./string_calculator.h"

using std::cout; using std::endl;
using std::string;


unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement
    //convert a string digit to an int digit
    if (digit >= 48 && digit <= 57){
        return (int)digit - '0';
    }

    else {
        throw std::invalid_argument("Invalid");
    }
}

char decimal_to_digit(unsigned int decimal) {
    //convert an int digit to a string digit
    if (decimal <= 9){
      return decimal + '0';
    }
    else{
        throw std::invalid_argument("Invalid");
    }
}

string trim_leading_zeros(string num) {

    string trimmed_string = num;
    string keep_the_sign = "";
    //if the string is negative store it in negative sign
    if (trimmed_string[0] == '-'){
        keep_the_sign.push_back(trimmed_string[0]);
        trimmed_string.erase(0,1);
    }
    while (trimmed_string[0] == '0'){
        //if the first character of the string is 0 get rid of it
        if (trimmed_string[0] == '0'){
            trimmed_string.erase(0,1);
            //if at any point trimmed string is empty put a zero back and break the loop
            if (trimmed_string == ""){
                //handling the special case of -0000->0
                keep_the_sign.erase();
                trimmed_string = "0";
                break;
            }
        }
    }
    //put the sign back in the front of the trimmed string
    trimmed_string = keep_the_sign + trimmed_string;
    return trimmed_string;
}

string add(string lhs, string rhs) {
    int i;
    int carry = 0;
    int pre_answer;
    string answer;
    string hold_sign = "";
     // TODO(student): implement
    
    // trim leading zeros 1st
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    int lhs_length = lhs.length();
    int rhs_length = rhs.length();
     //check negative sign
     if (lhs[0] == '-'&& rhs[0] == '-'){
        //store then erase the negative sign
        hold_sign = "-";
        lhs.erase(0,1);
        rhs.erase(0,1);
     }
        //calculate the case when one of the terms is 0
     if (lhs == "0"){
        answer = rhs;
        return answer;
     }
     else if (rhs == "0"){
        answer = lhs;
        return answer;
     }
    if (lhs_length > rhs_length){
        rhs.insert(0, lhs_length - rhs_length, '0');
    }
   
    if (lhs_length < rhs_length){
        lhs.insert(0, rhs_length - lhs_length, '0');   
    }
     //iterate based on the size of either string since they are equal
     for (i = lhs.size() - 1; i >= 0; i--){
        //convert both digits to int and sum each digit and anything in carry
        pre_answer = (rhs[i] - '0') + (lhs[i] - '0') + carry;
        //convert back to str and put the ones place in the answer
        answer.insert(0, 1, pre_answer % 10 + '0');
        //put the tens place in carry
        carry = pre_answer / 10;
     }
     //after the numbers are added if anything remains in carry, insert it in the front of answer
     if (carry){
        answer.insert(0, 1, carry + '0');
     }
     //don't forget the sign
     answer = hold_sign + answer;
     return answer;
    

   
}

string multiply(string lhs, string rhs){

    // TODO(student): implement
     //trim leading zeros 1st
    string trimmed_lhs = trim_leading_zeros(lhs);
    string trimmed_rhs = trim_leading_zeros(rhs);

     //if either or both sides are 0
    if (trimmed_lhs == "0"){
        return "0";
    }
    else if (trimmed_rhs == "0"){
        return "0";
    }
    string hold_sign = "";
     //check negative sign

     if (trimmed_lhs[0] == '-' && trimmed_rhs[0] == '-'){
        //store then erase the negative sign
         hold_sign = "";
        trimmed_lhs.erase(0,1);
        trimmed_rhs.erase(0,1);
     }
     else if (trimmed_lhs[0] == '-'){
        hold_sign = "-";
        trimmed_lhs.erase(0,1);
     }
     else if (trimmed_rhs[0] == '-'){
        hold_sign = "-";
        trimmed_rhs.erase(0,1);
     }
     if (trimmed_lhs.length() == 0){
        return "0";
     }
          if (trimmed_rhs.length() == 0){
        return "0";
     }
     int a = trimmed_lhs.length();
     int b = trimmed_rhs.length();
     string final_answer(a + b, '0');
     //multiplication process from right to left
     for (int i = a - 1; i >= 0; i--) {
          for (int j = b - 1; j >= 0; j--) {
               int c = (trimmed_lhs[i] - '0') * (trimmed_rhs[j] - '0') + (final_answer[i + j + 1] - '0');
               final_answer[i + j + 1] = decimal_to_digit(c % 10);
               final_answer[i + j] += c / 10;
          }
     }
     return final_answer = hold_sign + trim_leading_zeros(final_answer);
    
 return final_answer;
}

