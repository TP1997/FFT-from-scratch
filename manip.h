#ifndef MANIP_H_INCLUDED
#define MANIP_H_INCLUDED
#include <SFML/Graphics/Color.hpp>
/*
struct windows {
    double s_curve[1000];
} test;*/

namespace algorithms{
    double scale(double val, double min, double max);
    double normalize(double val, double min, double max);
    double mag_octave();
    double log(double, double);
    double exponential(double);
    double test(double&);
    sf::Color calcColor(double);

}

#endif // MANIP_H_INCLUDED
