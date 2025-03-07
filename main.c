/*
 * DOCUMENTATION SECTION
 * NAME : VIVEK R
 * DATE : 22/01/25
 * DESCRIPTION : Car Black Box Project Using PIC18F4580
 */

#include "main.h"

// Variables to store clock data and formatted time string
unsigned char clock_reg[3]; // Array to hold hour, minute, and second values from RTC
char time[9];               // Formatted time string (HH:MM:SS\0)
unsigned char hour, min, sec; // Individual time components (optional, but unused here)

// Function to initialize hardware and peripherals
static void init_config(void)
{
    init_clcd();    // Initialize character LCD
    init_adc();     // Initialize ADC for analog sensors
    init_mkp();     // Initialize matrix keypad
    init_uart();    // Initialize UART for serial communication
    init_i2c();     // Initialize I2C communication
    init_ds1307();  // Initialize RTC (DS1307)
}

// Main function of the program
void main(void)
{
    init_config(); // Initialize all configurations
    unsigned char key; // Variable to store key press input
    State current_state = e_Dashboard; // Starting state is Dashboard

    while (1) // Infinite loop
    {
        get_time(); // Update the time from RTC
        key = read_matrix_keypad(STATE); // Read the key press

        // State machine handling based on the current state
        if (current_state == e_Dashboard)
        {
            Dashboard(key, &current_state); // Handle Dashboard state
        }
        else if (current_state == e_menu)
        {
            menu(key, &current_state); // Handle Menu state
        }
        else if (current_state == e_viewlog)
        {
            viewlog(key, &current_state); // Handle View Log state
        }
        else if (current_state == e_downloadlog)
        {
            downloadlog(&current_state); // Handle Download Log state
        }
        else if (current_state == e_clearlog)
        {
            clearlog(&current_state); // Handle Clear Log state
        }
        else if (current_state == e_settime)
        {
            settime(key, &current_state); // Handle Set Time state
        }
    }

    return; // This line is unreachable, but ensures proper function termination
}

// Function to get time from the RTC (DS1307) and format it as HH:MM:SS
static void get_time(void)
{
    // Read hours, minutes, and seconds from RTC
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    // Format hours based on 12/24-hour mode
    if (clock_reg[0] & 0x40) // 12-hour mode
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01); // Tens place
        time[1] = '0' + (clock_reg[0] & 0x0F);        // Units place
    }
    else // 24-hour mode
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03); // Tens place
        time[1] = '0' + (clock_reg[0] & 0x0F);        // Units place
    }

    // Format minutes
    time[2] = ':';                                    // Separator
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);     // Tens place
    time[4] = '0' + (clock_reg[1] & 0x0F);           // Units place

    // Format seconds
    time[5] = ':';                                    // Separator
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);     // Tens place
    time[7] = '0' + (clock_reg[2] & 0x0F);           // Units place

    time[8] = '\0'; // Null-terminate the string
}
