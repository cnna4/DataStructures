// L4 Code Fragments Linked List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//Cell class
class Cell {
	friend class SList;
public:
	string data; //data part of cell
	Cell* next = nullptr; //address part of the next cell
public:
	//constructor
	Cell(string dataPassedIn) : data(dataPassedIn) {}
};
//Linked List class
class SList {
public: //Note: For P3 you must replace with private: Only used public for this code fragment.
		Cell* head; // the head pointer.
	Cell* scan = nullptr;
	Cell* follow = nullptr;
	int count; // number of items currently.
public:
	SList() = default; //constructor
	void start(); // to initialize the head.
	void insert(string value); //to insert the cell into the list. Note: For P3 you must create this method
		void print(ostream& out) const; //
};
void SList::start() {
	head = nullptr; //initializing the head with null pointer
	count = 0; // and count with null
	//Cell *newcell = newCell(data)
}
void SList::print(ostream& out) const {
	Cell* s = head; // assign head value to temporary pointer
	while (s != nullptr) { // repeat the operation until temporary pointer is null
		out << s->data << endl; //out the cell data
		s = s->next; // move to next cell
	}
}
void SList::insert(string data) {
	Cell* newcell = new Cell(data); // creating new cell
	if (head != nullptr) {
		newcell->next = head; // save head in new item
	}
	head = newcell;
	count++;
}
int main() {
	ifstream inputFile("p3Meow.txt");
	ofstream outputFile("consoleOutput.txt");
	string line;
	string firstLine;
	/*if (getline(inputFile, firstLine)) {
	Print or process the first line here
	cout << "First line of the input file: " << firstLine << endl;
	}
	else {
	cout << "Input file is empty." << endl;
	}
	*/
	SList myList;
	myList.start();
	while (getline(inputFile, line)) {
		myList.insert(line);
	}
	myList.print(outputFile);
	//SList *Start_of_list_Larry = new SList(); // creating List object
	//SList *Start_of_list_LarryInsert = new SList(); // creating List object
	//Start_of_list_LarryInsert->start();
	//end loop
	//for loop read in next line from file
	//read a line from file
	//Cell* newcellInsert = new Cell("Vi");
	//Start_of_list_LarryInsert->head = newcellInsert;
	//Start_of_list_LarryInsert->count++;
	//Start_of_list_LarryInsert->insert("Oz");
	//Start_of_list_LarryInsert->insert("Ed");
	//Start_of_list_LarryInsert->insert("Al");
	if (!inputFile.is_open() || !outputFile.is_open())
	{
		cout << "Error: Unable to open file" << endl;
		return 1;
	}
	inputFile.close();
	outputFile.close();
	return 0;
}