// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define BUFFER_SIZE 4096

//Allocate a character array of specific size.
char* newCharArray(int size)
{
  size = size > 0 ? size : BUFFER_SIZE;
  char* arrayPointer;
  arrayPointer = malloc(sizeof(char*) * size);
  return arrayPointer;
};

int* newIntArray(int size)
{
  size = size > 0 ? size : BUFFER_SIZE;
  int* arrayPointer;
  arrayPointer = malloc(sizeof(int*) * size);
  return arrayPointer;
};

int* pushVectorContentsToArray(VECTOR* vec)
{
  int* returnArray;
  const int vecTotal = vector_total(vec);
  returnArray = newIntArray(vecTotal + 1);
  returnArray[0] = vecTotal;
  for (int i = 0; i < vecTotal; i++)
  {
    int* num;
    num = vector_get(vec, i);
    returnArray[i + 1] = num;
  };
  return returnArray;
};

int* parseTokenForNumbers(char* strArray)
{
  int returnArray[] = { 0,0 };
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
    VECTOR newVector;
    vector_init(&newVector);

    while (token != NULL)
    {
      int* numArray;
      numArray = parseTokenForNumbers(token);
      if (numArray[0] == 1)
      {
        isNumberInLine = 1;
        int* ptr;
        int num = numArray[1];
        ptr = num;
        vector_add(&newVector, ptr);
      };
      token = strtok(NULL, searchToken);
    };
    if (isNumberInLine == 1)
    {
      int* newArray;
      newArray = pushVectorContentsToArray(&newVector);
      vector_set(vec, i, newArray);
    }
    else
    {
      vector_delete(vec, i);
      i--;
    };
    vector_free(&newVector);
    free(currentLine);
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
    char* buffer = newCharArray(BUFFER_SIZE);
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
  printf("[");
  for (int i = 0; i < vector_total(&bufferVector); i++)
  {
    int* subArray;
    subArray = vector_get(&bufferVector, i);
    if (subArray[0] > 1)
      printf("[");
    int j = 1;
    for (;j <= subArray[0];j++)
    {
      printf("%i", subArray[j]);
      if (j != subArray[0])
        printf(", ");
      if (subArray[0] > 1 && j == subArray[0])
        printf("]");
    };
    if (i == vector_total(&bufferVector) - 1)
      printf("]");
    else
      printf(", ");

  };
  vector_free(&bufferVector);
  //CODE TO CLEAN UP SUB VECTORS AND MAIN VECTOR
  return 0;
}
