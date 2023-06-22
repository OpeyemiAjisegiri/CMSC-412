#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <bits/stdc++.h> 
#include <cstdio>  
#include <algorithm> 
#include <cmath> 
#include <deque> 
#include <vector> 
#include <queue> 
#include <string> 
#include <cstring> 
#include <map> 
#include <stack> 
#include <set>
using namespace std;


void MenuDisplay(){
  cout<<"    \n\n Menu Options   "<<endl;
  cout<<"Pick one of the options using the precedent number"<<endl;
  cout<<"0 – Exit"<<endl;
  cout<<"1 – Read reference string"<<endl;
  cout<<"2 – Generate reference string"<<endl;
  cout<<"3 – Display current reference string"<<endl;
  cout<<"4 – Simulate FIFO"<<endl;
  cout<<"5 – Simulate OPT"<<endl;
  cout<<"6 – Simulate LRU"<<endl;
  cout<<" 7 – Simulate LFUT"<<endl;
  cout<<"\t Menu Option: ";
}

/*  Generating a random reference sequence of length n  */
 vector <int> CreatRandSeq (int n) {
	vector< int > randSeq, randStr(n);
	for (int i = 0; i < n; i++) {
		  randStr[i] = rand() % 10;
		randSeq.push_back(randStr[i]);
	}
	return randSeq;
}

/*  First In First Out algorithm  */
int FIFOSimulation(vector<int> pages, int n, int numOfFrames){
  unordered_set<int> set;
  queue<int> indexes;
  int pageFault = 0;
  for(int i = 0; i < n; i++){
    if(set.size() < numOfFrames){
      if(set.find(pages[i]) == set.end()){
        set.insert(pages[i]);
        pageFault++;
        indexes.push(pages[i]);
      }
    }
    else{
      if(set.find(pages[i])  == set.end()){
        int value = indexes.front();
        indexes.pop(); 
        set.erase(value);
        set.insert(pages[i]);
        indexes.push(pages[i]);
        pageFault++;
      }
    }
  }
  return pageFault;
}

/**  Least Recently Used Algorithm **/
int LRUSimulation(vector<int> pages,int n, int numOfFrames){
  unordered_set<int> set;
  unordered_map<int,int> indexes;
  int pageFault = 0;
  for(int i = 0; i < n; i++){
    if(set.size() < numOfFrames){
      if(set.find(pages[i]) == set.end()){
        set.insert(pages[i]);
        pageFault++;
      }
      indexes[pages[i]] = i;
    }
    else{
      if(set.find(pages[i]) == set.end()){
        int leastRecUse = INT_MAX, value;
        for(auto k = set.begin(); k != set.end(); k++){
          if(indexes[*k] < leastRecUse){
            leastRecUse = indexes[*k];
            value = *k;
          }
        }
        set.erase(value);
        set.insert(pages[i]);
        pageFault++;  
      }
      indexes[pages[i]] = i;
    }
  }
  return pageFault;
}

int predict(vector<int> pages, vector<int>& fr, int n, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++) {
        int j;
        for (j = index; j < n; j++) {
            if (fr[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}
  
/*  OPT simulation */

/* Checking if the frame is already in memory*/
bool search(int key, vector<int>& fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}
  
/* Predicting Frames that wont be used in the nearest future */
int predict(int pages[], vector<int>& frame, int n, int index)
{
    int res = -1, leastUsed = index;
    for (int i = 0; i < frame.size(); i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > leastUsed) {
                    leastUsed = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}
  
int optimalPage(vector<int> pages, int n, int fn)
{
    vector<int> frames;
    int pageHits, pageFault = pageHits = 0;
    for (int i = 0; i < n; i++) {
        if (search(pages[i], frames)) {
            pageHits++;
            continue;
        }
        if (frames.size() < fn)
            frames.push_back(pages[i]);
        else {
            int j = predict(pages, frames, n, i + 1);
            frames[j] = pages[i];
        }
    }
    return (n - pageHits);
}

/*  Main Function*/
int main() {
  int menuOption, strLn = 19;
  int refdigit, pageFault = 0;
  vector<int> refstring(strLn), grefstring(strLn);
  //vector< vector < int > > result;
  int n = sizeof(refstring)/sizeof(refstring[0]);
  int frames = 0;
  vector< bool > is_miss;
  MenuDisplay();
  cin>>menuOption;
  while(menuOption != 0){
    switch(menuOption){
      case 1:
        cout<<"Enter the reference String, a digit at a time."<<endl;
        for(int i = 0; i < strLn; i++){
          cin>> refdigit;
          if(refdigit>9){
             cout<<"Enter an integer equal to or less than 9"<<endl;
             cin>>refdigit;
          }
          refstring[i] = refdigit;
        }
       break;
      case 2:
        cout<<"Regenerating the reference string."<<endl;
        cout<<"Enter the length of the reference string to be randomized: "<<endl;
        cin>>strLn;
        grefstring = CreatRandSeq (strLn);
        for(int j = 0; j < strLn; j++){
          cout<<grefstring.at(j) << " ";
        }
        break;
      case 3:  
        if(refstring.empty())
          cout<<"The reference string buffer is empty. Choose option one first."<<endl;
        cout<<"Displaying the current reference string"<<endl;
        for(int j = 0; j < strLn; j++){
         cout<<refstring.at(j) << " ";
        }
        break;
      case 4:
        if(refstring.empty())
          cout<<"The reference string buffer is empty. Choose option one first."<<endl;
        cout<<"Enter the number of frames to be used: ";
        cin>> frames;
        //result = FIFO(refstring, is_miss);
        cout<<"The number of page faults per FIFO is: "<<FIFOSimulation(refstring, n,frames);
        break; 
      case 5:
        if(refstring.empty())
          cout<<"The reference string buffer is empty. Choose option one first."<<endl;
        cout<<"Enter the number of frames to be used: ";
        cin>> frames;
        cout<<"The number of page miss per OPT is: "<<optimalPage(refstring, n, frames)<<endl;
        break;
      case 6:
        if(refstring.empty())
          cout<<"The reference string buffer is empty. Choose option one first."<<endl;
        cout<<"Enter the number of frames to be used: ";
        cin>> frames;
        cout<<"The number of page faults per LRU is: "<<LRUSimulation(refstring, n,frames);
        break; 
      case 7:
        if(refstring.empty())
          cout<<"The reference string buffer is empty. Choose option one first."<<endl;
       break;
      default:
        cout<<"Thanks for using the application, see you soon."<<endl;
    }
    MenuDisplay();
    cin>>menuOption;
  }
  cout<<"Thanks for using the application, see you soon."<<endl;
}