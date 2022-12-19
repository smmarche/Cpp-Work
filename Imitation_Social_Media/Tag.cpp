

#include <string>
#include <stdexcept>
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName):tagName(tagName),tagPosts({}) /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks
 
  //throw an error: the first character of tagName is not ‘#’
  if(tagName[0] != '#'){
    throw std::invalid_argument("the first character of tagName is not '#'");
  }
  //throw an error: tagName length is less than 2
  if (!(tagName.length() >= 2)){
    throw std::invalid_argument("The tagName is less than 2");
  }
  //throw an error: the second character in tagName is not from ‘a’ - ‘z’
  if(!islower(tagName[1])){
    throw std::invalid_argument("the second character in tagName is not a lower case letter");
  }

  //throw an error: if a char is uppercase
  bool is_one_char_uppercase = false;
  for(int i = 0; i <= tagName.length()-1; ++i){//iterate through each char in TagName
    if(isupper(tagName[i])){//check to see if the char is uppercase
      is_one_char_uppercase = true;
    }
  }
  if(is_one_char_uppercase){//if there is an uppercase throw an error
    throw std::invalid_argument("There is at least 1 uppercase letter");
  }

  //throw an error: if more than 1 consecutive ('!', ',', '.', '?')


  if((tagName[tagName.length()-1]=='!' || tagName[tagName.length()-1]==',' || tagName[tagName.length()-1]=='.' || tagName[tagName.length()-1]=='?') ){
    throw std::invalid_argument("error");
  }
 // a constructor returns nothing(not even void)

}

string Tag::getTagName() {
  // TODO(student): implement getter
  return tagName;//return tagName
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter
  return tagPosts;//return tagPosts
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts
  if(post != nullptr){
    tagPosts.push_back(post);
  }

  else if(post == nullptr){
    throw std::invalid_argument("This is a nullptr");
  }

}
