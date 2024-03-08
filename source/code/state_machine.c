#include "state_machine.h"

void initial_position(Elevator *e) {
    while (elevio_floorSensor() != 0) {
        elevio_motorDirection(DIRN_DOWN);
    }
    if (elevio_floorSensor() == 0){
        elevio_motorDirection(DIRN_STOP);
        e->current_floor = 0;
    }
    e->state = still;
    
}


