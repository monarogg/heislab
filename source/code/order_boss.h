#pragma once
#include "../driver/elevio.h"
#include "state_machine.h"



typedef enum {
    order_up = 1,
    order_down = -1,
    order_all = 2,
} Orders;

void add_order(Orders order, struct Elevator e);

void remove_order(Orders order, struct Elevator e);
void empty_orders(struct Elevator e); 
//tømmer hele listen
