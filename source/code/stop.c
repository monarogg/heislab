#include "stop.h"
#include "state_machine.h"
#include "timer.h"

void check_emergency(Elevator *e) {  
    if (elevio_stopButton() == 1) {
        elevio_motorDirection(DIRN_STOP);
        empty_orders(e);

        while (elevio_stopButton() == 1) {
            elevio_stopLamp(1);

            if (elevio_floorSensor() != -1) {
                elevio_doorOpenLamp(1);

            }
        }
        elevio_stopLamp(0);

        if (elevio_floorSensor() == -1) {
            initial_position(e);
            empty_orders(e);
        }
        if (elevio_floorSensor() != -1) {
            start_timer(e);
            check_buttons(e);
            check_orders(e);
        }
    }
}
