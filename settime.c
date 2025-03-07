#include "main.h"

// External variables
extern char time[9]; // Stores the current time in HH:MM:SS format as a string
unsigned char hour, min, sec; // Variables to hold the hour, minute, and second
unsigned char flag = 0;       // Flag to indicate initialization
unsigned char field = 0;      // Field selection: 0 for hour, 1 for minute, 2 for second
unsigned long delay;          // Variable for managing delay

// Function to set the time
// Parameters:
// - key: Input key for user interaction
// - current_state: Pointer to the current state variable
void settime(char key, State *current_state)
{
    // Initialize time variables from the external `time` string
    if (flag == 0)
    {
        hour = time[0] - '0';
        hour = hour * 10 + time[1] - '0'; // Convert string HH to integer
        min = time[3] - '0';
        min = min * 10 + time[4] - '0';   // Convert string MM to integer
        sec = time[6] - '0';
        sec = sec * 10 + time[7] - '0';   // Convert string SS to integer
        flag = 1;                         // Mark initialization complete
    }

    // Handle SW1 key: Increment the selected field
    if (key == SW1)
    {
        if (field == 0) // Increment hour, wrap around at 24
        {
            if (hour++ == 23)
            {
                hour = 0;
            }
        }
        if (field == 1) // Increment minute, wrap around at 60
        {
            if (min++ == 59)
            {
                min = 0;
            }
        }
        if (field == 2) // Increment second, wrap around at 60
        {
            if (sec++ == 59)
            {
                sec = 0;
            }
        }
    }

    // Handle SW2 key: Move to the next field
    if (key == SW2)
    {
        if (field++ == 2)
        {
            field = 0; // Cycle back to the first field
        }
    }

    // Handle SW4 key: Save the time to RTC and return to menu
    if (key == SW4)
    {
        // Convert hour, minute, and second to BCD format and write to RTC
        hour = ((hour / 10) << 4) | (hour % 10);
        write_ds1307(HOUR_ADDR, hour);

        min = ((min / 10) << 4) | (min % 10);
        write_ds1307(MIN_ADDR, min);

        sec = ((sec / 10) << 4) | (sec % 10);
        write_ds1307(SEC_ADDR, sec);

        // Reset flag and return to menu state
        *current_state = e_menu;
        flag = 0;
        return;
    }

    // Handle SW5 key: Cancel and return to menu without saving
    if (key == SW5)
    {
        *current_state = e_menu;
        flag = 0;
        return;
    }

    // Display the time being set
    clcd_print(" HH:MM:SS ", LINE1(0));
    if (delay++ < 500)
    {
        // Show all fields
        clcd_putch(' ', LINE2(0));
        clcd_putch('0' + hour / 10, LINE2(1));
        clcd_putch('0' + hour % 10, LINE2(2));
        clcd_putch(':', LINE2(3));
        clcd_putch('0' + min / 10, LINE2(4));
        clcd_putch('0' + min % 10, LINE2(5));
        clcd_putch(':', LINE2(6));
        clcd_putch('0' + sec / 10, LINE2(7));
        clcd_putch('0' + sec % 10, LINE2(8));
    }
    else
    {
        // Blink the selected field for user feedback
        if (field == 0) // Blink hour
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch(' ', LINE2(1));
            clcd_putch(' ', LINE2(2));
            clcd_putch(':', LINE2(3));
            clcd_putch('0' + min / 10, LINE2(4));
            clcd_putch('0' + min % 10, LINE2(5));
            clcd_putch(':', LINE2(6));
            clcd_putch('0' + sec / 10, LINE2(7));
            clcd_putch('0' + sec % 10, LINE2(8));
        }
        else if (field == 1) // Blink minute
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch('0' + hour / 10, LINE2(1));
            clcd_putch('0' + hour % 10, LINE2(2));
            clcd_putch(':', LINE2(3));
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
            clcd_putch(':', LINE2(6));
            clcd_putch('0' + sec / 10, LINE2(7));
            clcd_putch('0' + sec % 10, LINE2(8));
        }
        else if (field == 2) // Blink second
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch('0' + hour / 10, LINE2(1));
            clcd_putch('0' + hour % 10, LINE2(2));
            clcd_putch(':', LINE2(3));
            clcd_putch('0' + min / 10, LINE2(4));
            clcd_putch('0' + min % 10, LINE2(5));
            clcd_putch(':', LINE2(6));
            clcd_putch(' ', LINE2(7));
            clcd_putch(' ', LINE2(8));
        }
    }

    // Reset delay counter after completing the cycle
    if (delay == 1000)
    {
        delay = 0;
    }
}
