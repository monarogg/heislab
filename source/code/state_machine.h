#pragma once
#include "../driver/elevio.h"


typedef enum {
    moving_down = -1,
    moving_up = 1,
    still = 0,
    inactive = 3,
    initial = 4,
    stop = 5,
} States;

typedef struct {
    States state;
    int current_floor;
    int destination;
    int last_floor;
    int moving;
    int queue[N_FLOORS][N_BUTTONS];
    
} Elevator;

void initial_position(Elevator *e); 


