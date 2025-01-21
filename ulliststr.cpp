#include <cstddef>
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
        head_ = tail_ = newItem;
        //assign first item to val
        newItem->val[0] = val;
        newItem->last = 1;
        size_ += 1;

    } else if(tail_->last == ARRSIZE) { //case: full list
        Item * newItem = new Item();
        //create a new node before the current node
        if(tail_ != nullptr) {
          tail_->next = newItem;
          newItem->prev = tail_;
        } else newItem->prev = nullptr;

        tail_ = newItem;
        
        //same assignment as when theres an empty node
        newItem->val[0] = val;
        newItem->last = 1;
        size_ += 1;
    } else {
        tail_->val[tail_->last] = val;
        tail_->last += 1;
        size_ += 1;
    }
}
void ULListStr::push_front(const std::string& val) {
  //adds elements into a new node when empty
    if(empty()) {
        Item * newItem = new Item();
        head_ = tail_ = newItem;
        //assign first item to val
        newItem->val[0] = val;
        newItem->last += 1;
        size_ += 1;
      //shifts all the elements
    } /*else if(head_->first == 0 && head_->last < ARRSIZE && !(head_->first == 0 && head_->last == ARRSIZE)) {
        int last = head_->last;
        if(last == 9) head_->val[9] = head_->val[8];
        if(last >= 8) head_->val[8] = head_->val[7];
        if(last >= 7) head_->val[7] = head_->val[6];
        if(last >= 6) head_->val[6] = head_->val[5];
        if(last >= 5) head_->val[5] = head_->val[4];
        if(last >= 4) head_->val[4] = head_->val[3];
        if(last >= 3) head_->val[3] = head_->val[2];
        if(last >= 2) head_->val[2] = head_->val[1];
        if(last >= 1) head_->val[1] = head_->val[0];

        //after shifting, assign the first index to value
        head_->val[0] = val;
        head_->last += 1;
        size_ += 1;
    } else if(head_->first == 0 && head_->last == ARRSIZE) { //case: full list
        Item * newItem = new Item();
        //create a new node before the current node
        if(head_ != nullptr) {
          head_->prev = newItem;
          newItem->next = head_;
        } else newItem->next = nullptr;
        
        head_ = newItem;

        //same assignment as when theres an empty node
        newItem->val[0] = val;
        newItem->last = 1;
        size_ += 1;
    }  else {
        //handles all other cases of moving the values
        head_->val[head_->first - 1] = val;
        head_->first -= 1;
        size_ += 1;
    }       */ 
}
void ULListStr::pop_front() {  
  if(empty()) return;

  //handles the shifting of elements
  /*if(head_->last > head_->first) {
    head_->val[head_->first] = head_->val[head_->first + 1];
    if(head_->first + 2 < head_->last) head_->val[head_->first + 1] = head_->val[head_->first + 2];
    if(head_->first + 3 < head_->last) head_->val[head_->first + 2] = head_->val[head_->first + 3];
    if(head_->first + 4 < head_->last) head_->val[head_->first + 3] = head_->val[head_->first + 4];
    if(head_->first + 5 < head_->last) head_->val[head_->first + 4] = head_->val[head_->first + 5];
    if(head_->first + 6 < head_->last) head_->val[head_->first + 5] = head_->val[head_->first + 6];
    if(head_->first + 7 < head_->last) head_->val[head_->first + 6] = head_->val[head_->first + 7];
    if(head_->first + 8 < head_->last) head_->val[head_->first + 7] = head_->val[head_->first + 8];
    if(head_->first + 2 < head_->last) head_->val[head_->first + 8] = head_->val[head_->first + 9];
  }*/
  /*head_->last -= 1;
  //handles last element removal
  if(head_->first == head_->last) {
    Item * old = head_;
    //moves head one node down
    head_ = head_->next;
    if(head_ != nullptr)
      head_->prev = nullptr;
    else tail_ = nullptr;
    delete old;
  }
  size_ -= 1; 
  //handles when size becomes zero to avoid valgrind errors
  if(size_ == 0) { 
    clear();
  }*/
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
    if(loc < 0 || loc >= size_) return nullptr;
    Item * current = head_;
    size_t currentIndex = 0;
    while(current != nullptr) {
      //check if node completed
      if(current->last + currentIndex <= loc) {
        currentIndex = currentIndex + current->last;
        current = current->next;
      }
      else return &current->val[loc - currentIndex]; //return the value of the found index

    }
    return nullptr;
}
