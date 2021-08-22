#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
using namespace std;


void readKeystrokes();                          // Function that reads keystrokes from file
void keydown(int keyCode, int sleepTime);       // Function that presses a specific key
void keyup(int keyCode, int sleepTime);         // Function that releases a specific key
void focusWebPage();                            // Function that focuses the webpage where your input field is

void main()
{
    focusWebPage();         // Set mouse cursor position to input field
    readKeystrokes();       // Read keystrokes that from a file and enter them
}

void focusWebPage() {       // Need to place cursor on input field before typing
    SetCursorPos(400, 1050);        // Set cursor position of webbrowser in taskbar     ( this is the same as alt-tabbing to the webpage)
                                    // Change variables as needed, first x coordinates then y
                                    // 400, 1050 for my pc
                                    // 280, 1000 for my laptop

    // Simulate a mouse click
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);  
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

    Sleep(500);     // Wait half a second to make sure the mouse click has gone through

    SetCursorPos(625, 255);         // Set cursor position of the input field
                                    // Change variables as needed, first x coordinates then y

    // Simulate a mouse click
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

    // Now input field should be clicked and highlighted, and program is ready to begin typing
}

void readKeystrokes() {         // Go through a file and run all keystrokes

    Sleep(3000);                // Wait 3 seconds, mostly just to make sure that the cursor is positioned correctly
    ifstream myFile;
    myFile.open("C:/Full/Path/Of/File");     // File to read from
    // CHANGE ME ^^^^^^^^^^

    /*
    The format of the file should be:
    user_id     session      repetition      typeOfKey:keyCode:timeSinceLastKey,typeOfKey:keyCode:timeSinceLastKey,typeOfKey:keyCode:timeSinceLastKey,............
    e.g.,
    1           1            1               0:190:0,1:190:149,0:84:249,1:84:107,0:73:61,1:73:117,0:69:104,................. 
    1   	    1	         2	             0:190:0,1:190:111,0:84:234,1:84:69,0:73:59,1:73:91,0:69:45,1:69:83,.................
    1	        1	         3	             0:190:0,1:190:133,0:84:74,1:84:73,0:73:56,1:73:82,0:69:72,1:69:81,.............
    1	        1	         4	             0:190:0,1:190:129,0:84:122,1:84:106,0:73:144,1:73:104,0:69:100,1:69:90,..............
    .
    .
    .
    .
    3	        5	         38	             0:190:0,0:84:142,1:190:20,0:73:68,1:84:25,0:69:152,1:73:1,1:69:50,.............
    3	        5	         39	             0:190:0,0:84:85,1:190:91,0:73:39,1:84:1,1:73:147,0:69:321,..............
    3	        5	         40          	 0:190:0,0:84:129,0:73:35,1:190:43,1:84:36,1:73:38,0:69:21,..............
    3	        5	         41          	 0:190:0,0:84:161,0:73:76,1:190:43,1:84:19,1:73:47,0:69:142,..................

    timeSinceLastKey is in MS
    user_id, session and repetition does not need to be INT

    IF your code does not have user_id, session and or repetition, then remove/comment lines 79-81 depending on what is missing
    */

    string line;
    int key, time, type, session, repetition;

    if (myFile.is_open()) {                                 // Check if file exist
        while (getline(myFile, line)) {                     // Go through all rows
            istringstream myline(line);
            string csvItem;
            getline(myline, csvItem, '\t');                 // Get user id and discard it, we dont use it
            getline(myline, csvItem, '\t');                 // Get session ID and discard it
            getline(myline, csvItem, '\t');                 // Get repetition ID and discard it
            while (getline(myline, csvItem, ',')) {         // Go through all keys, both press and release
                istringstream secondline(csvItem);
                string item;
                int counter = 1;                            // Counter that specifies what item we are grabbing
                while (getline(secondline, item, ':')) {    // Go through all information for each key press/release
                    if (counter == 1) {                     // If counter == 1, means we are grabbing the type, i.e. either key press or key release
                        // type of key
                        type = stoi(item);                  // Is either 1 or 0, 0 = keypress and 1 = keyrelease
                    }
                    else if (counter == 2) {                // If counter == 2, means we are grabbing the keycode of the key
                        key = stoi(item);                   // Convert string to int, int can actually be used as keycode
                        // lol this is fine, dont need to convert this into anything else, perhaps UINT instead of int tho
                        // https://stackoverflow.com/questions/30083750/how-to-print-press-using-keybd-event-function
                        // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput
                        // https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
                        // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-mapvirtualkeya?redirectedfrom=MSDN


                        // At least this is fine for passwords where we KNOW the keys that are always going to be entered
                        // Might find some issues when doing it for continous authentication, where we might not neccessarily know what a user is typing
                        // e.g. some special keys might cause issues
                    }
                    else {
                        time = stoi(item);                  // If counter == 3, means we are grabbing the time in ms to next key press/release
                    }
                    counter++;
                }
                if (type == 0) {                // If type is 0, it means a keypress
                    keydown(key, time);         // Simulate a keypress
                }
                else {
                    // keyup                    // Otherwise, means keyrelease
                    keyup(key, time);           // Simulate a keyrelease
                }
            }
        }
    }
}

// Function to simulate a key press
void keydown(int keyCode, int sleepTime) {
    INPUT input;
    input.type = INPUT_KEYBOARD;            // Define input type

    input.ki.wVk = keyCode;                 // Define what key is to be pressed
    input.ki.dwFlags = 0;                   // No special flags, time or extra info
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    if (sleepTime != 0) {                   // No need to sleep if time since previous key is 0
        Sleep(sleepTime);                   // This simulate the "waiting" time between keystrokes
                                            // Sleep is not the best option to use as it is not the most accurate wait function
                                            // Other options could be using e.g. windows multimedia timers
                                            // Also, windows resolution timer is around 16 ms, meaning we will sometimes get extra delay added to the sleep function
                                            // A possible way to go around this is to lower the resolution timer using timeBeginPeriod() function in windows
                                            // https://docs.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timebeginperiod 
    }
    SendInput(1, &input, sizeof(INPUT));    // Simulate a keypress using SendInput, the 1 is the amount of keys to be pressed (just one in this instance)
}

void keyup(int keyCode, int sleepTime) {    // Simulate key release
    INPUT input;
    input.type = INPUT_KEYBOARD;            // Define input type

    input.ki.wVk = keyCode;                 // Define what key is to be released
    input.ki.dwFlags = KEYEVENTF_KEYUP;     // Define that this is to be a key release
    input.ki.time = 0;                      // No special time or extra info
    input.ki.dwExtraInfo = 0;

    if (sleepTime != 0) {                   // No need to wait if time since previous key is 0
        Sleep(sleepTime);
    }
    SendInput(1, &input, sizeof(INPUT));    // Simulate key release
}
