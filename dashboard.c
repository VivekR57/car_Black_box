#include "main.h"

// Global variable to keep track of the EEPROM address for storing data
unsigned char address = 0;

// External time variable, formatted as HH:MM:SS
extern char time[9];

// Function to store data into EEPROM
// Parameters:
// - time: Current time as a string
// - speed: Current speed as a single-byte value
// - ev: Event matrix, where each row contains a 2-character event code
// - row: Index of the event in the event matrix
void store_eeprom(char *time, char speed, char ev[][3], char row)
{
    char arr[10]; // Temporary array to hold data to be written to EEPROM

    // If EEPROM is full (address exceeds 90), shift older entries to make room
    if (address > 90)
    {
        for (address = 0; address < 90; address++)
        {
            write_eeprom(address, (read_eeprom(address + 10))); // Shift entries up by 10 bytes
        }
    }

    // Format data into the array
    arr[0] = time[0]; // Hour (tens place)
    arr[1] = time[1]; // Hour (units place)
    arr[2] = time[3]; // Minute (tens place)
    arr[3] = time[4]; // Minute (units place)
    arr[4] = time[6]; // Second (tens place)
    arr[5] = time[7]; // Second (units place)
    arr[6] = ev[row][0]; // First character of the event
    arr[7] = ev[row][1]; // Second character of the event
    arr[8] = speed / 10 + '0'; // Speed tens place as ASCII character
    arr[9] = speed % 10 + '0'; // Speed units place as ASCII character

    // Write the formatted data into EEPROM
    for (int i = 0; i < 10; i++)
    {
        write_eeprom(address + i, arr[i]);
    }

    // Update the address for the next entry
    address = address + 10;
}

// Function to handle the Dashboard state
// Parameters:
// - key: The key pressed (SW1, SW2, SW3, SW4)
// - current_state: Pointer to the current state variable
void Dashboard(char key, State *current_state)
{
    unsigned short adc_reg_val; // ADC value for the speed sensor
    char speed;                 // Current speed value
    char speed_str[3];          // Speed string for display
    char ev[9][3] = {"ON", "GR", "GN", "G1", "G2", "G3", "G4", "G5", "CO"}; // Event matrix
    static char row = 0;        // Current event row (persistent across function calls)

    // Read ADC value from speed sensor
    adc_reg_val = read_adc(CHANNEL4);

    // Convert ADC value to speed (scale factor of 10.33 assumed)
    speed = (adc_reg_val / 10.33);

    // Event-specific actions based on the key pressed
    if (row == 8) // Special case for event "CO"
    {
        if (key == SW1 || key == SW2)
        {
            row = 2; // Reset to "GN" (Green)
            store_eeprom(time, speed, ev, row); // Store data in EEPROM
        }
    }
    else if (key == SW1) // Increase event row (if possible)
    {
        if (row <= 6) // Ensure the row does not exceed the limit
        {
            row++;
        }
        store_eeprom(time, speed, ev, row); // Store data in EEPROM
    }
    else if (key == SW2) // Decrease event row (if possible)
    {
        if (row > 1) // Ensure the row does not go below the minimum
        {
            row--;
        }
        store_eeprom(time, speed, ev, row); // Store data in EEPROM
    }
    else if (key == SW3) // Set event to "CO" (critical)
    {
        row = 8;
        store_eeprom(time, speed, ev, row); // Store data in EEPROM
    }
    else if (key == SW4) // Transition to the menu state
    {
        *current_state = e_menu; // Change the state to menu
        CLEAR_DISP_SCREEN;       // Clear the LCD screen
        return;                  // Exit the function
    }

    // Convert speed value to string for display
    speed_str[0] = (speed / 10) + '0'; // Tens place
    speed_str[1] = (speed % 10) + '0'; // Units place
    speed_str[2] = '\0';               // Null-terminate the string

    // Display data on the LCD
    clcd_print("Time      EV  SP", LINE1(0)); // Header
    clcd_print(time, LINE2(0));              // Current time
    clcd_print(speed_str, LINE2(14));        // Speed
    clcd_print(ev[row], LINE2(10));          // Event
}
