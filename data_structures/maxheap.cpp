#include "maxheap.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

MaxHeap::MaxHeap (const std::string& filename){ //const string& filename
    std::ifstream file(filename);
    int num;
    heap = (int*) malloc(100*sizeof(int));
    alloc_size=100;
    while (file >> num) {
        this->insert(num); // insert is a class function to insert to the heap
    }
}

MaxHeap::~MaxHeap(){
    free(heap);
}

void MaxHeap::insert(int num){
    if(alloc_size-count<10){
        heap = (int*) realloc(heap, (100+alloc_size)*sizeof(int));
        alloc_size+=100;
    }
    count++; 
    heap[count]=num;
    int check=count;
    while (check>0 && heap[getParent(check)]<heap[check]){
        int save=heap[getParent(check)];
        heap[getParent(check)]=heap[check];
        heap[check]=save;
        check=getParent(check);
    }

    
}

int MaxHeap::getSize(){
    return(count+1);
}

int MaxHeap::findMax(){
    return(heap[0]);
}

void MaxHeap::deleteMax(){
    //give the root the value of heap's last node
    int save;
    heap[0]=heap[count];
    count--;
    //compaire the new root to it's children and swap if needed
    //continiue until the heap is shorted properly
    int L=getLeft(0);
    int R=getRight(0);
    int swap=0;
    while ((L!=-1 && R!=-1) && (heap[swap]<heap[L] || heap[swap]<heap[R])){
        if (heap[L]>heap[R]){
            save=heap[L];
            heap[L]=heap[swap];
            heap[swap]=save;
            swap=L;
        }
        else{
            save=heap[R];
            heap[R]=heap[swap];
            heap[swap]=save;
            swap=R;
        }
        L=getLeft(swap);
        R=getRight(swap);
        //if the left child is the last index then R will be -1
        //this case only happens if just have a left child and not a right one 
        if (R==-1){
            save=heap[L];
            heap[L]=heap[swap];
            heap[swap]=save;
            swap=L;
        }
        
    }
}
