#ifndef TRIALWF1FULL_H
#define TRIALWF1FULL_H

#include "wavefunction.h"
#include <iostream>

//using std::vector;
using std::cout;
using std::endl;

class trialWF1Full: public Wavefunction
{
    public:
        trialWF1Full( int NParticles, int NDimensions );

        void setParameters( vector<double> parameters )
        {
            m_omega = parameters[0];
            m_alpha = parameters[1];
        }
        double sumSquares( const vector< vector<double> > & positions );
        double distanceSquared( const vector< vector<double> > & positions );
        double distance( const vector< vector<double> > & positions )
        {
            m_distance = std::sqrt(distanceSquared(positions));
            return m_distance;
        }

        double powers( const vector< vector<double> > & positions );
        double localEnergy( const vector< vector<double> > & positions );

        // getters and setters
        double omega() {return m_omega; }
        double alpha() {return m_alpha; }
        double kinetic() {return m_kinetic; }
        double potential() {return m_potential; }
        double distance() { return m_distance; }


    private:
        double m_omega = 0;
        double m_alpha = 0;
        double m_distanceSquared = 0;
        double m_distance = 0;
        double m_kinetic = 0;
        double m_potential = 0;

}; // end class

inline double trialWF1Full::powers
(
 const vector< vector<double> > &positions
)
{
    return -0.5*m_alpha*m_omega*sumSquares(positions);
}

inline double trialWF1Full::localEnergy
(
   const vector< vector<double> > &positions
)
{ //returns vector with [0] as kinetic and [1] as potential energy
    vector<double> energy;
    energy.push_back
        (
         (3.0 - 0.5*m_omega*m_alpha*sumSquares(positions))*m_alpha*m_omega
        );
    energy.push_back
        (
         0.5*m_omega*m_omega*sumSquares( positions ) + 1/distance(positions)
        );
    m_kinetic = energy[0];
    m_potential = energy[1];
    return energy[0] + energy[1];
}

#endif // TRIALWF1FULL_H
