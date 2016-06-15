/*
 * Sche.h
 *
 *  Created on: Mar 29, 2016
 *      Author: priya
 */

#ifndef SCHE_H_
#define SCHE_H_
#include <string>
#include <vector>
using namespace std;

class Sche {
int process_id;
int arrival_time;
int burst_time;
int remaining_time;
int completion_time;
public :
	Sche();
	Sche(int process_id,int arrival_time,int burst_time,int remaining_time);
	Sche(int process_id,int completion_time);
	//object type vector to store input data
	vector <Sche> data;
	//object type vector to store output data
	vector <Sche> output;
	//function to generate random numbers
	vector<Sche> randomNumbers(int input);
	//function to read from file
	vector<Sche> input_read(string myfile);
	//Fifo implementation
	void fifo_sche(vector <Sche> data,bool verbose);
	//Round Robin implementation
	void RR_sche(vector <Sche> data,bool verbose,int quantum);
	//Shortest Remaining Job first (preemtive) implementation
	void SRJF_sche(vector <Sche> data,bool verbose);
	//friend class for queue and vector sorting
	class Sort {
		public:
			bool operator()(Sche const & lhs,Sche const & rhs);
	};
	class Sort_arrivalTime {
			public:
				bool operator()(Sche const & lhs,Sche const & rhs);
		};
	class Sort_processId {
				public:
					bool operator()(Sche const & lhs,Sche const & rhs);
			};
	friend class Sort;
	friend class Sort_arrivalTime;
	friend class Sort_processId;
};

#endif /* SCHE_H_ */
