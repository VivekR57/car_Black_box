#include "main.h"

// External variable tracking the address in EEPROM
extern unsigned char address;
char index = 0; // Variable to keep track of the current log entry being viewed

// Function to view logs stored in EEPROM
// Parameters:
// - key: The key pressed (SW1, SW2, SW4)
// - current_state: Pointer to the current state variable
void viewlog(char key, State *current_state)
{
    // Handle SW2 (Move to the next log entry)
    if (key == SW2)
    {
        if (index < (address / 10) - 1) // Ensure we don't exceed the stored log count
            index++; // Increment the index to view the next log entry
    }

    // Handle SW1 (Move to the previous log entry)
    if (key == SW1)
    {
        if (index > 0) // Ensure we don't go below the first log entry
            index--; // Decrement the index to view the previous log entry
    }

    // Check if there is no data in EEPROM
    if (address == 0)
    {
        clcd_print("No Data found    ", LINE1(0)); // Display "No Data found" on Line 1
        clcd_print("                ", LINE2(0)); // Clear Line 2

        // Wait for some time to allow the user to read the message
        for (unsigned long wait = 500000; wait--;)
            ;

        *current_state = e_menu; // Return to the menu state
        return;
    }

    // Handle SW4 (Return to the menu)
    if (key == SW4)
    {
        CLEAR_DISP_SCREEN;    // Clear the LCD screen
        *current_state = e_menu; // Transition to the menu state
        index = 0;            // Reset the index to the first log entry
        return;
    }

    // Display the log details on the LCD
    clcd_print("# Time     EV SP", LINE1(0)); // Header: Display column labels on Line 1

    // Display the current log index as an entry number
    clcd_putch(index + '0', LINE2(0)); // Convert index to ASCII and print at Line 2, position 0

    // Display the log details from EEPROM (each log entry is 10 bytes)
    clcd_putch(' ', LINE2(1));                              // Add a space for formatting
    clcd_putch(read_eeprom((index * 10)), LINE2(2));        // Hour (tens place)
    clcd_putch(read_eeprom((index * 10) + 1), LINE2(3));    // Hour (units place)
    clcd_putch(':', LINE2(4));                              // Separator
    clcd_putch(read_eeprom((index * 10) + 2), LINE2(5));    // Minute (tens place)
    clcd_putch(read_eeprom((index * 10) + 3), LINE2(6));    // Minute (units place)
    clcd_putch(':', LINE2(7));                              // Separator
    clcd_putch(read_eeprom((index * 10) + 4), LINE2(8));    // Second (tens place)
    clcd_putch(read_eeprom((index * 10) + 5), LINE2(9));    // Second (units place)

    clcd_putch(' ', LINE2(10));                             // Add a space for formatting
    clcd_putch(read_eeprom((index * 10) + 6), LINE2(11));   // Event code (first character)
    clcd_putch(read_eeprom((index * 10) + 7), LINE2(12));   // Event code (second character)

    clcd_putch(' ', LINE2(13));                             // Add a space for formatting
    clcd_putch(read_eeprom((index * 10) + 8), LINE2(14));   // Speed (tens place)
    clcd_putch(read_eeprom((index * 10) + 9), LINE2(15));   // Speed (units place)
}
