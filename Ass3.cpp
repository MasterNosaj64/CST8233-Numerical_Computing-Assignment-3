/****************************************************************************************************************************************
File Name:						Ass3.cpp
Version:						1.0
Auther/Student Name:			Jason Waid
Student Number:					040912687
Couse Name and Number:			Numerical Computing CST8233
Lab Section:					303
Assignment Number:				Assignment #3
Assignment Name:				Transient-Response Analysis of 1st Order Systems
Due Date:						08/07/2020
Submission Date of Assignment:	08/07/2020
Professor's Name:				Abdullah Kadri
Purpose:						Find the solution of 1st order Ordinary Differential Equations (ODE) using well known
								methods; namely, Euler’s and Runge-Kutta 4th Order Methods.
******************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
using namespace std;


int main() {

	//Main Menu variable for choosing method to use
	int method = 0;

	//Variables for table
	double time = 0;
	double exactTemp = 0;
	double estimatedTemp = 0;
	double percentageError = 0;

	//Variables unique to Runge-Kuta 4th Order Method
	double k1 = 0;
	double k2 = 0;
	double k3 = 0;
	double k4 = 0;

	//Variables shared between Runge-Kuta 4th Order and Euler's Method.
	double xi = 0;
	double yi = 0;
	double x = 0;
	double y = 0;
	double y0 = 3;
	double h = 0;

	//Infinite loop for menu
	for (;;) {

		cout << ">> Choose the method for solving ODE:" << endl;
		cout << "1. Euler's Method\n2. Runge-Kutta 4th Order Method" << endl;
		cout << ">> ";
		cin >> method;

		//Menu Error handling
		while (method != 1 && method != 2 ) {
			cout << "ERROR - INCORRECT MENU OPTION" << endl;
			cout << ">> Choose the method for solving ODE:" << endl;
			cout << "1. Euler's Method\n2. Runge-Kutta 4th Order Method" << endl;
			cout << ">> ";
			cin >> method;
		}

		cout << ">> Choose step size \"h\" (0.8, 0.2, 0.05)" << endl;
		cout << ">> ";
		cin >> h;

		//Menu Error handling
		while (h != 0.8 && h != 0.2 && h != 0.05) {
			cout << "ERROR - INCORRECT MENU OPTION" << endl;
			cout << ">> Choose step size \"h\" (0.8, 0.2, 0.05)" << endl;
			cout << ">> ";
			cin >> h;
		}

		cout << "Time(Second)\tExact Temp(C)\tEstimated Temp(C)\tPercentage Error(%)" << endl;
		
		//Initial x & y coordinates
		yi = y0;
		xi = 0;

		for (time = h; time <= 2;){

			//Calc Exact Value
			//0(t) = 0.1 cos 4t + 0.2 sin 4t + 2.9 e^-2t
			exactTemp = 0.1 * cos(4 * time) + 0.2 * sin(4 * time) + 2.9 * exp(-2 * time);

			if (method == 1) {
				//Calc Euler's Method
				//h = 0.8, 0.2, 0.05, y0 = 3, 0 <= 0 <= 2
				//d0(t)/dt + 2*0(t) = cos(4*t)
				//converted the above formula to: d0(t)/dt = cos(4*t) - 2*0(t)

				//Calc Euler Method
				//yi + 1 = yi + f(xi,yi) * h
				x = xi;
				y = yi;

				estimatedTemp = yi + (cos(4 * x) - (2 * y)) * h;

			}

			if (method == 2) {
				//Calc Runge-Kutta 4th Order Method
				//h = 0.8, 0.2, 0.05, y0 = 3, 0 <= 0 <= 2
				//d0(t)/dt + 2*0(t) = cos(4*t)
				//converted the above formula to: d0(t)/dt = cos(4*t) - 2*0(t)


				//Calc k1
				// k1 = f(xi,yi) = f(0, 1)
				x = xi;
				y = yi;
				k1 = cos(4 * x) - 2 * (y);

				//Calc k2
				//k2 = f(xi + 1/2 * h, yi + 1/2 * k1 * h)
				x = xi + 0.5 * h;
				y = yi + 0.5 * k1 * h;
				k2 = cos(4 * x) - 2 * (y);

				//Calc k3
				//k3 = f(xi + 1/2 * h, yi + 1/2 * k2 * h)
				x = xi + 0.5 * h;
				y = yi + 0.5 * k2 * h;
				k3 = cos(4 * x) - 2 * (y);

				//Calc k4
				//k4 = f(xi + h, yi + k3 * h)
				x = xi + h;
				y = yi + k3 * h;
				k4 = cos(4 * x) - 2 * (y);

				//Calc value of next yi
				//yi+1 = yi + 1/6 * (k1 + 2 * k2 + 2 * k3 + k4) * h;
				estimatedTemp = yi + 1.0 / 6.0 * (k1 + (2 * k2) + (2 * k3) + k4) * h;


			}
			
			//Next x point
			xi = xi + h;
			//Next y point
			yi = estimatedTemp;

			//Calc Percentage Error
			percentageError = fabs(((estimatedTemp / exactTemp) * 100)- 100);

			//Print row
			cout << fixed << setprecision(1) << time << "\t\t" << fixed << setprecision(3) << exactTemp << "\t\t" << estimatedTemp << "\t\t\t" << fixed << setprecision(2) << percentageError << endl;
			
			//Increment time (x)
			time += h;
		}
	}
	return 0;
}