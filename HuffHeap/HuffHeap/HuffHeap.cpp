#include <iostream>
#include <fstream>
#include <string>
#include <map>

class Node {
private:
    char character;
    int frequency;
    Node* left;
    Node* right;

    friend class HuffHeap;
    friend class HuffTree;

public:
    typedef Node* Tree;

    Node() = default;

    Node(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}

    Node(Node* leftSon, Node* rightSon) : character('@'), frequency(leftSon->frequency + rightSon->frequency), left(leftSon), right(rightSon) {}


    ~Node() {
        delete left;
        delete right;
    }

  
    void debug() const {
        std::cout << "Character: " << character << ", Frequency: " << frequency << ", Left: " << left << ", Right: " << right;
    }
};

class HuffHeap {
public:
    static const int MAX_TREES = 257;
    Node::Tree trees[MAX_TREES];
    int lastUsedSlot;

    HuffHeap() : lastUsedSlot(0) {
        for (int i = 0; i < MAX_TREES; ++i) {
            trees[i] = nullptr;
        }
    }

    void add(Node* newNode) {
        trees[++lastUsedSlot] = newNode;
        upHeap();
    }

    Node* remove() {
        Node* temp = trees[1];
        trees[1] = trees[lastUsedSlot--];
        downHeap();
        return temp;
    }

    void heapify();
    void upHeap();
    void downHeap();
};

void HuffHeap::upHeap() {
    int child = lastUsedSlot;
    int parent = child / 2;

    Node* temp = trees[child];

    while (parent > 0 && temp->frequency < trees[parent]->frequency) {
        trees[child] = trees[parent];
        child = parent;
        parent = child / 2;
    }

    trees[child] = temp;
}

void HuffHeap::downHeap() {
    int parent = 1;
    int child = 2;

    Node* temp = trees[parent];

    while (child <= lastUsedSlot) {
        if (child < lastUsedSlot && trees[child + 1]->frequency < trees[child]->frequency) {
            child++;
        }
        if (temp->frequency <= trees[child]->frequency) {
            break;
        }
        trees[parent] = trees[child];
        parent = child;
        child = parent * 2;
    }

    trees[parent] = temp;
}

class HuffTree {

public:
    Node* root;
    std::map<char, std::string> codeMap;

    HuffTree() : root(nullptr) {}

    void heapToTree(HuffHeap* heap);
    void print(Node* root, std::string indent) const;
    void mapCode(Node* root, std::string code);
};

void HuffTree::heapToTree(HuffHeap* heap) {
    while (heap->lastUsedSlot > 1) {
        Node* left = heap->remove();
        Node* right = heap->remove();
        Node* combinedNode = new Node(left, right);
        heap->add(combinedNode);
    }
    root = heap->trees[1];
}

void HuffTree::print(Node* root, std::string indent) const {
    if (root != nullptr) {
        print(root->right, indent + "    ");
        std::cout << indent << root->character << ":" << root->frequency << std::endl;
        print(root->left, indent + "    ");
    }
}

void HuffTree::mapCode(Node* root, std::string code) {
    if (root->left == nullptr && root->right == nullptr) {
        codeMap[root->character] = code;
        return;
    }
    if (root->left != nullptr) {
        mapCode(root->left, code + "0");
    }
    if (root->right != nullptr) {
        mapCode(root->right, code + "1");
    }
}

class Huffman {
private:
    int tally[256];
    std::ifstream inputFile;
    int charCount;

    void doTally();

public:

    Huffman(const std::string& filename) : charCount(0) {

        inputFile.open(filename);

        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            exit(1);
        }
    }
    void compress(const std::string& outputFilename);

    void print(std::ofstream& outputFile) const;
};

void Huffman::doTally() {
    char ch;

    for (int i = 0; i < 256; ++i) {
        tally[i] = 0;
    }
    while (inputFile.get(ch)) {
        ++tally[static_cast<unsigned char>(ch)];
        ++charCount;
    }
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);
}

void Huffman::compress(const std::string& outputFilename) {
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to create file " << outputFilename << std::endl;
        exit(1);
    }
    doTally();
    print(outputFile);

    // Step 1: Convert HuffHeap to HuffTree
    HuffHeap heap;
    for (int i = 0; i < 256; ++i) {
        if (tally[i] != 0) {
            heap.add(new Node(static_cast<char>(i), tally[i]));
        }
    }
    HuffTree tree;
    tree.heapToTree(&heap);


    outputFile << "\nHuffman Tree:\n";
    tree.print(tree.root, "");


    tree.mapCode(tree.root, "");

 
    outputFile << "\nCharacter Codes:\n";
    for (const auto& pair : tree.codeMap) {
        outputFile << pair.first << ": " << pair.second << std::endl;
    }

    outputFile.close();
}

void Huffman::print(std::ofstream& outputFile) const {
    outputFile << "Tally Array:\n";
    for (int i = 0; i < 256; ++i) {
        if (tally[i] != 0) {
            outputFile << "ASCII " << i << ": " << tally[i] << " occurrences\n";
        }
    }
    outputFile << "Total characters in the file: " << charCount << std::endl;
}

void banner() {
    std::cout << "Welcome to HuffHeap The Final Final Program ! This is Part 3 created By Chidi Nna\n";
    std::cout << "---------------------------------------\n";
}

void bye() {
    std::cout << "\nCompression complete. Output written to output.txt. This is now the end of the program. Goodbye! See you in Part 2 \n";
}

int main() {
    banner();

    Huffman huffman("p3Meow.txt");

    huffman.compress("output.txt");

    bye();

    return 0;
}
