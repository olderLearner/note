#include <fstream>
#include <iostream>
using namespace std;
int main()
{

  char data[100];
  

  //open file in write mode
  ofstream outfile;
  outfile.open("testfile.dat");

  cout << "Writing to file" << endl;
  cout << "Enter your name:";
  cin.getline(data,100);
  // write to file 
  outfile << data << endl;

  cout << "Enter your age:";
  cin >> data;
  cin.ignore();
  // write to file again
  outfile << data << endl;
  // close the opened file
  outfile.close();

  //open file in read mode
  ifstream infile;
  infile.open("testfile.dat");

  cout << "Reading from the file" << endl;
  infile >> data;

  // write data on screen
  cout << data << endl;
  // read data from file again,then display on screen
  infile >> data;
  cout << data << endl;
  // close file 
  infile.close();

  return 0;
}
