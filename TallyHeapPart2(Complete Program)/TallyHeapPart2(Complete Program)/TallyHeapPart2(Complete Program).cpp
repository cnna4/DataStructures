#include <iostream>
#include <fstream>
#include <string>

class Node {
private:
    char character;
    int frequency;
    Node* left;
    Node* right;

    friend class HuffHeap;

public:
    typedef Node* Tree; 

    Node(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}

private:
    void print(std::ofstream& outputFile) const {
        // Print the character or ASCII code
        if (std::isprint(character)) {
            outputFile << character;
        }
        else {
            outputFile << "ASCII " << static_cast<int>(character);
        }
        outputFile << " " << frequency;
    }
};

class HuffHeap {
private:
    static const int MAX_TREES = 257;
    Node::Tree trees[MAX_TREES];
    int lastUsedSlot;
    int father, leftSon, rightSon;

public:
    HuffHeap() : lastUsedSlot(0), father(0), leftSon(0), rightSon(0) {
        for (int i = 0; i < MAX_TREES; ++i) {
            trees[i] = nullptr;
        }
    }

    HuffHeap(int tally[]) : lastUsedSlot(0), father(0), leftSon(0), rightSon(0) {
        for (int i = 0; i < 256; ++i) {
            if (tally[i] != 0) {
                trees[++lastUsedSlot] = new Node(i, tally[i]);
            }
        }
    }

    void print(std::ofstream& outputFile) const {
        outputFile << "Number of Trees in the heap: " << lastUsedSlot << std::endl;
        for (int i = 1; i <= lastUsedSlot; ++i) {
            trees[i]->print(outputFile);
            outputFile << std::endl;
        }
    }

    void heapify();
};

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

void banner();
void bye();

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
    std::cout << "Welcome to Huffman Compression Program! This is Part 2 of 2 created By Chidi Nna\n";
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
