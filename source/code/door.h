#pragma once
#include "../driver/elevio.h"
#include "state_machine.h"

void open_door(struct Elevator e);
//gir beskjed til state_machine - endre state til door_open
void close_door(struct Elevator e);
//gir beskjed til state_machine - endre state til door_closed?