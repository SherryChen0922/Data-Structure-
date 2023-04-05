/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <vector>
template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  if(tail_ != nullptr && tail_ -> next == NULL) {
    ListNode* end = new ListNode();
    tail_ -> next = end;
    end -> prev = tail_;
  }
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  if(tail_ != nullptr && tail_ -> next == NULL) {
    ListNode* end = new ListNode();
    tail_ -> next = end;
    end -> prev = tail_;
  }
  return List<T>::ListIterator(tail_ -> next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while(head_) {
    ListNode* next = head_ -> next;
    delete head_;
    head_ = next;
  }
  //delete tail_ -> next;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  // ListNode * newNode = new ListNode(ndata);
  // newNode -> next = head_;
  // newNode -> prev = NULL;
  
  // if (head_ != NULL) {
  //   head_ -> prev = newNode;
  //   head_ = newNode;
  // } else {
  //   tail_ = head_= newNode;
  // }
  // length_++;
  if(head_ == NULL) {
    head_ = tail_ = new ListNode(ndata);
    length_ = 1;
    return;
  } 
  length_++;
  ListNode* tmp = new ListNode(ndata);
  head_->prev = tmp;
  tmp->next = head_;
  head_ = tmp;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if(head_ == NULL) {
    head_ = tail_ = new ListNode(ndata);
    length_ = 1;
    return;
  } 
    ListNode* tmp = new ListNode(ndata);
    tail_ ->next = tmp;
    tmp -> prev = tail_;
    tail_ = tmp;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if(start==NULL) {
    return NULL;
  }
  if(splitPoint == 0) {
    return start;
  }
  if(length_ == 0) {
    return NULL;
  }
  if(length_ < splitPoint) {
    return NULL;
  }
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if(this->size() < 3) {
    return;
  }
  ListNode* curr1 = head_;
  ListNode* curr2 = head_->next;
  ListNode* curr3 = head_->next->next;
  int rest = this->size()%3;
  int todevide = this->size()-rest;
  int group = todevide/3;
  if(group == 1) {
    curr1 ->next = curr3 ->next;
    //curr3 ->next ->prev = curr1;
    curr2 ->prev = NULL;
    head_ = curr2;
    curr1 ->prev = curr3;
    curr3 ->next = curr1;
    return;
  }
    curr1 ->next = curr3 ->next;
    curr3 ->next ->prev = curr1;
    curr2 ->prev = NULL;
    head_ = curr2;
    curr1 ->prev = curr3;
    curr3 ->next = curr1;
    curr1 = curr3->next ->next;
    curr2 = curr1->next;
    curr3 = curr2 ->next;
  for (int i = 1; i < group -1 ; i++) {
    curr1 ->next = curr3 ->next;
    curr3 ->next ->prev = curr1;
    curr2 ->prev = curr1 ->prev;
    curr1->prev ->next = curr2;
    curr1 ->prev = curr3;
    curr3 ->next = curr1;
    if(i < group - 1) {
    curr1 = curr3->next ->next;
    curr2 = curr1->next;
    curr3 = curr2 ->next;
    }
  }
  if(rest != 0) {
    curr1 ->next = curr3 ->next;
    curr3 ->next ->prev = curr1;
    curr2 ->prev = curr1 ->prev;
    curr1->prev ->next = curr2;
    curr1 ->prev = curr3;
    curr3 ->next = curr1;
  } else {
  curr1 ->next = curr3 ->next;
    //curr3 ->next ->prev = curr1;
    tail_ = curr1;
    curr2 ->prev = curr1 ->prev;
    curr1->prev ->next = curr2;
    curr1 ->prev = curr3;
    curr3 ->next = curr1;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if(startPoint == endPoint) {
    return;
  }
  if(startPoint == NULL) {
    return;
  }
  if(startPoint -> next  == endPoint) {
    // endPoint -> prev = startPoint -> prev;
    endPoint -> prev = NULL;
    startPoint -> prev = endPoint;
    startPoint -> next = NULL;
    endPoint -> next = startPoint;
    ListNode* tmp = endPoint;
    endPoint = startPoint;
    startPoint = tmp;
    return;
  }
  ListNode * one = startPoint;
  ListNode * two = startPoint ->next;
  //one -> next = one -> prev;
  one -> next = NULL;
  one -> prev = two;
  ListNode * tmp = one;
  one = two;
  two = two -> next;
  while(two != endPoint) {
    one -> next = one ->prev;
    one -> prev = two;
    one = two;
    two = two -> next;
  }
  one -> next = one ->prev;
  one -> prev = two;
  //two -> prev = two -> next;
  two ->prev = NULL;
  two -> next = one;
  startPoint = two;
  endPoint = tmp;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if(n >= this->size()) {
    this->reverse();
    return;
  }
  int rest = this->size()%n;
  int todevide = this->size()-rest;
  int group = todevide/n;
  // vector<ListNode*> grouphead;
  // vector<ListNode*> grouptail;
  ListNode* start = head_;
  ListNode* end = head_; 
  ListNode* end1 = head_ ->next;
  for(int i = 1; i < n; i++) {
    end = end -> next;
    end1 = end1 ->next;
  }
  this->reverse(start, end);
  end -> next = end1;
  if(end1 != NULL) {
    end1 -> prev = end;
  }
  ListNode * tmp = start;
  for(int i = 1; i < group; i++) {
    ListNode * tmp1 = end;
  for(int j = 0; j < n; j++) {
    start = start-> next;
    end = end -> next;
    if(!(i == group - 1 && rest == 0)) {
      end1 = end1 -> next;
    }
  }
  this->reverse(start,end);
  if(!(i == group - 1 && rest == 0)) {
    end -> next = end1;
  end1 -> prev = end;
  }
  tmp1 -> next = start;
  start -> prev = tmp1;
  }
  if(rest == 0) {
  head_ = tmp;
  head_ ->prev = NULL;
  tail_ = end;
  tail_ -> next = NULL;
  } else {
    ListNode* tmp1= end;
    end = tail_;
    this->reverse(end1,end);
    tmp1->next = end1;
    end1-> prev = tmp1;
    head_ = tmp;
  head_ ->prev = NULL;
  tail_ = end;
  tail_ -> next = NULL;
  }
  
  
  
  

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first == NULL && second == NULL) {
    return NULL;
  }
  if(first == NULL) {
    return second;
  } 
  if (second == NULL) {
    return first; 
  }

  
  ListNode* output;
  ListNode* outputhead;
  if(first ->data < second ->data) {
    output = first;
    first = first -> next; 
  } else {
    output = second;
    second = second -> next;
  }

  //set the output head
  outputhead = output ; 

  while(first != NULL && second != NULL) {
    if(first -> data < second ->data) {
    output -> next = first;
    first -> prev = output;
    first = first -> next;
  } else {
    output -> next = second;
    second -> prev = output;
    second = second -> next;
  }
  output = output -> next; 
  }

  if (first == NULL) {
    output -> next = second; 
    second -> prev = output;
  } else { 
    output -> next = first; 
    first -> prev = output;
  }

  return outputhead;
  //return NULL;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  //base case
  if(chainLength == 1){
    return start;
  } else {
    int middle = chainLength/2;
    ListNode* curr = split(start, middle);
    ListNode* one = mergesort(start, middle);
    ListNode* two = mergesort(curr, chainLength - middle);
    return merge(one,two);
  }
}
