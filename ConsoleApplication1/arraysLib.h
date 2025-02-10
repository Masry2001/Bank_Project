#pragma once

#include <iostream>
#include "myLibrary.h"
using namespace std;

namespace arraysLib {

	int readPositiveNumber(string message) {
		int N;
		do {
			cout << message << endl;
			cin >> N;
		} while (N < 0);
		return N;
	}

	// moved to clsUtil
	int generateRandomNum(int from, int to) {
		int random = rand() % (to - from + 1) + from;
		return random;
	}

	// moved to clsUtil
	void printIntArray(int arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++) {
			cout << arr[i] << " ";
		}
	}

	// moved to clsUtil
	void printStringArray(string arr[100], int arrLength) {

		for (int i = 0; i < arrLength; i++) {
			cout << "arr[" << i << "]: " << arr[i] << endl;
		}
	}

	// moved to clsUtil
	void swap(int& A, int& B) {
		int temp;
		temp = A;
		A = B;
		B = temp;
	}

	// moved to clsUtil
	void shuffleArray(int arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++) {
			swap(arr[i], arr[generateRandomNum(0, arrLength - 1)]);
		}
	}

	void addNumToArr(int number, int arr[100], int& arrLength) {
		arrLength++;
		arr[arrLength - 1] = number;
	}

	void readNumsAndSaveThemToArr(int arr[100], int& arrLength) {
		bool addMoreNums = true;

		do {

			addNumToArr(readPositiveNumber("Inter A Number: "), arr, arrLength);

			cout << "Do You Want To Add More Nums? [0]: No, [1]: Yes \n";
			cin >> addMoreNums;

		} while (addMoreNums);
	}

	// moved to clsUtil
	void arrayOfKeys(string arr[100], int numberOfKeys) {
		for (int i = 0; i < numberOfKeys; i++) {
			arr[i] = myLibrary::generateKey(4);
		}
	}

	void readArray(int arr[100], int& arrLength) {
		arrLength = readPositiveNumber("enter number of array elements");

		cout << "enter array elements:" << endl;
		for (int i = 0; i < arrLength; i++) {
			cout << "enter element [" << i + 1 << "]: ";
			cin >> arr[i];
		}
		cout << endl;
	}

	int frequencyOfNumInArr(int& numberToCheck, int arr[100], int arrLength) {

		int frequency = 0;
		numberToCheck = readPositiveNumber("enter the number you want to check: ");
		for (int i = 0; i < arrLength; i++) {
			if (numberToCheck == arr[i]) {
				frequency++;
			}
		}
		return frequency;
	}

	// moved to clsUtil
	void arrOfRandomNums(int arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++) {
			arr[i] = generateRandomNum(0, 100);
		}
	}

	int maxNumberOfArr(int arr[100], int arrLength) {
		int maxNumber = arr[0];
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] > maxNumber) {
				maxNumber = arr[i];
			}
		}
		return maxNumber;
	}

	int minNumberOfArr(int arr[100], int arrLength) {
		int minNumber = arr[0];
		for (int i = 0; i < arrLength; i++) {
			if (minNumber > arr[i]) {
				minNumber = arr[i];
			}
		}
		return minNumber;
	}

	int sumOfRandomArr(int arr[100], int arrLength) {
		int sum = 0;
		for (int i = 0; i < arrLength; i++) {
			sum = sum + arr[i];
		}
		return sum;
	}

	float averageOfRandomArr(int arr[100], int arrLength) {
		float average = (float)sumOfRandomArr(arr, arrLength) / arrLength;
		return average;
	}


	void copyPrimeNumsOfArr(int arr[100], int arrLength, int primeNumsArr[100], int& primeNumsArrLength) {
		int index = 0;
		for (int i = 0; i < arrLength; i++) {
			if (myLibrary::checkPrime(arr[i]) == myLibrary::enPrimeOrNotPrime::prime) {
				primeNumsArr[index] = arr[i];
				index++;
			}
		}
		primeNumsArrLength = index;
	}

	void sumOfTwoArr(int arr1[100], int arr2[100], int arrLength, int sumArr[100]) {

		for (int i = 0; i < arrLength; i++) {
			sumArr[i] = arr1[i] + arr2[i];
		}
	}

	void reverseArray(int arr[100], int arrLength) {
		int half = ceil(arrLength / 2);
		for (int i = 0; i < half; i++) {
			swap(arr[i], arr[arrLength - i - 1]);
		}
	}

	void copyRandomArr(int arr[100], int arrLength, int copyArr[100]) {
		for (int i = 0; i < arrLength; i++) {
			copyArr[i] = arr[i];
		}
	}

	void copyArrInReverseOrder(int arr[100], int arrLength, int copyArr[100]) {
		copyRandomArr(arr, arrLength, copyArr);
		reverseArray(copyArr, arrLength);
	}

	void copyArrUsingAddNumToArr(int arr[100], int arr2[100], int arrLength, int& arr2Length) {
		for (int i = 0; i < arrLength; i++) {
			addNumToArr(arr[i], arr2, arr2Length);
		}
	}

	void copyOddNumsToAnotherArr(int arr[100], int arr2[100], int arrLength, int& arr2Length) {
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] % 2 == 1) {
				addNumToArr(arr[i], arr2, arr2Length);
			}
		}
	}

	void copyEvenNumsToAnotherArr(int arr[100], int arr2[100], int arrLength, int& arr2Length) {
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] % 2 == 0 && arr[i] != 0) {
				addNumToArr(arr[i], arr2, arr2Length);
			}
		}
	}

	void copyPrimeNumsOfArr(int arr[100], int primeNumsArr[100], int arrLength, int& primeNumsArrLength) {
		for (int i = 0; i < arrLength; i++) {
			if (myLibrary::checkPrime(arr[i]) == myLibrary::enPrimeOrNotPrime::prime) {

				addNumToArr(arr[i], primeNumsArr, primeNumsArrLength);

			}
		}
	}

	short IndexOfNumInArr(int numberToCheck, int arr[100], int arrLength) {


		for (int i = 0; i < arrLength; i++) {
			if (numberToCheck == arr[i]) {
				return i;
			}
		}
		return -1;
	}

	bool isNumberInArr(int numberToCheck, int arr[100], int arrLength) {
		return IndexOfNumInArr(numberToCheck, arr, arrLength) != -1;
	}

	void copyDistinctNumsFromArrToAnotherArr(int arr[100], int arr2[100], int arrLength, int& arr2Length) {
		for (int i = 0; i < 10; i++) {
			if (!isNumberInArr(arr[i], arr2, arr2Length)) {
				addNumToArr(arr[i], arr2, arr2Length);
			}
		}
	}

	void reverseArr(int arr[10], int reversedArr[10], int arrLength) {

		for (int i = 0; i < arrLength; i++) {
			reversedArr[arrLength - i - 1] = arr[i];
		}
	}

	bool isItPalindrome(int arr[10], int reversedArr[10], int arrLength) {

		reverseArr(arr, reversedArr, arrLength);
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] != reversedArr[i]) {
				return false;
			}
		}
		return true;
	}

	int numberOfOddNumsInArr(int arr[100], int arrLength) {
		int counter = 0;
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] % 2 == 1) {
				counter++;
			}
		}
		return counter;
	}

	int numberOfEvenNumsInArr(int arr[100], int arrLength) {
		int counter = 0;
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] % 2 == 0) {
				counter++;
			}
		}
		return counter;
	}

	int numberOfPrimeNumsInArr(int arr[100], int arrLength) {
		int counter = 0;
		for (int i = 0; i < arrLength; i++) {
			if (myLibrary::checkPrime(arr[i]) == myLibrary::enPrimeOrNotPrime::prime) {
				counter++;
			}
		}
		return counter;
	}

	int numberOfPositiveNumsInArr(int arr[100], int arrLength) {
		int counter = 0;
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] > 0) {
				counter++;
			}
		}
		return counter;
	}

	int numberOfNegativeNumsInArr(int arr[100], int arrLength) {
		int counter = 0;
		for (int i = 0; i < arrLength; i++) {
			if (arr[i] < 0) {
				counter++;
			}
		}
		return counter;
	}


	void multiTableUsingTwoDimArr() {
		int nums[10][10] = {};

		for (int row = 0; row < 10; row++) {
			for (int col = 0; col < 10; col++) {
				nums[row][col] = (row + 1) * (col + 1);
			}
		}

		for (int row = 0; row < 10; row++) {
			for (int col = 0; col < 10; col++) {
				printf("%03d | ", nums[row][col]);
			}
			cout << endl;
		}
	}

	void randomMatrix(int matrix[3][3], short numOfRows, short numOfCols) {

		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {
				matrix[row][col] = myLibrary::generateRandomNum(0, 10);
			}
		}
	}

	void orderedMatrix(int matrixOrdered[3][3], short numOfRows, short numOfCols) {
		int number = 1;
		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {
				matrixOrdered[row][col] = number;
				number++;
			}
		}
	}

	void printMatrix(int matrix[3][3], short numOfRows, short numOfCols) {

		cout << setw(10) << numOfRows << " * " << numOfCols << " Matrix : " << endl << endl;

		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {
				printf("%02d  ", matrix[row][col]);
			}
			cout << endl << endl;
		}
	}

	int rowSum(int matrix[3][3], short rowNumber, short numOfCols) {
		int sum = 0;
		for (short col = 0; col < numOfCols; col++) {
			sum += matrix[rowNumber][col];
		}
		return sum;
	}



	void addEachRowSumToArr(int rowsArr[3], int matrix[3][3], short rows, short cols) {
		for (int rowNumber = 0; rowNumber < rows; rowNumber++) {
			rowsArr[rowNumber] = rowSum(matrix, rowNumber, cols);
		}
	}

	int colSum(int matrix[3][3], short numOfRows, short colNumber) {
		int sum = 0;
		for (short row = 0; row < numOfRows; row++) {
			sum += matrix[row][colNumber];
		}
		return sum;
	}

	void addEachColSumToArr(int colsArr[3], int matrix[3][3], short rows, short cols) {
		for (short colNumber = 0; colNumber < cols; colNumber++) {
			colsArr[colNumber] = colSum(matrix, rows, colNumber);
		}
	}


	void printEachRowSum(int matrix[3][3], short numOfRows, short numOfCols) {
		cout << "\n The Sum Of Each Row In A Matrix\n";
		for (short rowNumber = 0; rowNumber < numOfRows; rowNumber++) {
			cout << "Sum of row " << rowNumber + 1 << " = " << rowSum(matrix, rowNumber, numOfCols) << endl;
		}
	}


	void printEachColSum(int matrix[3][3], short numOfRows, short numOfCols) {
		cout << "\n The Sum Of Each Col In A Matrix\n";
		for (short colNumber = 0; colNumber < numOfCols; colNumber++) {
			cout << "Sum of col " << colNumber + 1 << " = " << colSum(matrix, numOfRows, colNumber) << endl;
		}
	}

	void transposedMatrix(int matrix[3][3], int transposeMatrix[3][3], int numOfRows, int numOfCols) {
		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {
				transposeMatrix[row][col] = matrix[col][row];
			}
		}
	}

	void multiplyTwoMatrices(int matrix1[3][3], int matrix2[3][3], int resultMatrix[3][3], short numberOfRows, short numberOfCols) {
		for (int row = 0; row < numberOfRows; row++) {
			for (int col = 0; col < numberOfCols; col++) {
				resultMatrix[row][col] = matrix1[row][col] * matrix2[row][col];
			}
		}
	}

	void printMiddleRowOfMatrix(int matrix[3][3], short numOfRows, short numOfCols) {
		short middleRow = floor(numOfRows / 2);
		cout << "\nMiddle row of matrix" << endl;
		for (int col = 0; col < numOfCols; col++) {

			printf("%02d  ", matrix[middleRow][col]);
		}
		cout << endl;

	}

	void printMiddleColOfMatrix(int matrix[3][3], short numOfRows, short numOfCols) {
		short middleCol = floor(numOfCols / 2);
		cout << "\nMiddle col of matrix" << endl;
		for (int row = 0; row < numOfRows; row++) {
			printf("%02d  ", matrix[row][middleCol]);
		}
		cout << endl;

	}

	int sumMatrixNumbers(int matrix[3][3], short numOfRows, short numOfCols) {
		int sum = 0;
		for (int row = 0; row < numOfRows; row++) {
			for (int col = 0; col < numOfCols; col++) {
				sum += matrix[row][col];
			}
		}
		return sum;
	}

	void checkMatricesEqualityFromTheirSum(int matrix1[3][3], int matrix2[3][3], short numberOfRows, short numberOfCols) {
		int matrix1Sum = sumMatrixNumbers(matrix1, numberOfRows, numberOfCols);
		int matrix2Sum = sumMatrixNumbers(matrix2, numberOfRows, numberOfCols);
		cout << "matrix1 Sum: " << matrix1Sum << endl;
		cout << "matrix2Sum: " << matrix2Sum << endl;

		if (matrix1Sum == matrix2Sum) {
			cout << "\n Yes: Matrices Sum Are Equal \n";
		}
		else {
			cout << "\n No: Matrices Sum Are Not Equal\n";
		}
	}

	bool checkIfMatricesAreTypical(int matrix1[3][3], int matrix2[3][3], short numberOfRows, short numberOfCols) {

		for (short row = 0; row < numberOfRows; row++) {
			for (short col = 0; col < numberOfCols; col++) {
				if (matrix1[row][col] != matrix2[row][col]) {
					return 0;
				}
			}
		}
		return 1;
	}

	bool checkIfMatrixIsIdentity(int matrix[3][3], short numOfRows, short numOfCols) {
		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {
				if (row == col && matrix[row][col] != 1) {

					return false;

				}
				else if (row != col && matrix[row][col] != 0) {

					return false;

				}
			}
		}
		return true;
	}

	bool checkIfMatrixIsScalar(int matrix[3][3], short numOfRows, short numOfCols) {
		// check if matrix[0][0] == matrix[1][1] == matrix[2][2] and the rest == 0
		short firstDiagonalNum = matrix[0][0];
		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {
				if (row == col && matrix[row][col] != firstDiagonalNum) {

					return false;

				}
				else if (row != col && matrix[row][col] != 0) {
					return false;
				}
			}
		}
		return true;
	}

	short countNumInMatrix(int matrix[3][3], short numOfRows, short numOfCols, short num) {
		short count = 0;
		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {
				if (matrix[row][col] == num) {
					count++;
				}
			}
		}
		return count;
	}


	short checkIfMatrixIsSparce(int matrix[3][3], short numOfRows, short numOfCols) {
		short zeros = 0;
		short nonZeros = 0;
		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {
				if (matrix[row][col] == 0) {
					zeros++;
				}
				else {
					nonZeros++;
				}
			}
		}
		return (zeros > nonZeros);
	}

	bool checkIfNumInMatrix(int matrix[3][3], short numOfRows, short numOfCols, short num) {

		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {
				if (matrix[row][col] == num) {
					return true;
				}
			}
		}
		return false;
	}


	void printIntersectedNumsInTwoMatrices(int matrix1[3][3], int matrix2[3][3], short numOfRows, short numOfCols) {

		cout << "Intersected Numbers are \n\n";
		short num;
		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {

				num = matrix1[row][col];
				if (arraysLib::checkIfNumInMatrix(matrix2, numOfRows, numOfCols, num)) {
					cout << setw(3) << num;
				}

			}
		}
	}

	short maxNumInMatrix(int matrix[3][3], short numOfRows, short numOfCols) {
		short maxNum = matrix[0][0];

		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {

				if (maxNum < matrix[row][col]) {
					maxNum = matrix[row][col];
				}
			}
		}

		return maxNum;
	}

	short minNumInMatrix(int matrix[3][3], short numOfRows, short numOfCols) {
		short minNum = matrix[0][0];

		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols; col++) {

				if (minNum > matrix[row][col]) {
					minNum = matrix[row][col];
				}
			}
		}

		return minNum;
	}

	bool checkIfMatrixIsPlaindrome(int matrix[3][3], short numOfRows, short numOfCols) {

		for (short row = 0; row < numOfRows; row++) {
			for (short col = 0; col < numOfCols / 2; col++) {

				if (matrix[row][col] != matrix[row][numOfCols - 1 - col]) {
					return false;
				}

			}
		}
		return true;

	}

}