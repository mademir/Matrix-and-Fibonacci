#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct myMat {			// Struct to store matrices
	int numRows;		// Number of its rows
	int numCols;		// Number of its colums
	int data[16];		// Data to represent the elements of the matrix
};

myMat zeroMat(int r, int c) {
	// create a matrix with r rows and c columns, filled with zeros
	myMat m;			// define matrix
	m.numRows = r;		// set size
	m.numCols = c;
	for (int ct = 0; ct < 16; ct++) m.data[ct] = 0;	// set elems to 0
	return m;			// return matrix
}

int getElem(myMat m, int r, int c) {
	// return the item at m[r,c]   where r is 0..m.numRows-1 etc
	return m.data[r*m.numCols + c];
}

void setElem(myMat &m, int r, int c, int val) {
	// set element m[r,c] to val
	m.data[r*m.numCols + c] = val;
}

myMat mFromStr(string s) {
	// create a matrix from string s
	// string of form "1,2;3,4;5,6"   ; separates rows and , separates columns ... No error check
	int ms;
	if (s.length()>0) ms = 1; else ms = 0;
	myMat m = zeroMat(ms, ms);						// is s empty create 0*0 matrix, else start with 1*1 matrix
	int mndx = 0;									// used to index into array
	string sub = "";								// sub string - numbers between , or ; set empty
	for (int ct = 0; ct < s.length(); ct++) {		// each char in turn
		if ((s[ct] == ',') || (s[ct] == ';') ) {	// if , or ; then sub contains number
			m.data[mndx++] = stoi(sub);				// convert number to integer, put in data array
			sub = "";								// clear sub string
			if (s[ct] == ';') m.numRows++;			// if found ; indicates an extra row
			else if (m.numRows == 1) m.numCols++;	// if , then (if in row 1) increase count of columns
		}
		else sub = sub + s[ct];						// add character to sub string
	}
	if (sub.length() > 0) m.data[mndx++] = stoi(sub);// add last sub string
	return m;
}

myMat mGetRow(myMat m, int row) {
	// create a matrix from m, having one row
	myMat res = zeroMat(1, m.numCols);		// create a matrix of 1 row
	for (int col = 0; col < m.numCols; col++)		// for each element in row
		res.data[col] = getElem(m, row, col);		// copy col element to res
	return res;
}

///Gets the column in the specified index end returns it as a 1 column matrix.
myMat mGetCol(myMat m, int col) {
	myMat res = zeroMat(m.numRows, 1);		//Empty matrix of 1 column in size
	for (int row = 0; row < m.numRows; row++)		//Iterate through the elements in column
		res.data[row] = getElem(m, row, col);		//For each row, copy the element
	return res;

}

///Calculates the dot product of 2 vectors. Returns the result as an integer value.
int dotProd(myMat v1, myMat v2) {
	int res = 0;
	for (int ct = 0; ct < v1.numRows; ct++)  	//For each row in the vectors
		res += v1.data[ct] * v2.data[ct];		//Add the product of the corresponding elements to the res value
	return res;
}

///Takes a matrix and returns the transpose of it.
myMat mTranspose(myMat m) {
	myMat res = zeroMat(m.numCols, m.numRows);	//Empty matrix with the number of rows as the original's number of columns and columns as the original's rows
	for (int col = 0; col < m.numCols; col++)	//For each column of the original matrix
		for (int i = 0; i < m.numRows; i++)		//For each row of the original matrix
			res.data[col*res.numCols+i] = mGetCol(m, col).data[i]; //Get the 'col'th column's i'th data and set the corresponding row's i'th data of the result.
	return res;
}

///Takes 2 matrices and returns the sum of them.
myMat mAdd(myMat m1, myMat m2) {
	for (int ct = 0; ct < m1.numRows*m1.numCols; ct++) //For each element for the matrices
		m1.data[ct] += m2.data[ct]; //Add the corresponding element to the first matrix.
	return m1;	//Return the first matrix with added values.
}

