#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream> //for sstream
#include <string>
#include <string.h>
#include <fstream> //for file I/O
#include <algorithm> // for sort
using namespace std;


//department index
struct dept{
	int did;
	string dname;
	double budget;
	int managerid;
}deptptr[300];
//employee index
struct emp{
	int eid;
	string ename;
	int age;
	double salary;
}empptr[300];

//compare function use in sort
bool compareDept(dept a, dept b){
	if(a.managerid < b.managerid){
		return true;
	}
	else return false;
};
bool compareEmp(emp a, emp b){
	if(a.eid < b.eid){
		return true;
	}
	else return false;
}; 
//compare
void RunDept(dept deptptr[], int n)
{

    sort(deptptr, deptptr+300, compareDept);
};

void RunEmp(emp empptr[], int n)
{

    sort(empptr, empptr+300, compareEmp);
};

int main() {
	int count = 0;
	int i=0;
	int block=22;
// First open up the file and create a new file for output
	ifstream fileDept;
	ifstream fileEmp;
	ofstream outfile;
	stringstream ss;
	fileDept.open("Dept.csv", ios::in);
	fileEmp.open("Emp.csv", ios::in);
	outfile.open("join.csv");

//use for read documents	
	string temp;
	string temp2;
	int dept_count = 0;
	int emp_count = 0;
//With the department file, we read line by line and put it into array
	
	while(getline(fileDept, temp, '\n')){  //read each line
		count = 0;
	
		stringstream ss(temp);
		while(getline(ss, temp2, ',')){   //read each ","
	   		if(count % 4 == 0){
				deptptr[dept_count].did = stoi(temp2); //change to integer
				//cout<<deptptr[dept_count].did<<endl;
			}
			if(count % 4 == 1){
				deptptr[dept_count].dname = temp2;
				//cout<<deptptr[dept_count].dname<<endl;
			}
			if(count % 4 == 2){
				deptptr[dept_count].budget = stod(temp2); //change to double
				//cout<<deptptr[dept_count].budget<<endl;
			}
			if(count % 4 == 3){
				deptptr[dept_count].managerid = stoi(temp2); //change to integer
				//cout<<deptptr[dept_count].managerid<<endl;
			}
			count= count +1;
   		}
		//cout<<"finish one line"<<endl;
   	dept_count = dept_count + 1;
	}
//With the employee file, we read line by line and put it into array
   	while(getline(fileEmp, temp, '\n')){  //read each line
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
		emp_count = emp_count + 1;
	}
// sort managerid and eid with block size



for(i=0;(i < (sizeof(deptptr)/sizeof(deptptr[0])));	i =i+ block){ 
		if(i + block < (sizeof(deptptr)/sizeof(deptptr[0]))){
			sort(deptptr + i, deptptr + i + (block - 1), compareDept);
		}
		else if(i + block > (sizeof(deptptr)/sizeof(deptptr[0]))){
			sort(deptptr + i, deptptr + ((sizeof(deptptr)/sizeof(deptptr[0]))), compareDept);

		}
}
RunDept(deptptr, (sizeof(deptptr)/sizeof(deptptr[0])));


for(i=0;(i < (sizeof(empptr)/sizeof(empptr[0])));i =i+ block){
		if(i + block < (sizeof(empptr)/sizeof(empptr[0]))){
			sort(empptr + i, empptr + i + (block - 1), compareEmp);

		}
		else if(i + block > (sizeof(empptr)/sizeof(empptr[0]))){
			sort(empptr + i, empptr + ((sizeof(empptr)/sizeof(empptr[0]))), compareEmp);

		}
			
}
RunEmp(empptr, (sizeof(empptr)/sizeof(empptr[0])));




sort(empptr,empptr+block,compareEmp);
sort(deptptr,deptptr+block,compareDept);
//

	i = 0;
	int j = 0;
	int k = 0;

//sizeof(deptptr)/sizeof(depptr[0])) could show the length of array deptptr, so as empptr
	while(i < (sizeof(deptptr)/sizeof(deptptr[0])) + (sizeof(empptr)/sizeof(empptr[0]))){
		if(deptptr[j].managerid > empptr[k].eid){

			k = k+1;
		}
		if(deptptr[j].managerid < empptr[k].eid){
			j = j+1;
		}
		if(deptptr[j].managerid == empptr[k].eid){
			if(deptptr[j].managerid > 0){
				outfile << deptptr[j].did << ',' << deptptr[j].dname << ',' << deptptr[j].budget << ',' << deptptr[j].managerid 
						<< ',' << empptr[k].eid << ',' << empptr[k].ename << ',' << empptr[k].age << ',' << empptr[k].salary << endl;
			}
			j = j+1;
		}
		i=i+1;
	}	
	//close all the file 
	outfile.close();
	fileDept.close();
	fileEmp.close();
	return 0;
}
