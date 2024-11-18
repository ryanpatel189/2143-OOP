/*****************************************************************************
*
*  Author:           Ryan Patel
*  Email:            ryanpatel189@gmail.com
*  Label:            P01
*  Title:            Fraction Class
*  Course:           CMPS 2143
*  Semester:         Fall 2024
*
*  Description:
*        This program implements a Fraction class to perform basic operations 
*        on fractions such as addition, subtraction, multiplication, and 
*        division. When needed, this program simplifies fractions, checks 
*        for equality, and validates them. The program also allows for the 
*        input of fractions from a file.
*
*  Usage:
*        - Compile the program and run it.
*        - Input fractions in the format x/y followed by an operator (+, -, *, /)
*        - The results will be printed in reduced form.
*
*  Files:            main.cpp : driver program for the Fraction class
*****************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

// Fraction class to handle operations on fractions
class Fraction {
private:
    int numerator;     // Numerator of the fraction
    int denominator;   // Denominator of the fraction

    // Function to calculate the Greatest Common Divisor (GCD)
    // GCD helps simplify the fraction by dividing both numerator and denominator by their GCD
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Function to calculate the Least Common Multiple (LCM)
    // Used when adding or subtracting fractions to find a common denominator
    int lcm(int a, int b) {
        return (a * b) / gcd(a, b); // LCM formula using GCD
    }

    // Function to reduce the fraction to its simplest form
    // Uses GCD to simplify the fraction after any operation
    void reduce() {
        int gcdValue = gcd(numerator, denominator); // Find GCD of numerator and denominator
        numerator /= gcdValue;   // Reduce numerator
        denominator /= gcdValue; // Reduce denominator
    }

public:
    // Constructor to initialize a Fraction object with a numerator and denominator
    // Validates that the denominator is not zero and reduces the fraction
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (den == 0) {
            throw invalid_argument("Denominator cannot be zero."); // Exception for zero denominator
        }
        reduce(); // Reduces fraction to simplest form
    }

    // Overloaded addition operator to add two fractions
    // Steps:
    // 1. Find the least common denominator (LCD) using the LCM of the denominators.
    // 2. Adjust both numerators to match the LCD.
    // 3. Add the adjusted numerators and return the result as a new Fraction.
    Fraction operator+(const Fraction& other) {
        int commonDen = lcm(denominator, other.denominator); // Step 1: Find LCD
        int num1 = numerator * (commonDen / denominator);    // Step 2: Adjust numerator
        int num2 = other.numerator * (commonDen / other.denominator);
        int resultNum = num1 + num2;                         // Step 3: Add numerators
        return Fraction(resultNum, commonDen);               // Return new Fraction
    }

    // Overloaded subtraction operator to subtract two fractions
    // Follows the same process as addition but performs subtraction
    Fraction operator-(const Fraction& other) {
        int commonDen = lcm(denominator, other.denominator); // Step 1: Find LCD
        int num1 = numerator * (commonDen / denominator);    // Step 2: Adjust numerator
        int num2 = other.numerator * (commonDen / other.denominator);
        int resultNum = num1 - num2;                         // Step 3: Subtract numerators
        return Fraction(resultNum, commonDen);               // Return new Fraction
    }

    // Overloaded multiplication operator to multiply two fractions
    // Multiply the numerators and denominators directly
    Fraction operator*(const Fraction& other) {
        int resultNum = numerator * other.numerator;          // Multiply numerators
        int resultDen = denominator * other.denominator;      // Multiply denominators
        return Fraction(resultNum, resultDen);                // Return new Fraction
    }

    // Overloaded division operator to divide two fractions
    // Divides by multiplying the first fraction by the reciprocal of the second
    Fraction operator/(const Fraction& other) {
        if (other.numerator == 0) {
            throw invalid_argument("Cannot divide by zero."); // Exception for division by zero
        }
        int resultNum = numerator * other.denominator;        // Multiply by reciprocal
        int resultDen = denominator * other.numerator;        // Denominator becomes numerator of the second fraction
        return Fraction(resultNum, resultDen);                // Return new Fraction
    }

    // Overloaded equality operator to check if two fractions are equal
    // Compares cross products of the fractions
    bool operator==(const Fraction& other) const {
        return (numerator * other.denominator) == (denominator * other.numerator);
    }

    // Overloaded output operator to print the fraction in the format "numerator/denominator"
    friend ostream& operator<<(ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator; // Output format
        return os;
    }

    // Static function to parse a fraction from a string in the format "x/y"
    // Uses a stringstream to extract the numerator and denominator
    static Fraction parseFraction(const string& fractionStr) {
        int num, den;       // Variables for numerator and denominator
        char slash;         // Variable to hold the '/' character
        stringstream ss(fractionStr); // String stream for parsing
        ss >> num >> slash >> den; // Extract numerator and denominator
        return Fraction(num, den); // Return new Fraction
    }

    // Second set of overloaded subtraction operator
    Fraction operator-(int value) const {
        Fraction other(value, 1);
        return (value * other.denominator - other.numerator);
        // Subtract integer value as a fraction
    }

    // Second set of overloaded multiplication operator
    Fraction operator*(int value) const {
        return Fraction(numerator * value, denominator); // Multiply by integer value
    }

    // Second set of overloaded division operator
    Fraction operator/(int value) const {
        if (value == 0) {
            throw invalid_argument("Cannot divide by zero."); // Exception for division by zero
        }
        return Fraction(numerator, denominator * value); // Divide by integer value
    }
};

/*****************************************************************************
*
*  Function:           main
*
*  Description:
*        The main function drives the program, reading fractions from input,
*        performing arithmetic operations, and displaying the results.
*
*  Params:
*      - None
*
*  Returns:
*      int : 0 for successful execution
*****************************************************************************/
int main() {
    // Open input file
    ifstream inputFile("input.txt"); 
    if (!inputFile) {
        cout << "Error opening file" << endl;
        return 1; // Exit if file not found
    }

    string input1, input2, oper; // Variables for input fractions and operator
    inputFile >> input1 >> oper >> input2; // Read fractions and operator from file
    inputFile.close(); // Close input file

    cout << "Enter first fraction: " << endl;
    cin >> input1; // Read first fraction from user input
    cout << "Enter operator: " << endl;
    cin >> oper; // Read operator from user input
    cout << "Enter second fraction: " << endl;
    cin >> input2; // Read second fraction from user input

    Fraction frac1 = Fraction::parseFraction(input1); // Parse first fraction
    Fraction frac2 = Fraction::parseFraction(input2); // Parse second fraction
    Fraction result; // Variable to hold the result of operations

    // Example usage of arithmetic operations
    Fraction resultAdd = frac1 + frac2;  
    Fraction resultSub = frac1 - frac2; 
    Fraction resultMul = frac1 * frac2;  
    Fraction resultDiv = frac1 / frac2;  

    
    cout << frac1 << " + " << frac2 << " = " << resultAdd << endl;
    cout << frac1 << " - " << frac2 << " = " << resultSub << endl;
    cout << frac1 << " * " << frac2 << " = " << resultMul << endl;
    cout << frac1 << " / " << frac2 << " = " << resultDiv << endl;

    return 0; 
}
