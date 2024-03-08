#include "door.h"
#include "timer.h"
#include "state_machine.h"
#include "stop.h"


void open_door(Elevator *e){
    elevio_doorOpenLamp(1);
    int obstruction = elevio_obstruction();
    while (obstruction == 1) {
        elevio_doorOpenLamp(1);
        obstruction = elevio_obstruction();
    }
    start_timer(e);
}
