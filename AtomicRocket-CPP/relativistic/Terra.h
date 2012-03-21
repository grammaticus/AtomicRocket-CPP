/* 
 * File:   Terra.h
 * Author: grammaticus
 *
 * Created on March 20, 2012, 9:35 AM
 */

#ifndef TERRA_H
#define	TERRA_H

class Terra {
    double tTime;       //Terra time (years)
    double d;           //Distance (lightyears)
public:
    Terra();
    Terra(const Terra& orig);
    virtual ~Terra();
    void setTTime(double time){ tTime = time; }
    double getTTime(){ return tTime; }
    void setD(double dist){ d = dist;}
    double getD(){ return d; }
private:

};

#endif	/* TERRA_H */

