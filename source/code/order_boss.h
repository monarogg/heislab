#pragma once
#include "../driver/elevio.h"
#include "state_machine.h"


//litt usikker på om vi trenger denne???
typedef enum {
    order_up = 1,
    order_down = -1,
    order_all = 2,
} Orders;

void add_order(int floor, int numbers, struct Elevator e);

void remove_order(int floor, struct Elevator e);

void empty_orders(struct Elevator e); 
//tømmer hele listen
