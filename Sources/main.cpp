/*
 * main.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: priya
 */
#include "Sche.h"
#include <vector>
#include<iostream>
#include<stdlib.h>
using namespace std;
int main(int argc, char *argv []){
	Sche s;
	string myFile;
	bool fileinput = false;
	bool randominput = false;
	bool RR = false;
	bool sf = false;
	bool ff = false;
	bool verbose = false;
	int k = 0;
	int input = 0;
	vector <Sche> data;
	//checks if dafault argument is valid
	if(argc < 4){
		cerr <<"Usage:" << argv[0] << "-[R k|S|F] [-f <filename>]";
		return 1;
	}
	else{
		//Loop to iterate through arguments
		for(int i=1;i<argc;i++){
			string arg = argv[i];
			//To check for file input
			if(arg=="-f"){
				if(!randominput){
					myFile = argv[i+1];
					data = s.input_read(myFile);
					fileinput = true;
				}
			}
			//To check for verbose input
			else if(arg=="-v"){
				verbose = true;
			}
			//To check for random input
			else if(arg=="-r"){
				if(!fileinput){
					input = atoi(argv[i+1]);
					data = s.randomNumbers(input);
					randominput = true;
				}
			}
			//Round Robin
			else if(arg=="-R"){
				if(!sf && !ff){
				RR = true;
				k = atoi(argv[i+1]);

				}
			}
			//SRJF
			else if(arg=="-S"){
				if(!RR && !ff){
					sf = true;

				}
		    }
			//FIFO
			else if(arg=="-F"){

				if(!sf && !RR){
					ff = true;
			}
		}
	 }
	}
	if(RR){
		s.RR_sche(data,verbose,k);
	}
	else if(sf){
		s.SRJF_sche(data,verbose);
	}
	else if(ff){
		s.fifo_sche(data,verbose);
	}
	return 0;
};


