
#include "MyString.h"
#include <iostream>
using std::ostream;

MyString::MyString() : string_size{0},char_array{new char[1]} ,string_capacity{1}{
    char_array[0] = '\0';
}

MyString::MyString(MyString& the_string) : string_size(the_string.string_size),char_array(new char[the_string.capacity()]),string_capacity(the_string.string_size+1){
    for(size_t b = 0; b < string_size; b++){
        char_array[b] = b < string_size ? the_string.at(b) : static_cast<char>(0);
    }

}

MyString::MyString(const char* charStr) : char_array{nullptr}, string_size{0}, string_capacity{0} {
    size_t num = 0; 

    while(charStr[num] != '\0'){
        num+=1;
    }

    char* possible_array = new char[num + 1]{};
    for(size_t c = 0; c < (num + 1); c++){
        possible_array[c] = charStr[c];
    }
    string_size = num;
    string_capacity = num + 1;
    delete[] char_array;
    char_array = possible_array;    
    
}

MyString::~MyString() {
    
    delete[] char_array;
    char_array = nullptr;
    string_capacity = 0;
    string_size = 0;

}

void MyString::resize(size_t sizeToResize) {
    if(sizeToResize < string_size){
        string_size = sizeToResize;
    }
    char_array[sizeToResize] = '\0';
    string_capacity = sizeToResize;

    

}

size_t MyString::capacity() const{
    return string_capacity;
}

size_t MyString::size() const {
    return string_size;
} 

size_t MyString::length() const {
    return string_size;
}

const char* MyString::data() const{
    return char_array;
}

bool MyString::empty() const {
    if(string_size != 0){
        return false;
    }else{
        return true;
    }
}

const char& MyString::front() const {
    if(string_size){
        return char_array[0];
    }
    else if (!string_size){
        throw std::out_of_range("error: empty");
    }
}

const char& MyString::at(size_t position) const{
    
    if (position >= string_size)
    {
        throw std::out_of_range("this position is outside of the scope of the string");


    }

    else if(position < string_size){
        return char_array[position];
    }

}

void MyString::clear() {

    for(size_t a = 0; a < string_size; ++a){
        char_array[a] = '\0';
    }
    string_size = 0;
    string_capacity = 1;
}

MyString& MyString::operator=(const MyString& the_string){
    bool a = (this == &the_string);
    if(!a){
        delete[] char_array;
        char_array = new char[the_string.size() + 1];
        for(size_t i = 0; i < the_string.size(); i++){
            char_array[i] = the_string.at(i);
        }
        this -> string_capacity = the_string.capacity();
        this -> string_size = the_string.size();
        this -> char_array[this->string_size] = '\0';
    }
    return *this;   
}

MyString& MyString::operator+=(const MyString& the_string){
    size_t size_of_string = the_string.string_size;
    size_t updated_size_of_string = 1 + size_of_string + string_size;
    char* possible_char_array = new char[updated_size_of_string]{};
    for(size_t y = 0; y < string_size; y++){
        possible_char_array[y] = char_array[y];
    }

    for(size_t w = (string_size); w < (updated_size_of_string); w++){
        possible_char_array[w] = the_string.char_array[w - string_size];
    }
    string_capacity = updated_size_of_string;
    string_size = updated_size_of_string - 1;

    delete[] char_array;
    char_array = possible_char_array;  
    
    return *this;
}

size_t MyString::find(const MyString& the_string, size_t given_position) const {
    
static const size_t character_position = -1;

    char beginning_char = the_string.char_array[0];
    size_t new_length = the_string.length();
    size_t return_value;
    bool found = true;
    for(size_t x = given_position; x < string_size; x++){
        if(char_array[x] == beginning_char){
            return_value = x;
            size_t m = x;
            for(size_t t = 0; t < new_length; t++){
                if(char_array[m] != the_string.char_array[t]){
                    found = false;
                    break;
                }
                m+=1;
            }
            if(found){
                return return_value;
            }
        }
    }
    return character_position;
}

bool operator==(const MyString& lhs, const MyString& rhs){


    if (lhs.size() != rhs.size()){
        return false;
    }
    for (size_t z = 0; z < lhs.size(); ++z){
        if (lhs.at(z) != rhs.at(z))
            return false;
    }

    return true;

}

ostream& operator<<(ostream& outputStr, const MyString& the_string){

    for(size_t n = 0; n < the_string.size(); n++){
        outputStr << the_string.at(n);
    }
    return outputStr;



}

MyString operator + (const MyString& rhs, const MyString& lhs){


    MyString addition(rhs.data());
    addition += lhs;
    return addition;


}

