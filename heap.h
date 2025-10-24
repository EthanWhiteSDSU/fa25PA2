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
        if(size == 0)
        {
            cout << "Heap is Empty!" << endl;
            return -1;
        }

        // save and replace smallest index
        int smallest = data[0];
        data[0] = data[size - 1];

        // only need to downheap if there are 2 or more nodes
        if(size > 2)
        {
            downheap(0, weightArr);
        }
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
            data[parentPos] = childData;
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

    void downheap(int parent, int (&weightArr)[]) 
    {
        // initialize variables
        int parentData = data[parent];
        int leftChildPos = (2 * parent) + 1;
        int leftChildData = data[leftChildPos];
        int rightChildPos = leftChildPos + 1;
        int rightChildData = data[rightChildPos];

        // stop once parent becomes a leaf node to prevent infinite loop
        while(leftChildPos <= size && rightChildPos <= size)
        {
            // left child case
            if(weightArr[parentData] > weightArr[leftChildData])
            {
                // swap data
                data[leftChildPos] = parentData;
                data[parent] = leftChildData;

                // set parent to left child
                parent = leftChildPos;
                parentData = data[parent];

                // set new left and right children
                leftChildPos = (2 * parent) + 1;
                leftChildData = data[leftChildPos];
                rightChildPos = leftChildPos + 1;
                rightChildData = data[rightChildPos];
            }

            // right child case 
            else if(weightArr[parentData] > weightArr[rightChildData])
            {
                // swap data
                data[rightChildPos] = parentData;
                data[parent] = rightChildData;

                // set parent to right child
                parent = rightChildPos;
                parentData = data[parent];

                // set new left and right children
                leftChildPos = (2 * parent) + 1;
                leftChildData = data[leftChildPos];
                rightChildPos = leftChildPos + 1;
                rightChildData = data[rightChildPos];
            }

            // if no swapping occurs, loop is no longer necessary
            else
            {
                break;
            }
        }

        return;
    }
};

#endif