///Multiply 2 matrices and retun the result matrix.
myMat mMult(myMat m1, myMat m2) {
	myMat res = zeroMat(m1.numRows, m2.numCols);	//Set an empty matrix with the size m1's rows and m2's columns.
	int ct = 0;
	for (int m1r = 0; m1r < m1.numRows; m1r++){		//For each row of m1
		for (int m2c = 0; m2c < m2.numCols; m2c++){	//For each column of m2
			for (int i = 0; i < m1.numCols; i++){	//For each element in m1's column
				res.data[ct] += getElem(m1, m1r, i) * getElem(m2, i, m2c); //Get the corresponding values from the corresponding rows and columns and multiply them, then add the value to the corresponding element in the result matrix.
			}
			ct++;
		}
	}
	return res;
}

///The fallowing functions are optionals.

///Takes an integer and a matrix and calculates the scalar multiplication.
myMat mScalarMult(int k, myMat m){
	for (int ct = 0; ct < m.numRows*m.numCols; ct++) //For each element in the matrix
		m.data[ct] *= k; //Multiply the element by the value
	return m;
}

///Finds the magic matrix for the given 2x2 matrix.
myMat findMagic(myMat m){
	myMat res = m; //Copies the original matrix
	setElem(res, 0, 0, -1 * getElem(m, 1, 1)); //Sets the element in 1st row 1st column to the negative of the element in 2nd row 2nd column.
	setElem(res, 1, 1, -1 * getElem(m, 0, 0)); //Sets the element in 2nd row 2nd column to the negative of the element in 1st row 1st column (from the original matrix).
	return res;
}

///Solves and returns the x values as a matrix in the equation Ax=b by using 'magic' matrix on 2x2 matrices.
myMat solveByMagic(myMat A, myMat b){
	myMat res = zeroMat(2,1);
	myMat M = findMagic(A); //Finds and assigns the magic matrix for the matrix.
	myMat MA = mMult(M, A); //Assigns the product of magic matrix and A to MA
	myMat Mb = mMult(M, b); //Assigns the product of magic matrix and b to Mb
	res.data[0] = Mb.data[0]/getElem(MA, 0, 0); //Divides the 1st element of Mb to the element in the 1st row 1st column of MA and stores the result as x1
	res.data[1] = Mb.data[1]/getElem(MA, 1, 1); //Divides the 2nd element of Mb to the element in the 2nd row 2nd column of MA and stores the result as x2
	return res;
}

///Takes a matrix and returns a matrix with the first row and the choosen column removed.
myMat subMat(myMat m, int col){
	myMat res = zeroMat(m.numRows - 1, m.numCols - 1);
	int k = 0; //'k' is to track the index of the data of the result matrix.
	for(int i = m.numCols; i <= (m.numCols * m.numRows); i++){ //Loops the data of the given matrix. 'i' is to track the index of the given matrix.
		if (i % m.numCols == col) i++; //If element is on the column to be removed increase 'i' to skip the element.
		res.data[k] = m.data[i]; //Assigns the element from the given matrix to the result matrix.
		k++; //Increases 'k' for the next iteration.
	}
	return res;
}

///Finds and returns the determinant of a square matrix of any size.
int findDet(myMat m){
	if (m.numRows == 1){ //If the matrix has only one row
		return m.data[0]; //Returns the first element on the matrix.
	}
	else if (m.numRows == 2){ //If the matrix has 2 rows
		return ((getElem(m, 0, 0) * getElem(m, 1, 1)) - (getElem(m, 0, 1) * getElem(m, 1, 0))); /*Returns the difference between the product of the elements in
																								1st row 1st column and 2nd row 2nd column and the product of the elements in the 
																								1st row 2nd column and the 2nd row 1st column.*/
	}
	else{
		int sum = 0;
		for (int i = 0; i < m.numCols; i++){ //For each element on the top row of the matrix
			sum += m.data[i] * pow(-1, i) * findDet(subMat(m,i));	/*Adds the product of the i'th element on the top row and the cofactor of that element
																	(which is - or + determinant of the sub-matrix without the first row and the i'th column) to 'sum'.*/
		}
		return sum;
	}
}

