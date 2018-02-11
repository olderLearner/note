#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

#define EXCLUDED_TAG "i.MXPowerHAL|athr_gps|dsp_hal"

int main(){

	char buffer[1024];
//char cID[10];
//char cmsg[256];
//char bugnum[10];
	int i = 0;
	ifstream myfile ("/home/fengxiaojun/basess.txt");
	ofstream outfile("/home/fengxiaojun/texto.txt");

	if(myfile){
  		//cout << "Can open myfile" <<endl;
       	// exit(1); // terminate with error
	}
	if(!outfile){
    	cout << "Unable to open outfile";
        //exit(1); // terminate with error
	}

// line copy
// 

  	while (!myfile.eof())
  	{
    	myfile.getline(buffer, 1024);
		char cID[10];
        char cmsg[256];
		char bugnum[10];

		char *l;
		l = strstr(buffer, "bug number:");

		if (l == NULL) {
			strncpy(cID, buffer, 7);
  			for(int kk = 0;kk<255;kk++) {
				cmsg[kk] = 0;
			}
			strncpy(cmsg, buffer+7, strlen(buffer)-7);
  			//cout<< cID <<"**"<<cmsg<<endl;
			//cout<< cID<<endl;
			//cout<<"none"<<endl;
			cout<< cmsg<<endl;
			//outfile<<cID<<endl;
		} else {
			strncpy(cID, buffer, 7);
			int lon = l - buffer ;
			//cout<<lon<<endl;
  			for(int kk = 0;kk<255;kk++) {
				cmsg[kk] = 0;
			}
  			strncpy(cmsg, buffer+22, lon -28);
			strncpy(bugnum, l+11, 7);
  			//cout<< cID <<"**"<<bugnum<<"**"<<cmsg<<endl;
			//cout<< cID<<endl;
			//cout<<bugnum<<endl;
			cout<<cmsg<<endl;
			//outfile<<cID<<endl;
		}
     	i++;
		//cout<<"-------->" << i<< "<-----" <<endl;
  	}
	myfile.close();
	return 0;
}



