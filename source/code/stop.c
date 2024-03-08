#include "stop.h"
#include "state_machine.h"
#include "timer.h"
#include <stdio.h>

void printMatrix(int matrix[4][3]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            printf("\t%d", matrix[i][j]);
        }
        printf("\n"); // New line at the end of each row
    }
}

void check_emergency(Elevator *e) {  //evt gjøres om til en void??
    if (elevio_stopButton() == 1) {
        elevio_motorDirection(DIRN_STOP);
        printf("Nå blir det godt med en pause\n");
        printMatrix(e->queue);
        empty_orders(e);
        printMatrix(e->queue);
        while (elevio_stopButton() == 1) {
            elevio_stopLamp(1);

            if (elevio_floorSensor() != -1) {
                elevio_doorOpenLamp(1);
                //check_obstruction(e);
            }
        }
        elevio_stopLamp(0);

        if (elevio_floorSensor() == -1) {
            initial_position(e);
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