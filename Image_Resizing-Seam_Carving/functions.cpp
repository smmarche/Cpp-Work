#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // delete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

int* createSeam(int length) {
  int* array_of_ints;
  //create a pointer that points to the address of an array on the heap
  array_of_ints = new int[length];
  for (int i = 0;i <= length - 1; ++i){
    array_of_ints[i] = 0;
  }
  return array_of_ints;
}

void deleteSeam(int* seam) {
  delete[] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  char file_type[3];
  int file_width = 0;
  int file_height = 0;
  int file_max_color_value = -1;
  int additional_info = -1;

  ifstream inFS; //input file stream

  //open file
  inFS.open(filename);
  // verify that it opened succesfully
  if(!inFS.is_open()){
    cout << "Error: failed to open input file - " << filename;
    return false;
  }

  // retrieve and check that the file type is P3
  inFS >> file_type;
    if(!(toupper(file_type[0]) == 'P' && file_type[1] == '3')){
    cout << "Error: type is " << file_type << " instead of P3";
    return false;
  }

 // retrieve and check the width is an integer
  inFS >> file_width;
  if(!inFS.good()){
    cout << "Error: read non-integer value";
    return false;
  }
  //check that the file width is equal to input width
  if(file_width != width){
    cout << "Error: input width (" << width <<") does not match value in file (" << file_width << ")";
    return false;
  }

  //retrieve and check the height is an integer
  inFS >> file_height;
  if(!inFS.good()){
    cout << "Error: read non-integer value";
    return false;
  }
  // check that the file height is equal to the input height
  if(file_height != height){
    cout << "Error: input height (" << height <<") does not match value in file (" << file_height << ")";
    return false;
  }

  //retrieve max color and verify that it is an integer
  inFS >> file_max_color_value;
  if(!inFS.good()){
    cout << "Read non-integer value for max color value";
    return false;
  }
  // verify that max color is 255
  if(file_max_color_value !=255){
    cout << "Error: max color value must be 255 " << file_max_color_value;
    return false;
  }
  // derive correct number of RGB

  //retrieve color values (formatted like createImage) by row and column
  for (int row=0; row <= height - 1; ++row) {
    for (int col=0; col <= width - 1; ++col) {

      //cout << "(" << col << ", " << row << ")" << endl;
      inFS >> image[col][row].r;
      if(inFS.fail() && !inFS.eof()){
        cout << "Error: read non-integer value";
        return false;
      }
      //check that each value is not less than 0 or great than max color value
      if (image[col][row].r < 0 || image[col][row].r > 255){
        cout << "Error: invalid color value " << image[col][row].r;
        return false;
      }

      inFS >> image[col][row].g;
      if(inFS.fail() && !inFS.eof()){
        cout << "Error: read non-integer value";
        return false;
      }
      //check that each value is not less than 0 or great than max color value
      if (image[col][row].g < 0 || image[col][row].g > 255){
        cout << "Error: invalid color value " << image[col][row].g;
        return false;
      }
      // check that there aren't less than the correct number of RGB values
      if(inFS.eof()){
        cout << "Error: not enough color values";
        return false;
      }
      inFS >> image[col][row].b;
      if(inFS.fail() && !inFS.eof()){
        cout << "Error: read non-integer value"; 
        return false;
      }
      //check that each value is not less than 0 or great than max color value
      if (image[col][row].b < 0 || image[col][row].b > 255){
        cout << "Error: invalid color value " << image[col][row].b;
        return false;
      }
    
    }

  }
  // check that there isn't more data after the for loop
  inFS >> additional_info;
  //if inFS doesn't fail there is more stuff in the file
  if(!inFS.fail()){
    cout << "Error: too many color value";
    return false;
  }
  

return true;
}

bool outputImage(string filename, const Pixel*const* image, int width, int height) {
  ofstream outFS; //output file stream
  string file_type = "P3";
  int max_color = 255;
  
  //open file
  outFS.open(filename);
  
  //check if file is open
  if(!outFS.is_open()){
    cout << "Error: failed to open output file - " << filename;
    return false;
  }
  //output the file type
  outFS << file_type << endl;
  
  //output the given height and width
  outFS << width << " " << height << endl;

  //output the max color
  outFS << max_color << endl;

  //output the rgb values for the image
  for (int row=0; row <= height - 1; ++row) {
    for (int col=0; col <= width - 1; ++col) {
      outFS << image[col][row].r << " ";
      outFS << image[col][row].g << " ";
      outFS << image[col][row].b << " " << endl;

    }

  }

  return true;
}

