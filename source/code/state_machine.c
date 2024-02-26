#include "state_machine.h"

void initial_position() {
    while (elevio_floorSensor() != 0) {
        elevio_motorDirection(DIRN_DOWN);
    }
    if (elevio_floorSensor() == 0){
        elevio_motorDirection(DIRN_STOP);
    }
}

// while


