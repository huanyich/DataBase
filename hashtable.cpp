#include<iostream>
#include<string>
#include <cstdlib>
#include <fstream>

using namespace std;

class Employee{
   public:
   int id;
   string name;
   Employee(){

   };
};

class MyHashTable{
   Employee **arr;
   int size;
   int count;
public:
   MyHashTable(int s){
      count = 0;
      size = s;
      arr = new Employee*[size];

      for(int i=0;i<size; i++){
         arr[i] = nullptr;
      } 
   }
   int hashIt(int n){
         return n%size;
      }
      //
   void insertItem(int key, string value){
         if(count == size){
            cout<<"full";
            return;
         }
      int hashIndex = hashIt(key);
      while (arr[hashIndex]!=nullptr){
         hashIndex = (hashIndex +1)% size;
      }
      arr[hashIndex] = new Employee();
      arr[hashIndex] ->id = key;
      arr[hashIndex] ->name = value;
      count++;
      }
      //
      void displayAll(){
         for(int i=0;i<size;i++){
            if(arr[i]!=nullptr){
               cout<<"HASH_TABLE["<<i<<"]"<<"[id]"<<arr[i]->id<<",info=>"<<arr[i]->name<<endl;
               
            }
         }
      }
      //
      string getItem(int key){
         if(count ==0){
            return"empty";
         }
         int hashIndex = hashIt(key);
         int temp = hashIndex;
         while(true){

            if(arr[hashIndex]==nullptr){
               hashIndex = (hashIndex+1)%size;
            }else if(arr[hashIndex]->id !=key){
               hashIndex=(hashIndex+1)%size;
            }else break;

            if(hashIndex==temp){
               temp=-1;
               break;
            }
         }
         if (temp=-1){
               return "not found";
               
         } 
         else {
            return arr[hashIndex]->name;
            
         }
      }

};




int main(){
   MyHashTable mht(5);
   string id;
   string lastname;
   string choose;
   int searchId;
   cout<<"Enter C to show table or L to search id:";
   cin>>choose;
   cout<<endl;
   if(choose =="C"){
   // read csv
   
   ifstream ip("Employee.csv");
   if(!ip.is_open()) cout << "ERROR: File Open" << '\n';
   //get values from csv
   while(ip.good()){

    getline(ip,id,',');
    getline(ip,lastname,'\n');

   //value insert into hashtable
   mht.insertItem(atoi(id.c_str()),lastname);
   }
   ip.close();
  


   mht.displayAll(); 
   }

   if(choose =="L"){
      cout<<"enter the id you want to search:";
      cin>>searchId;
      mht.getItem(searchId);
   }
  
   return 0;
}