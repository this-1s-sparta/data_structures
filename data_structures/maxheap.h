#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <string>
class MaxHeap
{
    // count is the number of elements inside heap
    // count increases every time I insert into the heap and decresses every time i delete from the heap
    // alloc_size is the space that I have allocated in the memory
    int count=-1;
    int alloc_size;
    int * heap;
    public:
    MaxHeap(const std::string& filename);
    ~MaxHeap();
    void insert(int num);
    int getSize();
    int findMax();
    void deleteMax();


    //getLeft returns the parameter's left node's position
    int getLeft(int index){
        int left=(2 * index) + 1;
        if (left<=count){
            return left;
        }
        return -1;
    }

    //getRight returns the parameter's right node's position
    int getRight(int index){
        int right=(2 * index) + 2;
        if (right<=count){
            return right;
        }
        return -1;
    }

    //getParent returns the parameter's parent's position
    int getParent(int place){
        return((place -1) / 2);
    }
};
#endif