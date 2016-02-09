#include "Matrix.h"


int main()
{
  Matrix MatrixA(3,3);
  MatrixA.Random();
  MatrixA.print();
  MatrixA.printFile("DataMatrixA.txt");


  return 0;
}
