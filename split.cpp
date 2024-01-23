/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"


void split(Node*& in, Node*& odds, Node*& evens)
{
  if(!in) { //check if in is empty, set evens and odds to null
    evens = nullptr;
    odds = nullptr;
  } 
  else if(in->value % 2 == 0) { //check if current list value is even
    evens = in;
    //point to the next value of in for both evens and in
    //since split will take the next value into account
    split(in->next, odds, in->next); 
  } else { //last check for odd value
    odds = in;
    if(in->value == 1 &&!in->next) {
      in = nullptr;
    } else {
      split(in->next, in->next, evens);
    }
      
    //point to the next value of in for both odds and in
    //since split will take the next value into account
    
  }
}

