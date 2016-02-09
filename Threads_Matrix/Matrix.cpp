#include "Matrix.h" //Uses class Matrix

/*Constructor:
  Parameter: input file name with matrix data
  Puts Data from input file to Matrix
*/

Matrix::Matrix(const char* FileName) 
{
  ifstream inFile;
  inFile.open(FileName);

  if(!inFile) //Checking if file exists
    {
      cout << "File not found" << endl; //error message to user
      exit(1);
    }

  else //File exists
    {
      inFile >> Row; //Take Row for Matrix
      inFile >> Column; //Take Column for Matrix
     
     Mat = new int*[Row];
      
     for(int i =0; i<Row; i++)
	{
	  Mat[i] = new int[Column];//Initialize new column for each row
	  for(int j =0; j<Column; j++)
	    {
	      inFile >> Mat[i][j]; //Read in data for matrix and store into matrix
	    }
	}
    }
	 
  inFile.close(); //Close File (Memory Leaks)
}

/*
Constructor:
Parameters: Takes Rows and Columns
*/
Matrix::Matrix(int R, int Col) 
{
  Row = R; //User defined rows
  Column = Col; //User defined columns
  Mat= new int*[Row]; //Setting new array with Rows set to user defined rows
  for(int i=0; i<Row;i++)
    {
      Mat[i]= new int[Column]; //Creating new column for each row
    }
}

/*Destructor:
  Delete all the allocated arrays
*/
Matrix::~Matrix()
{
  for(int i=0; i<Row; i++)
    {
      delete[] Mat[i];
    }
  delete[] Mat; //Delete allocated arrays

}

/*Set all elements of Matrix to 0*/
void Matrix:: zero()
{
  for(int i=0; i<Row; i++)
    {
      for(int j=0; j<Column; j++)
	{
	  Mat[i][j] = 0;
	}
    }
}  

/*Print all elements in the Matrix (Row-Major)*/
void Matrix:: print()
{
 
  for(int i=0; i<Row; i++)
    {
      for(int j=0; j<Column; j++)
        {
          cout << Mat[i][j] << " ";
        }
          cout << endl;
    }
}

/*Parameters: Accepts user output file name
  Output the rows and columns as well as each element in the matrix to a output file that the user defines
*/
void Matrix:: printFile(const char* FileName)
{
  ofstream fout;
  fout.open(FileName);

  fout << Row << endl;
  fout << Column << endl;

  for(int i=0; i<Row; i++)
    {
      for(int j=0; j<Column; j++)
	{
	  fout << Mat[i][j] << " ";
	}
     fout << endl;
    }
  fout.close();
 
}

/*Return type: Returns direct value inside a matrix with user passing in rows and columns they want to access*/
 
int Matrix:: getValue(int i, int j)
{
  return Mat[i][j];
}

/* Matrix with user row and column gets a certain value*/
void Matrix:: set(int i, int j, int data)
{
  Mat[i][j]=data;
}

/*Matrix randomizes numbers and puts inside the matrix*/

void Matrix:: Random()
{
  for(int i=0; i<Row; i++)
    {
      for(int j= 0; j<Column; j++)
	{
	  Mat[i][j] = (rand() % 101);
	}
    }
}

/*Returns the row of a matrix */
int Matrix:: getRow()
{
  return Row;
}

/*Returns the column of a matrix*/
int Matrix:: getColumn()
{
  return Column;
}

