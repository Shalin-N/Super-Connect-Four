#ifndef SUPERGAME_HPP
#define SUPERGAME_HPP

#include "Game.hpp"

class SuperGame : public Game {
public:

    /*
    Execute the turn of the next player by attempting to insert a disc into the indicated column of the game grid. If
    the move was successful, this method should return `true`. If the move was could not be completed (e.g. the
    specified column in the grid is full, or the game is invalid or already complete) this method should return `false`.
    Invalid moves (i.e. where this method returns `false`) should have no effect on the state of the Game or the Grid.

    This method should have no effect if the current game status is not GS_IN_PROGRESS.
    */
    bool playNextTurn(unsigned int column);

    /*
    checks for a connect 4 for the current turn.
    */
    void checkConnect4(int indexRow, int indexColumn, Grid::Cell disc);

    /*
    checks for a connect 4 for each condition.
    */
    std::vector<vector<int>> checkConditions(int checkRow, int checkColumn, Grid::Cell checkDisc);

    /*
    insertion sort
    used to avoid errors when deleting nodes from the linked list
    */
    std::vector<vector<int>> sort(std::vector<vector<int>> base);

    /*
    helper function that checks if a train of disc is longer than 4
    */
    bool winningCondition(int connect4);

    /*
    function to check all other spots after a drop
    */
    void recursion(int indexRow, int indexColumn);

    /*
    function to check all other spots after a drop
    */
    bool deleteDiscs(std::vector<vector<int>> all);

    /*
    function to remove all dupliactes from delete array
    */
    std::vector<vector<int>> removeDuplicates(std::vector<vector<int>> all);

};

#endif /* end of include guard: SUPERGAME_HPP */
