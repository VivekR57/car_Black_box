#include "main.h"

// External variables used in the function
extern unsigned char address; // Tracks the current EEPROM address
extern char index;            // Tracks the current log index

// Function to clear all log entries stored in EEPROM
// Parameters:
// - current_state: Pointer to the current state variable
void clearlog(State *current_state)
{
    // Display a message indicating that the logs have been cleared
    clcd_print("clear success   ", LINE1(0)); // Display "clear success" on line 1 of the LCD
    clcd_print("                ", LINE2(0)); // Clear line 2 of the LCD

    // Small delay to allow the user to read the message
    for (unsigned long wait = 500000; wait--;);
    address = 0;
    index = 0;

    // Transition back to the menu state
    *current_state = e_menu;

    return; // Exit the function
}
