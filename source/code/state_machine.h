#pragma once
#include "../driver/elevio.h"


typedef enum {
    moving = -1,
    moving_up = 1,
    still = 0,
    inactive = 3,
    initial = 4,
} States;

void initial_position(); 

typedef struct Elevator {
    States state;
    int current_floor;
    int emergency;
    int queue[N_FLOORS][N_BUTTONS];
};

