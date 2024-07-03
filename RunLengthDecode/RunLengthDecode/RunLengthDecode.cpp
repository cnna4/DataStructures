//Chidi Nna
//ASSN 1
//Data Structures
#include <iostream>
#include <fstream>
using namespace std;
int main() {
	char escape_letter, my_character;
	unsigned short int charcount;
	std::ifstream input("compressed.txt");
	std::ofstream outputFile("console_output.txt");
	if (!input.is_open()) {
		std::cout << "Error opening file." << std::endl;
	}
	if (!outputFile.is_open()) {
		std::cout << "Error opening output file." << std::endl;
		input.close();
	}
	while (input.get(my_character)) {
		if (input.eof()) {
			break; // Quit if end of file happens
		}
		if (my_character != '\x7f')
		{
			std::cout << my_character;
			outputFile << my_character;
		}
		else {
			input >> noskipws >> escape_letter;
			input >> noskipws >> charcount;
			for (unsigned short int i = 0; i < charcount; ++i) {
				std::cout << escape_letter;
				outputFile << escape_letter;
			}
		}
	}
	input.close();
	outputFile.close();
	return 0;
}
