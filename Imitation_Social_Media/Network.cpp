

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::stringstream;
//??HELP line 44
Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file
  //open the file
  ifstream input_file; 
  input_file.open(fileName); //open file
  //if the file does NOT open throw error
  if(!input_file.is_open()){
    throw std::invalid_argument("Ummm that's embarrassing, this file didn't open");
  }
    //verify the file follows the proper format any errors past this point should be runtime errors

  try{
    string current_line = "";
    while(getline(input_file, current_line)){// continuously take in each line until there are no more
      //check that each word is the right one
      stringstream sstream;
      //put the whole line into the stringstream variable
      sstream << current_line;
      //put the first word from the line into variable
      string word_User_or_Post;
      sstream >> word_User_or_Post;
      char expression;
      int posts_id;
      string user = "";
      string the_post_word;
      string full_post;
  
      //file format verification below

      if(word_User_or_Post == "User"){
        expression ='U';
      }
      else if(word_User_or_Post == "Post"){
        expression = 'P';
      }
      else if(word_User_or_Post != "User" && word_User_or_Post != "Post"){ //the start of the line should be user or post 
        throw std::runtime_error("The word isn't User or Post Toodles!");
      }

      //the case that the word is post
      switch(expression) {
        case 'P':
        //read in post id, user, and the post
          sstream >> posts_id;
          if(sstream.fail()){
            throw std::runtime_error("error");
          }
          sstream >> user;
          if(sstream.fail()){
            throw std::runtime_error("error");
          }
          if(user == ""){
            throw std::runtime_error("This is empty");
          }
          for(int i = 0; i < user.size(); i++){
            if(!isalpha(user[i])){
              throw std::runtime_error("This is not a letter");
            }
          }
          //loop to read in each wordS of the potentially multi-word post

          while(sstream >> the_post_word){//loop while words keep coming
            full_post += the_post_word + " ";
          }
          full_post.pop_back();
          addPost(posts_id, user, full_post);
          break;
        //case that the word is user
        case 'U':
          sstream >> user; //read in the user 
            if(sstream.fail()){
            throw std::runtime_error("error");
          }
          if(user == ""){
            throw std::runtime_error("This is empty");
          }
          for(int i = 0; i < user.size(); i++){
            if(!isalpha(user[i])){
              throw std::runtime_error("This is not a letter");
            }
          }
          addUser(user); //add the user
          break;
      }   

    }
  }


  catch(...){
    throw std::runtime_error("PSSSTT, there is some error in the file format...");
  }

// << inserts formatted data
// >> extract formatted data
}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network
  
  //make sure the username is lower case
  for(int c = 0; c <= userName.length() - 1; c++){
    userName[c] = tolower(userName[c]);
  }

  //check if the given username exist in the vector if so throw err
  for(int d = 0; d < users.size(); d++){ //must use .size() not .length() on a vector
  //check the names in the list against the given one
  //line 45 was:  if((*users[d]).getUserName() == userName) what's wrong with this?
    if(users[d]->getUserName() == userName){ //(*users[d]).getUserName() is a pointer to the object getUserName since users is a vector of pointers 
      throw std::invalid_argument("This usesrname is in the Network already");
    }
  }


  //add new user to the vector
