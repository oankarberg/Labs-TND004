/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS


Node::Node(ELEMENT v, Node *l, Node *r)
 : value(v), left(l), right(r)
{
    l_thread = r_thread = false;
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node()
{
    //ADD CODE
    // delete right;
    // delete left;
    // cout << "Destructor  " << endl;
    // if(!l_thread)
    //     delete left;
    // if(!r_thread)
    //     delete right;


}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    //ADD CODE
    if(v.first < this->value.first)
    {
        //If this node doesn't store any node in the left
        if(l_thread){
            Node *temp = this;
            this->left = new Node(v, temp->left, temp);
            Node* child = this->left;
            child->l_thread = child->r_thread = true;

            this->l_thread = false;
            counter++;
            return true;
        //Keep looking
        }else
            return this->left->insert(v);
    }else if(v.first > this->value.first){
        //If this node doesn't store any node in the right
        if(r_thread){
            Node *temp = this;
            this->right = new Node(v, temp, temp->right);
            Node* child = this->right;
            child->l_thread = child->r_thread = true;
            this->r_thread = false;
            counter++;
            return true;
        //Keep looking
        }else
            return this->right->insert(v);
    }else{
        // Increment counter for the ELEMENT
        v.second++;

    }
    return false;
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    //ADD CODE
    //If the key match with the nodes key.
    if(key == this->value.first){
        // cout << "Remove key = " << key << endl;
        if(this->l_thread == false && this->r_thread == false){
            // cout << "Recursively " << endl;
            Node *temp = this->left;
            // cout << "Temp value " << temp->value.first << endl;
            Node *valueNode = this->left->findMax();
            // cout << "findMax " << valueNode->value.first << endl;
            this->value = valueNode->value;
            return temp->remove(valueNode->value.first, this, isRight);

        }else{
            // cout << " parent " << parent->value.first << endl;
            this->removeMe(parent, isRight);
            return true;
        }
        
    //If the value is bigger the node is to right
    }else if(key > this->value.first){
        return this->right->remove(key, this, true);
    //If the key is smaller the node is to left.
    }else if(key < this->value.first){
        return this->left->remove(key, this, false);
    }


    return false;
}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight)
{   

   //ADD CODE
   //1a: a left child with only a right child
    if(isRight == false && l_thread == true && r_thread == false){
        // cout << "in 1a" << endl;
        parent->left = this->right;
        parent->l_thread = false;
        // Node * tempP = this->right;
        // tempP->right = parent;
    }else if(isRight == false && l_thread == false && r_thread == true){
        parent->left = this->left;
        parent->l_thread = false;
        Node * tempP = this->left;
        tempP->right = parent;
        // cout << "in 1b" << endl;
    }
    //No childs, to the left.
    else if(isRight == false && l_thread == true && r_thread == true){
        parent->left = this->left;
        parent->l_thread = true;
        // cout << "in 1c" << endl;
    //2a: a right child with only a right child
    }
    else if(isRight == true && l_thread == true && r_thread == false){
        parent->right = this->right;
        parent->r_thread = false;
        // Node * tempP = this->right;
        // tempP->left = parent;
        // cout << "in 2a" << endl;
    }else if(isRight == true && l_thread == false && r_thread == true){
        parent->right = this->left;
        parent->r_thread = false;
        // Node * tempP = this->left;
        // tempP->right = parent;
        // cout << "in 2b" << endl;
    }
    else if(isRight == true && l_thread == true && r_thread == true){
        parent->right = this->right;
        parent->r_thread = true;
        // cout << "in 2c  " << this->value.first << "   " << this->value.second<<  endl;
    }
    // this->l_thread = this->r_thread = true;
    delete this;
    

}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    //ADD CODE

    if(this->value.first == key){
        return this;
    }else 
    {   
        //Go to right
        if(key > this->value.first){
            //Return not found if we reached a leaf node
            if(r_thread)
                return nullptr;
            //Keep searching down the right tree..
            else 
                return this->right->find(key);
        //Go to left
        }else if(key < this->value.first){
            //Return not found if we reached a leaf node
            if(l_thread)
                return nullptr;
            //Keep searching down the left tree..
            else 
                return this->left->find(key);
        }
    }


    return nullptr;
}


//Return a pointer to the node storing the smallest value
//of the tree whose root is this node
Node* Node::findMin()
{
    //ADD CODE
    Node *temp = this;
    while(temp->l_thread == false){
        temp = temp->left;
    }
    return temp;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    //ADD CODE
    Node *temp = this;
    while(temp->r_thread == false){
        temp = temp->right;
    }
    return temp;
}



//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const
{
    if ( !l_thread ) //display left sub-tree
        left->display();

    cout << value.first << " "; //display key stored in the node

    if ( !r_thread ) //display right sub-tree
        right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
