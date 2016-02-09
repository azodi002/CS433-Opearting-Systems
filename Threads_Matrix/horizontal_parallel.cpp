#include "Matrix.h"// Matrix Class
#include <vector>

struct Pass //Used for runner function
{
  Matrix *MatrixA;
  Matrix *MatrixB;
  Matrix *MatrixC;
  vector<int> *RowIndex;
};

void HorizontalMultiply(Matrix& MatrixA, Matrix& MatrixB, Matrix& MatrixC);
void *runner(void* param);
//__________________________________________________________
void HorizontalMultiply2(Matrix& MatrixA, Matrix& MatrixB, Matrix& MatrixC);

int main()
{
  long start_time; //Used for execution time (Start of execution)
  long stop_time; //Used for execution end time (End of execution)

  Matrix MatrixA("DataMatrixA.txt");//Input File data goes to Matrix A
  Matrix MatrixB("DataMatrixB.txt");// Input File data goes to Matrix B
  Matrix MatrixC(MatrixA.getRow(),MatrixB.getColumn());//Matrix C result gets rows of A and columns of B
  
  start_time=clock();//Starts timer 
  HorizontalMultiply(MatrixA, MatrixB,MatrixC);//Computing Multiplication
  stop_time=clock();//End timer
  
  double Horizontal_Time= (stop_time-start_time)/(double)(CLOCKS_PER_SEC); //Execution time
  
  MatrixC.print(); //Print result of Matrix C
  
  cout << endl;
  cout << "________________________________________________________________ " << endl;
  cout << "Divide Horizontal Time: (Core Count in System): " << Horizontal_Time << " seconds" << endl;
  cout << "________________________________________________________________ " << endl;

  long start_time2; //Timer for twice the core count
  long stop_time2;//End timer for twice the core count
  
  Matrix MatrixC2(MatrixA.getRow(),MatrixB.getColumn()); //MatrixC2 gets A rows and B cols
  start_time2= clock();//Start timer for function for twice core count
  HorizontalMultiply2(MatrixA, MatrixB, MatrixC2);//Twice core count multipling
  stop_time2 = clock();//End timer for function for twice core count
  
  double Horizontal_Time2 = (stop_time2-start_time2)/(double)(CLOCKS_PER_SEC); //Total execution time of twice core count Multiply
  
  MatrixC2.print();//Print Matrix C 
  
  cout << endl;
  cout << "_______________________________________________________________"<< endl;
  cout << "Divide Horizontal Time: (Twice amount of Cores in a system): " << Horizontal_Time2 << " seconds " << endl;
  cout << "_______________________________________________________________" << endl;
  
  return 0;
}

void HorizontalMultiply(Matrix& MatrixA, Matrix& MatrixB, Matrix& MatrixC)
{
  int cores = (int)sysconf(_SC_NPROCESSORS_ONLN); //Get # of cores from system
 
  pthread_t tid[cores]; //Make thread ids for number of cores available in system
  Pass passlist[cores];// Make an array of struct for number of cores available 
  Pass *temp; // Pointer to the struct 

  cout << "Your computer has " << cores << " cores available " << endl;
  
  vector<int>array[cores]; //Arrays made for number of cores

  for(int row=0;row<MatrixA.getRow();row++) //Partition to where the threads would be 
    {
      array[row%cores].push_back(row); 
    }
  
  for(int i=0; i< cores; i++)
    {          /*Set struct pointer to corresponding values*/
	  temp=&passlist[i];
	  temp->RowIndex=array+i;
	  temp->MatrixA=&MatrixA;
	  temp->MatrixB=&MatrixB;
	  temp->MatrixC=&MatrixC;
	  pthread_create(&tid[i],NULL,runner,(void*)temp);
	
    }
  /*After threads are done with execution we will join*/
  for(int i=0; i< cores; i++)
    {
       pthread_join(tid[i],NULL);
    }

}//End function

/*Gets called in pthread_create() function*/
void *runner(void* param)
{
  Pass* p = (Pass*)(param);//To access elements not visible

  /*Calculate product of MatrixC*/

  for(size_t ri=0; ri< p->RowIndex->size(); ri++) //Row index
     {
       int i= p->RowIndex->at(ri);
      
      for(int j=0; j< p->MatrixB->getColumn();j++)
	{
	   int product=0;
	   for(int l=0; l<p->MatrixA->getColumn();l++)
	     {
	       product+=(p->MatrixA->getValue(i,l) * p->MatrixB->getValue(l,j));
	       p->MatrixC->set(i,j,product);
	     }
	}
    }

  return NULL;
}

/*Calculates product of Matrix C however using twice the number of cores*/
void HorizontalMultiply2(Matrix& MatrixA, Matrix& MatrixB, Matrix& MatrixC)
{
  int cores2 = ((int)sysconf(_SC_NPROCESSORS_ONLN)) * 2; //Twice number of cores on system

  pthread_t tid[cores2]; //Thread id made for amount of cores
  Pass passlist[cores2]; 
  Pass *temp;//Pointer to struct (Used to Access elements) and be able to pass to runner* in pthread_create

  cout << "Your computer has double the amount of cores: " << cores2 << " cores available " << endl;

  vector<int>array[cores2]; //Arrays made for number of cores

  for(int row=0;row<MatrixA.getRow();row++) //Partition our threads to the number of cores we have
    {
      array[row%cores2].push_back(row);
    }


  for(int i=0; i< cores2; i++)
    {
      /*Set all struct members to real values */
      temp=&passlist[i];
      temp->RowIndex=array+i;
      temp->MatrixA=&MatrixA;
      temp->MatrixB=&MatrixB;
      temp->MatrixC=&MatrixC;
      pthread_create(&tid[i],NULL,runner,(void*)temp);

    }

  /*After thread execution we join*/
  for(int i=0; i< cores2; i++)
    {
      pthread_join(tid[i],NULL);
    }

}//End function

