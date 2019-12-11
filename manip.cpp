#include "manip.h"
#include <math.h>

//using namespace algorithms;

double algorithms::scale(double val, double min, double max){
    return (val-min)/(max-min)*200 - 20;
}
double algorithms::normalize(double val, double min, double max){

}
double algorithms::log(double base, double val){
    return (std::log(val)/std::log(base));
}
double algorithms::exponential(double val){
    return std::log2(val*0.00001)*50;
}
double algorithms::test(double &val){
    return val*std::log(val)/10;
}
sf::Color algorithms::calcColor(double val){
    int amp=255/2;
    float freq=0.01;

    int r=amp*sin(freq*val)+amp;
    int g=amp*sin(freq*val+2)+amp;
    int b=amp*sin(freq*val+4)+amp;
    sf::Color color(r,g,b);
    return color;
}
