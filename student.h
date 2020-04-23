#ifndef STUDENT_H_
#define STUDENT_H_
#include <iostream>

using namespace std;

class Student {
public:

	Student();
	Student(int tA, int tW);
	~Student();

	int TimeAtWindow;
	int ArrivalTime;
	int TimeLeftLine;
	int WindowNum;
	int WaitingTime;

};

#endif /* STUDENT_H_ */
