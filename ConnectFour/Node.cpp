#include "Node.hpp"

Node::Node() {
    next = 0; 
    cell = 0;
}

Node::Node(int cell) {
    this->cell = cell;
    this->next = 0;
}

void Node::setValue(int cell) { 
    this->cell = cell; 
}

void Node::setNext(Node *next) { 
    this->next = next; 
}

int Node::getValue() const { 
    return this->cell; 
}

Node * Node::getNext() const { 
    return this->next; 
    }

Node::~Node(){}