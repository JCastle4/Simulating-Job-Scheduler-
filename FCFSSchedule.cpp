#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void getAvgFCFS(vector<int> input, vector<string> job);
void getInput(vector<int> &input, vector<string> &jobVec, string theFile);
void getInput(vector<int> &input, vector<string> &jobVec);
void toCSV(double avgTurnaround, int jobNum);

int main(){
    vector<int> input;
    vector<string> job;
    getInput(input, job);
    getAvgFCFS(input, job);
    /*for(int i = 0; i < 20; i++){
        string fileName = "15jobs" + to_string(i+1) + ".txt";
        getInput(input, job, fileName);
        getAvgFCFS(input, job);
        input.clear();
        job.clear();
    }*/
}

//finds average for first come first serve
void getAvgFCFS(vector<int> input, vector<string> job){
    int currentTime = 0;
    int turnaround = 0;
    
    //prints header for schedule table
    cout << "Job#	| Start Time	| End Time  | Job Completion " << endl;

    //reads the jobs in order of first come first serve
    for(int i = 0; i < input.size(); i++){
    	//print job# and start time
        cout << job[i] << "	|" << currentTime << "		|"; 
        //calculates end time
        currentTime+=input[i];
        //calculated turnaround 
        turnaround += currentTime;
        //print end time and job completion
		cout << currentTime << " 	    | " << job[i] << " completed @" << currentTime << endl;
    }
    //prints average turnaround time 
    double turn = (double)turnaround/ input.size();
    cout << "Average turnaround: " << turn << endl;
    //toCSV(turn, input.size());
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

void toCSV(double avgTurnaround, int jobNum){
    ofstream out;
    string jobFile = "FCFS5.csv";
	out.open(jobFile, std::ios::out | std::ios::app);
	out << jobNum << "," << avgTurnaround << endl;
	out.close();
}