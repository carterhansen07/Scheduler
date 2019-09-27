#include<iomanip>
#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;

struct periodtasks{
	string id;
	int executiontime;
	int period;
	int nextdeadline;
	int remaindertoexecute;
	
};

struct aperiod{
	string id;
	int executiontime;
	int deadline=500;
	int remaindertoexecute;
	int available;
	
	
	
	
	
	
};

//got help for sorting vectors from stack overflow
bool comparebyperiod(const periodtasks &a,const periodtasks &b){
	return a.period<b.period;	
}

bool comparebydeadline(const periodtasks &a, const periodtasks &b){
	return a.nextdeadline<b.nextdeadline;
	
	
	
	
}


int main(int argc, char **argv){
int preemptions=0;
string lasttoexecute;
bool finished=true;
int aperiodicsum=0;
int misseddeadline=0;
int numberoftasks;
int hyperperiod;
string idtoprint="";
int numberaperiodic;
string test;

int testy;
if (argc!=3){
cout<<"Error: You need to enter 2 input files."<<endl;

return -1;
}
//basic file checking and getting the first two values
cout<<"you inputed: "<<argv[1]<<" as your input"<<endl;
cout<<"you inputed: "<<argv[2]<<" as your output"<<endl;
ofstream outputfile;
ifstream inputfile;
inputfile.open(argv[1]);
outputfile.open(argv[2]);

getline(inputfile,test);
numberoftasks=stoi(test);
getline(inputfile,test);
hyperperiod=stoi(test);
cout<<"this is our number of tasks "<<numberoftasks<<endl;
cout<<"This is the period "<< hyperperiod<<endl;



vector<periodtasks> tasks;
vector<aperiod> aperiodic;

//inputs our data into a vector of structs

for (int ni=0;ni<numberoftasks;ni++){
	tasks.push_back(periodtasks());
	
	getline(inputfile,test,',');
	cout<<test<<endl;
	test.erase(remove(test.begin(),test.end(), '\n'), test.end());
	tasks[ni].id=test;
	
	getline(inputfile,test,',');
	testy=stoi(test);
	tasks[ni].executiontime=testy;
	cout<<testy<<endl;
	getline(inputfile,test);
	testy=stoi(test);
	cout<<testy<<endl;
	tasks[ni].period=testy;
	tasks[ni].remaindertoexecute=tasks[ni].executiontime;
	tasks[ni].nextdeadline=tasks[ni].executiontime;
	
}
//now we modify to get our aperiodic tasks. 
if (getline(inputfile,test)){
	numberaperiodic=stoi(test);
	for (int xl=0;xl<numberaperiodic;xl++){
		aperiodic.push_back(aperiod());
		
		getline(inputfile,test,',');
		test.erase(remove(test.begin(),test.end(), '\n'), test.end());
		aperiodic[xl].id=test;
		getline(inputfile,test,',');
		testy=stoi(test);
		aperiodic[xl].executiontime=testy;
		
		getline(inputfile,test);
		testy=stoi(test);
		aperiodic[xl].available=testy;
		aperiodic[xl].remaindertoexecute=aperiodic[xl].executiontime;
		cout<<"our aperiodic task is available at: "<<aperiodic[xl].available<<endl;
	}
	
}
//now I am going to sort our vectors by the RMF principal
//I am going to use the standard sort algorithm for simplicity

sort(tasks.begin(),tasks.end(),comparebyperiod);

//verify they printed in order
cout<<"Print in order verification"<<endl;
for(int xi=0;xi<numberoftasks;xi++)
	

	{
		cout<<tasks[xi].period<<endl;
		
		
		
	}




for (int i=1;i<=hyperperiod;i++){

for (int xj=0;xj<numberoftasks;xj++){
	if (i%tasks[xj].period==0){
		if (tasks[xj].remaindertoexecute>0){
			
			cout<<"we are on cycle: "<<i<<endl;
			
			cout<<"we have this many to execute: "<<tasks[xj].remaindertoexecute<<endl;
			cout<<"uh oh.... missed deadline"<<endl;
		misseddeadline++;
		}
		tasks[xj].remaindertoexecute+=tasks[xj].executiontime;
	}	
}

idtoprint="n/a";
for (int lj=0;lj<numberoftasks;lj++){
	if (tasks[lj].remaindertoexecute>0){
		idtoprint=tasks[lj].id;
		if (idtoprint!=lasttoexecute&&finished==false){
			preemptions++;
		}
		tasks[lj].remaindertoexecute=tasks[lj].remaindertoexecute-1;
		if (tasks[lj].remaindertoexecute==0){
			finished=true;
		}
		else{finished=false;}
		lasttoexecute =idtoprint;
		
		lj=numberoftasks;
		
		
	}
	
	else{
		// here we can handle the aperiodic tasks
		if (lj==(numberoftasks-1)){
			for (int mj=0; mj<numberaperiodic;mj++){
				//cout<<"aperiodictaskt time"<<endl;
				if (i>=aperiodic[mj].available){
					
				if (aperiodic[mj].remaindertoexecute>0){
					
				idtoprint=aperiodic[mj].id;
				aperiodic[mj].remaindertoexecute=aperiodic[mj].remaindertoexecute-1;
				if (aperiodic[mj].remaindertoexecute==0){
					aperiodicsum+=i-aperiodic[mj].available;
					
					
				}
				}
				
			
				
				
			}
			
		}}
	}
	
	
}
outputfile<<"|";


outputfile<<setw(4)<<idtoprint;




//simple method for printing the key for which "millisecond" we are on
if((i%20)==0){	

outputfile<<"\r\n";

	for (int j=1;j<=20;j++){
		
		outputfile<<"|";
		outputfile<<setw(4)<<(i-20+j);
		
		
		
	}
	
	outputfile<<"\r\n";
	
	outputfile<<"\r\n";
	
}}

outputfile<<"You missed this many deadlines for the RMA protocol: " <<misseddeadline<<endl;
outputfile<<"\r\n\r\n";
outputfile<<"There were this many preemptions: " <<preemptions<<endl;
outputfile<<"\r\n\r\n";
outputfile<<"average response for aperiodic= "<<aperiodicsum/numberaperiodic<<endl;

outputfile<<"\r\n\r\n";
outputfile<<"Here is the EDF protocol";
outputfile<<"\r\n\r\n";





misseddeadline=0;

//very similiar to that of the RMA protocol. All we have to change is to constantly sort our vector based on upcoming deadlines.
for (int rem=0;rem<numberoftasks;rem++){
	
	
	
	tasks[rem].remaindertoexecute=tasks[rem].executiontime;
	tasks[rem].nextdeadline=tasks[rem].period;
	
	
	
	
}

preemptions=0;

for (int ap=0;ap<numberaperiodic;ap++){
	
	aperiodic[ap].remaindertoexecute=aperiodic[ap].executiontime;
	
	
	
	
}
aperiodicsum=0;

for (int i=1;i<=hyperperiod;i++){
sort(tasks.begin(),tasks.end(),comparebydeadline);

for (int xj=0;xj<numberoftasks;xj++){
	
	if (tasks[xj].nextdeadline==i){
		if (tasks[xj].remaindertoexecute>0){
			
			cout<<"we are on cycle: "<<i<<endl;
			cout<<"task is goign to be late: "<<tasks[xj].id<<endl;
			cout<<"we have this many to execute: "<<tasks[xj].remaindertoexecute<<endl;
			cout<<"uh oh.... missed deadline"<<endl;
		misseddeadline++;
		}
		tasks[xj].remaindertoexecute+=tasks[xj].executiontime;
		tasks[xj].nextdeadline+=tasks[xj].period;
		
	}	
}



idtoprint="n/a";
for (int lj=0;lj<numberoftasks;lj++){
if (tasks[lj].remaindertoexecute>0){
		idtoprint=tasks[lj].id;
		if (idtoprint!=lasttoexecute&&finished==false){
			preemptions++;
		}
		tasks[lj].remaindertoexecute=tasks[lj].remaindertoexecute-1;
		if (tasks[lj].remaindertoexecute==0){
			finished=true;
		}
		else{finished=false;}
		lasttoexecute =idtoprint;
		
		lj=numberoftasks;
		
		
	}
else{
		// here we can handle the aperiodic tasks
		if (lj==(numberoftasks-1)){
			for (int mj=0; mj<numberaperiodic;mj++){
				//cout<<"aperiodictaskt time"<<endl;
				if (i>=aperiodic[mj].available){
					
				if (aperiodic[mj].remaindertoexecute>0){
					
				idtoprint=aperiodic[mj].id;
				aperiodic[mj].remaindertoexecute=aperiodic[mj].remaindertoexecute-1;
				
			if (aperiodic[mj].remaindertoexecute==0){
					aperiodicsum+=i-aperiodic[mj].available;
				
					
			}	
				
				
				
			}
			
		}}
	}	
	
}}
outputfile<<"|";


outputfile<<setw(4)<<idtoprint;




//simple method for printing the key for which "millisecond" we are on
if((i%20)==0){	

outputfile<<"\r\n";

	for (int j=1;j<=20;j++){
		
		outputfile<<"|";
		outputfile<<setw(4)<<(i-20+j);
		
		
		
	}
	
	outputfile<<"\r\n";
	
	outputfile<<"\r\n";
	
}}
outputfile<<"\r\n  You missed this many deadlines for the EDF protocol: " <<misseddeadline<<endl;
outputfile<<"\r\n\r\n";
outputfile<<"\r\n average response for aperiodic= "<<aperiodicsum/numberaperiodic<<endl;
outputfile<<"\r\n\r\n";
outputfile<<"There were this many preemptions: " <<preemptions<<endl;
inputfile.close();
outputfile.close();

return 0;
}
