#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void getAvgRR(vector<int> input, vector<string> job, int sliceSize);
void getInput(vector<int> &input, vector<string> &jobVec);
void getInput(vector<int> &input, vector<string> &jobVec, string theFile);
void toCSV(double avgTurnaround, int jobNum);

int main(){
	vector<int> input;
	vector<string> job;

    getInput(input, job);
    getAvgRR(input, job, 2);

    /*for(int i = 0; i < 20; i++){
        string fileName = "15jobs" + to_string(i+1) + ".txt";
        getInput(input, job, fileName);
        getAvgRR(input, job, 5);
        input.clear();
        job.clear();
    }*/
}

//finds average for Round Robin
void getAvgRR(vector<int> input, vector<string> job, int sliceSize){
	int currentTime = 0;
    int turnaround = 0;
    bool done = false;

    //prints header for schedule table
    cout << "Job#	| Start Time	| End Time  | Job Completion " << endl;

    //reads the jobs in order of first come first serve
    while(!done){
        done = true;
        //go through all available jobs
        for(int i = 0; i < input.size(); i++){
            //if the job is not done yet, work on job
            if(input[i] > 0){
                done = false;
                //if remaining job is greater than time slice then decriment by slice size
                if(input[i] > sliceSize){
                    //print job# and start time
                    cout << job[i] << "	|" << currentTime << "		|"; 
                    //calculates end time
                    currentTime+= sliceSize;
                    input[i] -= sliceSize;
                    cout << currentTime << " 	    | " << endl;
                }
                // if remaining time is less than time slice then only work on the remaining time
                else{
                    //print job# and start time
                    cout << job[i] << "	|" << currentTime << "		|";
                    //calculates end time
                    currentTime += input[i];
                    //calculated turnaround
                    turnaround += currentTime;
                    input[i] = 0;
                    //print end time and job completion
                    cout << currentTime << " 	    | " << job[i] << " completed @" << currentTime << endl;
                }
            }
        }
    }
    double turn = (double)turnaround / input.size();
    cout << "Average turnaround: " << turn << endl;
    //toCSV(turn, input.size());
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
void toCSV(double avgTurnaround, int jobNum){
    ofstream out;
    string jobFile = "RR5.csv";
	out.open(jobFile, std::ios::out | std::ios::app);
	out << jobNum << "," << avgTurnaround << endl;
	out.close();
}