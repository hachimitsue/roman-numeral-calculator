#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function prototypes
int romanToDecimal(char *roman);
void decimalToWords(int num, char *words);
int performOperation(int num1, int num2, char op);
void processLine(char *line, FILE *outputFile);

// Main function
int main() {
    FILE *inputFile = fopen("input.txt", "r"); // Open input file for reading
    FILE *outputFile = fopen("output.txt", "w"); // Open output file for writing
    char line[100]; // Buffer to store each line from the input file

    // Check if input file opened successfully
    if (inputFile == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    // Check if output file opened successfully
    if (outputFile == NULL) {
        printf("Error opening output file\n");
        fclose(inputFile);
        return 1;
    }

    // Read and process each line from the input file
    while (fgets(line, sizeof(line), inputFile)) {
        processLine(line, outputFile);
    }

    // Close the input and output files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

// Function to process a single line of input
void processLine(char *line, FILE *outputFile) {
    char roman1[20], roman2[20], op;
    int num1, num2, result;
    char words[100];

    // Parse the line to extract Roman numerals and the operator
    sscanf(line, "%s %c %s", roman1, &op, roman2);

    // Convert Roman numerals to decimal
    num1 = romanToDecimal(roman1);
    num2 = romanToDecimal(roman2);

    // Perform the arithmetic operation
    result = performOperation(num1, num2, op);

    // Convert the result to words
    decimalToWords(result, words);

    // Write the result to the output file
    fprintf(outputFile, "%s\n\n", words);
}

// Function to convert Roman numeral to decimal
int romanToDecimal(char *roman) {
    int i, num = 0, prev = 0, curr;
    // Iterate through the Roman numeral from right to left
    for (i = strlen(roman) - 1; i >= 0; i--) {
        // Determine the value of the current Roman numeral character
        switch (roman[i]) {
            case 'I': curr = 1; break;
            case 'V': curr = 5; break;
            case 'X': curr = 10; break;
            case 'L': curr = 50; break;
            case 'C': curr = 100; break;
            case 'D': curr = 500; break;
            case 'M': curr = 1000; break;
            default: return -1; // Invalid Roman numeral
        }
        // Apply subtractive principle if necessary
        if (curr < prev) num -= curr;
        else num += curr;
        prev = curr;
    }
    return num;
}

// Function to convert decimal number to words
void decimalToWords(int num, char *words) {
    // Arrays to store words for units, teens, tens, and thousands
    char *units[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    char *thousands[] = {"", "Thousand", "Million", "Billion"};

    // Handle the case where the number is zero
    if (num == 0) {
        strcpy(words, "Zero");
        return;
    }

    // Handle negative numbers
    if (num < 0) {
        strcpy(words, "Negative ");
        num = -num;
    } else {
        words[0] = '\0';
    }

    // Split the number into parts of thousands
    int part[4] = {0}, i = 0;
    while (num > 0) {
        part[i++] = num % 1000;
        num /= 1000;
    }

    // Convert each part to words
    for (i = 3; i >= 0; i--) {
        if (part[i] == 0) continue;
        int n = part[i];
        if (n >= 100) {
            strcat(words, units[n / 100]);
            strcat(words, " Hundred ");
            n %= 100;
        }
        if (n >= 20) {
            strcat(words, tens[n / 10]);
            strcat(words, " ");
            n %= 10;
        } else if (n >= 10) {
            strcat(words, teens[n - 10]);
            strcat(words, " ");
            n = 0;
        }
        if (n > 0) {
            strcat(words, units[n]);
            strcat(words, " ");
        }
        strcat(words, thousands[i]);
        strcat(words, " ");
    }
}

// Function to perform arithmetic operation
int performOperation(int num1, int num2, char op) {
    int result;
    // Perform the operation based on the operator
    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': 
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                printf("Error: Division by zero\n");
                result = 0; // or handle it as needed
            }
            break;
        default: result = 0; // Invalid operation
    }
    return result;
}