///Solves and returns the x values as a matrix in the equation Ax=b by using Cramer's Rule on square A matrices of any size.
myMat solveByCramer(myMat A, myMat b){
	myMat res = zeroMat(A.numRows, 1);
	int detA = findDet(A);	//Finds and assigns the determinant of the matrix
	myMat temp = A;			//Copies A to a temporary matrix
	for (int i = 0; i < A.numRows; i++){ //For each row in A
		for (int k = 0; k < A.numCols; k++){ //For each column in A
			setElem(temp, k, i, getElem(b, k, 0)); //Assigns the corresponding element on b to A
		}
		res.data[i] = findDet(temp) / detA;	//Finds the determinant of temp and divides it to determinant of A then assigns it to the corresponding element in the result
		temp = A; //Copies A to temp again for the next iteration
	}
	return res;
}

///Prints the given matrix to the user.
void printMat(const char* mess, myMat m) {
	cout << mess << " = " << "\n";
	for (int r = 0; r < m.numRows; r++) {
		for (int c = 0; c < m.numCols; c++)
			cout << getElem(m, r, c) << "\t";
		cout << "\n";
	}
	cout << "\n";
}

///The main function to call the other functions.
int main(int argc, char *argv[])
{
	cout << "Matrix Program\n";
	myMat m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, mA, mb, mA2, mb2, mA3, mb3, mA4, mb4, v1, v2;

	m1 = mFromStr("2,6,7;9,1,6");	//From question 1 A
	m2 = mFromStr("8,7;10,10;2,9");	//From question 1 C
	printMat("A", m1);
	printMat("C", m2);
	m3 = mAdd(m1, mTranspose(m2));
	printMat("A + C'", m3);
	m4 = mMult(m1, m2);
	printMat("A * C", m4);
	m5 = mMult(m2, m1);
	printMat("C * A", m5);

	///To create a matrix being a column vector from given matrix
	m6 = mGetCol(m2, 1);
	printMat("Column vector from C's second column", m6);

	///Next are random vectors to show the dot product.
	v1 = mFromStr("3;6;9"); //Random values
	v2 = mFromStr("2;4;8"); //Random values
	printMat("v1", v1);
	printMat("v2", v2);
	cout << "v1.v2 (Dot Product) =\n" << dotProd(v1, v2) << "\n\n";

	//Next are the optional functions.

	///To multiple each element in a matrix by a scalar
	m7 = mAdd(mScalarMult(9, m1), mScalarMult(-1, mTranspose(m2))); //Values from question 1
	printMat("9A - 1C' (Scalar Multiplication, From Q1)", m7);

	///Solving equation using 'magic' Matrix
	mA = mFromStr("1,6;1,10");	//Values from question 2
	mb = mFromStr("57;89");		//Values from question 2
	m8 = solveByMagic(mA, mb);
	printMat("Q2 A values", mA);
	printMat("Q2 b values", mb);
	printMat("Solving Q2 using 'magic' Matrix", m8);

	///Solving equations using Cramer's Rule
	mA2 = mFromStr("9,8;10,6"); //Values from question 8
	mb2 = mFromStr("138;136");	//Values from question 8
	m9 = solveByCramer(mA2, mb2);
	printMat("Q8 A values", mA2);
	printMat("Q8 b values", mb2);
	printMat("Solving Q8 using Cramer's Rule", m9);

	mA3 = mFromStr("6,7,1;10,6,8;7,10,2");	//Example values for 3x3
	mb3 = mFromStr("106;132;141"); 			//Example values for 3x3
	m10 = solveByCramer(mA3, mb3);
	printMat("3x3 example A values", mA3);
	printMat("3x3 example b values", mb3);
	printMat("Solving 3x3 example using Cramer's Rule", m10);

	mA4 = mFromStr("2,9,8,9;10,6,7,13;1,10,6,3;8,14,2,19"); //Example values for 4x4
	mb4 = mFromStr("188;226;122;279");						//Example values for 4x4
	m11 = solveByCramer(mA4, mb4);
	printMat("4x4 example A values", mA4);
	printMat("4x4 example b values", mb4);
	printMat("Solving 4x4 example using Cramer's Rule", m11);

	system("pause");
	return 0;
}

