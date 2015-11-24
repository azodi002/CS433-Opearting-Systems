/**************************************************

Group Names: Omid Azodi
Due Date: 10/18/2015
Professor: Dr. Majd
Class: CS433 (Operating Systems)

Programming Project: Pipe Programming
Language: C++
Compiler: g++
File names: Pipes.cpp

Description: 
Creating two ordinary pipes. Each ordinary pipe has a read and write end.

***************************************************/
#include <iostream>
#include <sys/types.h>
#include <string>
#include <unistd.h>
#include <cstdlib>
using namespace std;

const int BUFFER_SIZE = 300;
const int WRITE_END = 1;
const int READ_END = 0;

void UserInputsMessage(char* write_msg);
void UserMessageEntered(char* write_msg);
void EncryptUserMessage(char* write_msg, char* read_msg);
void PrintEncryptedMessage(char* read_msg);


int main()
{
  char write_msg[BUFFER_SIZE]; //Original Message && Encrypted
  char read_msg[BUFFER_SIZE]; //Original Message
  char read_msg2[BUFFER_SIZE]; //Encrypted Message

  UserInputsMessage(write_msg);
  UserMessageEntered(write_msg);//Print original message

  /*
    fd[0] = read end of the pipe;
    fd[1] = write end of the pipe;
    WRITE_END = represents 1
    READ_END = represents 0
  */
  int fd[2];

  /*
    fd[0] = read end of the pipe;
    fd[1] = write end of the pipe;
    WRITE_END = represents 1
    READ_END = represents 0
  */
  int fd2[2];
  
  pid_t pid;//Process ID

  if(pipe(fd) < 0)
    {
      cout << " Pipe [failed] " << endl;
      cout << "****** TERMINATING PROGRAM *******" << endl;
      exit(1); // Terminate Program 
    }

  pipe(fd2);
  pid=fork(); 
  
  if(pid < 0)
    {
      cout << "pid = fork); FORK FAILED" << endl;
      cout << " ****** TERMINATING PROGRAM *****" << endl;
      exit(1); //Terminate Program
    }

  if(pid > 0) //Parent
    {
      close(fd[READ_END]);
      close(fd2[WRITE_END]); 
      write(fd[WRITE_END], write_msg, sizeof(write_msg) -1);
      close(fd[WRITE_END]);
      read(fd2[READ_END], read_msg2, BUFFER_SIZE);
    }

  else //Child
    {
      close(fd[WRITE_END]);
      read(fd[READ_END], read_msg, BUFFER_SIZE);
      close(fd2[READ_END]);
      close(fd[READ_END]);
      close(fd2[WRITE_END]);
      EncryptUserMessage(read_msg, write_msg);
      write(fd2[WRITE_END], read_msg, sizeof(write_msg) -1);     
      PrintEncryptedMessage(read_msg);    
      close(fd[READ_END]);
      close(fd2[READ_END]);
      close(fd[WRITE_END]);
    }      

  return 0;
}

/*
Function Purpose: User enters message 
Parameters: Character pointer (C-style string)
Parameter Description: Message that user enters into
*/

void UserInputsMessage(char* write_msg)
{
  cout << "Enter a message: ";
  cin.get(write_msg,9999999);
  cout << endl;
}



//________________________________________________________________

/*
Function Purpose: Prints user message that was entered
Parameters: Character pointer (C-style string)
Parameter Description: Message that user entered
*/
void UserMessageEntered(char* write_msg)
{
  cout << "The message you entered was: " << write_msg << endl;
  //Prints out Original Message of user input.
}

//________________________________________________________________

/*
Function Purpose: To encrypt the user message
Parameters: Character Pointer (C-style string), Character Pointer (C-style string)
Parameter Description: 
1st Parameter: Encrypted message returned after the function ends
2nd Parameter: Original message that the user entered and will be encrypted
*/
void EncryptUserMessage(char* read_msg, char* write_msg)
{
  /* Check each character in the string */
  for(int i=0; i< strlen(read_msg); i++)
    {
      /*Check character for lowercase*/
      if(read_msg[i] >= 'a' && read_msg[i] <= 'y')
	{
	  /*Change character from lowercase to capital character & encrypt moving one alphabet to the right */
	  read_msg[i] = (char)(read_msg[i]-31);
	}

      /*Check character for uppercase*/
      else if(read_msg[i] >= 'A' && read_msg[i] <= 'Y')
        {
	  /*Change character from uppercase to lowercase & encrypt moving one alphabet to the right*/
	  read_msg[i] = (char)(read_msg[i] + 33);
	}
      /*Check character if lowercase z or uppercase Z*/
       else if(read_msg[i] == 'z' || read_msg[i] == 'Z')
	 {
	   /*Don't shift z over, just change the size(Lower->Upper)*/
	   if(read_msg[i] == 'z')
	     {
	       read_msg[i] = 'Z';
             }
	   /*Don't shift Z over, just change the size(Upper->Lower)*/
	    else if(read_msg[i] == 'Z')
	      {
		read_msg[i] = 'z';
	      }
	  }
      }//End for loop
}

//____________________________________________________________________

/*Function Purpose: Print encrypted message to screen
  Parameters: Character Pointer (C-Style string)
  Parameter Description: The message that was encrypted after the EncryptUserMessage function was called
*/

void PrintEncryptedMessage(char* read_msg)
{
  cout << "The message encrypted: " << read_msg << endl;
}
