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
/* Add a prototype for a helper function here if you need */

void null(Node*& node) {
  node == nullptr;
}
void split(Node*& in, Node*& odds, Node*& evens)
{
  splitHelper(in, odds, evens);

  in = nullptr;
}
void splitHelper(Node*& in, Node*& odds, Node*& evens) {
  if(in == nullptr) {
        in = nullptr;
        evens = nullptr;
        odds = nullptr;
        return;
    }
    //evens case
    if(in->value % 2 == 0) {
      evens = in;
      splitHelper(in->next, odds, evens->next);
        
    }
    //odds case
    else {
      odds = in;
      splitHelper(in->next, odds->next, evens);
    } 
}