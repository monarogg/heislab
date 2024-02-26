#pragma once
#include "../driver/elevio.h"


typedef enum {
    moving_down = -1,
    moving_up = 1,
    still_at_floor = 0,
    door_open = 2,
    door_closed = 3,
    stop_in_shaft = 4,
    stop_at_floor = 5,
    inactive = 6,
    initial = 7,
} States;

void initial_position(); 

typedef struct Elevator {
    States state;
    int queue[N_FLOORS][N_BUTTONS];
};

