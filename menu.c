#include "main.h"

// Function to handle the Menu state
// Parameters:
// - key: The key pressed (SW1, SW2, SW4, SW5)
// - current_state: Pointer to the current state variable
void menu(char key, State *current_state)
{
    // Array holding the menu options, each 16 characters long
    static char menu[][16] = {"View_log    ", "Download_log", "Clear_log", "Set_time"};
    static char m_ind = 0;  // Menu index to track the current highlighted option
    static char s_flag = 0; // Selection flag to track the highlighted row (0 for Line 1, 1 for Line 2)

    // Handle SW1 (Move Up or Toggle Selection)
    if (key == SW1)
    {
        if (m_ind > 0 && s_flag == 0) // Move to the previous menu item if on Line 1
        {
            m_ind--;          // Decrement the menu index
            CLEAR_DISP_SCREEN; // Clear the LCD screen
        }
        if (s_flag == 1) // If on Line 2, toggle to Line 1
        {
            s_flag = 0; // Set flag to indicate Line 1
        }
    }

    // Handle SW2 (Move Down or Toggle Selection)
    if (key == SW2)
    {
        if (m_ind < 2 && s_flag == 1) // Move to the next menu item if on Line 2
        {
            m_ind++;          // Increment the menu index
            CLEAR_DISP_SCREEN; // Clear the LCD screen
        }
        if (s_flag == 0) // If on Line 1, toggle to Line 2
        {
            s_flag = 1; // Set flag to indicate Line 2
        }
    }

    // Handle SW4 (Select the current menu option)
    if (key == SW4)
    {
        if (s_flag == 0) // If selecting the option in Line 1
        {
            if (m_ind == 0) // View Log option
            {
                *current_state = e_viewlog; // Transition to View Log state
                CLEAR_DISP_SCREEN;          // Clear the LCD screen
                return;
            }
            else if (m_ind == 1) // Download Log option
            {
                *current_state = e_downloadlog; // Transition to Download Log state
                CLEAR_DISP_SCREEN;
                return;
            }
            else if (m_ind == 2) // Clear Log option
            {
                *current_state = e_clearlog; // Transition to Clear Log state
                CLEAR_DISP_SCREEN;
                return;
            }
        }
        else // If selecting the option in Line 2
        {
            if (m_ind + 1 == 1) // Download Log option
            {
                *current_state = e_downloadlog; // Transition to Download Log state
                CLEAR_DISP_SCREEN;
                return;
            }
            else if (m_ind + 1 == 2) // Clear Log option
            {
                *current_state = e_clearlog; // Transition to Clear Log state
                CLEAR_DISP_SCREEN;
                return;
            }
            else if (m_ind + 1 == 3) // Set Time option
            {
                *current_state = e_settime; // Transition to Set Time state
                CLEAR_DISP_SCREEN;
                return;
            }
        }
    }

    // Handle SW5 (Return to Dashboard)
    if (key == SW5)
    {
        CLEAR_DISP_SCREEN;    // Clear the LCD screen
        m_ind = 0;            // Reset the menu index to the first option
        s_flag = 0;           // Reset the selection flag to Line 1
        *current_state = e_Dashboard; // Transition to the Dashboard state
        return;
    }

    // Highlight the current selection using '*' on the appropriate line
    if (s_flag == 0) // Highlight Line 1
    {
        clcd_putch('*', LINE1(0)); // Place '*' at the start of Line 1
        clcd_putch(' ', LINE2(0)); // Clear the start of Line 2
    }
    else // Highlight Line 2
    {
        clcd_putch(' ', LINE1(0)); // Clear the start of Line 1
        clcd_putch('*', LINE2(0)); // Place '*' at the start of Line 2
    }

    // Display the menu options on the LCD
    clcd_print(menu[m_ind], LINE1(1));      // Print the current option on Line 1
    clcd_print(menu[m_ind + 1], LINE2(1)); // Print the next option on Line 2
}
