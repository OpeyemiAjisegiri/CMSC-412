#include <iostream>  //standard input and output header files
#include <thread>   //thread header files
 

/*  Anonymous functions for threads to implement  */
void foo(int z){
  std::cout<<"Thread 1 Running: Iteration number "<< z << "\n\n" ; 
}

void bar(int x){
  std::cout<<"Thread 2 Running: Iteration number "<< x <<"\n\n";
}

void sar(int a){
  std::cout<<"Thread 3 Running: Iteration number "<< a <<"\n\n";
}

/*  Main Function  */
int main() 
{
  for(int g = 0; g < 5; g++){
    /*  Creating and defining threads and its parameters  */
    std::thread first(foo,g+1);
    std::thread second(bar,g+1);
    std::thread third(sar, g+1);

    /*  Synchronizing threads */
    first.join();
    second.join();
    third.join();
  }
  return 0;
}