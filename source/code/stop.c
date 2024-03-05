#include "stop.h"
#include "state_machine.h"
#include "timer.h"

void check_emergency(Elevator *e) {  //evt gjøres om til en void??
    if (elevio_stopButton() == 1) {
        elevio_motorDirection(DIRN_STOP);
        empty_orders(e);

        while (elevio_stopButton() == 1) {
            elevio_stopLamp(1);

            if (elevio_floorSensor() != -1) {
                elevio_doorOpenLamp(1);
                //check_obstruction(e);
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

// void check_obstruction(Elevator *e) {
//     int obstruction = elevio_obstruction();
//     while (obstruction == 1) {
//         elevio_doorOpenLamp(1);
//         obstruction = elevio_obstruction();
//     }
//         start_timer(e);
// }