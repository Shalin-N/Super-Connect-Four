#ifndef NODE_HPP_
#define NODE_HPP_

/*
The Node class provides the data structure for construction of single linked lists of vehicle objects.
*/
class Node {
public:

    /*
    Default node constructor.
    */
    Node();

    /*
    Paramterised node constructor.
    */
    Node(int cell);

    /*
    Set the next node in the linked list.
    */
    void setValue(int cell);
    
    /*
    Set the next node in the linked list.
    */
    void setNext(Node *next);

    /*
    Returns the vehicle object associated with this node.
    */
    int getValue() const;

    /*
    Returns the next node in the linked list.
    */
    Node * getNext() const;
  
    /*
    Destroy the node.
    */
    virtual ~Node();

private:
    int cell;
    Node *next;
    
};

#endif /* NODE_HPP_ */