//HELP: explain this line?why are we using new
  users.push_back(new User(userName));//to the vector called users at the end add the user

  cout << "Added User " << userName << endl;

}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network
  //check that the postid does not already exist in std::vector<Post*> posts;
  //iterate through vector called posts
  for(int e = 0; e < posts.size(); e++){
    if(posts[e]->getPostId() == postId){//check that there is no userid in the vector posts that's the same as the given postid
      throw std::invalid_argument("Error: This postId already exists");
    }
  }
  
  //check that the user exists in std::vector<User*> users;
  bool user_exists = false;
  int user_index= -1;
  for(int d = 0; d < users.size(); d++){ 
  //check the names in the list against the given one
    if(users[d]->getUserName() == userName){ //this iterates thru the ENTIRE list
      user_exists = true;//if at any point in the list the given username matches user exists = true
      user_index = d;
    }
  }

  if (!user_exists){ //if it is true that the user does not exist throw that error
    throw std::invalid_argument("Houston we have a problem - that username is NOT in the network data member");
  }

  //ADD a post to the network
  //create a post and add it to Network data member post
  Post* newly_created_post = new Post(postId, userName, postText);

  posts.push_back(newly_created_post); // data member is posts and your adding to the end a newly created post with paraments given from the data member function Post(x,y,z) in post.h

  //add post information to the user
  //vector users (indexed by the current user that exists) locate add user post to associate it w/ the user
  users[user_index]->addUserPost(newly_created_post);

  //EXTRACTION of candidate hashtages in the post
  vector<std::string> possible_tags_vector = newly_created_post->findTags();//this is a vector of all tags extracted from the new post
  //check the network data member tag against our possible_tags_vector to see if any are not in there

  for(int g = 0; g < possible_tags_vector.size(); g++){//this loop will check all tags(from the new post) against each element in network data member tags
  bool possible_tag_exist = false;
    for(int f = 0; f < tags.size(); f++){
      if(tags[f]->getTagName() == possible_tags_vector.at(g)){//this loop check all elements in network data member tag vector
        tags[f]->addTagPost(newly_created_post);
        possible_tag_exist = true;
      } 
    }

    if(!possible_tag_exist){//if possible_tag_exists remains false after coming out of the loop then it's not in the Network data member and NEEDS to be added
    //create a tag and add it to the network data member tag
    //make a pointer of type Tag to the address of the new tag to be added

      //try block set up since the error would come from here if the tag to add isn't appropriate
      try {
      Tag* new_tag_ptr = new Tag(possible_tags_vector[g]); //create a new tag at the index of the tag we found didn't exist above
      //add the new_tag_ptr to the newtwork data member
      tags.push_back(new_tag_ptr);
      tags[tags.size()-1]->addTagPost(newly_created_post);//for the new tag we just added to the end of the tags vector we need to add the associated info to addTagpost
      }
    //don't catch anything
      catch(...){
        continue;
      }
      //add post info to the tag void addTagPost(Post* post);

    }
  }
  string statement = " by " + userName;
cout << "Added Post " << postId << statement << endl;

}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user
  if(userName.empty()){
    throw std::invalid_argument("There's no one home");
  }

  for(int i = 0; i < users.size(); i++){
    if(userName == users.at(i) ->getUserName()){
      return users[i]->getUserPosts();
    }
  }
  throw std::invalid_argument("Oops, this name is not recognized");

}

vector<Post*> Network::getPostsWithTag(string tagName) {
  //TODO(student): return posts containing the given tag
  
  if(tagName.empty()){
    throw std::invalid_argument("there is no tagname present");
  }
//   bool exists_tag = false;
//   int tag_location;
//   for (int o = 0; o < tags.size(); o++) { 
//     //string member_data_tag = tags[o]->getTagName();
//     if (tags[o]->getTagName() == tagName){ //tag is in there
//       tag_location = o;
//       exists_tag = true;
//     }

//   }
//   if(exists_tag){
//     return tags[tag_location]->getTagPosts();
//   }
// //if the tag isn't in there
//   if(!exists_tag){
//     throw std::invalid_argument("There's no tag after all");
//   }

  std::vector<Post*> posts_w_tag;
  for(unsigned int q = 0; q < tags.size(); q++) {
    if (tags.at(q)->getTagName()==tagName) {//when the given tag = tag within network vector
      posts_w_tag = tags.at(q)->getTagPosts();//return the posts with that particular tag in it
    }
  }

  if(!posts_w_tag.empty()){
    return posts_w_tag;
  }
  throw std::invalid_argument("INVALID");

//////////////////////////////////////////////

}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts
    // vector to return w/ most popular hashtag
  vector<string> vector_of_tag_in_most_posts = {}; 
  int most_tags = 0; 


  for (int i = 0; i < tags.size(); i++) {  // check all the tags in the network
    // if tags sie if greater then max
    if(i == 0){
      most_tags = tags.at(0)->getTagPosts().size();//set most_tags at the 0 index 
        vector_of_tag_in_most_posts.push_back(tags.at(i) -> getTagName());  
    }
    else if ( most_tags < tags.at(i) -> getTagPosts().size() ) {
      // update max size
      most_tags = tags.at(i) -> getTagPosts().size();// # of posts with a certain tag in it
      vector_of_tag_in_most_posts.clear();
      vector_of_tag_in_most_posts.push_back(tags.at(i) -> getTagName());
    }
    else if(most_tags == tags.at(i) -> getTagPosts().size()) {  // handle ties
      vector_of_tag_in_most_posts.push_back(tags.at(i) -> getTagName());
    }
  }


  // return a vector of the tags or the tag in most posts
  return vector_of_tag_in_most_posts;
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
