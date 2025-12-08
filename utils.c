#define _USE_MATH_DEFINES
#include "utils.h"
#include <math.h>



double calculate_distance(double lat1, double lat2, double lon1, double lon2) {
    // Converting lats and lons to radians
    int earth_radius = 3959;
    double lat1_radians = lat1 * (M_PI / 180);
    double lat2_radians = lat2 * (M_PI / 180);
    
    double lon1_radians = lon1 * (M_PI / 180);
    double lon2_radians = lon2 * (M_PI / 180);

    // Get difference in lat
    double difference_lat = lat2_radians - lat1_radians;
    // Get difference in lon
    double difference_lon = lon2_radians - lon1_radians;


    double sin_lat = sin(difference_lat / 2.0);
    double sin_lat_double = sin_lat * sin_lat;


    double sin_lon = sin(difference_lon / 2.0);
    double sin_lon_double = sin_lon * sin_lon;

    double a = sin_lat_double + cos(lat1_radians) * cos(lat2_radians) * sin_lon_double;
     
    // c = 2 × atan2(√a, √(1-a))
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return earth_radius * c;

}   

