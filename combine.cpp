#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream> //for sstream
#include <string>
#include <string.h>
#include <fstream> //for file I/O
#include <algorithm> // for sort
#include <queue>
using namespace std;

#define block 22


//employee index
struct emp{
	int eid;
	string ename;
	int age;
	double salary;
}empptr[300];

bool compareEmp(emp a, emp b){
	if(a.eid < b.eid){
		return true;
	}
	else return false;
}; 
/*
struct compare{
	bool operator()(const emp &empptr1,const emp &empptr2){
		return empptr1.eid > empptr2.eid;
		
	}
};
*/
class Compare
{
public:
    //Ascending order sort
    bool operator() (pair<emp, emp> pair1, pair<emp, emp> pair2)
    {
        return pair1.first.eid > pair2.first.eid;
    }
};
string mergeFiles(int Mcount){
	string fileA, fileB;
	ifstream opentemp;
	string temp;
	string temp2;
	int emp_count = 0;
	int count = 0;
	priority_queue< pair<emp,emp>, vector<pair<emp,emp>>,Compare> minHeap;
	ifstream* handles = new ifstream[count];
	for (int i = 1; i <= Mcount; i++) {
        string sortedInputFileName = "output" + to_string(i) + ".csv";
		//cout<<sortedInputFileName<<endl;
		opentemp.open(sortedInputFileName, ios::in);

		while(getline(opentemp, temp, '\n')){  //read each line
	  		count = 0;
			cout<<sortedInputFileName<<endl;
			stringstream ss(temp);
			while(getline(ss, temp2, ',')){   //read each ","
	   			if(count % 4 == 0){
					empptr[i-1].eid = stoi(temp2);
					cout<<empptr[i-1].eid<<endl;
				}
				if(count % 4 == 1){
					empptr[i-1].ename = temp2;
					cout<<empptr[i-1].ename<<endl;
				}
				if(count % 4 == 2){
					empptr[i-1].age = stoi(temp2);
					cout<<empptr[i-1].age<<endl;
				}
				if(count % 4 == 3){
					empptr[i-1].salary = stod(temp2);
					cout<<empptr[i-1].salary<<endl;
				}
			count =count+1;
		}
			emp_count = emp_count + 1;
		}
	emp firstValue;
	empptr[i-1] = firstValue;
	//minHeap.push(empptr[i-1]);
	minHeap.push(pair<emp,emp>(firstValue,empptr[i-1]));

		

    }
	
	string outputFileName ="output.csv";
	ofstream outputFile(outputFileName.c_str());
	
	while (minHeap.size() > 0){
		pair<emp,emp> minPair = minHeap.top();
		minHeap.pop();
		outputFile << minPair.first.eid << ',' <<  minPair.first.ename << ',' <<  minPair.first.age << ',' <<  minPair.first.salary << endl;
		emp nextValue;
		flush(outputFile);
		if(minPair.second.eid > nextValue.eid){
			minHeap.push(pair <emp, emp>(nextValue, minPair.second));
		}
	}
	for (int i = 1; i <=Mcount; i++) {
        handles[i - 1].close();
    }
    outputFile.close();
    delete[] handles;
 
    return outputFileName;


}


int main() {
	ifstream file_emp;
	ofstream outfile;
	int count = 0;
	stringstream ss;
	int i=0;
	int numberOfChunks = 1;
	int chunkSize = 2;
    int readValue = 0;
    int currentCount = 0;
    bool unprocessedData = true;




	file_emp.open("input.csv", ios::in);
	outfile.open("output.csv");


	if(!file_emp){
		cout << "Can't open  the file of employee" << endl;
		return -1;
	}
//use for read documents	
	string temp;
	string temp2;
	int emp_count = 0;
//With the employee file, we read line by line and put it into array
   	while(getline(file_emp, temp, '\n')){  //read each line
	  	count = 0;


		stringstream ss(temp);
		while(getline(ss, temp2, ',')){   //read each ","
	   		if(count % 4 == 0){
				empptr[emp_count].eid = stoi(temp2);

			}
			if(count % 4 == 1){
				empptr[emp_count].ename = temp2;

			}
			if(count % 4 == 2){
				empptr[emp_count].age = stoi(temp2);

			}
			if(count % 4 == 3){
				empptr[emp_count].salary = stod(temp2);

			}
			count =count+1;
		}
		//emp_count = emp_count + 1;
		
		
		sort(empptr,empptr+1,compareEmp);
		string outputFileName = "output" + to_string(numberOfChunks) + ".csv";
		ofstream outputFile(outputFileName);
		
		
		outputFile <<empptr[emp_count].eid << ',' << empptr[emp_count].ename << ',' << empptr[emp_count].age << ',' << empptr[emp_count].salary << endl;
		
		
		//cout <<empptr[emp_count].eid << ',' << empptr[emp_count].ename << ',' << empptr[emp_count].age << ',' << empptr[emp_count].salary << endl;
		
		outputFile.close();
		//
        numberOfChunks++;
		emp_count = emp_count + 1;
			
        //emp_count = 0;
		
		
		
		
	}
	numberOfChunks--;
	cout<<"numberOfChunks"<<numberOfChunks<<endl;

	file_emp.close();
	if(numberOfChunks!=0){
		//priority_queue<emp, vector<emp>,compare> minHeap;
		priority_queue< pair<emp,emp>, vector<pair<emp,emp>>,Compare> minHeap;
		cout<<"output is in file:"<<mergeFiles(numberOfChunks);
	}
	
	return 0;
}
