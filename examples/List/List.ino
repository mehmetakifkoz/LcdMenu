/*
 Menu Item List

 https://lcdmenu.forntoh.dev/examples/string-list

*/

#include <ItemList.h>
#include <LcdMenu.h>
#include <utils/commandProccesors.h>

#define LCD_ROWS 2
#define LCD_COLS 16

// Configure keyboard keys (ASCII)
#define UP 56        // NUMPAD 8
#define DOWN 50      // NUMPAD 2
#define LEFT 52      // NUMPAD 4
#define RIGHT 54     // NUMPAD 6
#define ENTER 53     // NUMPAD 5
#define BACK 55      // NUMPAD 7

// Declare the callbacks
void colorsCallback(uint16_t pos);
void numsCallback(uint16_t pos);

// Declare the array
extern String colors[];
// Initialize the array
String colors[] = {"Red",  "Green",  "Blue",   "Orange",
                   "Aqua", "Yellow", "Purple", "Pink"};

// Declare the array
extern String nums[];
// Initialize the array
String nums[] = {
    "5", "7", "9", "12", "32",
};

// Initialize the main menu items
MAIN_MENU(
    ITEM_BASIC("List demo"),
    ITEM_STRING_LIST("Col", colors, 8, colorsCallback),
    ITEM_STRING_LIST("Num", nums, 5, numsCallback),
    ITEM_BASIC("Example")
);

// Construct the LcdMenu
LcdMenu menu(LCD_ROWS, LCD_COLS);

void setup() {
    Serial.begin(9600);
    // Initialize LcdMenu with the menu items
    menu.setupLcdWithMenu(0x27, mainMenu);
}

void loop() {
    if (!Serial.available()) return;
    char command = Serial.read();

    processMenuCommand(menu, command, UP, DOWN, ENTER, BACK, LEFT, RIGHT);
}

// Define the callbacks
void colorsCallback(uint16_t pos) {
    // do something with the index
    Serial.println(colors[pos]);
}

void numsCallback(uint16_t pos) {
    // do something with the index
    Serial.println(nums[pos]);
}
