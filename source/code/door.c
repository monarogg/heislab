#include "door.h"
#include "timer.h"
#include "state_machine.h"


void open_door(){
    elevio_doorOpenLamp(1);
    start_timer();

}
