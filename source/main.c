#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "code/state_machine.h"
#include "code/door.h"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    struct Elevator elevator;
    // initialiserer elevator:
    elevator.state = 7;
    for (int i = 0; i < N_FLOORS; i++){
        for (int j = 0; j < N_BUTTONS; j++){
            elevator.queue[i][j] = 0;
        }
    }

    elevio_doorOpenLamp(0);

    while(1){


    switch (elevator.state)
    {
    case moving_down:
        elevio_motorDirection(DIRN_DOWN);
        break;

    case moving_up:
        elevio_motorDirection(DIRN_UP);
        break;

    case initial:
        initial_position();
        elevator.state = 2;
        break;

    case door_open:
        open_door(elevator);
        break;

    case door_closed:
        close_door(elevator);
        break;


    default:
        break;
    }
    }

    return 0;
}
