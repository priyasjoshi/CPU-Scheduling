/*
 * Sche.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: priya
 */

#include <iostream>
#include <fstream>
#include "../Headers/Sche.h"
#include <sstream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
using namespace std;

Sche::Sche(){};
Sche::Sche(int process_id,int arrival_time,int burst_time,int remaining_time){
	this->process_id = process_id;
	this->arrival_time = arrival_time;
	this->burst_time = burst_time;
	this->remaining_time = remaining_time;
};
Sche::Sche(int process_id,int completion_time){
	this->process_id = process_id;
	this->completion_time = completion_time;
};
vector<Sche> Sche::input_read(string myFile){
		string line;
		stringstream ss;
		//To get the file input and return vector data
		ifstream myfile (myFile.c_str());
				if(myfile.is_open()){
					getline(myfile,line);
					while(getline(myfile,line)){
						int process_id,arrival_time,burst_time;
						ss << line;
						ss>> process_id>> arrival_time >> burst_time;
						//cout << process_id << "\n" << arrival_time << "\n" << burst_time << "\n";
						Sche sche (process_id,arrival_time,burst_time,burst_time);
						data.push_back(sche);
						ss.clear();
						}
					}
			else{
				cout << "Error:";
			}
			//Sort according to process arrival time
			sort(data.begin(),data.end(),Sort_arrivalTime());
			return data;
}
void Sche::fifo_sche(vector <Sche> data,bool verbose){
	//To check for the verbose input
	if(verbose){
		//Queue of type class Sche
		queue <Sche> readyq;
		static int currentTime = data[0].arrival_time;
		Sche s (data[0].process_id,data[0].arrival_time,data[0].burst_time,data[0].burst_time);
		readyq.push(s);
		//Erase  vector data
		data.erase(data.begin()+0);
		do{
			Sche CurrentElement = readyq.front();
			cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY" <<"\n";
			cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY->RUNNING"<<"\n";
			readyq.pop();
			currentTime = currentTime + CurrentElement.burst_time;
			cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " RUNNING->TERMINATED"<<"\n";
			Sche result (CurrentElement.process_id,currentTime);
			output.push_back(result);
			for(unsigned i=0 ;i< data.size();i++){
				if(data[i].arrival_time <= currentTime){
					Sche process (data[i].process_id,data[i].arrival_time,data[i].burst_time,data[i].burst_time);
					readyq.push(process);
					data.erase(data.begin()+i);
				}
			}
		}while(!readyq.empty());

	}
	else{
		queue <Sche> readyq;
		static int currentTime = data[0].arrival_time;
		Sche s (data[0].process_id,data[0].arrival_time,data[0].burst_time,data[0].burst_time);
		readyq.push(s);
		data.erase(data.begin()+0);
		do{
			Sche CurrentElement = readyq.front();
			readyq.pop();
			currentTime = currentTime + CurrentElement.burst_time;
			Sche result (CurrentElement.process_id,currentTime);
			output.push_back(result);
			for(unsigned i=0 ;i< data.size();i++){
				if(data[i].arrival_time <= currentTime){
					Sche process (data[i].process_id,data[i].arrival_time,data[i].burst_time,data[i].burst_time);
					readyq.push(process);
					data.erase(data.begin()+i);
				}
			}
		}while(!readyq.empty());
		//To sort the vector according to process ID's
		sort(output.begin(),output.end(),Sort_processId());
		for(unsigned i = 0;i<output.size();i++){
			cout << output[i].process_id <<"\t" << output[i].completion_time <<"\n";
		}
	}
}
void Sche::RR_sche(vector <Sche> data,bool verbose,int quantum){
	//To check for the verbose input flag
	if(verbose){
		deque <Sche> readyq;
		int currentTime = data[0].arrival_time;
		Sche s (data[0].process_id,data[0].arrival_time,data[0].burst_time,data[0].burst_time);
		readyq.push_front(s);
		Sche CurrentElement = readyq.front();
		// delete vector element
		data.erase(data.begin()+0);
		cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY" <<"\n";
		cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY->RUNNING"<<"\n";
		do{
			readyq.pop_front();
			if(CurrentElement.remaining_time > 0){
				if(CurrentElement.remaining_time >= quantum){
					CurrentElement.remaining_time = CurrentElement.remaining_time - quantum;
					currentTime += quantum;
					//iterate through the vector to get the process arrival time
					for(unsigned i = 0;i<data.size();i++){
						if(data[i].arrival_time <= currentTime){
							Sche process (data[i].process_id,data[i].arrival_time,data[i].burst_time,data[i].burst_time);
							readyq.push_front(process);
							//delete from vector here
							data.erase(data.begin()+i);
							cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " RUNNING->READY"<<"\n";
							cout <<"At Time " << currentTime << "," << "job " << process.process_id << " READY" <<"\n";
							cout <<"At Time " << currentTime << "," << "job " << process.process_id << " READY->RUNNING"<<"\n";
						}
					 }
					//Check process current time to push into a queue back
					if(CurrentElement.remaining_time > 0){
						readyq.push_back(CurrentElement);
					}
				}
				else{
					// remaining time is less than the quantum
					CurrentElement.remaining_time = 0;
					currentTime =currentTime +CurrentElement.remaining_time;
					cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " TERMINATED"<<"\n";
				}
			}
		} while(!readyq.empty());
	}
	else{
	//For default input
	deque <Sche> readyq;
	int currentTime = data[0].arrival_time;
	Sche s (data[0].process_id,data[0].arrival_time,data[0].burst_time,data[0].burst_time);
	readyq.push_back(s);
	Sche CurrentElement = readyq.front();
	// delete vector element
	data.erase(data.begin()+0);
	do{
		readyq.pop_front();
		if(CurrentElement.remaining_time > 0){
			if(CurrentElement.remaining_time >= quantum){
				CurrentElement.remaining_time = CurrentElement.remaining_time - quantum;
				currentTime += quantum;
				for(unsigned i = 0;i<data.size();i++){
					if(data[i].arrival_time <= currentTime){
						Sche process (data[i].process_id,data[i].arrival_time,data[i].burst_time,data[i].burst_time);
						readyq.push_front(process);
						//delete from vector here
						data.erase(data.begin()+i);
					}
				 }
				if(CurrentElement.remaining_time > 0){
					readyq.push_back(CurrentElement);
				}
			}
			else{
				CurrentElement.remaining_time = 0;
				currentTime =currentTime + CurrentElement.remaining_time;
				Sche result (CurrentElement.process_id,currentTime);
				output.push_back(result);
			}
		}
	  } while(!readyq.empty());
		//To sort the vector according to process ID's
		sort(output.begin(),output.end(),Sort_processId());
		for(unsigned i = 0;i<output.size();i++){
			cout << output[i].process_id <<"\t" << output[i].completion_time <<"\n";
		}
	}
}
void Sche::SRJF_sche(vector <Sche> data,bool verbose){
	//To check for the verbose input flag
	if(verbose){
		priority_queue <Sche,vector<Sche>,Sche::Sort> readyq;
		static int currentTime = data[0].arrival_time;
		Sche s (data[0].process_id,data[0].arrival_time,data[0].burst_time,data[0].burst_time);
		int Clock = 1;
		readyq.push(s);
		Sche CurrentElement = readyq.top();
		// delete vector element
		data.erase(data.begin()+0);
		cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY" <<"\n";
		cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY->RUNNING"<<"\n";
		do{
			Sche temp = readyq.top();
			cout <<"At Time " << currentTime << "," << "job " << temp.process_id << " READY" <<"\n";
			cout <<"At Time " << currentTime << "," << "job " << temp.process_id << " READY->RUNNING"<<"\n";
			readyq.pop();
			if(CurrentElement.remaining_time > 0){
				CurrentElement.remaining_time = CurrentElement.remaining_time - Clock;
				currentTime += Clock;
				cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY" <<"\n";
				cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY->RUNNING"<<"\n";
				for(unsigned i = 0;i < data.size();i++){
					if(data[i].arrival_time == currentTime){
						Sche process (data[i].process_id,data[i].arrival_time,data[i].burst_time,data[i].burst_time);
						readyq.push(process);
						Sche top = readyq.top();
						data.erase(data.begin()+i);
						cout <<"At Time " << currentTime << ",job " << top.process_id << " READY" <<"\n";
						cout <<"At Time " << currentTime << ",job " << top.process_id << " READY->RUNNING"<<"\n";
					}
				}
				if(CurrentElement.remaining_time > 0){
					readyq.push(CurrentElement);
					cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY" <<"\n";
					cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY->RUNNING"<<"\n";
				}
				else{
					Sche result(CurrentElement.process_id,currentTime);
					output.push_back(result);
				}
			}
			cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY" <<"\n";
			cout <<"At Time " << currentTime << "," << "job " << CurrentElement.process_id << " READY->RUNNING"<<"\n";
		}while(!readyq.empty());

	}
	else{
		// For default output
		priority_queue <Sche,vector<Sche>,Sche::Sort> readyq;
		static int currentTime = data[0].arrival_time;
		Sche s (data[0].process_id,data[0].arrival_time,data[0].burst_time,data[0].burst_time);
		int Clock = 1;
		readyq.push(s);
		// delete vector element
		data.erase(data.begin()+0);
		do{
			Sche CurrentElement = readyq.top();
			readyq.pop();
			if(CurrentElement.remaining_time > 0){
				CurrentElement.remaining_time = CurrentElement.remaining_time - Clock;
				currentTime += Clock;

				for(unsigned i = 0;i < data.size();i++){
					if(data[i].arrival_time == currentTime){
						Sche process (data[i].process_id,data[i].arrival_time,data[i].burst_time,data[i].burst_time);
						readyq.push(process);
						data.erase(data.begin()+i);
					}
				}
				if(CurrentElement.remaining_time > 0){
					readyq.push(CurrentElement);
				}
				else{
					Sche result(CurrentElement.process_id,currentTime);
					output.push_back(result);
				}
			}

		}while(!readyq.empty());
		//To sort the vector according to process ID's
    	sort(output.begin(),output.end(),Sort_processId());
		for(unsigned i = 0;i<output.size();i++){
			cout << output[i].process_id <<"\t" << output[i].completion_time <<"\n";
		}
	}
}
// Functions for vector and queue sorting
bool Sche::Sort::operator()(const Sche& a, const Sche& b){
	return a.remaining_time > b.remaining_time;
}
bool Sche::Sort_arrivalTime::operator()(const Sche& a, const Sche& b){
	return a.arrival_time < b.arrival_time;
}
bool Sche::Sort_processId::operator()(const Sche& a, const Sche& b){
	return a.process_id < b.process_id;
}
vector<Sche> Sche::randomNumbers(int input){
		srand (time(NULL));
		//cout << "process_id\t" << "arrival_time\t" << "burst_time\t" << "\n";
		for(int i =0; i< input;i++){
			int arrival_time  = rand()%20+1;
			int burst_time = rand()%30+1;
			Sche sche (i,arrival_time,burst_time,burst_time);
			data.push_back(sche);
			cout << i <<"," << arrival_time<<"," << burst_time<<"," << "\n";
		}
		cout << "--------------------------------------------------------------------"<< "\n";
		sort(data.begin(),data.end(),Sort_arrivalTime());
		return data;
}







