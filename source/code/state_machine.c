#include "state_machine.h"

void initial_position(Elevator *e) {
    //skru av alle lys
    while (elevio_floorSensor() != 0) {
        elevio_motorDirection(DIRN_DOWN);
    }
    if (elevio_floorSensor() == 0){
        elevio_motorDirection(DIRN_STOP);
        e->current_floor = 0;
    }
    elevio_floorIndicator(0);
    e->state = still;
    //printf("%d", e->state);
}


