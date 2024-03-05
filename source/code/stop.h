#pragma once
#include "../driver/elevio.h"
#include "state_machine.h"
#include "lights.h"
#include "order_boss.h"
#include "location.h"


void check_emergency(Elevator *e);

void check_obstruction(Elevator *e);