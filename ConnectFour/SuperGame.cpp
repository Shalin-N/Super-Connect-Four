#include "SuperGame.hpp"
#include <iostream>
using namespace std;

bool SuperGame::playNextTurn(unsigned int column){
    // check status of game
    if (statusVar != GS_IN_PROGRESS)
        return false;

    // handle error thrown by creating variable in an if statement
    Grid::Cell disc;

    // check which player
    if(turn%2)  disc = Grid::GC_PLAYER_ONE;
    else        disc = Grid::GC_PLAYER_TWO;

    // try and make move 
    bool test = grid->insertDisc(column, disc);

    //  check for full grid
    for (unsigned int i=0; i < grid->columnCount(); i++){
        if (grid->cellAt(0, i) == Grid::GC_EMPTY){
            break;
        }

        if (i == grid->columnCount()-1){
            statusVar = GS_COMPLETE;
            checkWinner();
            return true;
        }
    }

    //  check for valid move
    if (test){ 
        checkConnect4(findIndexRow(column), column, disc);
        turn++;
        return true;
    }
    
    return false;
}

void SuperGame::checkConnect4(int indexRow, int indexColumn, Grid::Cell disc){
    std::vector<int> hoz;
    std::vector<int> d1;
    std::vector<int> d2;

    // get all nodes to delete
    std::vector<vector<int>> all = checkConditions(indexRow, indexColumn, disc);
    
    // check if any nodes to delete
    if (deleteDiscs(all)){
        // check for player1 score increment
        if (disc == Grid::GC_PLAYER_ONE){
            playerOne->increaseScore();
        // check for player2 score increment
        } else if(disc == Grid::GC_PLAYER_TWO){
            playerTwo->increaseScore();
        }


        recursion(indexRow, indexColumn);
    }
}

std::vector<vector<int>> SuperGame::checkConditions(int checkRow, int checkColumn, Grid::Cell checkDisc){
    std::vector<int> hoz;
    std::vector<int> d1;
    std::vector<int> d2;
    std::vector<vector<int>> all;

    // vertical connect 4 condition
    if (checkVertical(checkRow, checkColumn, checkDisc)){

        // append nodes for deletion
        for (int k=0; k < 4; k++){
            all.push_back({checkRow+k, checkColumn});
        }
    }

    // horizontal connect 4 condition
    hoz = checkHorizontal(checkRow, checkColumn, checkDisc);
    if (!hoz.empty()){

        // append nodes for deletion
        for (int k=0; k < hoz[1]; k++){
            all.push_back({checkRow, hoz[0]+k});
        }
    }

    // upper diagonal connect 4 condition
    d1 = checkDiagonal1(checkRow, checkColumn, checkDisc);
    if (!d1.empty()){

        // append nodes for deletion
        for (int k=0; k < d1[2]; k++){
            all.push_back({d1[0]-k, d1[1]+k});
        }
    }
    
    // lower diagonal connect 4 condition
    d2 = checkDiagonal2(checkRow, checkColumn, checkDisc);
    if (!d2.empty()){

        // append nodes for deletion
        for (int k=0; k < d2[2]; k++){
            all.push_back({d2[0]+k, d2[1]+k});
        }
    }
    return all;
}

bool SuperGame::deleteDiscs(std::vector<vector<int>> all){
    // check if any nodes to delete
    if (!all.empty()){

        // sort nodes to avoid deletion errors
        all = sort(all);

        // loop through deletion vector
        for (unsigned int i=0; i<all.size(); i++){

            // prepare for delete disc
            int a = all[i][0];
            int b = all[i][1];

            grid->deleteDisc(a, b);
        }
        return true;
    }
    return false;
}

void SuperGame::recursion(int indexRow, int indexColumn){
    std::vector<vector<int>> toDelete;
    bool one = false;
    bool two = false;

    // loop through rows
    for (int i = 0; i < indexRow+1; i++){
        // loop through columns
        for(int j = indexColumn-4; j < indexColumn+6; j++){
            // get disc at current position
            Grid::Cell currentCell = grid->cellAt(i, j);

            // check for player disc
            if (currentCell != Grid::GC_EMPTY){
                std::vector<vector<int>> temp = checkConditions(i, j, currentCell);
                toDelete.insert(toDelete.end(), temp.begin(), temp.end()); 

                // check for player1 score increment
                if (!one && currentCell == Grid::GC_PLAYER_ONE && !temp.empty()){
                    playerOne->increaseScore();
                    one = true;

                // check for player2 score increment
                } else if(!two && currentCell == Grid::GC_PLAYER_TWO && !temp.empty()){
                    playerTwo->increaseScore();
                    two = true;
                }
            }
        }
    }

    // delete disc and recall till stable {nothing changes}
    if (deleteDiscs(toDelete)){
        recursion(findIndexRow(indexColumn), indexColumn);
    }
}

std::vector<vector<int>> SuperGame::sort(std::vector<vector<int>> base){
    
    // loop through all elements
    for (unsigned int i=0; i<base.size()-1; i++){
        // set current to minimum
        unsigned int min = i;

        // loop through all others
        for (unsigned int j=i+1; j<base.size(); j++){

            // erase vector if duplicate
            if (base[j] == base[min]){
                base.erase(base.begin() + j);

            // overwrite if [j] smaller
            } else if (base[j] < base[min]){
                min = j;
            }
        }

        // swap if there was a change
        if (min != i){
            std::vector<int> temp = base[i];
            base[i] = base[min];
            base[min] = temp;
        }
    }

    return base;
}

bool SuperGame::winningCondition(int connect4){
    //check for 4 in a row or more
    if (connect4 >= 4){
        return true;
    }
    return false;
}
