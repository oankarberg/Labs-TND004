/**********************************************
* File: BiIterator.cpp                        *
* Author: Aida Nordman                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/


#include "BiIterator.h"


#ifndef DOXYGEN_SHOULD_SKIP_THIS


// Constructor
BiIterator::BiIterator(Node *ptr)
 : current(ptr)
 {

 }


//Dereferencing operator
ELEMENT& BiIterator::operator*() const
{
  //ADD CODE
  return current->value;
}


//Member access operator
ELEMENT* BiIterator::operator->() const
{
    //ADD CODE
    return &current->value;
}


//Equality comparison operator
bool BiIterator::operator==(const BiIterator &it) const
{
    //ADD CODE
  if(it.current == this->current)
    return true;
  else
    return false;
}


//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const
{
   //ADD CODE
  if(it.current != this->current)
    return true;
  else
    return false;
}


//Pre increment operator
BiIterator& BiIterator::operator++()
{
   //ADD CODE
  if(this->current->r_thread)
    this->current =  this->current->right;
  else
    this->current = this->current->right->findMin();
  return *this;
}



//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int)
{
   //ADD CODE
  BiIterator b(*this);
  ++(*this);
  return b;


}

//Pre decrement operator
BiIterator& BiIterator::operator--()
{
  //ADD CODE
  if(this->current->l_thread)
    this->current = this->current->left;
  else
    this->current = this->current->left->findMax();

  return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int)
{
   //ADD CODE
  BiIterator b(*this);
  --(*this);
  return b;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
