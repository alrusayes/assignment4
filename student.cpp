#include <iostream>
#include "student.h"

using namespace std;

Student::Student(int tA, int tW) {
	ArrivalTime = tA;
	TimeAtWindow = tW;
	WaitingTime = 0;
}
