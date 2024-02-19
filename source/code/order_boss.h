#include "../driver/elevio.h"


// bestillinger er av typen buttontype. altså enten 0, 1 eller 2 

// orders er en liste? eller array eller noe av order av typen buttontype

void add_order(ButtonType order);
// egt være av typen bestilling,men har ikke lagd enda.

void remove_order(ButtonType order);
void empty_orders(); 
//tømmer hele listen
