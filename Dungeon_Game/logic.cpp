#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout; using std::endl; using std::ifstream; using std::string;

/**
 * TODO:  implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    //int additional_info;
    char remainingchar;
    bool is_exit = false;
    bool is_door = false;
    //take in file
    ifstream inFS; //input file stream

  //open file
    inFS.open(fileName);
  // verify that it opened succesfully
    if(!inFS.is_open()){
        return nullptr;
    }
    //check the row is a int value
    inFS >> maxRow;
    if(!inFS.good()){
        return nullptr;
    }
    //check that the row is a natural number
    if(maxRow <= 0){
        return nullptr;    
    } 

    //check the column is a int value
    inFS >> maxCol;
    if(!inFS.good()){
        return nullptr;
    }
    //check that the column is a natural number
    if(maxCol <= 0){
        return nullptr;    
    } 
    //check if area is too large row*height

    //check if area is too large row*height
    if ((maxRow > INT32_MAX / maxCol)) {  
        return nullptr;
    }
    if (!(INT32_MAX > maxRow)){   // maxrow too large
        return nullptr;
    }
    if (!(INT32_MAX > maxCol)) {   // maxcol too large
        return nullptr;
    }

    //check and update the player start cordinates
    inFS >> player.row;//read in the value and store it in player struct
    if(!inFS.good()){
        return nullptr;
    }
    //check that the column is a natural number and check that player row not greater than maxRow
    if(player.row < 0 || player.row >= maxRow){//if either is true->Houston we have a problem, then this runs
        return nullptr;    
    } 

    inFS >> player.col;//read in the value and store it in player struct
    if(!inFS.good()){
        return nullptr;
    }
    //check that the column is a natural number
    if(player.col < 0 || player.col >= maxCol){
    return nullptr;    
    }     
    //make a map
    char** dungeon_map = createMap(maxRow, maxCol);

    for(int row = 0; row < maxRow; row++){
        for (int col = 0; col < maxCol; col++) {
            inFS >> remainingchar;
            if(inFS.fail()){
                deleteMap(dungeon_map, maxRow);
                return nullptr;
            }
            if(remainingchar != '-' && remainingchar != 'o' && remainingchar != '@' && remainingchar != '!' && remainingchar !='?' && remainingchar != '+' && remainingchar != 'M' && remainingchar != '$' ){ 
                deleteMap(dungeon_map, maxRow);
                return nullptr;
            }
            if(remainingchar == '?'){
                is_door = true;
            }
            if(remainingchar == '!'){
                is_exit = true;
            }
            dungeon_map[row][col] = remainingchar; 
      
        }
    }

    // There is not any sort of exit/door
    if (is_door == false && is_exit == false) {
        deleteMap(dungeon_map, maxRow);
        return nullptr;
    } 

    dungeon_map[player.row][player.col] = 'o';
    char additional_char;

    //check for additional items in the file
    inFS >> additional_char;
    if(!inFS.fail()){
        deleteMap(dungeon_map, maxRow);
        return nullptr;
  }
    return dungeon_map;
}

/**
 * TODO:  implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    switch (tolower(input)) {
        case MOVE_LEFT:
          nextCol-=1;
          break;
        case MOVE_UP:
          nextRow-=1;
          break;
        case MOVE_RIGHT:
          nextCol+=1;
          break;
        case MOVE_DOWN:
          nextRow+=1;
          break;
     }
}

/**
 * TODO: implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {

    //map can take on any size dimensions-use a pointer to the heap
    char **map = new char*[maxRow];

    for (int row = 0; row <= maxRow - 1; ++row){//row x col double array
        map[row] = new char[maxCol]; 
        for(int col = 0; col <= maxCol - 1; ++ col){
            map[row][col] = TILE_OPEN;// set each cell to -
        }
    }   
// return newly generated map
    return map;
}

/**
 * TODO: implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    //map possibly already deleted
    if (map == nullptr){
        maxRow = 0;
    }
    else{
        for(int count = 0; count <= maxRow -1; ++count){
            delete[] map[count]; 
        }
        delete[] map;
        maxRow = 0;
    }
    map = nullptr;
}

/**
 * TODO:  implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if (map == nullptr){
        return nullptr;
    }
    if(maxRow <= 0){
        return nullptr;    
    }
    else if(maxRow >INT32_MAX/2)  {
        return nullptr;
    } 
    if(maxCol <= 0){
        return nullptr;    
    }
    else if(maxCol > INT32_MAX/2)  {
        return nullptr;
    }
    char** bigger_dungeon_map = createMap(2*maxRow, 2*maxCol);
    for(int row=0; row < maxRow ; row ++){
        for(int col = 0; col <maxCol; col++){
            if(map[row][col] != TILE_PLAYER){
                bigger_dungeon_map[row][col] = map[row][col];
                bigger_dungeon_map[row + maxRow][col + maxCol] = map[row][col];
                bigger_dungeon_map[row][col + maxCol] = map[row][col];
                bigger_dungeon_map[row + maxRow][col] = map[row][col];            
            }

            else{
                bigger_dungeon_map[row][col]=TILE_PLAYER;
                bigger_dungeon_map[row + maxRow][col + maxCol]=TILE_OPEN;
                bigger_dungeon_map[row+maxRow][col]=TILE_OPEN;
                bigger_dungeon_map[row][col+maxCol]=TILE_OPEN;
            }
        }
    }
    int sameRow = maxRow;
    deleteMap(map,sameRow);
    maxCol = maxCol + maxCol;
    maxRow = maxRow + maxRow;
    return bigger_dungeon_map;
}

/**
 * TODO:  implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    //stay if your next move is a boundary
    if(nextCol>=maxCol)
        return STATUS_STAY;
    else if(nextRow>=maxRow)
        return STATUS_STAY;
    else if(nextRow<0)
        return STATUS_STAY;
    else if(nextCol<0)
        return STATUS_STAY;

     //update status and coordinates depending on where the player can go next
    if (map[nextRow][nextCol] == '+')//can't walk into a pillar
        return STATUS_STAY;
    else if(map[nextRow][nextCol] == 'M')//can't walk into a monster
        return STATUS_STAY;    
    else if(map[nextRow][nextCol] == '-'){//can move onto an open tile
        //before moving, update the player's spot on the map w/ an open tile '-' 
        map[player.row][player.col]='-';
        //update player coordinates
        player.row = nextRow;
        player.col = nextCol;
        //after the move, update the players spot on the map w/ player on it 'o'
        map[player.row][player.col]='o';
        return STATUS_MOVE;
    }
    else if(map[nextRow][nextCol] == '@'){ //though a hazard, can move onto an amulet
        //before moving, update the player's spot on the map w/ an open tile '-' 
        map[player.row][player.col]='-';
        //update player coordinates
        player.row = nextRow;
        player.col = nextCol;
        //after the move, update the players spot on the map w/ player on it 'o'
        map[player.row][player.col]='o';
        return STATUS_AMULET;

    }
    else if(map[nextRow][nextCol] == '$'){//can move onto treasure
        //before moving, update the player's spot on the map w/ an open tile '-' 
        map[player.row][player.col]='-';
        //update player coordinates
        player.row = nextRow;
        player.col = nextCol;
        //after the move, update the players spot on the map w/ player on it 'o'
        map[player.row][player.col]='o';
        //update the player treasure count
        player.treasure += 1;
        return STATUS_TREASURE;
    }
    else if(map[nextRow][nextCol] == '!'){//can move onto an exit ONLY IF you have treasure
        if (player.treasure > 0){
            //before moving, update the player's spot on the map w/ an open tile '-' 
            map[player.row][player.col]='-';
            //update player coordinates
            player.row = nextRow;
            player.col = nextCol;
            //after the move, update the players spot on the map w/ player on it 'o'
            map[player.row][player.col]='o';
            return STATUS_ESCAPE;
        }
        else{
            return STATUS_STAY; //no treasure no exit
        }
    }
    else if(map[nextRow][nextCol] == '?'){//can move onto a door
        //before moving, update the player's spot on the map w/ an open tile '-' 
        map[player.row][player.col]='-';
        //update player coordinates
        player.row = nextRow;
        player.col = nextCol;
        //after the move, update the players spot on the map w/ player on it 'o'
        map[player.row][player.col]='o';
        return STATUS_LEAVE;
    }
    return 0;
}

/**
 * TODO:  implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    bool player_captured = false; //player not captured

    //look left to find monster w.r.t. player coordinates
    for(int col = player.col - 1; col > -1; --col){//start left of the player and look left until the left edge
        
        if(map[player.row][col] == TILE_PILLAR){
            goto obstacle1;//get out of loop
        }
            
        //look for a monster
        else if(map[player.row][col] == TILE_MONSTER){
            //move the monster closer to the player
            map[player.row][col] = TILE_OPEN;//change where the monster was at to empty tile
            map[player.row][col+1] = TILE_MONSTER; // move to the right to get closer to the player
        
            if(map[player.row][player.col] == TILE_MONSTER)
                player_captured = true;//player captured
        }
    }
obstacle1://pick up here
    //look right to find monster w.r.t. player coordinates
    for(int col = player.col + 1; col < maxCol; ++col){//start right of the player and look right until the right edge
        
        if(map[player.row][col] == TILE_PILLAR){
            goto obstacle2;//get out of loop
        }
            
        //look for a monster
        else if(map[player.row][col] == TILE_MONSTER){
            //move the monster closer to the player
            map[player.row][col] = TILE_OPEN;//change where the monster was at to empty tile
            map[player.row][col-1] = TILE_MONSTER; // move to the left to get closer to the player
            if(map[player.row][player.col] == TILE_MONSTER)
                player_captured = true;//player captured
        }
    }
obstacle2:   
    //look up to find monster w.r.t. player coordinates
    for(int row = player.row - 1; row > -1; --row){

        if(map[row][player.col] == TILE_PILLAR){
            goto obstacle3;//get out of loop
        }
            
        //look for a monster
        else if(map[row][player.col] == TILE_MONSTER){
            //move the monster closer to the player
            map[row][player.col] = TILE_OPEN;//change where the monster was at to empty tile
            map[row + 1][player.col] = TILE_MONSTER; // move down to get closer to the player
            if(map[player.row][player.col] == TILE_MONSTER)
                player_captured = true;//player captured
        }
    }
obstacle3:
    //look down to find monster w.r.t. player coordinates
    for(int row = player.row + 1; row < maxRow; ++row){
        
        if(map[row][player.col] == TILE_PILLAR){
            goto obstacle4;//get out of loop
        }
            
        //look for a monster
        else if(map[row][player.col] == TILE_MONSTER){
            //move the monster closer to the player
            map[row][player.col] = TILE_OPEN;//change where the monster was at to empty tile
            map[row -1][player.col] = TILE_MONSTER; // move up to get closer to the player
            if(map[player.row][player.col] == TILE_MONSTER)
                player_captured = true;//player captured
        }
    }
obstacle4:
    return player_captured;//was the player captured or not?
}
