/*
  Author: Opeyemi Ajisegiri
  Date:   April 13th, 2021
  Project: Assignment 4[Banker's Algorithm]
  Class:   CMIS 412
*/
/*            ALGORITHM  
    The program reads the allocation, Maximum and, available matrices from a supplies file
    Computes the need matrice for the algorithm 
    Computes the safe sequences by checking if the needed resources by the process is 
          less than or equal to the available resources
    Uses Recursion and a Vector variable to keep track of all possible Safe sequences
    Prints out the Need matrices, Safe Sequences and the number of total possible Safe Sequences.
*/

#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <fstream>
using namespace std;

const int P = 5; //7;
const int R = 4; //5;
int numOfSeq = 0;

/*  Computing and printing the need matrice */
void getNeed(int need[P][R], int max[][R], int allocated[][R]){
  cout<< "The need Matrix: \n";
  for (int i = 0; i < P; i++){
    for (int j = 0; j < R; j++){
      need[i][j] = max[i][j] - allocated[i][j];
      cout<< need[i][j] << " ";
    }
    cout<< "\n\n";
    }
}
 
/*  Checking if the resources can be released i.e less than
     or equal to the available resources  */
bool isAvailable(int pid, int need[][R], int available[]){
  bool checkFlag = true;
  for (int i = 0; i < R; i++) {
    if (need[pid][i] > available[i])
      checkFlag = false;
  }
  return checkFlag;
}
 
/*  Computing all the possible safe sequences   */
void safeSequence(bool found[], int alloc[][R], int max[][R], int need[][R], int available[], vector<int> safeSeq){
  for (int i = 0; i < P; i++) {
    if (!found[i] && isAvailable(i, need, available)) {
      /* True if process' needed resources can be released */
      found[i] = true;
      /*  Releasing the resources used in the previous process   */
      for (int j = 0; j < R; j++)
        available[j] += alloc[i][j];
      safeSeq.push_back(i);
      /*  Using recursion to find all possible safe sequence*/
      safeSequence(found, alloc, max, need, available, safeSeq);
      safeSeq.pop_back();
      found[i] = false;
      for (int j = 0; j < R; j++)
        available[j] -= alloc[i][j];
    }
  }
  /*  Print all the safe sequences found*/
  if (safeSeq.size() == P) {
    numOfSeq++;
    for (int i = 0; i < P; i++) {
      cout << "P" << safeSeq[i];
      if (i != (P - 1))
        cout << "-> ";
    }
    cout << endl;
  }
}
 
int main(){
  /*  Read from File inputted by user */
  fstream inFile; string text; //int process;
  cout << "Please enter a file for the program to read from: \n"
 <<endl;
 cin >> text;
  //cin>> text>>P>>R;
  inFile.open(text);
  int alloc[P][R], max[P][R],available[R];
  cout << "Allocation: \t Max: \n" ;
  for(int i = 0; i < P; i++){
    for(int j = 0; j < R; j++){
      inFile>> alloc[i][j];
      cout << alloc[i][j] << " ";
    }
    cout << "\t\t";
    for(int j = 0; j < R; j++){
      inFile>> max[i][j];
      cout << max[i][j] << " ";
    }
    cout<< "\n\n";
  }
  cout << "Available: \n ";
  for(int i = 0; i < R; i++){
    inFile>> available[i];
    cout << available[i] << " ";
  }
  cout<< "\n\n";
  inFile.close();
  int resources[R] = { 2, 9, 10, 12 };
  for(int i = 0; i < R; i++) {
    int sum = 0;
    for (int j = 0; j < P; j++)
      sum -= alloc[j][i];
    available[i] = resources[i] - sum;
    }
  /*  Utilizing vector properties: pop_back() and push_back()
      to keep track of other possible safe sequences  */
  vector<int> safeSeq;
  bool found[P];
  int need[P][R];
  /* Calculate need matrix  */
  getNeed(need, max, alloc);

  /*  Print safe sequences and number of number of possible safe sequences  */
  cout << "The possible safe sequences are:" << endl;
  safeSequence(found, alloc, max, need, available, safeSeq);
  cout << "\nThere are " << numOfSeq << " possible safe-sequences" << endl;
  return 0;
}