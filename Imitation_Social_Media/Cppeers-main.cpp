/*g++ -std=c++17 -Wall -Wextra -pedantic -g -fsanitize=address,undefined Network.cpp User.cpp Post.cpp Tag.cpp Cppeers-main.cpp/*

 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "Network.h"
#include <vector>

using std::cout, std::cin, std::endl;
using std::string, std::vector;

void printMenu() {
  cout << "Welcome to CPPeers" << endl;
  cout << "The options are: " << endl;
  cout << "1. load data file and add information" << endl;
  cout << "2. show posts by user" << endl;
  cout << "3. show posts with hashtag" << endl;
  cout << "4. show most popular hashtag" << endl;
  cout << "9. quit" << endl;
  cout << "--------> Enter your option: ";
}

void processLoad(Network& cppeers) {
  string fileName = "";
  cout << "Enter filename: ";
  cin >> fileName;
  cppeers.loadFromFile(fileName);
}

void processPostsByUser(Network& cppeers) {
  // TODO(student): implement
  string input_username;
  cout << "Enter username: ";
  cin >> input_username;
  for (Post* post : cppeers.getPostsByUser(input_username)){
    cout << post->getPostText() << "\n";
  }
}

void processPostsWithHashtags(Network& cppeers) {
  // TODO(student): implement
  string input_tagname;
  cout << "Enter tagname: ";
  cin >> input_tagname;
  // for (Post* post : cppeers.getPostsWithTag(input_tagname)){
  //   cout << post->getPostText() << endl;
  // }

  vector<Post*> all_posts = cppeers.getPostsWithTag(input_tagname);

  for (int i = 0; i < all_posts.size(); i++) {
    cout << all_posts.at(i) -> getPostText() << endl;
  }
}

void processMostPopularHashtag(Network& cppeers) {
  // TODO(student): implement
  vector<string> themostpopularTags = cppeers.getMostPopularHashtag();
  for (long unsigned int z = 0; z < themostpopularTags.size(); z++){
    cout << themostpopularTags[z] << endl;
  }

}

int main() {

  try {
    Network cppeers;

    int choice = 0;

    // present menu
    do {
      printMenu();
      cin >> choice;
      switch(choice) {
        case 1: {
          processLoad(cppeers);
          break;
        }
        case 2: {
          processPostsByUser(cppeers);
          break;
        }
        case 3: {
          processPostsWithHashtags(cppeers);
          break;
        }
        case 4: {
          processMostPopularHashtag(cppeers);
          break;
        }
      }
    } while (choice != 9);
  } catch (std::exception& exc) {
    std::cout << exc.what() << endl;
  }

  return 0;
}
