#pragma once
#include "../driver/elevio.h"
#include "state_machine.h"


//litt usikker på om vi trenger denne???
typedef enum {
    order_up = 1,
    order_down = -1,
    order_all = 2,
} Orders;

void add_order(int floor, int numbers, Elevator *e);

void remove_order(int floor, Elevator *e);

void empty_orders(Elevator *e); 
//tømmer hele listen

void check_buttons(Elevator *e);

void check_orders(Elevator *e);