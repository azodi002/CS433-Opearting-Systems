//Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

class Matrix
{
 private:
 
  int Row;
  int Column;
  int** Mat; // 2-D array (Dynamically Allocated)

 public:
  /*Constructor that takes inputfile name and reads in data for Matrix*/
  Matrix(const char* FileName);
  /*Constructor that takes Rows and Columns and makes 2D array with those dimensions*/
  Matrix(int R, int Col);
  /*Destructor deletes all dynamically allocated arrays*/
  ~Matrix();
  /*Sets all elements in matrix to 0*/
  void zero();
  /*Prints all elements in matrix*/
  void print();
  /*Sets certain location in matrix to a certain element (Data) */
  void set(int Row, int Column, int Data);  
  /*Sets all of Matrix to randomly generated number from 0-100*/
  void Random();
  /*Prints matrix to outputfile in format needed (Row, Column, then values of matrix) */ 
  void printFile(const char* FileName);
  /*Returns Row(Number of Rows FIRST DIMENSION) for a Matrix*/
  int getRow();
  /*Returns Column(Number of Columns SECOND DIMENSION) for a Matrix*/
  int getColumn();
  /*Returns element(Data) of a exact Matrix location using Rows and Columns*/
  int getValue(int i, int j);
 
};

#endif
