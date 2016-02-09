#include "Matrix.h" //Matrix Class
#include <time.h> //Use some Timer functions

int main()
{
  long start_time;//Start of execution time
  long stop_time;//End of execution

  /*Matrices assigned from the input files*/
  Matrix MatrixA("DataMatrixA.txt");
  Matrix MatrixB("DataMatrixB.txt");
 
  /*Invalid multiplication*/
  if(MatrixA.getColumn()!=MatrixB.getRow())
    {
      /*Error message to user*/
      cout << "Invalid Multiplication will not work" << endl;
      cout << "TERMINATING PROGRAM" << endl;
      exit(1);//Terminates program
    }


  //Matrix C is always A rows by B columns 
  Matrix MatrixC(MatrixA.getRow(), MatrixB.getColumn());
  /*Initialize matrix to 0 to get rid of junk element values */
  MatrixC.zero();
  /*Used to set the element in the Matrix C*/
  int product=0;

  start_time=clock();//Write before the multiplication occurs start timer
  for(int i=0; i<MatrixA.getRow(); i++) //Start by A rows (Rows get incremented slowest
    {
      for(int j=0; j< MatrixB.getColumn();j++) //B Cols gets shifted 2nd slowest
	{ 
	  for(int l=0; l<MatrixA.getColumn();l++) // A columns shift fastest (Due to how matrix multiplcation works
	    {
	      product += MatrixA.getValue(i,l) * MatrixB.getValue(l,j);//Add the values A row and A col to B Column value store in product
	    }
	  MatrixC.set(i,j,product);//Put the value of product after it computed the whole column of B to one element in Matrix C
	  product=0;//Reset product to 0 so we can have new value be computed and stored to Matrix C
	}
    }
  stop_time=clock();//End timer because execution needed has ended
  double SerialTime = (stop_time-start_time)/(double)(CLOCKS_PER_SEC); //Holds total time of execution in seconds unit
 
  MatrixC.print();//Prints Matrix C value when Matrix A * Matrix B
   cout << "_______________________________________________________" << endl;
  
   cout << "Serial Time is: " << SerialTime << " seconds" << endl;
  return 0;
}

