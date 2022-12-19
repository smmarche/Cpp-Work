

#include <string>
#include <stdexcept>
#include "User.h"

using std::string;
using std::vector;

User::User(string userName) /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks
  if(userName == ""){//error if string is empty
    throw std::invalid_argument("This username is empty");
  }
  if(!islower(userName[0])){//error if 1st char is lowercase letter
    throw std::invalid_argument("This first character isn't a lowercase letter");
  }

  //throw an error: if a char is uppercase
  for(int i = 0; i <= userName.length()-1; ++i){//iterate through each char in TagName
    if(isupper(userName[i])){//check to see if the char is uppercase
      throw std::invalid_argument("There is at least 1 uppercase letter");
    }
  }
 this->userName = userName;
}

string User::getUserName() {
  // TODO(student): implement getter
  return userName;
}

vector<Post*>& User::getUserPosts() {
  // TODO(student): implement getter
  return userPosts;
}

void User::addUserPost(Post* post) {
  // TODO(student): add post to user posts
  if(post != nullptr){
    userPosts.push_back(post);
  }
  else if(post == nullptr){
    throw std::invalid_argument("ERROR: This post is a nullptr");
  }
}
