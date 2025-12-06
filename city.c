#include "city.h"
#include <stdlib.h>
#include <string.h>

// Put your load_cities_from_csv() implementation here
// Put your update_field() helper here
// Put your get_new_city() here (rename to get_random_city)


// This function will help us decide what field in our city struct to update
int update_field(City *city_arr, int city_index, int field_index, char token[50]) {

    // We use the field index to determine what to update
    switch(field_index) {
        // 0 index in the struct is the name
        case 0:
            strcpy(city_arr[city_index].name, token);
            break;

        // 1 index in the struct is the lattitude
        case 1:
            city_arr[city_index].latitude = atof(token);
            break;


        // 2 index in the struct is the longitude
        case 2:
            city_arr[city_index].longitude = atof(token);
            break;

        // 3 index in the struct is the population
        case 3: 
            city_arr[city_index].population = atof(token);
            break;
        default:
            return -1;
    }

    return 0;
}




City* get_random_city(int count, City *cities) {
    // This will generate a random index in the bounds of the array length
    int random_index = rand() % count;
    

    // This returns the address of the random city entry
    return &cities[random_index];

}



City* load_cities_from_csv(FILE *fptr, int* city_count) {
    char line[100];

    // if first line is null, return null. 
    if (fgets(line, sizeof(line), fptr) == NULL) {
        return NULL;
      
    }

    // we initialize capacity to 20
    int capacity = 20;

    City *cities = (City *)malloc(capacity  * sizeof(City));

    // If there was not enough memory for structs, we return null
    if (cities == NULL) {
        return NULL;
    }


    // this will serve as current city index in memory and city count
    int city_index = 0;

    // While we have a line to process
    while(fgets(line, sizeof(line), fptr)) {

        // Update capacity if city count exceeds capacity
        if (city_index >= capacity) {
            capacity *= 2;

            // reallocate into bigger chunk of memory
            City *temp = realloc(cities, capacity * sizeof(City));

            // If no space for reallocation, return null
            if (temp == NULL) {
                free(cities);
                return NULL;
            }
            

            cities = temp;
        }


        // pointer to token
        char *token;

        //pointer to save point
        char *saveptr;

        // This will get the name 
        token = strtok_r(line, ",", &saveptr);
        

        // This is to determine what field in the city struct to change
        int field_index = 0;

        while(token != NULL) {

            // This will determine what to update in the struct, as well as which struct in our memory.
            update_field(cities, city_index, field_index, token);
            token = strtok_r(NULL, ",", &saveptr);
            field_index++;
        }   

        city_index++;

    }

    // When we are done, change the value that we passed in to our city index, which is the total.
    *city_count = city_index;
    return cities;
}


