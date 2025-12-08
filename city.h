#ifndef CITY_H
#define CITY_H

#include <stdio.h>

typedef struct {
    char name[50];
    double latitude;
    double longitude;
    int population;
} City;

// Function declarations
City* load_cities_from_csv(FILE *fptr, int *city_count);
City* get_random_city(int count, City *cities);

#endif