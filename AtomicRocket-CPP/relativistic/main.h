/* 
 * File:   main.h
 * Author: grammaticus
 *
 * Created on March 19, 2012, 5:49 PM
 */

#ifndef MAIN_H
#define	MAIN_H

/*Menus for ship and Terra setter functions*/
void shipMenu(ship &myShip);
void terraMenu(Terra &myTerra);

/*Use ship and Terra menus to gather data, then calculates unknowns*/
void calculate();

/*Call ship setter method*/
void accel(ship &myShip);
void ev(ship &myShip);
void mr(ship &myShip);
void pTime(ship &myShip);

/*Call Terra setter methods*/
void tTime(Terra &myTerra);
void d(Terra &myTerra);

/*Note that only a few of the formulae are actually used*/
/*The rest are simply included for the sake of completeness*/

/*Terra Time formulae*/
double tTime1(double a, double pTime);
double tTime2(double ev, double mr, double a);
double tTime3(double a, double d);

/*Distance formulae*/
double tDist1(double a, double pTime);
double tDist2(double ev, double mr, double a);
double tDist3(double a, double tTime);

/*Final Velocity formulae*/
double tVFin1(double a, double pTime);
double tVFin2(double ev, double mr);
double tVFin3(double a, double tTime);

/*Proper Time (spaceship's frame of reference) formulae*/
double pTime1(double a, double tTime);
double pTime2(double a, double d);

/*Time dilation factor (gamma) formulae*/
double gamma1(double a, double pTime);
double gamma2(double ev, double mr);
double gamma3(double a, double tTime);
double gamma4(double a, double d);

/*Miscellaneous formulae*/
double asinh(double x);
double acosh(double x);
double atanh(double x);
double years(double t);
double meters(double d);
double seconds(double t);
double lightyears(double d);
double psl(double v);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

