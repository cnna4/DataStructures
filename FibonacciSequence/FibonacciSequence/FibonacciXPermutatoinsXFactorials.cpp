// Chidi Nna
// Program # Extra Credit
// Data Structures
// CSCI 6620 -Prof Shokite
// the program demonstrates various concepts of recursion, 
// including generating permutations, calculating factorial,
// generating Fibonacci sequence, and calculating the sum of digits of
// a number, all through recursive functions. 


#include <iostream>
#include <string>
#include <vector>


void generatePermutations( std::string& str, int start, int end, std::vector<std::string>& permutations) {
    if (start == end) {
        permutations.push_back(str);
    }
    else {
        for (int i = start; i <= end; ++i) {
            std::swap(str[start], str[i]);
            generatePermutations(str, start + 1, end, permutations);
            std::swap(str[start], str[i]); // Backtrack
        }
    }
}


void printPermutations( std::vector<std::string>& permutations) {
    std::cout << "Permutations:" << std::endl;
    for ( std::string& perm : permutations) {
        std::cout << perm << std::endl;
    }
}


unsigned long long factorial(int n) {
    if (n == 0) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

void generateFibonacci(int limit, int a, int b, int count = 0) {
    if (count >= limit)
        return;
    std::cout << a << " ";
    generateFibonacci(limit, b, a + b, count + 1);
}

void banner() {
    std::cout << "Welcome to The Extra Credit Program ! This is Recursion Based Program created By Chidi Nna\n";
    std::cout << "---------------------------------------\n";
}

void bye() {
    std::cout << "\Program Complete, Goodbye  \n";
}



int sumOfDigits(int num) {
    if (num == 0) {
        return 0;
    }
    else {
        return (num % 10) + sumOfDigits(num / 10);
    }
}

int main() {
   
    
    banner();

    std::string input;
    std::cout << "Enter a string: ";
    std::cin >> input;

    std::vector<std::string> permutations;
    generatePermutations(input, 0, input.length() - 1, permutations);

    printPermutations(permutations);


    int num;
    std::cout << "Enter a number to calculate its factorial: ";
    std::cin >> num;
    std::cout << "Factorial of " << num << " is: " << factorial(num) << std::endl;

 
    int fibLimit;
    std::cout << "Enter the limit for Fibonacci sequence: ";
    std::cin >> fibLimit;
    std::cout << "Fibonacci sequence up to " << fibLimit << " terms: ";
    generateFibonacci(fibLimit, 0, 1);
    std::cout << std::endl;

    int number;
    std::cout << "Enter a positive integer to calculate sum of its digits: ";
    std::cin >> number;
    std::cout << "Sum of digits of " << number << " is: " << sumOfDigits(number) << std::endl;

    bye();

    return 0;

   
}
