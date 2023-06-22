#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

/* Converting String to hexadecimal */
std::string HexConversion(const std::string& s)
{
  std::ostringstream retain;
  for (std::string::size_type i = 0; i < s.length(); ++i)
    retain << std::hex << std::setfill('0') << std::setw(2) << (int)s[i];
  return retain.str();
}

/*  Dispaying Selection Options */
void display(){
  std::cout<<"\t0 - Exit"<<std::endl;
  std::cout<<"\t1 – Select directory"<<std::endl;
  std::cout<<"\t2 – List directory content (first level)"<<std::endl;
  std::cout<<"\t3 – List directory content (all levels)"<<std::endl;
  std::cout<<"\t4 – Delete file"<<std::endl;
  std::cout<<"\t5 – Display file (hexadecimal view)"<<std::endl;
  std::cout<<"\t6 – Encrypt file (XOR with password)"<<std::endl;
  std::cout<<"\t7 – Decrypt file (XOR with password)"<<std::endl;
  std::cout<<"Select option"<<std::endl;
}
/*  Main Function */
int main() {
  /*  Declaring attributes  */
  int option, j;
  std::string directoryPath;
  std::string file, input;
  std::ifstream infileStream;
  std::ofstream outfileStream;
  char fileName[25]; /*, password[250];*/
  std::string password;
  //bool fileFlag;

  /*  Getting user Options*/
  display();
  std::cin>>option;

  while(option != 0){
    std::string j;
    switch(option){
      case 1:
      /*  Getting the name/root of the chosen directory  */
        std::cout<<"Enter the directory [absolute] name of the directory:\n"<<std::endl;
        std::cin>> directoryPath;
        break;
      case 2:
      /*  Displaying the  the files, and directories in the chosen directory  */
        if(directoryPath.empty())
          std::cout<<"Please select option 1 and enter a directory."<<std::endl;
        for (const auto & file : std::filesystem::directory_iterator(directoryPath))
          std::cout << file.path() << std::endl;
        break;
      case 3:
      /*  Displaying all the files, directories and sub-directories in the chosen directory  */
        if(directoryPath.empty())
          std::cout<<"Please select option 1 and enter a directory."<<std::endl;
        for (const auto & file : std::filesystem::recursive_directory_iterator(directoryPath))
          std::cout << file.path() << std::endl;
        break;
      case 4:
      /*  Deleting the chosen file  */
        if(directoryPath.empty())
          std::cout<<"Please select option 1 and enter a directory."<<std::endl;
        std::cout<<"Enter the name of the file to be deleted"<<std::endl;
        int fileStatus;
        std::cin>>fileName;
        fileStatus = std::remove(fileName);
        if(fileStatus == 0)
          std::cout<<"File deleted." << std::endl;
        else 
          std::cout<<"File was not deleted."<<std::endl;
        break;
      case 5:
      /*  Displaying the content of the chosen file in hexadecimal  */
        std::cout<<"Enter a file in the selected directory to display."<<std::endl;
        std::cin>>file;
        infileStream.open(file, std::ios::out | std::ios::app | std::ios::binary);
        if(infileStream.is_open())
          std::cout<<"The File is Open"<<std::endl;
        else 
          std::cout<<"File Open Error"<<std::endl;
        while(!infileStream.eof()){ 
          infileStream>>input;
          std::cout<<HexConversion(input)<<" ";//std::endl;
          }
          std::cout<<"\n\n"<<std::endl;
        infileStream.close();
        break;
      case 6:
      /*  Encrypting the chosen file and outputting it into a different file */
        std::cout<<"Enter the file to be encrypted"<<std::endl;
        std::cin>>file;
        std::cout<<"Enter the password(max: 256 bytes long)"<<std::endl;
        std::cin>>password;
        infileStream.open(file, std::ios::out | std::ios::app | std::ios::binary);
        outfileStream.open("output.txt", std::ios::out | std::ios::binary);
        if(infileStream.is_open()  && outfileStream.is_open())
          std::cout<<"The File is Open"<<std::endl;
        else 
          std::cout<<"File Open Error"<<std::endl;
        infileStream>>input;
        while(!infileStream.eof()){   
          for(int x = 0; x < password.length(); x++){
            input[x] ^= password[x % password.size()];
           outfileStream << input[x];
         }
        infileStream>>input;
        }
        infileStream.close();
        outfileStream.close();
        break;
      case 7:
      /*  Decrypting the chosen file and outputting it into a different file */
        std::cout<<"Enter the file to be decrypted"<<std::endl;
        std::cin>>file;
        std::cout<<"Enter the key(max: 256 bytes long)"<<std::endl;
        std::cin>>password;       
        infileStream.open(file, std::ios::out | std::ios::app | std::ios::binary);
        outfileStream.open("outputSecond.txt", std::ios::out | std::ios::binary);
        infileStream>>input;
        while(!infileStream.eof()){   
          for(int x = 0; x < input.length(); x++){
            input[x] ^= password[x % password.size()];
          outfileStream << input[x];
         }
         infileStream>>input;
        }
        infileStream.close();
        outfileStream.close();
        break;
      default:
        std::cout<<"Thanks for using the file system application."<<std::endl;
    }
    /*  Displaying and Getting options until user enters "0"  */
    display();
    std::cin>>option;
    std::cout<<option<<std::endl;
  }
  std::cout<<"Thanks for using the file system application."<<std::endl;
  return 0;
}