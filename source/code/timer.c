#include "timer.h"
#include "door.h"
#include <time.h>
#include "state_machine.h"


void start_timer(Elevator *e){
    // noe for obstruction, etter hvert:


    time_t start;
    time_t end;
    time(&start);
    time(&end);

    //for å sjekke om tiden for timeren er riktig:
    //printf("%d", difftime(time(&start), time(&end)));

    while (difftime(end, start) < 3.0)
    {
        //legg til noe for obstruction
        time(&end);
        check_buttons(e);
        check_orders(e);

        //legg til noe for obstruction
    }
    
    //lukker dør:
    elevio_doorOpenLamp(0);
}

//funksjon for obstruction