/* 
 * File:   ship.h
 * Author: grammaticus
 *
 * Created on March 19, 2012, 2:51 PM
 */

#ifndef SHIP_H
#define	SHIP_H

class ship {
    double a;       //Acceleration (m/s^2)
    double mr;      //Mass Ratio (dimensionless number)  
    double ev;      //Exhaust Velocity (m/s)
    double pTime;   //Proper Time in years (spaceship's frame of reference)
    double v;       //Ship's velocity; calculated from Terra's frame of
                        //reference, but conceptually it makes more sense here
                        //Represented as a fraction of the speed of light
    double gamma;   //Time dilation factor
public:
    ship();
    ship(const ship& orig);
    virtual ~ship();
    void setA(double accel) { a = accel; }
    double getA() const { return a; }
    void setEV(double exhaustv) { ev = exhaustv; }
    double getEV() const { return ev; }
    void setMR(double massr) { mr = massr; }
    double getMR() const { return mr; }
    void setPTime(double propertime){ pTime = propertime; }
    double getPTime() const { return pTime; }
    void setV(double vel) { v = vel; }
    double getV() const { return v; }
    void setGamma(double g) { gamma = g; }
    double getGamma() const { return gamma; }
private:

};


#endif	/* SHIP_H */

