#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "listnode.h"
#include "queue.h"
#include "student.h"


using namespace std;

int AvailableWindows;
string line;

// Checks if the window is empty of has anyone.
bool windowsEmpty(int *a, int size) {
	for(int i=0; i<size; i++) {
		if(a[i] != 0) {
			return false;
		}
	}
	return true;
}


int compare(const void * a, const void * b) {
	return ( *(int*)a - *(int*)b );
}

int main(int argc, char* argv[])  {
//Takes a file name as in line argument
	if (argc > 1){
    cout <<"\nYour file name is " <<argv[1] <<"\n"<<endl;
  }

  else{
    cout <<"No file name entered. ";
    return -1;
  }
//opens the file
	ifstream file(argv[1]);

//Checks if the file is good
	if (file.is_open() && file.good()) {

//Creating a queue to store the students that are coming into the office
	GenQueue<Student*> *queue = new GenQueue<Student*>();

//Get the string on the line and converting it to an integer.
	getline(file, line);
	AvailableWindows = stoi(line);

//Creates an array for the number of available windows in the office
	int *WArray = new int[AvailableWindows];
	for(int i=0; i<AvailableWindows; i++) {
		WArray[i] = 0;
	}

	int TNumStudents = 0;

//Get the string on the line and converting it to an integer.
	while(getline(file, line)) {
		int clockTick = stoi(line);

//Get the string on the line and converting it to an integer.
		getline(file, line);
		int NumStudentsArrived = stoi(line);
//Adds the student as they come to the total number of students.
		TNumStudents += NumStudentsArrived;

		for(int i=0; i<NumStudentsArrived; i++) {
			getline(file, line);
			int TimeAtWindow = stoi(line);
			//Make an object for each student in the file provided
			Student *s = new Student(clockTick, TimeAtWindow);

			queue->insert(s);
		}
	}

//create a list to hold students who have exited the line
	 doublyLinkedList<Student*> *studentExited = new  doublyLinkedList<Student*>();

	int currentTime = 0;
	int TotalIdleTimes = 0;
	bool allWindowsFull;
	int FullWindows;

//A while loop to run the simulation until the lines are empty and all of the windows are empty
	while(!(queue->isEmpty()) || (FullWindows != 0)) {
		FullWindows = 0;
		allWindowsFull = false;

		for(int i=0; i<AvailableWindows; i++) {
			if(WArray[i] != 0) {
				WArray[i] -= 1;
				if(WArray[i] != 0) {
					FullWindows++;
				}
			}
		}

		if(FullWindows == AvailableWindows) {
			allWindowsFull = true;
		}


		if(!(queue->isEmpty())) {


			while(!(queue->isEmpty()) && (currentTime >= queue->peek()->ArrivalTime) && !allWindowsFull) {

				for(int i=0; i<AvailableWindows; i++) {
					if(WArray[i] == 0) {
						WArray[i] = queue->peek()->TimeAtWindow;
						queue->peek()->TimeLeftLine = currentTime;

						queue->peek()->WindowNum = i;
						FullWindows++;
						break;
					}
				}

				studentExited->insertBack(queue->remove());

				if(FullWindows == AvailableWindows) {
					allWindowsFull = true;
				}
			}

			if((currentTime >= queue->peek()->ArrivalTime) && allWindowsFull) {
				queue->peek()->WaitingTime += 1;
			}
		}

		for(int i=0; i<AvailableWindows; i++) {
			if(WArray[i] == 0) {
				TotalIdleTimes++;
			}
		}
		currentTime++;
	}

	//----------------------- Metrics -----------------------//


//Initializing idle times
	double meanWindowIdleTime = (double)TotalIdleTimes/AvailableWindows;
	int *idleTimeArray = new int[AvailableWindows];

	for(int i=0; i<AvailableWindows; ++i) {
		idleTimeArray[i] = currentTime;
	}

//Initializing wait time of each student
	int *WaitingTimeArray = new int[TNumStudents];
	for(int i=0; i<TNumStudents; i++) {
		WaitingTimeArray[i] = 0;
	}

	Student *student;

// This is a while loop to fill idleTime array with idle times for each window
		while(!studentExited->isEmpty()) {

			student = studentExited->removeFront();
			int studentWindowNum = student->WindowNum;

			for(int i=0; i<AvailableWindows; ++i) {
				if(studentWindowNum == i) {

				idleTimeArray[i] -= student->TimeAtWindow;

			}
		}

//This is a for loop filling WaitTimeArray with the wait times of each student

		for(int i=0; i<TNumStudents; ++i) {

			if(i == (studentExited->getSize())) {
				WaitingTimeArray[i] = student->WaitingTime;
			}
		}
	}

//---- Calculating----//

	int longestWindowIdleTime = 0;
	int WTime;
	int AvailableWindowsIdleOverFiveMinutes = 0;

	for(int i=0; i<AvailableWindows; ++i) {
		if(idleTimeArray[i] > longestWindowIdleTime) {
			longestWindowIdleTime = idleTimeArray[i];
			WTime = i+1;
		}

		if(idleTimeArray[i] > 5) {
			AvailableWindowsIdleOverFiveMinutes++;
		}

	}


	int TotalWaitingTimes = 0;
	int longestWaitingTime = 0;
	int numberStudentsWaitingOverTenMin = 0;


	for(int i=0; i<TNumStudents; i++) {

		TotalWaitingTimes += WaitingTimeArray[i];

		if(WaitingTimeArray[i] > longestWaitingTime) {

			longestWaitingTime = WaitingTimeArray[i];
		}

		if(WaitingTimeArray[i] > 10) {
			numberStudentsWaitingOverTenMin++;
		}

	}

	double mean = (double)TotalWaitingTimes/TNumStudents;

//This sorts array of wait times
	qsort(WaitingTimeArray, TNumStudents, sizeof(int), compare);

//This is to calculate the median
	int middleIndex = (TNumStudents/2);
	int secondIndex = 0;


	//This says if the array has an even number of elements, find a second index
	if(middleIndex%2 == 0) {
		secondIndex = middleIndex-1;
	}

	double median;
	if(secondIndex == 0) {
		median = WaitingTimeArray[middleIndex];
	}
	else {
		median = (double)(WaitingTimeArray[middleIndex] + WaitingTimeArray[secondIndex])/2;
	}

	cout << "Mean student wait time: " << mean << endl;
	cout << "Median student wait time: " << median << endl;
	cout << "Longest student wait time: " << longestWaitingTime << endl;
	cout << "Number of students waiting over 10 minutes is: " << numberStudentsWaitingOverTenMin << endl;
	cout << "Mean window idle time is: " << meanWindowIdleTime << endl;
	cout << "Longest window idle time is: " << longestWindowIdleTime << endl;
	cout << "Number of windows idle for over 5 minutes is: " << AvailableWindowsIdleOverFiveMinutes <<"\n"<< endl;

	file.close();
	return 0;
	}

	else {
         cout << "No file is found...\n";
         return 0;
     }
}
