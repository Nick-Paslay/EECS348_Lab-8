#include <iostream>
#include <fstream>
#include <vector>

class MatrixOperations {
private:
    int N;
    std::vector<std::vector<int>> matrix1;
    std::vector<std::vector<int>> matrix2;

public:
    // Function to load matrices from a file
    bool loadMatrices(const std::string& filename) {
        std::ifstream file(filename);

        file >> N; // takes in file and reads matriz size, N.
        if (N <= 0) {
            std::cerr << "Invalid matrix size." << std::endl; // if matrix size, N, is below 0, it returns an error. 
            return false;
        }

        matrix1.assign(N, std::vector<int>(N)); // reads first matrix.
        matrix2.assign(N, std::vector<int>(N));// reads second matrix.

        for (int i = 0; i < N; ++i) // for each row, go to the column and for each column integer, read the number from the row,column[i].
            for (int j = 0; j < N; ++j)
                file >> matrix1[i][j];

        for (int i = 0; i < N; ++i)// same as before, but for matrix 2.
            for (int j = 0; j < N; ++j)
                file >> matrix2[i][j];

        file.close(); // close file. 
        return true;
    }

const std::vector<std::vector<int>>& getMatrix1() const { return matrix1; }
const std::vector<std::vector<int>>& getMatrix2() const { return matrix2; }


    // Function to print a matrix
    void printMatrix(const std::vector<std::vector<int>>& matrix, const std::string& label) {
        std::cout << label << ":\n";
        for (const auto& row : matrix) { // for each row, print val
            for (int val : row)
            std::cout << val << "  ";// this aligns the columns to look better.
            std::cout << std::endl;
        }
    }

    // Function to add two matrices
    void addMatrices() {
        std::vector<std::vector<int>> result(N, std::vector<int>(N)); // takes in the matrices.
        for (int i = 0; i < N; ++i) // for each size, takes in the row and column, and adds each integer in it, and then returns it.
            for (int j = 0; j < N; ++j)
                result[i][j] = matrix1[i][j] + matrix2[i][j];

        printMatrix(result, "Adding Two Matrices: "); // a line to print for adding two matrices
    }

    // Function to multiply two matrices
    void multiplyMatrices() {
        std::vector<std::vector<int>> result(N, std::vector<int>(N, 0)); // creates the matrix with all 0s.
        for (int i = 0; i < N; ++i) // for each row, for each column, multiply each single number and replace the 0 with the result.
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < N; ++k)
                    result[i][j] += matrix1[i][k] * matrix2[k][j];

        printMatrix(result, "Multiplying Two Matrices");
    }

    // Function to calculate diagonal sums
    void diagonalSum() {
        int mainDiagonalSum = 0, secondaryDiagonalSum = 0;
        for (int i = 0; i < N; ++i) {
            mainDiagonalSum += matrix1[i][i]; //finds the first diagonail.
            secondaryDiagonalSum += matrix1[i][N - 1 - i]; //finds the opposite diagonal, secondary diagonal. 
        }
        std::cout << "Sum of First  Diagonal: " << mainDiagonalSum << std::endl;
        std::cout << "Sum of Second Diagonal: " << secondaryDiagonalSum << std::endl;
    }

    // Function to swap two rows
    void swapRows(int r1, int r2) {
        if (r1 >= 0 && r1 < N && r2 >= 0 && r2 < N) { // confirms that these are rows.
            std::swap(matrix1[r1], matrix1[r2]); // this swaps the rows with each other.
            printMatrix(matrix1, "Matrix After Swapping Rows");
        } else {
            std::cerr << "Invalid row indices!" << std::endl; // in case they are not rows.
        }
    }

    // Function to swap two columns
    void swapColumns(int c1, int c2) {
        if (c1 >= 0 && c1 < N && c2 >= 0 && c2 < N) { // confirms they are columns
            for (int i = 0; i < N; ++i)
                std::swap(matrix1[i][c1], matrix1[i][c2]); // this function swaps the columns. 
            printMatrix(matrix1, "Matrix After Swapping Columns");
        } else {
            std::cerr << "Invalid column indices!" << std::endl; // in case they are now columns.
        }
    }

    // Function to update a matrix element
    void updateElement(int row, int col, int newValue) { // takes in the wanted value, and position of where the new element will be.
        if (row >= 0 && row < N && col >= 0 && col < N) { // confirms it exists,
            matrix1[row][col] = newValue; //swaps new value with old value 
            printMatrix(matrix1, "Matrix After Update"); // reprints the matrix.
        } else {
            std::cerr << "Invalid indices!" << std::endl;// if it doesn't exist, return an error.
        }
    }
};

// Main function
int main() {
    MatrixOperations matrixOps;
    std::string filename; // make a vlue, filename 
    
    std::cout << "Enter file name: ";
    std::cin >> filename;// get filename from user 
    
    if (!matrixOps.loadMatrices(filename)) { // this entire function takes the filename, reads each row and column from the file. 
        return 1;
    }
    matrixOps.printMatrix(matrixOps.getMatrix1(), "Matrix 1"); // prints matrix 1.
    matrixOps.printMatrix(matrixOps.getMatrix2(), "Matrix 2"); // prints matrix 2.


    matrixOps.addMatrices(); // runs the add function
    matrixOps.multiplyMatrices(); // runs the multiplication function
    matrixOps.diagonalSum(); // runs the diagonal row and column function

    int r1, r2, c1, c2, row, col, newValue;
    
    std::cout << "\nEnter two row indices to swap: "; // asks user what indices they want to swap. 
    std::cin >> r1 >> r2; 
    matrixOps.swapRows(r1, r2); // uses function to swap 

    std::cout << "\nEnter two column indices to swap: "; // asks user what columns they want to swap
    std::cin >> c1 >> c2;
    matrixOps.swapColumns(c1, c2); // ueses function to swap

    std::cout << "\nEnter row, column, and new value to update an element: "; // asks user for the row, column and new element that they want to swap it with .
    std::cin >> row >> col >> newValue;
    matrixOps.updateElement(row, col, newValue); // runs the function for it.

    return 0; // end of program. 
}
