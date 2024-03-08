#include "order_boss.h"
#include "state_machine.h"
#include "stop.h"
#include "door.h"
#include <stdio.h>



void add_order(int floor, int number, Elevator *e){
    // up er index 0, down er 1, ab er 2
    e->queue[floor][number] = 1;

    //for å teste på sanntid:
    //printf("\n %d \n", e.queue[floor][order]);
}


void remove_order(int floor, Elevator *e) {
    //fordi fjerner alle orders fra samme etasje
    for(int b = 0; b < N_BUTTONS; b++){
        e->queue[floor][b] = 0;
        elevio_buttonLamp(floor, b, 0);
    }
}


void empty_orders(Elevator *e){
    printf("Emptying orders :)\n");
    
    for (int f = 0; f < N_FLOORS; f++){
        for (int b = 0; b < N_BUTTONS; b++){
            e->queue[f][b] = 0;
            elevio_buttonLamp(f, b, 0);
        }
        //elevio_floorIndicator(f); kanskje ikke denne?

    
    }
    e->destination = 0; //should go to first
    
}

void check_buttons(Elevator *e) {
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {

            int btn_pressed = elevio_callButton(f, b);
            if (btn_pressed) {
               add_order(f, b, e);
               e->destination = f;
               light_on(f,b);
            }
        }
    }
}

void check_orders(Elevator *e) {

    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            if (e->queue[f][b] == 1) {
                if (e->current_floor < f) {
                    e->state = moving_up;
                    e->destination = f;
                    break;
                }
                if (e->current_floor > f) {
                    e->state = moving_down;
                    e->destination = f;
                    break; 

                }
                if (e->destination == f) {
                    e->state = still;
                    e->current_floor = f;
                    remove_order(e->current_floor, e);  //endret fra f til e->current_floor
                    light_off(f);
                    break;
                }
            }
        }
    }
}

void move_up(Elevator *e) {
    int floor = elevio_floorSensor(); 
   // e->current_floor = elevio_floorSensor(); // evt bruke denne
    while (floor != e->destination) {
        if (floor != -1) {
            elevio_floorIndicator(floor);
        }
        if (elevio_floorSensor() != -1) {
            e->last_floor = floor;
           
        }
        check_buttons(e);
        check_emergency(e);
        
        for (int f = 0; f < N_FLOORS; f++) {
            floor = elevio_floorSensor();
            if (((e->queue[f][0] == 1) && (floor < f) && (f <= e->destination)) || ((e->queue[f][2] == 1) && (floor < f) && (f <= e->destination))) {
                e->destination = f;
                if (elevio_floorSensor() == f) {
                    elevio_floorIndicator(f);
                    elevio_motorDirection(DIRN_STOP);
                    open_door(e);
                }
            }
        }
        
        floor = elevio_floorSensor();
        elevio_motorDirection(DIRN_UP); 
        if (floor == e->destination) {
            elevio_floorIndicator(floor);
            elevio_motorDirection(DIRN_STOP);
            e->current_floor = e->destination;
            open_door(e);
            remove_order(elevio_floorSensor(), e);  //fjerne bestillinger for denne etasjen

            break;
        }
    }
    e->state = still;
}

void move_down(Elevator *e) {
    int floor = elevio_floorSensor();

    while (floor != e->destination) {
        if (floor != -1) {
            elevio_floorIndicator(floor);
        }
        if (elevio_floorSensor() != -1) {
            e->last_floor = floor;
            
        }
        check_buttons(e);
        check_emergency(e);
        
        for (int f = 0; f < N_FLOORS; f++) {
            floor = elevio_floorSensor();
            if (((e->queue[f][1] == 1) && (floor > f) && (f >= e->destination)) || ((e->queue[f][2] == 1) && (floor > f) && (f >= e->destination))) {
                e->destination = f;
                if (elevio_floorSensor() == f) {
                    elevio_floorIndicator(f);
                    elevio_motorDirection(DIRN_STOP);
                    open_door(e);
                }
            }
        }
        floor = elevio_floorSensor();
        elevio_motorDirection(DIRN_DOWN); 
        if (floor == e->destination) {
            elevio_floorIndicator(floor);
            elevio_motorDirection(DIRN_STOP);
            e->current_floor = e->destination;
            open_door(e);
            remove_order(e->current_floor, e);  //fjerne bestillinger for denne etasje

            break;
        }
    }
    e->state = still;
}
