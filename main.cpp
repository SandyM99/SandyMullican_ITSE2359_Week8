#include <iostream>
#include <fstream>

// Function to calculate gcd (Euclid's algorithm)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Fraction class definition
class Fraction {
private:
    int numerator;
    int denominator;

public:
    // Constructor with default values
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {}

    // Overload the + operator to add two fractions
    Fraction operator+(const Fraction& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        int divisor = gcd(num, denom);  // Simplify the fraction
        return Fraction(num / divisor, denom / divisor);
    }

    // Overload the == operator to compare two fractions
    bool operator==(const Fraction& other) const {
        return numerator * other.denominator == other.numerator * denominator;
    }

    // Overload << operator to print the fraction
    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction) {
        out << fraction.numerator << '/' << fraction.denominator;
        return out;
    }

    // Overload >> operator to input a fraction in the form num/denom
    friend std::istream& operator>>(std::istream& in, Fraction& fraction) {
        char slash;
        in >> fraction.numerator >> slash >> fraction.denominator;
        return in;
    }
};

// Function to process fractions from input and write results to output
void processFractions(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (!inFile || !outFile) {
        std::cerr << "Error opening input or output file." << std::endl;
        return;
    }

    Fraction f1, f2;

    while (inFile >> f1 >> f2) {  // Read fractions from file
        // Add fractions and write the result
        Fraction sum = f1 + f2;
        outFile << f1 << " + " << f2 << " = " << sum << std::endl;

        // Compare fractions and write the result
        if (f1 == f2) {
            outFile << f1 << " is equal to " << f2 << std::endl;
        } else {
            outFile << f1 << " is not equal to " << f2 << std::endl;
        }
    }
}

int main() {
    std::string inputFile = "fractions.txt";   // Input file path
    std::string outputFile = "results.txt";    // Output file path

    processFractions(inputFile, outputFile);   // Process the fractions
    std::cout << "Processing complete. Results written to " << outputFile << std::endl;

    return 0;
}

