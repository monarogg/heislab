#include "location.h"


void compare_floors(Elevator *e){
        if (e->last_floor < e->destination){
            e->state = moving_up;
        }
        if (e->last_floor > e->destination){
            e->state = moving_down;
        }
}

