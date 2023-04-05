
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include <cmath>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return currentIdx*2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return currentIdx*2 + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return std::floor((currentIdx-1)/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(_elems.size() > leftChild(currentIdx)) {
        return true;
    } else {
        return false;
    }
    //return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if(_elems.size()-1 <= leftChild(currentIdx)) {
        return leftChild(currentIdx);
    } else if(higherPriority(_elems[leftChild(currentIdx)],_elems[rightChild(currentIdx)])) {
        return leftChild(currentIdx);
    } else {
        return rightChild(currentIdx);
    }
    //return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
   if(hasAChild(currentIdx)) {
    //base case
    int min = maxPriorityChild(currentIdx);
    //find max child
    if(higherPriority(_elems[min], _elems[currentIdx])) {
        std::swap(_elems[currentIdx], _elems[min]);
        heapifyDown(min);
    }
    //compare / swap / heapifydown
   }
// if(currentIdx *2 + 1 < elem.size) {
//     int min = elem[currentIdx *2 + 1];
//     if(currentIdx *2 + 2 > urrentIdx *2 + 1 && currentIdx *2 + 1 < elem.size) {
//         min = elem[currentIdx *2 + 2];
//         if(min > currentIdx) {
//             std::swap(min currentidx);
//             heapifyDownmin
//         }
//     }
// }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
        //base case
    size_t parentIdx = parent(currentIdx);
        //find parent of current
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
    //compare / swap / heapifyup
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
   // _elems.push_back(T{});
    for(size_t i = 0; i < elems.size(); i++) {
        _elems.push_back(elems[i]);
       // heapifyUp(_elems.size()-1);
       // heapifyDown(parent(_elems.size() - 1) -i);
    }
    for(unsigned i = 0; i <=parent(_elems.size() - 1);i++) {
        heapifyDown(parent(_elems.size() - 1) -i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T output = _elems[0];
    _elems[0] = _elems[_elems.size() -1];
    _elems.pop_back();
    heapifyDown(0);
    return output;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() -1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    for(unsigned i = 0; i <= parent(_elems.size()-1);i++) {
        heapifyDown(parent(_elems.size()-1) -i);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size() == 0) {
        return true;
    }
    return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