int energy(const Pixel*const* image, int x, int y, int width, int height) { 
 int left_x = x-1;
 int right_x = x+1;
 int top_y = y-1;
 int bottom_y = y+1;
 int change_in_x_R;
 int change_in_x_B;
 int change_in_x_G;
 int change_in_y_R;
 int change_in_y_G;
 int change_in_y_B;
 int x_gradient;
 int y_gradient;
 int energy_pixel;


// handling border cases
  if(width > 1){
    if(x == 0){
      left_x = width-1; //use x value in right most column
    }
    else if(x == width - 1){
      right_x = 0; //use x value in left most column
    }
  

  // calculate x_gradient 

  change_in_x_R = (image[left_x][y].r - image[right_x][y].r);
  change_in_x_G = (image[left_x][y].g - image[right_x][y].g);
  change_in_x_B = (image[left_x][y].b - image[right_x][y].b);

  x_gradient = pow(change_in_x_R,2) + pow(change_in_x_G,2) + pow(change_in_x_B,2);
  }

  else{
    x_gradient = 0;
  }

 // calculate y_gradient 
   if(height > 1){
    if(y == 0){
      top_y = height-1; //use y value in bottom most row
    }
    else if(y == height-1){
      bottom_y = 0;//use y value in top most row
    }
  change_in_y_R = (image[x][top_y].r - image[x][bottom_y].r);
  change_in_y_G = (image[x][top_y].g - image[x][bottom_y].g);
  change_in_y_B = (image[x][top_y].b - image[x][bottom_y].b);

  y_gradient = pow(change_in_y_R,2) + pow(change_in_y_G,2) + pow(change_in_y_B,2);
   }

  else{
    y_gradient = 0;
  }

 //energy pixel
 energy_pixel = x_gradient + y_gradient;

  return energy_pixel;
}



int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  int total_energy;
  //initialized to energy for pixel (start_col,0)
  total_energy = energy(image, start_col, 0, width, height);
  //loads the first position
  seam[0] = start_col;
  int right;
  int left;
  int forward;

  //iterate through by row
  for(int i = 1; i < height; ++i){
    if (width == 0){//you can only go forward
      right = INT32_MAX;
      left = INT32_MAX;
      forward = energy(image, start_col, i, width, height);

    }
    //HELP: not passing 2i - the case of 1 column
    else if(width == 1 && start_col == 0){//you can only go left or forward
      right = INT32_MAX;
      left = INT32_MAX;
      forward = energy(image, start_col, i, width, height);
    
    }
    else if(width == 1 && start_col == width){//you can only go right or forward
      right = energy(image, start_col - 1, i, width, height);
      left = INT32_MAX;
      forward = energy(image, start_col, i, width, height);

    }

    else if(start_col == 0){ //start col has a right edge 
      right = INT32_MAX;
      left = energy(image, start_col + 1, i, width, height);
      forward = energy(image, start_col, i, width, height);
    }
    else if (start_col == width - 1){//start col has a left edge
      left = INT32_MAX;
      right = energy(image, start_col - 1, i, width, height);
      forward = energy(image, start_col, i, width, height);    
    }
    else{//start col has columns on either side
    right = energy(image, start_col - 1, i, width, height);
    forward = energy(image, start_col, i, width, height);
    left = energy(image, start_col + 1, i, width, height);
    }

    //decide which energies to use and include cases of a tie
    if((left < right) && (left < forward)){// case where left is less than both
      start_col += 1;
      total_energy += left; //add minimum energy to total energy
      seam[i] = start_col;
    }
    else if ((right < left) && (right < forward)){//case where right is less than both
      start_col -= 1;
      total_energy += right;
      seam[i] = start_col;
    }
    
    else if((forward < left) && (forward < right)){//case where forward is less than both
      total_energy += forward;
      seam[i] = start_col;    
    }

    //tie breaker
    else if (left == forward){// go forward
      total_energy += forward;
      seam[i] = start_col; 
      continue;
    }
    else if (right == forward){//go forward
      total_energy += forward;
      seam[i] = start_col; 
      continue;
    } 
    else if (left == right){// go left
      start_col += 1;
      total_energy += left; //add minimum energy to total energy
      seam[i] = start_col;
      continue;
    }
  }
  return total_energy;
}



int* findMinVerticalSeam(Pixel** image, int width, int height) {
  int minimum_energy;

  //create a seam of the given height to return
  int* seam = createSeam(height);//this is the capacity of the number of rows

  //load candidate seam
  int* candidate_seam = createSeam(height);

  //set minimum_energy to the minimum seam of the first column
  minimum_energy = loadVerticalSeam(image, 0, width, height, seam); //gives minimum energy amount
  
  // traverse thru each column and update w/ new minimum energy
  for (int i = 1; i < width; ++ i){//run this loop until the last column which is the given width
    if (minimum_energy > loadVerticalSeam(image, i, width, height, candidate_seam)){
      //set min energy amount to the smallest out of all the columns traversed
      minimum_energy = loadVerticalSeam(image, i, width, height, candidate_seam); //a possible seam depending on i column your on
      //set the seam you will return = to the candidate seam
      seam = candidate_seam;
    }

    else{
      delete[] candidate_seam; 
    }
  
  }
  return seam;
}



void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
  //because you are traversing the 2D array use 2 for loops
  //go col major
  for(int row = 0; row < height; ++row){//stop at the height since that is the bottom of the rows
    for(int column = 0; column < width - 1; ++column){//stop at the width since that is the end of the columns
      //remove pixel(seam[row],row)
      if(column >= verticalSeam[row]){
        image[column][row] = image[column + 1][row];

      }

    }
  }

}



// void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
// }
