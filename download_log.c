#include "main.h"

// External variable tracking the EEPROM address
extern unsigned char address;

// Function to download and display logs from EEPROM over UART
// Parameters:
// - current_state: Pointer to the current state variable
void downloadlog(State *current_state)
{
    static unsigned char index = 0; // Index to track the current log entry being downloaded
    char arr[20];                   // Buffer to store a formatted log entry for transmission

    // Print the header for log data to UART
    puts("# Time     EV SP \n\r");

    // Loop through all stored log entries in EEPROM
    while (index < (address / 10))
    {
        // Format the log entry
        arr[0] = index + '0';                        // Log entry number
        arr[1] = ' ';                                // Separator
        arr[2] = read_eeprom((index * 10));          // Hour (tens place)
        arr[3] = read_eeprom((index * 10) + 1);      // Hour (units place)
        arr[4] = ':';                                // Time separator
        arr[5] = read_eeprom((index * 10) + 2);      // Minute (tens place)
        arr[6] = read_eeprom((index * 10) + 3);      // Minute (units place)
        arr[7] = ':';                                // Time separator
        arr[8] = read_eeprom((index * 10) + 4);      // Second (tens place)
        arr[9] = read_eeprom((index * 10) + 5);      // Second (units place)
        arr[10] = ' ';                               // Separator
        arr[11] = read_eeprom((index * 10) + 6);     // Event code (first character)
        arr[12] = read_eeprom((index * 10) + 7);     // Event code (second character)
        arr[13] = ' ';                               // Separator
        arr[14] = read_eeprom((index * 10) + 8);     // Speed (tens place)
        arr[15] = read_eeprom((index * 10) + 9);     // Speed (units place)
        arr[16] = '\n';                              // Newline for UART display
        arr[17] = '\r';                              // Carriage return for UART display
        arr[18] = '\0';                              // Null terminator to mark the end of the string

        // Send the formatted log entry via UART
        puts(arr);

        // Move to the next log entry
        index++;
    }

    // Small delay to ensure proper transmission and allow user to view logs
    for (unsigned long wait = 500000; wait--;);

    // Transition back to the menu state
    *current_state = e_menu;

    // Reset the log index for future downloads
    index = 0;

    return;
}
