#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int main() {
  string filename;
  int width = 0;
  int height = 0;
  int targetWidth = 0;
  int targetHeight = 0;
  
  // Add code to validate input (Do in part 1)
  cout << "Input filename: ";
  cin >> filename;
  cout << "Input width and height: ";
  cin >> width;
  //check that width is a number;
  if(cin.fail()){   // .fail() returns true if the cin failed
    cout << "Error: width is a non-integer value";
    return 1;
  }
  //check if our width is less than 1 and immediately exit if it's are not valid
  if(width <= 0){
    cout <<"Error: width must be greater than 0. You entered " << width << endl;
    return 1;
  }

  cin >> height;
  //check that height is a number
    if(cin.fail()){
    cout << "Error: height is a non-integer value";
    return 1;
  }
  //check if our height is less than 1 and immediately exit if it's are not valid
  if(height <= 0){
    cout <<"Error: height must be greater than 0. You entered " << height << endl;
    return 1;
  }


  cout << "Input target width and target height: ";
  cin >> targetWidth;
  //check if target width is a number
  if(cin.fail()){
    cout << "Error: target width is a non-integer value";
    return 1;
  }
  //check if target width is less than 1
  if(targetWidth <= 0){
    cout <<"Error: target width must be greater than 0. You entered " << targetWidth << endl;
    return 1;    
  } 

  cin >> targetHeight;
  //check if target height is a number
  if(cin.fail()){
    cout << "Error: target height is a non-integer value";
    return 1;
  }
  //check if target height is less than 1
  if(targetHeight <=0){
    cout <<"Error: target height must be greater than 0. You entered " << targetHeight << endl;
    return 1;    
  } 


  //check if our inputs are less than the target and immediately exit if they are not valid
  if(width < targetWidth){
    cout << "Error: target width must be less than width, " << targetWidth << " is greater than " << width << endl;
    return 1;
  }

  if (height < targetHeight){
    cout << "Error: target height must be less than height, " << targetHeight << " is greater than " << height << endl;
    return 1;
  }


  int originalWidth = width; // need to delete image array at end of program

  Pixel** image = createImage(width, height); // create array of size that we need
  if (image != nullptr) {
    if (loadImage(filename, image, width, height)) {
      cout << "Start carving..." << endl;
      
      //  remove seams 
      while((width > targetWidth) || (height > targetHeight)){
        if(width > targetWidth){
          int* Seam = findMinVerticalSeam(image, width, height);
          removeVerticalSeam(image, width, height, Seam);
          delete[] Seam;
          width -= 1;
        }
      }
      // set up output filename
      stringstream ss;
      ss << "carved" << width << "X" << height << "." << filename;
      outputImage(ss.str().c_str(), image, width, height);
    }
  
    // call last to remove the memory from the heap
    deleteImage(image, originalWidth);
  }
  



return 0;
}