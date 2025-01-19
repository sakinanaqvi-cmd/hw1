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
        Item * newItem = new Item();
        head_ = newItem;
        tail_ = newItem;

        //assign first item to val
        newItem->val[0] = val;
        newItem->last = 1;
        size_ += 1;

    } else if(tail_->last == ARRSIZE) { //case: full list
        Item * newItem = new Item();
        if(tail_ != nullptr) {
          tail_->next = newItem;
          newItem->prev = tail_;
        } else { newItem->prev = nullptr; };
        
        newItem->next = nullptr;
        tail_ = newItem;

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
  //adds elements of a new node into
    if(empty()) {
        Item * newItem = new Item();
        head_ = newItem;
        tail_ = newItem;
        //assign first item to val but at the end
        newItem->val[0] = val;
        newItem->last = 1;
        size_ += 1;

    } else if(head_->last == ARRSIZE) { //case: full list

        Item * newItem = new Item();
        if(head_ != nullptr) {
          head_->prev = newItem;
          newItem->next = head_;
        } else newItem->next = nullptr;
        
        newItem->prev = nullptr;
        head_ = newItem;
                newItem->val[0] = val;
        newItem->last = 1;
        //newItem->first = ARRSIZE - 1;
        size_ += 1;
    } else {
        if(head_->last < ARRSIZE) {
          for(int i = head_->last - 1; i >= 0; --i) {
            head_->val[i + 1] = head_->val[i];
          }
        
        head_->val[0] = val;
        head_->last += 1;
        size_ += 1;
      } 
    }
        
}
void ULListStr::pop_front() {  
  if(empty()) return;
  else {
    for(int i = head_->first; i < head_->last - 1; ++i) {
        head_->val[i] = head_->val[i + 1];
      }
      head_->val[head_->last - 1].clear();
      head_->last -= 1;
      size_ -= 1;

      if(head_->first == head_->last && head_->next != nullptr) {
        Item * old = head_;
        head_ = head_->next;
        head_->prev = nullptr;
        delete old;
      }
  }
}
void ULListStr::pop_back() {  
  if(empty()) return;
  else {
    tail_->last -= 1;
    size_ -= 1;
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
      else return &current->val[loc - currentIndex];

    }
    return nullptr;
}
