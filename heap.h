//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap 
{
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int (&weightArr)[]) 
    {
        data[size] = idx;
        // no need to upheap if only root node
        if(size > 0)
        {
            upheap(size, weightArr);
        }
        size++;
        return;
    }

    int pop(int (&weightArr)[]) 
    {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int smallest = data[0];
        data[0] = data[size];
        data[size] = 0;
        downheap(0, weightArr);
        size--;
        return smallest;
    }

    void upheap(int child, int (&weightArr)[]) 
    {
        // initialize variables
        int childData = data[child];
        int parentPos = (child - 1) / 2;
        int parentData = data[parentPos];

        while(weightArr[childData] < weightArr[parentData])
        {
            // swap data (parent data already saved)
            data[parentPos] = data[child];
            data[child] = parentData; 

            // set child to its parent
            child = parentPos; 
            childData = parentData; 

            // set parent to its parent
            parentPos = (child - 1) / 2;
            parentData = data[parentPos];
        }

        return;
    }

    void downheap(int pos, int (&weightArr)[]) 
    {
        // TODO: swap parent downward while larger than any child
    }
};

#endif