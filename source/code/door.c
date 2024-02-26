#include "door.h"
#include "timer.h"
#include "state_machine.h"


void open_door(struct Elevator e){
    elevio_doorOpenLamp(1);
    e.state = 2; 
    //start_timer();

}

void close_door(struct Elevator e){
    elevio_doorOpenLamp(0);
    //e.state = 3;
}