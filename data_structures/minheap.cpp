#include "minheap.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

MinHeap::MinHeap (const std::string& filename){ //const string& filename
    std::ifstream file(filename);
    int num;
    heap = (int*) malloc(100*sizeof(int));
    alloc_size=100;
    while (file >> num) {
        this->insert(num); // insert is a class function to insert to the heap
    }
}

MinHeap :: ~MinHeap(){
    free(heap);
}

void MinHeap::insert(int num){
    if(alloc_size-count<10){
        heap = (int*) realloc(heap, (100+alloc_size)*sizeof(int));
        alloc_size+=100;
    }
    //100
    //99
    count++; 
    //3
    heap[count]=num;
    //heap[3]=97
    int check=count;
    while (check>0 && heap[getParent(check)]>heap[check]){
        //heap[0]>heap[1] 100>97
        int save=heap[getParent(check)];
        //save=100
        heap[getParent(check)]=heap[check];
        //heap[1]=97
        heap[check]=save;
        //heap[3]=100
        check=getParent(check);
    }
    //[98,100,99,97] 
    //[98,97,99,100] 
    
}

int MinHeap::getSize(){
    return(count+1);
}

int MinHeap::findMin(){
    return(heap[0]);
}

void MinHeap::deleteMin(){
    //give the root the value of heap's last node
    int save;
    heap[0]=heap[count];
    count--;
    //compaire the new root to it's children and swap if needed
    //continiue until the heap is shorted properly
    int L=getLeft(0);
    int R=getRight(0);
    int swap=0;
    while ((L!=-1 && R!=-1) && (heap[swap]>heap[L] || heap[swap]>heap[R])){
        if (heap[L]<heap[R]){
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
