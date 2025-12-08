#include "city.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    FILE *fptr = fopen("cities.csv", "r");

    if (fptr == NULL) {
        perror("File did not open properly");
        return 1;
    }


    int city_count;
    City *my_cities = load_cities_from_csv(fptr, &city_count);
    if (my_cities == NULL) {
        fprintf(stderr, "Failed to load cities\n");
        fclose(fptr);
        return 1;
    }

    fclose(fptr);



    srand(time(NULL));

    GameState *game = start_new_game(my_cities, city_count, 5);

    while(game->round < game->total_rounds) {
        double lat_guess, long_guess;
        printf("Enter Latitude and Longitude (e.g., 47.6 -122.3): ");
         if (scanf("%lf %lf", &lat_guess, &long_guess) == 2) {
        // Input successful, 2 items were read

        // 3. Confirm the input using printf
        // For printf, you can use %f or %lf for doubles.
        printf("You entered Latitude: %.4f and Longitude: %.4f\n", lat_guess, long_guess);

        } else {
            printf("Invalid input format. Please enter two numbers.\n");
        }

        double distance = process_guess(game, lat_guess, long_guess);
        printf("The city was %s\n", game->secret_city.name);
        printf("You were %.1f miles off!\n", distance);
        printf("Current total score: %.0f\n", game->score);
        

        City *random_city;
        random_city = get_random_city(city_count, my_cities);
        game->secret_city = *random_city;
        game->round++;

    }

    printf("Your total score was: %f\n", game->score);

    free(game);


    // double distance = calculate_distance(my_cities[0].lattitude, my_cities[1].lattitude, my_cities[0].longitute, my_cities[1].longitute);

    // printf("This is the distance between %s and %s: %f\n", my_cities[0].name, my_cities[1].name, distance);



    free(my_cities);

    return 0;
}