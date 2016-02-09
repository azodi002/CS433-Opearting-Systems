#include "Matrix.h"
#include <pthread.h>

struct Pass
{
  int i;
  int j;
  Matrix *MatrixA;
  Matrix *MatrixB;
  Matrix *MatrixC;
};

void MatrixMultiplication(Matrix &MatrixA, Matrix &MatrixB, Matrix &MatrixC);
void *runner(void* param);

int main()
{
  long start_time;
  long stop_time;

  Matrix MatrixA("DataMatrixA.txt");
  Matrix MatrixB("DataMatrixB.txt");
  Matrix MatrixC(MatrixA.getRow(), MatrixB.getColumn());

  start_time=clock();
  MatrixMultiplication(MatrixA,MatrixB,MatrixC);
  stop_time=clock();

  double Parallel_Time = (stop_time-start_time)/(double)(CLOCKS_PER_SEC);
  MatrixC.print();
  cout << "__________________________________________________________________ " << endl;
  cout << "Parallel Time: " << Parallel_Time << " seconds" << endl;

  return 0;
}

  void MatrixMultiplication(Matrix &MatrixA, Matrix &MatrixB, Matrix &MatrixC)
   {
     pthread_t tid[MatrixA.getRow()][MatrixB.getColumn()];
     Pass passlist[MatrixA.getRow()][MatrixB.getColumn()];
     Pass *temp;

     for(int i=0; i< MatrixA.getRow(); i++)
       {
	 for(int j=0; j<MatrixB.getColumn(); j++)
	   {
	     temp=&passlist[i][j];
	     temp->i=i;
	     temp->j=j;
	     temp->MatrixA=&MatrixA;
	     temp->MatrixB=&MatrixB;
	     temp->MatrixC=&MatrixC;
	     pthread_create(&tid[i][j],NULL,runner,(void*)temp);   
	   }
       }

     for(int i=0; i<MatrixA.getRow();i++)
      {
	for(int j =0; j<MatrixB.getColumn();j++)
	  {
	    pthread_join(tid[i][j], NULL);
	  }
      }
  }

void *runner(void* param)
{
  Pass* p = (Pass*)(param);
  
  int product=0;
  for(int l=0; l< p->MatrixA->getColumn(); l++)
    {
      product+=(p->MatrixA->getValue(p->i,l) * p->MatrixB->getValue(l,p->j));
      p->MatrixC->set(p->i,p->j,product);
    }
    
  return NULL;
}
