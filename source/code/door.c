#include "door.h"
#include "timer.h"
#include "state_machine.h"
#include "stop.h"


void open_door(Elevator *e){
    elevio_doorOpenLamp(1);
    //check_obstruction(e);
    start_timer(e);
}
