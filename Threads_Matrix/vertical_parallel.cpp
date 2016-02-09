#include "Matrix.h"
#include <vector>

struct Pass //Pointer to this struct passed into pthread_create.
{
  Matrix *MatrixA;
  Matrix *MatrixB;
  Matrix *MatrixC;
  vector<int> *ColIndex;
};


void ColumnMultiply(Matrix& MatrixA, Matrix& MatrixB, Matrix& MatrixC);
void *runner(void* param);
void ColumnMultiply2(Matrix& MatrixA, Matrix& MatrixB, Matrix& MatrixC);

int main()
{
  long start_time;//Start timer for execution
  long stop_time;//End timer for execution

  Matrix MatrixA("DataMatrixA.txt");//MatrixA gets initialized with data from input file
  Matrix MatrixB("DataMatrixB.txt");//MatrixB gets initialized with data from input file
  Matrix MatrixC(MatrixA.getRow(),MatrixB.getColumn());//MatrixC gets A rows and B columns

  start_time=clock();//Start the timer
  ColumnMultiply(MatrixA, MatrixB,MatrixC);//Compute the multiplication and store in Matrix C.
  stop_time=clock();//End the timer after computation has ended
  
  double Vertical_Time= (stop_time-start_time)/(double)(CLOCKS_PER_SEC);//Total execution time 
  
  MatrixC.print();//Print matrixC results after computations
  

  /*Print out total time execution for function */
  cout << "________________________________________________________________ " << endl;
  cout << "Divide Vertically Time: " << Vertical_Time << " seconds" << endl;
  

  /*Create 2nd Matrix initialized to A rows and B columns*/ 
  Matrix MatrixC2(MatrixA.getRow(),MatrixB.getColumn());


  long start_time2; //Timer for function with twice the core count 
  long stop_time2; //End the timer after computation for twice the core count
  start_time2=clock();//Start timer for execution
  /*Computed multiplication and store results in MatrixC*/
  ColumnMultiply2(MatrixA,MatrixB,MatrixC2);
  stop_time2=clock();//End the timer after computation for twice the core count
  
  MatrixC2.print();//Print the Matrix C2 after computation for twice the core count

  /*Total execution time after computing matrix C2 with twice the core count*/
  double Vertical_Time2 = (stop_time2 - start_time2)/(double)(CLOCKS_PER_SEC);

  /*Print total execution time for computing Matrix C2 with twice the core count*/

  cout << "________________________________________________________________" << endl;
  cout << "Divide Vertically Time: " << Vertical_Time2 << endl;
  cout << "________________________________________________________________" << endl;


  return 0;
}

/*Multiplying Matrix A and Matrix B and storing value in Matrix C */
void ColumnMultiply(Matrix& MatrixA, Matrix& MatrixB, Matrix& MatrixC)
{
  int cores = (int)sysconf(_SC_NPROCESSORS_ONLN);//Number of cores in system
  
  pthread_t tid[cores];
  Pass passlist[cores];
  Pass *temp;//Pointer to the struct 

  cout << "Your computer has " << cores << " cores available " << endl;
  
  vector<int>array[cores]; //Arrays made for number of cores

  for(int col=0; col<MatrixB.getColumn(); col++)//Partition number of threads 
    {
      array[col%cores].push_back(col);
    }
  
  for(int i=0; i< cores; i++)
    {          
      /*Initialize struct attributes to real values*/
	  temp=&passlist[i];
	  temp->ColIndex=array+i;
	  temp->MatrixA=&MatrixA;
	  temp->MatrixB=&MatrixB;
	  temp->MatrixC=&MatrixC;
	  pthread_create(&tid[i],NULL,runner,(void*)temp);
	
    }
  /*Join threads after done executing*/
  for(int i=0; i< cores; i++)
    {
       pthread_join(tid[i],NULL);
    }

}//End function

/*Multiplying and adding the correct elements occur here*/
void *runner(void* param)
{
  Pass* p = (Pass*)(param);
  for(int i=0; i < p->MatrixA->getRow(); i++)
    {
      for(size_t ci=0; ci < p->ColIndex->size(); ci++)
	{
	  int product=0;
	  int j=p->ColIndex->at(ci);
	  for(int l=0; l< p->MatrixA->getColumn(); l++)
	    {
	      product+=(p->MatrixA->getValue(i,l)* p->MatrixB->getValue(l,j));
	    }
	  /*Set the final product after computation for one spot into MatrixC*/
	  p->MatrixC->set(i,j,product);
	}
    }
	       
return NULL;
}

/*Same as ColumnMultiply2 Just has twice the core count*/
void ColumnMultiply2(Matrix& MatrixA, Matrix& MatrixB, Matrix& MatrixC)
{
  int cores2 = (int)sysconf(_SC_NPROCESSORS_ONLN)*2; //Twice the core count

  pthread_t tid[cores2];
  Pass passlist[cores2];
  Pass *temp;//Pointer to struct

  cout << "Your computer has " << cores2 << " cores available " << endl;

  vector<int>array[cores2]; //Arrays made for number of cores

  for(int col=0; col<MatrixB.getColumn(); col++)//Partition threads 
    {
      array[col%cores2].push_back(col);
    }

  for(int i=0; i< cores2; i++)
    {
      //Set attributes to real values
      temp=&passlist[i];
      temp->ColIndex=array+i;
      temp->MatrixA=&MatrixA;
      temp->MatrixB=&MatrixB;
      temp->MatrixC=&MatrixC;
      pthread_create(&tid[i],NULL,runner,(void*)temp);

    }
  /*Thread joins after executing */
  for(int i=0; i< cores2; i++)
    {
      pthread_join(tid[i],NULL);
    }

}//End function

