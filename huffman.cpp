#include <iostream>
#include <queue>
using namespace std;
 
// Maximum Height of Huffman Tree.
#define MAX_SIZE 100
 
class HuffmanTreeNode {
public:
    
    char data;
 
    int freq;
 
    
    HuffmanTreeNode* right;
    HuffmanTreeNode(char character,
                    int frequency)
    {
        data = character;
        freq = frequency;
        left = right = NULL;
    }
};
 
class Compare {
public:
    bool operator()(HuffmanTreeNode* a,
                    HuffmanTreeNode* b)
    {
        
        return a->freq > b->freq;
    }
};
