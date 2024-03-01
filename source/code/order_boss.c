#include "order_boss.h"
#include "state_machine.h"


void add_order(int floor, int number, struct Elevator e){
    // up er index 0, down er 1, ab er 2
    e.queue[floor][number] = 1;

    //for å teste på sanntid:
    //printf("\n %d \n", e.queue[floor][order]);

}


void remove_order(int floor, struct Elevator e) {
    //fordi fjerner alle orders fra samme etasje
    for(int b = 0; b < N_BUTTONS; b++){
        e.queue[floor][b] = 1;
    }
}


void empty_orders(struct Elevator e){
    
    for (int i = 0; i < N_FLOORS; i++){
        for (int j = 0; j < N_BUTTONS; j++){
            e.queue[i][j] = 0;
        }
    }
}