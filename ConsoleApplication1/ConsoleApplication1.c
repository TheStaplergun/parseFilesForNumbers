// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define BUFFER_SIZE 4096

//Allocate a character array of specific size.
char* new_array(int size)
{
  size = size > 0 ? size : BUFFER_SIZE;
  char* arrayPointer;
  arrayPointer = malloc(sizeof(char*) * size);
  return arrayPointer;
};

int* parseTokenForNumbers(char* strArray)
{
  int returnArray[2];
  int num = atoi(strArray);
  if (num == 0)
  {
    if (strlen(strArray) == 1)
      if (strArray[0] >= 48 && strArray[0] <= 57)
      {
        returnArray[0] = 1;
        returnArray[1] = 0;
      }
  }
  else
  {
    returnArray[0] = 1;
    returnArray[1] = num;
  };
  return returnArray;
};


//Parse each line of the file from memory.
void parseLines(VECTOR* vec)
{
  char* token;
  const char searchToken[2] = ",";
  for (int i = 0; i < vector_total(vec); i++)
  {
    char* currentLine;
    int isNumberInLine = 0;
    currentLine = vector_get(vec, i);
    token = strtok(currentLine, searchToken);
    while (token != NULL)
    {
      int* numArray;
      numArray = parseTokenForNumbers(token);
      if (numArray[0] == 1)
      {
        isNumberInLine = 1;
        printf("%i," , numArray[1]);
      };
      token = strtok(NULL, searchToken);
    };
    if (isNumberInLine == 1)
      printf("\n");
  };
};

int main()
{
  //Initiate file object and open
  FILE* file;
  fopen_s(&file, "C:/test.txt", "r");

  //Ensure a file successfully opened
  if (!file) {
    perror("File opening failed");
    return EXIT_FAILURE;
  }

  //Set up the vector struct members
  VECTOR bufferVector;
  vector_init(&bufferVector);

  //Read file to memory
  while (1)
  {
    char* buffer = new_array(BUFFER_SIZE);
    if (fgets(buffer, BUFFER_SIZE, file) != NULL)
    {
      //Store line from file in vector
      vector_add(&bufferVector, buffer);
    }
    else
    {
      fclose(file);
      break;
    };
  };
  
  parseLines(&bufferVector);
  vector_free(&bufferVector);
  //CODE TO CLEAN UP SUB VECTORS AND MAIN VECTOR
  return 0;
}
