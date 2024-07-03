
//Program 5
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
// Define the Student class
class Student {
public:
	// Constructor
	Student(std::string first_name, std::string last_name) : fname(first_name),
		lname(last_name), seen(false) {}
	// Attributes
	std::string fname;
	std::string lname;
	bool seen;
};
// Define the Cell class
class Cell {
public:
	// Constructor
	Cell(Student student) : student(student), next(nullptr) {}
	// Attributes
	Student student;
	Cell* next;
	friend class List;
};
class List {
public:
	// Constructor
	List() : head(nullptr), current(nullptr) {}
	// Destructor
	~List() {
		if (head != nullptr) {
			Cell* current = head;
			Cell* temp;
			do {
				temp = current->next;
				delete current;
				current = temp;
			} while (current != head);
		}
	}
	void addCell(Student student) {
		Cell* newCell = new Cell(student);
		if (head == nullptr) {
			head = newCell;
			head->next = head;
		}
		else {
			newCell->next = head->next;
			head->next = newCell;
		}
	}
	void makeCircular() {
		if (head != nullptr) {
			Cell* current = head;
			while (current->next != head) {
				current = current->next;
			}
			current->next = head;
		}
	}
	void findLoser() {
		int N = current->student.lname.length();
		while (true) {
			for (int i = 0; i < N; ++i) {
				current = current->next;
			}
			if (current->student.seen) {
				std::cout << "The loser is: " << current->student.fname << " " <<
					current->student.lname << std::endl;
				return;
			}
			else {
				current->student.seen = true;
			}
		}
	}
	void startSelection() {
		current = head;
		findLoser();
	}
private:
	Cell* head;
	Cell* current;
};
void readLateFile(List& lateList) {
	std::ifstream file("late.txt");
	if (!file.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return;
	}
	std::string first_name, last_name;
	while (file >> first_name >> last_name) {
		Student student(first_name, last_name);
		lateList.addCell(student);
	}
	file.close();
	lateList.makeCircular();
}
void bye() {
	cout << "Thank you for using the Meany Program. Goodbye!" << endl;
}
void Banner() {
	ifstream bannerFile("banner.txt"); // Open the banner file
	if (!bannerFile.is_open()) {
		cout << "Error: Unable to open banner file" << endl;
		return;
	}
	// Display the banner message
	cout << "Banner message:" << endl;
	string line;
	while (getline(bannerFile, line)) {
		cout << line << endl;
	}
	bannerFile.close(); // Close the banner file
}
int main() {
	Banner();
	std::cout << "Processing..." << std::endl;
	List lateList;
	readLateFile(lateList);
	lateList.startSelection();
	std::cout << "Process complete." << std::endl;
	bye();
	return 0;
}}