#include "Grid.hpp"
#include <iostream>
using namespace std;

Grid::Grid(unsigned int rows, unsigned int columns){

    if (rows > 4)
        this->rows = rows;
 

    if (columns > 4)
        this->columns = columns;

    // loop through columns
    for (unsigned int i=0; i < this->columns; i++){
        // create the head node
        gridV.push_back(new Node(GC_EMPTY));
        gridV[i]->setNext(new Node(GC_EMPTY));

        // get next
        Node *n = gridV[i]->getNext();

        // loop through rows -1
        for (unsigned int j=0; j < this->rows-1; j++){

            // set next as an empty node
            n->setNext(new Node(GC_EMPTY));
            n = n->getNext();
        }
    }
}

Grid::~Grid(){
    for (unsigned int i = 0; i< columnCount(); i++){
        Node* n = gridV[i];
        for (unsigned int j=0; j<rowCount(); j++){    
            Node* temp = n;
            n = n->getNext();
            delete temp;    
        }
    }
}

bool Grid::insertDisc(unsigned int column, Cell disc){
    Node* n = gridV[column];

    if(n->getValue() != GC_EMPTY)
        return false;

    //loop through rows 
    for (unsigned int i=0; i < rows; i++){
        // check next row for disc
        if (n->getNext()->getValue() != GC_EMPTY || i == rows-1){
            n->setValue(disc);
            //printGrid();
            return true;
        }
        n = n->getNext();
    }
    
    return false;
}

Grid::Cell Grid::cellAt(unsigned int row, unsigned int column) const{
    // check for valid row and column
    if (row >= rows || column >= columns)
        return GC_EMPTY;


    // set first to head of column
    Node* n = gridV[column];
    
    // if first index
    if (row == 0)
        return Cell(gridV[column]->getValue());
    
    // loop through rows for specified column
    for (unsigned int i=0; i < row; i++){
        n = n->getNext();
    } 

    return Cell(n->getValue());
}


void Grid::reset(){
    // loop through each row
    for (unsigned int i=0; i < columns; i++){

        // create the head node
        gridV[i]->setValue(GC_EMPTY);

        // get next
        Node *n = gridV[i]->getNext();
        n->setValue(GC_EMPTY);

        // loop through rows -1
        for (unsigned int j=0; j < rows-1; j++){

            // set next as an empty node
            n = n->getNext();
            n->setValue(GC_EMPTY);
        }
    }
}

unsigned int Grid::rowCount() const{
    return rows;
}

unsigned int Grid::columnCount() const{
    return columns;
}


void Grid::deleteDisc(unsigned int deleteRow, unsigned int deleteCol){
    if (deleteRow == 0){
        gridV[deleteCol]->setValue(GC_EMPTY);
        return;
    }
    
    Node* n = gridV[deleteCol];

    // loop to the node before delete node
    for (unsigned int i=1; i < deleteRow; i++){
        n = n->getNext();
    }

    // delete node
    Node* temp = n->getNext()->getNext();
    delete n->getNext();
    n->setNext(temp);

    // add empty node at top
    Node* head = new Node(GC_EMPTY);
    head->setNext(gridV[deleteCol]);
    gridV[deleteCol] = head;
}


void Grid::printGrid() const {
    // loop through rows
    for (unsigned int j = 0; j < rows; j++){
        // loop through columns
        for (unsigned int i = 0; i < columns; i++){
            // print current cell
            cout << cellAt(j,i) << " ";
        }
        cout << endl;
    }
}