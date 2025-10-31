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
        int child = size;
        data[child] = idx;
        size++;

        // no need to upheap if only root node
        if(size > 0)
        {
            upheap(child, weightArr);
        }

        return;
    }

    int pop(int (&weightArr)[]) 
    {
        if(size == 0)
        {
            cout << "Heap is Empty!" << endl;
            return -1;
        }

        // save and replace smallest index
        int smallest = data[0];
        data[0] = data[size - 1];
        size--;

        // only need to downheap if there are 2 or more nodes
        if(size > 1)
        {
            downheap(0, weightArr);
        }

        return smallest;
    }

    void upheap(int child, int (&weightArr)[]) 
    {
        while(child > 0)
        {
            // initialize variables
            int childData = data[child];
            int parentPos = (child - 1) / 2;
            int parentData = data[parentPos];

            // if parent weight is less than child weight, then stop
            if(weightArr[parentData] <= weightArr[childData])
            {
                break;
            }

            // else, swap data (parent data already saved)
            data[parentPos] = childData;
            data[child] = parentData; 

            // set child to its parent
            child = parentPos; 
        }

        return;
    }

    void downheap(int parent, int (&weightArr)[]) 
    {
        // stop once parent becomes a leaf node to prevent infinite loop
        while(true)
        {
            // initialize variables
            int parentData = data[parent];
            int leftChildPos = (2 * parent) + 1;
            int leftChildData = data[leftChildPos];
            int rightChildPos = leftChildPos + 1;
            int rightChildData = data[rightChildPos];

            // if left child exists outside of heap, then stop
            if(leftChildPos >= size)
            {
                break;
            }

            int swapChildPos = leftChildPos;
            int swapChildData = leftChildData;

            // check if right child is smaller (as long as right child is within heap)
            if(rightChildPos < size && weightArr[rightChildData] < weightArr[leftChildData])
            {
                swapChildPos = rightChildPos;
                swapChildData = rightChildData;
            }

            // if smaller child weight is greater than parent weight, then stop
            if(weightArr[parentData] <= weightArr[swapChildData])
            {
                break;
            }

            // else, swap data
            data[swapChildPos] = parentData;
            data[parent] = swapChildData;

            // set parent to smaller child
            parent = swapChildPos;
        }

        return;
    }
};

#endif