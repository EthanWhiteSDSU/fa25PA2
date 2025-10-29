//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES]; 
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// only for verification/debugging purposes. DELETE LATER. NOT IN FINAL PRODUCT
void printHeap(MinHeap min, int (&weightArr)[])
{
    int n = min.size;
    int level = 0;
    int count = 0;
    int nextLevel = 1;
    
    for (int i = 0; i < n; ++i) 
    {
        cout << min.data[i] << "(" << weightArr[min.data[i]] << ")" << " ";
        count++;
        if (count == nextLevel) 
        {
            cout << endl;
            level++;
            count = 0;
            nextLevel = 1 << level;
        }
    }

    cout << "\n" << endl;
    return;
}

// only for verification/debugging purposes. DELETE LATER. NOT IN FINAL PRODUCT
void printArrays(int nextFree, char (&charArr)[], int (&weightArr)[], int (&leftArr)[], int (&rightArr)[])
{
    cout << "charArr: ";

    for(int i = 0; i < nextFree; i++)
    {
        cout << charArr[i] << " ";
    }

    cout << "\nweightArr: ";

    for(int i = 0; i < nextFree; i++)
    {
        cout << weightArr[i] << " ";
    }

    cout << "\nleftArr: ";

    for(int i = 0; i < nextFree; i++)
    {
        cout << leftArr[i] << " ";
    }

    cout << "\nrightArr: ";

    for(int i = 0; i < nextFree; i++)
    {
        cout << rightArr[i] << " ";
    }

    cout << "\n" << endl;
    return;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) 
{
    // Create heap
    MinHeap min = MinHeap();

    cout << "\n";

    // Form initial heap
    for(int i = 0; i < nextFree; i++)
    {
        min.push(i, weightArr);
    }

    printHeap(min, weightArr);
    printArrays(nextFree, charArr, weightArr, leftArr, rightArr);

    while(min.size > 1)
    {
        // pop and save two smallest nodes
        int smallOne = min.pop(weightArr);
        int smallTwo = min.pop(weightArr);

        // create new parent node
        charArr[nextFree] = 'P';
        weightArr[nextFree] = weightArr[smallOne] + weightArr[smallTwo];
        leftArr[nextFree] = smallOne;
        rightArr[nextFree] = smallTwo;

        // push new parent node index into heap
        min.push(nextFree, weightArr);
        nextFree++;
    } 

    printHeap(min, weightArr);
    printArrays(nextFree, charArr, weightArr, leftArr, rightArr);

    cout << nextFree - 1 << endl;

    // return index of new root node
    return nextFree - 1;
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) 
{
    // create stack and push root
    stack<pair<int, string>> stk;
    stk.push({root, ""});

    while(!stk.empty())
    {
        // save top node, then pop it from stack
        pair<int, string> pr = stk.top();
        cout << "int: " << pr.first << " string: " << pr.second << endl;
        stk.pop();

        // get left and right children of top node
        int rightNode = rightArr[pr.first];
        int leftNode = leftArr[pr.first];

        // if top node is a leaf node, save code to codes and clear code
        if(leftNode == -1 && rightNode == -1 && isalpha(charArr[pr.first]))
        {
            codes[charArr[pr.first] - 'a'] = pr.second;
            pr.second.clear();
        }

        else
        {
            // push right child first so left node is accessed first (LIFO)
            if(rightNode != -1)
            {
                cout << "right" << endl;
                // add '1' to code when moving right
                stk.push({rightNode, pr.second + '1'});
            }
                
            if(leftNode != -1)
            {
                cout << "left" << endl;
                // add '0' to code when moving left
                stk.push({leftNode, pr.second + '0'});
            }
        }        
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message: ";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}