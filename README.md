# Roman Numeral Calculator

This project is a Roman numeral calculator that reads arithmetic operations involving Roman numerals from an input file, performs the calculations, and writes the results in words to an output file.

## Files

- `test.c`: The main source code file containing the implementation of the calculator.
- `input.txt`: The input file containing the arithmetic operations in Roman numerals.
- `output.txt`: The output file where the results in words are written.
- `.gitignore`: Git ignore file to exclude certain files and directories.
- `.gitattributes`: Git attributes file for text file normalization.
- `README.md`: This documentation file.

## Functions

### `int main()`

The main function that opens the input and output files, reads each line from the input file, processes it, and writes the result to the output file.

### `void processLine(char *line, FILE *outputFile)`

Processes a single line of input, which includes parsing the Roman numerals and operator, converting the Roman numerals to decimal, performing the arithmetic operation, converting the result to words, and writing the result to the output file.

### `int romanToDecimal(char *roman)`

Converts a Roman numeral string to its decimal equivalent.

### `void decimalToWords(int num, char *words)`

Converts a decimal number to its word representation.

### `int performOperation(int num1, int num2, char op)`

Performs an arithmetic operation (`+`, `-`, `*`, `/`) on two decimal numbers.

## Usage

1. Place the arithmetic operations in Roman numerals in the `input.txt` file, one operation per line.
2. Compile the `test.c` file using a C compiler:
