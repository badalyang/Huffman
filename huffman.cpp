#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char ch, int freq)
        : ch(ch)
        , freq(freq)
        , left(nullptr)
        , right(nullptr)
    {
    }
    Node(char ch, int freq, Node* left, Node* right)
        : ch(ch)
        , freq(freq)
        , left(left)
        , right(right)
    {
    }
};

struct compare {
    bool operator()(Node* l, Node* r)
    {
        return l->freq > r->freq;
    }
};

void printCodes(Node* root, string str, unordered_map<char, string>& huffmanCode)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

void serializeTree(Node* root, string& serialized)
{
    if (root == nullptr) {
        serialized += "#"; // Use '#' as a marker for null nodes
        return;
    }
    serialized += root->ch;
    serializeTree(root->left, serialized);
    serializeTree(root->right, serialized);
}

Node* deserializeTree(string& serialized, int& index)
{
    if (index >= serialized.size() || serialized[index] == '#') {
        index++;
        return nullptr;
    }
    Node* node = new Node(serialized[index], 0);
    index++;
    node->left = deserializeTree(serialized, index);
    node->right = deserializeTree(serialized, index);
    return node;
}

void buildHuffmanTree(string text)
{
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, compare> pq;
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    printCodes(root, "", huffmanCode);

    // Compress
    string encodedStr = "";
    for (char ch : text) {
        encodedStr += huffmanCode[ch];
    }

   
    string serializedTree = "";
    serializeTree(root, serializedTree);

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << "\n";
    }

    cout << "\nOriginal string:\n" << text << "\n";
    cout << "\nEncoded string:\n" << encodedStr << "\n";
    cout << "\nSerialized Tree:\n" << serializedTree << "\n";

    
    auto decode = [&](string encodedStr, string serializedTree) {
        int index = 0;
        Node* deserializedRoot = deserializeTree(serializedTree, index);

        cout << "\nDecoded string:\n";
        Node* curr = deserializedRoot;
        for (char bit : encodedStr) {
            if (bit == '0') {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
            if (!curr->left && !curr->right) {
                cout << curr->ch;
                curr = deserializedRoot;
            }
        }
        cout << "\n";
    };

    decode(encodedStr, serializedTree);
}

int main()
{
    string text = "HUFFMAN";
    buildHuffmanTree(text);
    return 0;
}
