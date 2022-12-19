
#ifndef _MYSTRING_H
#define _MYSTRING_H
#include <iostream>
using std::ostream;



class MyString {

    private:
        size_t string_capacity; 
        char* char_array; 
        size_t string_size; 
        

    public:
    //Constructor
        MyString();
    //Copy constructor

        MyString(MyString& the_string);
        MyString(const char* char_string);
    //Destructor
        ~MyString();
    //remaining string functions

    //Resize the string to the sizeToResize
        void resize(size_t new_resize); 
    //The size of the storage capacity currently allocated for the string
        size_t capacity() const; 
    //bytes in the string
        size_t size() const; 
    //string size
        size_t length() const; 
        const char* data() const;
        // return false if string is not empty (length > 0)
        bool empty() const;
        //return address to first char in string
        const char& front() const;
        //return address to specified index in string
        const char& at(size_t position) const;//index
        //deletes everything in string
        void clear();
        //Copy assignment operator
        MyString& operator = (const MyString& the_string);
        MyString& operator += (const MyString& the_string);
        size_t find(const MyString& the_string, size_t index = 0) const;   

          
};
MyString operator + (const MyString& lhs, const MyString& rhs);
bool operator == (const MyString& lhs, const MyString& rhs);
ostream& operator << (ostream& stringout, const MyString& the_string);

#endif