//
// Created by Neal  Snooke on 24/10/2017.
//
//using namespace std;
#include <cstdlib>
#include <fstream>
#include <cmath>

#include "Location.h"
using namespace std;

/*
 * constructor
 */
Location::Location(double lat, double lng) : lat_(lat), lng_(lng){

#ifdef DEBUG
    std::cout << "Location constructor " << lat_ << "," << lng_ << std::endl;
#endif
}

/**
 * construnt from file
 * @param file_in
 */
Location::Location(std::ifstream &file_in) {
    file_in >> lat_;
    file_in >> lng_;
}

/* This code based on the wikipedia article at
 * http://en.wikipedia.org/wiki/Great_circle_distance
 *
 * This code by Dave Price, dap@aber.ac.uk, 11th November 2009
 * converted into class Neal Snooke 24 October 2017
 */
double Location::distance(const Location finish) const {
    double theta_s, lambda_s, theta_f, lambda_f;
    double denominator, t1, t2, numerator;
    double delta_rho, distance;

    theta_s = lat_ * PI /180.0;
    lambda_s = lng_ * PI /180.0;

    theta_f = finish.lat_ * PI /180.0;
    lambda_f = finish.lng_ * PI /180.0;

    t1 = cos(theta_f)*sin(lambda_s-lambda_f);
    t2 = cos(theta_s)*sin(theta_f) - sin(theta_s)*cos(theta_f)*cos(lambda_s-lambda_f);

    denominator = sqrt(t1*t1 + t2*t2);

    numerator = sin(theta_s)*sin(theta_f) + cos(theta_s) * cos(theta_f) * cos(lambda_s-lambda_f);

    delta_rho = atan2(denominator, numerator);
    distance = delta_rho * EARTH_RADIUS;

#ifdef DEBUG
    cout << "Delta_rho = " << delta_rho << " distance = " << distance << endl;
#endif
    return (distance);
}

/**
 *
 * @param lat
 * @param lng
 * @return
 */
void Location::setLocation(double new_lat, double new_lng){
    lat_ = new_lat;
    lng_ = new_lng;
}

/**
 * insertion operator overload for stream template instantiation
 *  send a formatted version of a location to a stream
 * @param os stream
 * @param location
 * @return
 */
std::basic_ostream<char>& operator<<(
        std::basic_ostream<char>& os, const Location & location){
    return os << "(" << location.lat_ << ", " << location.lng_ << ")";
}
