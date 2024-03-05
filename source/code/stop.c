#include "stop.h"
#include "state_machine.h"
#include "timer.h"

int check_emergency(Elevator *e) {  //evt gjøres om til en void??
    if (elevio_stopButton() == 1) {
        elevio_motorDirection(DIRN_STOP);
        empty_orders(e);

        while (elevio_stopButton() == 1) {
            elevio_stopLamp(1);

            if (elevio_floorSensor() != -1) {
                elevio_doorOpenLamp(1);
                e->open_door = 1;
            }
        }
        elevio_stopLamp(0);

        if (elevio_floorSensor() == -1) {
            e->state = initial;
        }
        if (elevio_floorSensor() != -1) {
            start_timer(e);
            check_buttons(e);
            check_orders(e);
        }
    }
}

int check_obstruction(Elevator *e) {
    if (e->open_door == 1) { 
        while (elevio_obstruction() == 1) {
            elevio_doorOpenLamp(1);
        }
        start_timer(e);
    }
}