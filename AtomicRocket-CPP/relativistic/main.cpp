/* 
 * File:   main.cpp
 * Author: grammaticus
 *
 * Created on March 19, 2012, 12:12 PM
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <istream>
#include <ostream>
#include <math.h>
#include <iomanip>
#include "ship.h"
#include "Terra.h"
#include "main.h"
using namespace std;

/*Constants*/
const double C = 299792458;  //Speed of light
const double SECS = 31556926;  //Seconds in a year
const double LY = 9.46 * pow(10, 15);  //Light year in meters

/*Main*/
int main(int argc, char** argv) {
    calculate();
    return 0;
}


/*********/
/* MENUS */
/*********/

/* Menu for inputting data relevant to the ship*/
void shipMenu(ship &myShip) {
    bool isDone = false;
    string done;
    int choice;
    while (isDone == false) {
        cout << "What information do you have about the ship?\n"
                "[1] Acceleration\n"
                "[2] Exhaust Velocity\n"
                "[3] Mass Ratio\n"
                "[4] Proper Time (ship's frame of reference)\n"
                "Please enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                accel(myShip);
                break;
            case 2:
                ev(myShip);
                break;
            case 3:
                mr(myShip);
                break;
            case 4:
                pTime(myShip);
                break;
            default:
                cout << "You have entered an invalid choice; please try again.";
        }
        cout << "Do you have any more information to enter? [Y] or [N] ";
        cin >> done;
        if ((done == "y") || (done == "Y")) {
            continue;
        } else if ((done == "n") || (done == "N")) {
            isDone = true;
        } else {
            cout << "You have entered an invalid choice.\n";
        }
    }
}

/*Menu for inputting data relevant to Terra*/
void terraMenu(Terra &myTerra) {
    bool isDone = false;
    string done;
    int choice;
    while (isDone == false) {
        cout << "What information do you have about Terra?\n"
                "[1] Distance\n"
                "[2] Time (from Terra's frame of reference)\n"
                "Please enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                d(myTerra);
                break;
            case 2:
                tTime(myTerra);
                break;
            default:
                cout << "You have entered an invalid choice; please try again.";
        }
        cout << "Do you have any more information to enter? [Y] or [N] ";
        cin >> done;
        if ((done == "y") || (done == "Y")) {
            continue;
        } else if ((done == "n") || (done == "N")) {
            isDone = true;
        } else {
            cout << "You have entered an invalid choice.\n";
        }
    }
}

/*Putting it all together - uses Ship Menu and Terra Menu to get input data*/
/*Uses that to calculate remaining data*/
void calculate() {

    cout << fixed << setprecision(2);	//2 decimal points for readability
    ship myShip;
    Terra myTerra;

    shipMenu(myShip);
    cout << endl;  //Line spacing
    terraMenu(myTerra);
    cout << endl;  //Line spacing
    
    double acceleration = myShip.getA();
    double ev = myShip.getEV();
    double mr = myShip.getMR();
    double pTime = myShip.getPTime();
    double tTime = myTerra.getTTime();
    double d = myTerra.getD();


	/*Acceleration MUST be a positive number in order for this to work*/
    while (acceleration <= 0) {
        cout << "You must enter an acceleration greater than 0." << endl;
        accel(myShip);
        acceleration = myShip.getA();
    }

	/*Default values for everything are -1; the following section checks to see 
     *what needs to be calculated*/

	if (tTime == -1) {
        double tt1 = tTime1(acceleration, pTime);
        double tt2 = tTime2(ev, mr, acceleration);
        double tt3 = tTime3(acceleration, d);
        if ((tt1 > 0) && (pTime > 0))
            myTerra.setTTime(tt1);
        else if (tt2 > 0)
            myTerra.setTTime(tt2);
        else
            myTerra.setTTime(tt3);
        tTime = myTerra.getTTime();
    }

    std::cout << "tTime = " << tTime << endl;

    if (pTime == -1) {
        double pt = pTime1(acceleration, tTime);
        cout << "pt: " << pt << endl;
        myShip.setPTime(pt);
        pTime = myShip.getPTime();
    }

    std::cout << "pTime = " << pTime << endl;

    if (d == -1) {
        double dist = tDist1(acceleration, pTime);
        myTerra.setD(dist);
        d = myTerra.getD();
    }

    std::cout << "d = " << d << endl;

    double velocity = tVFin1(acceleration, pTime);
    myShip.setV(velocity);

    std::cout << "v = " << velocity << endl;

    double g = gamma1(acceleration, pTime);
    myShip.setGamma(g);

    std::cout << "gamma = " << g << endl << endl;

}


/***************/
/* SHIP VALUES */
/***************/

/*Calls ship setter method for acceleration*/
void accel(ship &myShip) {
    double a;
    std::cout << "Enter acceleration in m/s^2\n"
            "(1 gravity ~ 10 m/s^2): ";
    std::cin >> a;
    myShip.setA(a);
}

