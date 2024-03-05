#include "order_boss.h"
#include "state_machine.h"
#include "stop.h"


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
    }
}


void empty_orders(Elevator *e){
    
    for (int f = 0; f < N_FLOORS; f++){
        for (int b = 0; b < N_BUTTONS; b++){
            e->queue[f][b] = 0;
            elevio_buttonLamp(f, b, 0);
        }
        //elevio_floorIndicator(f); kanskje ikke denne?

    
    }
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
            e->state = moving_up; // kan hende dette gir problemer ettersom det er en case i switch??
        }
        check_buttons(e);
        check_emergency(e);
        check_obstruction(e);
        
        for (int f = 0; f < N_FLOORS; f++) {
            if ((e->queue[f][0] == 1) && (e->current_floor < f)) {
                e->destination = f;
            }
        }
        floor = elevio_floorSensor();
        //elevio_motorDirection(DIRN_UP); kanskje v må ha med denne i stedet for mye i main
        if (floor == e->destination) {
            elevio_floorIndicator(floor);
            //elevio_motorDirection(DIRN_STOP);
            e->current_floor = e->destination;
            e->state = still;
            // evt : legge inn funksjonaliteten fra still her.
            remove_order(e->current_floor, e);  //fjerne bestillinger for denne etasjen

            break;
        }
    }
}

void move_down(Elevator *e) {
    int floor = elevio_floorSensor();

    while (floor != e->destination) {
        if (floor != -1) {
            elevio_floorIndicator(floor);
        }
        if (elevio_floorSensor() != -1) {
            e->last_floor = floor;
            e->state = moving_up; // kan hende dette gir problemer ettersom det er en case i switch??
        }
        check_buttons(e);
        check_emergency(e);
        check_obstruction(e);
        
        for (int f = 0; f < N_FLOORS; f++) {
            if ((e->queue[f][0] == 1) && (e->current_floor < f)) {
                e->destination = f;
            }
        }
        floor = elevio_floorSensor();
        //elevio_motorDirection(DIRN_DOWN); evt ha med denne, på samme måte som for move_up

        if (floor == e->destination) {
            elevio_floorIndicator(floor);
            //e->current_floor = e->destination;
            e->current_floor = e->destination;
            e->state = still;
            // evt : legge inn funksjonaliteten fra still her.
            remove_order(e->current_floor, e);  //fjerne bestillinger for denne etasjen
            printf("er knappen slettet? %d", e->queue[e->current_floor][0]); // for å se om bestillng er fjernet

            break;
        }
    }
}
