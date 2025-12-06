#ifndef GAME_H
#define GAME_H

#include "city.h"

typedef struct {
    City secret_city;
    int round;
    double score;
    int total_rounds;
} GameState;

GameState* start_new_game(City *cities, int count, int rounds);
double process_guess(GameState *game, double guess_lat, double guess_lon);

#endif