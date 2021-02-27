/*
To compile: g++ lab2.cpp lab2timing.cpp timer.cpp
*/
#include "timer.h"
#include <iostream>
using namespace std;

unsigned int factorial (unsigned int n);
double power (double base, unsigned int n);
unsigned int fibonacci (unsigned int n);

int main(void){
	//unsigned int n = 35;
	unsigned int n[] = { 35,36,37,38,39,40,41 };
	unsigned int rc;
	Timer t;
	//t.start();
	//rc=fibonacci(n);
	//t.stop();
	//cout << "fibonacci (" << n << ") = " << rc << endl;
	//cout << "fibonacci (" << n << ") took " << t.currtime() << " s" << endl;

	// FACTORIAL
	// NA

	// POWER 
	// NA

	// FIBONACCI
	for (int i = 0; i < 7; i++)
	{
		t.start();
		rc = fibonacci(n[i]);
		t.stop();

		if (i != 0) cout << endl;
		cout << "fibonacci (" << n[i] << ") = " << rc << endl;
		cout << "fibonacci (" << n[i] << ") took " << t.currtime() << " s" << endl;
	}

	return 0;
}