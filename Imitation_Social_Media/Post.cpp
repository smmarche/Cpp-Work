

#include <iostream>
#include <string>
#include <stdexcept>
#include "Post.h"
#include <sstream>

using std::string;
using std::vector, std::stringstream;


Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {//throw an error if postid is 0, and username and posttext are empty
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  // TODO(student): extracts candidate tags based on occurrences of # in the post

  //set up a vector to return
  vector<string> candidate_tag_vector;

  //taking in a string
  stringstream sstream(getPostText());
  string word_to_analyze ="";

  while(sstream >> word_to_analyze){ //run while there is are still words
    //make sure the tag starts w/ #
    if(word_to_analyze[0] == '#'){
      for(int a = 1; a <= word_to_analyze.length()-1; a++){//make everything lower case by starting 1 unit after the #
        word_to_analyze[a] = tolower(word_to_analyze[a]);
      }

      //move punctuation at the end of the word
      for(int b = word_to_analyze.length()-1; b >= 1; b--){//start at the end of the word and move backward continually removing punctuation
        if(word_to_analyze[b]=='!' || word_to_analyze[b]==',' || word_to_analyze[b]=='.' || word_to_analyze[b]=='?'){
          //code to delete special char
          word_to_analyze.erase(b,1);
        }
        else if(islower(word_to_analyze[b])){//if the char is lowercase we are at the 1st last letter (there are no more ending special characters)
          goto putTagIntoVector;
        }

      }

putTagIntoVector:
      //put the word in the vector
      candidate_tag_vector.push_back(word_to_analyze);
    }
      
  }
  //return the vector with only the correct tag
  return candidate_tag_vector;
}
