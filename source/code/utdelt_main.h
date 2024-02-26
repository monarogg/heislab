/*
INNI WHILE-LOOPEN:

    // oppretter en variabel med nåværende etasje
        int floor = elevio_floorSensor();
    
    // hvis heisen er i 1.etasje, kjør opp
        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

    // hvis heisen er i 4.etasje kjør ned
        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }

    // sender inn kombinasjon av hver button og etasje og sjekker om knapp er trykket - sjekker "tabellen"
    // skrur på lyset i gjeldende etasje der knapp evt er trykket inn - på heispanel
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

    // dersom obstruction slås på - stoplyset skrus på
    // hvis ikke skal stopplampen være av
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
    // dersom stoppknappen trykkes skal motoren stoppe - while loopen stoppes
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    
    // venter bittelitt før den kjører løkken igjen
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);

*/