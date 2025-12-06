#include "game.h"
#include "utils.h"
#include <stdlib.h>

// Put start_new_game() here
// Put process_guess() here



// This will return a GameState struct
GameState* start_new_game(City *cities, int count, int rounds) {

    // Allocate memory in heap for the new game struct
    GameState *round_information = malloc(sizeof(GameState));

    // if no memory, then we return null
    if (round_information == NULL) {
        return NULL;
    }



    // Get random city address
    City *random_city = get_random_city(count, cities);    


    // update struct with random city strucct
    round_information->secret_city = *random_city;

    // round will be 0 at start
    round_information->round = 0;

    // score will be 0 at start
    round_information->score = 0;

    // User defines this
    round_information->total_rounds = rounds;

    return round_information;

}



double process_guess(GameState *game, double guess_lat, double guess_lon) {
     // Calculate distance between guess and secret_city
    double distance = calculate_distance(game->secret_city.latitude, guess_lat, game->secret_city.longitude, guess_lon);
    // Convert distance to points (decide scoring formula)
    // Perfect guess: 5000 points
    // 50 miles off: ~3750 points
    // 100 miles off: ~2500 points  
    // 200 miles off: ~0 points
    // 200+ miles: 0 points

    int points = (int)(5000 - (distance * 25));
    if (points < 0) points = 0;


    game->score += points;

    return distance;
    
}
