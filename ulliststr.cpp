#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{  
  clear();
}

bool ULListStr::empty() const
{ 
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = nullptr;
  size_ = 0;
}
std::string const & ULListStr::front() const {
    return head_->val[head_->first];
}
std::string const & ULListStr::back() const {
    return tail_->val[tail_->last - 1];
}
void ULListStr::push_back(const std::string& val) {
    //case: empty list
    if(empty()) {
        //adds elements into a new node when empty
        Item * newItem = new Item();
        //assign last item to val
        newItem->val[ARRSIZE - 1] = val;
        newItem->last = ARRSIZE;
        newItem->first = ARRSIZE - 1;
        head_ = tail_ = newItem;
        size_ += 1;

    } else if(tail_->last >= ARRSIZE - 1) { //case: full list
        Item * newItem = new Item();
        //create a new node before the current node
        if(tail_ != nullptr) {
          tail_->next = newItem;
          newItem->prev = tail_;
        } else newItem->prev = nullptr;

        tail_ = newItem;
        
        //same assignment as when theres an empty node
        newItem->val[ARRSIZE - 1] = val;
        newItem->last = ARRSIZE;
        newItem->first = ARRSIZE - 1;
        size_ += 1;
    } else {
        tail_->val[tail_->last] = val;
        tail_->last += 1;
        size_ += 1;
    }
}
void ULListStr::push_front(const std::string& val) {
  //case: empty list
    if (empty()) {
       //adds elements into a new node when empty
        Item * newItem = new Item();
        //assign last item to val
        newItem->val[ARRSIZE - 1] = val;
        newItem->last = ARRSIZE;
        newItem->first = ARRSIZE - 1;
        head_ = tail_ = newItem;
        size_ += 1;
    }
    else if (head_->first == 0) { //case: full list
        Item * newItem = new Item();
        //create a new node before the current node
        if(head_ != nullptr) {
          head_->prev = newItem;
          newItem->next = head_;
        } else newItem->next = nullptr;

        head_ = newItem;
        
        //same assignment as when theres an empty node
        newItem->val[ARRSIZE - 1] = val;
        newItem->last = ARRSIZE;
        newItem->first = ARRSIZE - 1;
        size_ += 1;
    }
    else { 
        //handling all other cases similiar to push_back
        head_->first -= 1;
        head_->val[head_->first] = val;
        size_ += 1;   
    }        
}

void ULListStr::pop_front() {  
    if(empty()) return;

    Item * newItem = head_;
    //move the first up the the next value since first will be deleted
    //also decrease size based on the changes being made
    head_->first += 1;
    size_ -= 1;

    //this is the check to see if the node is empty 
    if (head_->last == head_->first) {
        //move to the next node and set it to head and then delete it
        head_ = head_->next;
        if(head_ == nullptr) tail_ = nullptr;
        else head_->prev = nullptr;

        delete newItem;
    }
}
void ULListStr::pop_back() {  
    if(empty()) return;
    
    //shifts the pointer to the previous value and decrease the size
    tail_->last -= 1;
    size_ -= 1;

    //handles last element removal
    if(tail_->last == 0) {
        Item * newItem = tail_;
        //moves tail one node up
        tail_ = tail_->prev;
        if(tail_ != nullptr) tail_->next = nullptr;
        else head_ = nullptr;

        delete newItem;
    }
}
std::string* ULListStr::getValAtLoc(size_t loc) const {
    //checking if the location is invalid
    if(loc >= size_) return nullptr;

    size_t currentIndex = loc;
    Item * current = head_;

    //go through the list until the item being looked for is found
    while(current != nullptr) {
        size_t size = current->last - current->first; //size will change for each node
        if(size <= currentIndex) {
            currentIndex = currentIndex - size; //update the index
            current = current->next;
        } else return &current->val[current->first + currentIndex];

    }
    return nullptr;
}