/*Calls ship setter method for exhaust velocity*/
void ev(ship &myShip) {
    double ev;
    std::cout << "Enter exhaust velocity in m/s: ";
    std::cin >> ev;
    myShip.setEV(ev);
}

/*Calls ship setter method for mass ratio*/
void mr(ship &myShip) {
    double mr;
    std::cout << "Enter mass ratio: ";
    std::cin >> mr;
    myShip.setMR(mr);
}

/*Calls ship setter method for proper time*/
void pTime(ship &myShip) {
    double pTime;
    std::cout << "Enter proper time (ship's frame of reference) in years: ";
    std::cin >> pTime;
    myShip.setPTime(pTime);
}


/****************/
/* TERRA VALUES */
/****************/

/*Calls Terra setter method for distance*/
void d(Terra &myTerra) {
    double dist;
    std::cout << "Enter the distance in light years: ";
    std::cin >> dist;
    myTerra.setD(dist);
}

/*Calls Terra setter method for Terra Time*/
void tTime(Terra &myTerra) {
    double tTime;
    std::cout << "Enter time from Terra's frame of reference in years: ";
    std::cin >> tTime;
    myTerra.setTTime(tTime);
}


/*****************************/
/* TERRA'S FRAME OF REFERENCE*/
/*****************************/

/*
* Terra Time
*/

/*given accel and proper time (spaceship's frame of reference)*/
double tTime1(double a, double pTime) {
    return years((C / a) * sinh(a * seconds(pTime) / C));
}

/*to expend all propellant, given acceleration, exhaust velocity and
     mass ratio*/
double tTime2(double ev, double mr, double a) {
    return years((C / a) * sinh(ev / C) * log(mr));
}

/*given accel and distance*/
double tTime3(double a, double d) {
    return years(sqrt(pow(meters(d) / C, 2) + (2 * meters(d) / a)));
}

/*
* Distance
*/

/*given accel and proper time (spaceship's frame of reference)*/
double tDist1(double a, double pTime) {
    return lightyears((pow(C, 2) / a)*(cosh(a * seconds(pTime) / C) - 1));
}

/*given acceleration, exhaust velocity and mass ratio, after all propellant
     expended*/
double tDist2(double ev, double mr, double a) {
    return lightyears((pow(C, 2) / a) * cosh((ev / C) * log(mr) - 1));
}

/*given acceleration and Terra time*/
double tDist3(double a, double tTime) {
    return lightyears((pow(C, 2) / a)*(sqrt(1 +
            pow(a * seconds(tTime) / C, 2)) - 1));
}

/*
* Velocity
*/

/*given accel and proper time (spaceship's frame of reference)*/
double tVFin1(double a, double pTime) {
    return psl(C * tanh(a * seconds(pTime) / C));
}

/*given exhaust velocity and mass ratio*/
double tVFin2(double ev, double mr) {
    return psl(C * tanh((ev / C) * log(mr)));
}

/*given accel and Terra time*/
double tVFin3(double a, double tTime) {
    return psl((a * seconds(tTime)) / (sqrt(1 +
            pow(a * seconds(tTime) / C, 2))));
}


/*********************************/
/* SPACESHIP'S FRAME OF REFERENCE*/
/*********************************/

/*given a and Terra time*/
double pTime1(double a, double tTime) {
    return years((C / a) * asinh(a * seconds(tTime) / C));
}

/*given acceleration and distance*/
double pTime2(double a, double d) {
    return years((C / a) * acosh(a * meters(d) / (pow(C, 2)) + 1));
}

/*
* Time Dilation
*/

/*given accel and proper time (spaceship's frame of reference)*/
double gamma1(double a, double pTime) {
    return cosh(a * seconds(pTime) / C);
}

/*given exhaust velocity and mass ratio*/
double gamma2(double ev, double mr) {
    return cosh((ev / C) * log(mr));
}

/*given accel and Terra time*/
double gamma3(double a, double tTime) {
    return sqrt(1 + pow(a * seconds(tTime) / C, 2));
}

/*given accel and distance*/
double gamma4(double a, double d) {
    return a * meters(d) / pow(C, 2) + 1;
}


/**************************/
/* MISCELLANEOUS FORMULAE */
/**************************/
/*asinh, acosh, and atanh not included in math libraries*/
double asinh(double x) {
    return log(x + sqrt(x * x + 1));
}

double acosh(double x) {
    return log(x + sqrt(x * x - 1.0));
}

double atanh(double x) {
    return 0.5 * log((x + 1.0) / (x - 1.0));
}

/*seconds -> years*/
double years(double t) {
    return t / SECS;
}

/*years -> seconds*/
double seconds(double t) {
    return t*SECS;
}

/*light years -> meters*/
double meters(double d) {
    return d*LY;
}

/*meters -> lightyears*/
double lightyears(double d) {
    return d / LY;
}

/*velocity as a percentage of the speed of light*/
double psl(double v) {
    return v / C;
}
