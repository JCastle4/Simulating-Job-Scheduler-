#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//#include<algorithm>
using namespace std;

void getAvgSJF(vector<int> input, vector<string> job);
void getInput(vector<int> &input, vector<string> &jobVec);
void getInput(vector<int> &input, vector<string> &jobVec, string theFile);
void sortSJF(vector<int> &inputSorted, vector<string> &jobSorted);
void toCSV(double avgTurnaround, int jobNum);

int main(){
	vector<int> input;
	vector<string> job;

    getInput(input, job);
    getAvgSJF(input, job);

    /*for(int i = 0; i < 20; i++){
        string fileName = "15jobs" + to_string(i+1) + ".txt";
        getInput(input, job, fileName);
        getAvgSJF(input, job);
        input.clear();
        job.clear();
    }*/
}

//finds average for Shortest Job First
void getAvgSJF(vector<int> input, vector<string> job){
	vector<int> inputSorted = input;
	vector<string> jobSorted = job;

	//sorts from smallest to largest
	sortSJF(inputSorted, jobSorted);
    
	int currentTime = 0;
    int turnaround = 0;

	//prints header for schedule table
    cout << "Job#	| Start Time	| End Time  | Job Completion " << endl;

	//reads the jobs in order of shortest job first
    for(int i = 0; i < inputSorted.size(); i++){
		//print job# and start time
    	cout << jobSorted[i] << "	|" << currentTime << "		|"; 
		//calculates end time
        currentTime+=inputSorted[i];
        //calculated turnaround			
        turnaround += currentTime;
		//print end time and job completion
		cout << currentTime << " 	    | " << jobSorted[i] << " completed @" << currentTime << endl;
    }
	//prints average turnaround time
    double turn = (double)turnaround / inputSorted.size();
    cout << "Average turnaround: " << turn << endl;
	//toCSV(turn, inputSorted.size());
}

//gets input from file
void getInput(vector<int> &input, vector<string> &jobVec){
    string theFile;
    cout << "Enter input file" << endl;
    cin >> theFile;
    std::ifstream inFile(theFile);
	//read input file
    if(inFile.is_open()){
        while(true){
            string job;
            int in;
			//job# into the job vector, burst time into the input vector
            if(!(inFile>>job)) break;
            if(!(inFile>>in)) break;
			jobVec.push_back(job);
            input.push_back(in);             
        }
        inFile.close();
    }
}

//gets input from file
void getInput(vector<int> &input, vector<string> &jobVec, string theFile){
    //string theFile;
    //cout << "Enter input file" << endl;
    //cin >> theFile;
    std::ifstream inFile(theFile);
    //read input file
    if(inFile.is_open()){
        while(true){
            string job;
            int in;
            //job# into the job vector, burst time into the input vector
            if(!(inFile>>job)) break;
            if(!(inFile>>in)) break;
			jobVec.push_back(job);
            input.push_back(in);             
        }
        inFile.close();
    }
}

//sorts from smallest to largets
void sortSJF(vector<int> &inputSorted, vector<string> &jobSorted){
	int i, j;
    bool swapped;
	//bubble sort 
    for (i = 0; i < inputSorted.size() - 1; i++) {
        swapped = false;
        for (j = 0; j < inputSorted.size() - i - 1; j++) {
            if (inputSorted[j] > inputSorted[j + 1]) {
                //smallest job first
				swap(inputSorted[j], inputSorted[j + 1]);
				//swap job# according to job size
				swap(jobSorted[j], jobSorted[j + 1]);
				swapped = true;
            }
        }
        if (swapped == false)
            break;
    }	
}

void toCSV(double avgTurnaround, int jobNum){
    ofstream out;
    string jobFile = "SjF.csv";
	out.open(jobFile, std::ios::out | std::ios::app);
	out << jobNum << "," << avgTurnaround << endl;
	out.close();
}