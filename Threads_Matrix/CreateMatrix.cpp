#include "Matrix.h" //Takes Matrix class

int main() //Will create executable for this file
{
  /*User input for rows*/
int Rows;
cout << "Enter Rows for A: " << endl;
cin >> Rows;
cout << endl;

/*User input for columns*/
int Columns; 
cout << "Enter Columns for A: " << endl;
cin >> Columns;
cout << endl;

/*Set MatrixA to rows and columns of user input*/

Matrix MatrixA(Rows,Columns);
MatrixA.Random();

/*User input for columns*/
int RowsB;
cout << "Enter Rows for B: " << endl;
cin >> RowsB;
cout << endl;

/*User input for Columns */

int ColumnsB;
cout << "Enter Columns for B: " << endl;
cin >> ColumnsB;
cout << endl;

/*Set user rows and columns for B*/
Matrix MatrixB(RowsB, ColumnsB);
 MatrixB.Random();


 /*Print the Matrixes to the corresponding outputfiles */
MatrixA.printFile("DataMatrixA.txt");
MatrixB.printFile("DataMatrixB.txt");

 return 0;
}
