#include "Game.hpp"
#include <iostream>
using namespace std;

 Game::Game(){
    statusVar = GS_INVALID;
    turn = 1;
    grid = 0;
    playerOne = 0;
    playerTwo = 0;
    winnerVar = 0;
 }

 Game::~Game(){
    delete this->grid;
 }

void Game::setGrid(Grid* grid){
    if (grid && &this->grid != &grid)
        this->grid = grid;

    checkGame();
}

void Game::setPlayerOne(Player* player){
    // check if the exist and are different
    if (player && &playerOne != &player )
        playerOne = player;

    checkGame();
}

void Game::setPlayerTwo(Player* player){
    // check if the exist and are different
    if (player && &playerTwo != &player)
        playerTwo = player;
    
    checkGame();
}

void Game::checkGame(){
    // check if they exist
    if (grid != 0 && playerOne != 0 && playerTwo != 0)
        statusVar = GS_IN_PROGRESS;
}

void Game::restart(){
    // check game status
    if (statusVar != GS_INVALID){

        // set everything back to deafult
        grid->reset();
        statusVar = GS_IN_PROGRESS;
        playerOne->resetScore();
        playerTwo->resetScore();
        turn = 1;
    }
}

Game::Status Game::status() const{
    return statusVar;
}

const Player* Game::winner() const{
    // check game status
    if (statusVar == GS_COMPLETE)   
        return winnerVar;
                                    
    return 0;
}

const Player* Game::nextPlayer() const{
    // check game status
    if (statusVar != GS_IN_PROGRESS) return 0;

    // return the correct player
    if(turn%2)  return playerOne;
    else        return playerTwo;
    
}

bool Game::playNextTurn(unsigned int column){
    // check status of game
    if (statusVar != GS_IN_PROGRESS)
        return false;

    // handle error thrown by creating variable in an if statement
    Grid::Cell disc;

    // get disc of next player
    if(turn%2)  disc = Grid::GC_PLAYER_ONE;
    else        disc = Grid::GC_PLAYER_TWO;

    // try and make move
    bool test = grid->insertDisc(column, disc);

    //  check for draw
    if(turn == grid->rowCount()*grid->columnCount()){
        statusVar = GS_COMPLETE;
        checkWinner();
        return true;
    }

    //  check for valid move
    if (test){ 
        checkConnect4(findIndexRow(column), column, disc);

        // next player and check if won
        turn++;
        checkWinner();
        return true;
    }

    return false;
}

unsigned int Game::findIndexRow(unsigned int indexColumn){
    unsigned int indexRow = 0;

    // loop through row
    for (unsigned int r = 0; r < grid->rowCount(); r++){
        //break out of statement when the correct disc is found
        if (grid->cellAt(r, indexColumn) != Grid::GC_EMPTY){
            indexRow = r;
            break;
        }
            
    }

    return indexRow;
}


void Game::checkConnect4(unsigned int indexRow, unsigned int indexColumn, Grid::Cell disc){
    // vertical connect 4 condition
    checkVertical(indexRow, indexColumn, disc);

    // horizontal connect 4 condition
    checkHorizontal(indexRow, indexColumn, disc);

    // upper diagonal connect 4 condition
    checkDiagonal1(indexRow, indexColumn, disc);
    
    // lower diagonal connect 4 condition
    checkDiagonal2(indexRow, indexColumn, disc);
}

int Game::checkVertical(int indexRow, int indexColumn, Grid::Cell disc){
    int connect4 = 0;

    // loop through row from first disc
    for (int r=indexRow; r < indexRow+5; r++){

        // check for same disc
        if (grid->cellAt(r, indexColumn) == disc){
            connect4++;

        // else the chain was broken
        } else {
            // check for winning condition
            if (winningCondition(connect4))
                return connect4;

            connect4=0;
        }
            
    }
    return 0;
}

std::vector<int> Game::checkHorizontal(int indexRow, int indexColumn, Grid::Cell disc){
    std::vector<int> a;
    int start = indexColumn-3;
    int connect4 = 0;

    // loop through column
    for (int c=start; c < indexColumn+5; c++){
        // check for same disc
        if (grid->cellAt(indexRow, c) == disc){
            connect4++;

            // check for broken chain
            if (start == -99){
                start = c;
            }

        // else the chain was broken
        } else {
            // check winning condition (4 in a row)
            if (winningCondition(connect4)){

                // formating for return
                a.push_back(start);
                a.push_back(connect4);
                return a;
            }
            
            // reset variable for broken chain
            connect4 = 0;
            start = -99;
        }
            
    }
    return a;
}

std::vector<int> Game::checkDiagonal1(int indexRow, int indexColumn, Grid::Cell disc){
    int connect4 = 0;
    std::vector<int> a;
    
    // logic for starting at the left most of the diagonal
    int currentRow = indexRow + 3;
    int currentCol = indexColumn - 3;

    int startRow = currentRow;
    int startCol = currentCol;
    

    // loop through the rows and columns till one reachs there end
    while (currentRow > indexRow-5  && currentCol < indexColumn+5){

        // check for same disc
        if (grid->cellAt(currentRow, currentCol) == disc){
            connect4++;

            // check for broken chain
            if (startRow == -99 || startCol == -99){
                startRow = currentRow;
                startCol = currentCol;
            }

        // check winning condition (4 in a row)
        } else {
            // check for winning condition
            if (winningCondition(connect4)){

                // formating for return
                a.push_back(startRow);
                a.push_back(startCol);
                a.push_back(connect4);
                return a;
            }
                
            // reset variable for broken chain
            connect4 = 0;
            startRow = -99;
            startCol = -99;

        }
        
        currentRow--;
        currentCol++;
    }
    return a;
}

std::vector<int> Game::checkDiagonal2(int indexRow, int indexColumn, Grid::Cell disc){
    int connect4 = 0;
    std::vector<int> a;

    // logic for starting at the left most of the diagonal
    int currentRow = indexRow - 3;
    int currentCol = indexColumn - 3;

    int startRow = currentRow;
    int startCol = currentCol;

    // loop through the rows and columns
    while (currentCol < indexColumn + 6 && currentRow < indexRow + 6){

        // check for same disc
        if (grid->cellAt(currentRow, currentCol) == disc){
            connect4++;

            // check for broken chain
            if (startRow == -99 || startCol == -99){
                startRow = currentRow;
                startCol = currentCol;
            }

        } else{
            // check winning condition (4 in a row)
            if (winningCondition(connect4)){

                // formating for return
                a.push_back(startRow);
                a.push_back(startCol);
                a.push_back(connect4);
                return a;
            }

            // reset variable for broken chain
            connect4 = 0;
            startRow = -99;
            startCol = -99;
        }
            
        
        currentRow++;
        currentCol++;
    }
    return a;
}

bool Game::winningCondition(int connect4){
    //check for 4 in a row or more
    if (connect4 >= 4){
        statusVar = GS_COMPLETE;

        // check which players turn it was and increment score
        if(turn%2){
            playerOne->increaseScore();        
            return true;

        }else{
            playerTwo->increaseScore();      
            return true;
        }       

    }
    return false;
}

void Game::checkWinner(){
    if (statusVar == GS_COMPLETE){
        unsigned int score1 = playerOne->getScore();
        unsigned int score2 = playerTwo->getScore();

        // draw
        if(score1 == score2){
            winnerVar = 0;

        // player1 won
        } else if (score1 > score2){
            playerOne->increaseWins();
            winnerVar = playerOne;
            
        // player 2 won
        }else if (score2 > score1){
            playerTwo->increaseWins();
            winnerVar = playerTwo;
            
        }
    }
}