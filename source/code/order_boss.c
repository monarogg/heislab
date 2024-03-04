#include "order_boss.h"
#include "state_machine.h"
#include "lights.h"
#include "location.h"


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
    
    for (int i = 0; i < N_FLOORS; i++){
        for (int j = 0; j < N_BUTTONS; j++){
            e->queue[i][j] = 0;
        }
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
                    remove_order(f, e);
                    light_off(f);
                    break;
                }
            }
        }
    }
}