#ifndef MENU_GENERATOR_H
#define MENU_GENERATOR_H

#include <MenuItem.h>

uint8_t index = 0;

MenuItem* creatMenu(uint8_t size, MenuItem* parent) {
    MenuItem* menu = new MenuItem[size + 2];
    menu[0] = parent != NULL ? ItemHeader(parent) : ItemHeader();
    menu[size + 1] = ItemFooter();
    return menu;
}

char* readLine(char* file) {
    uint8_t i = 0;
    bool EOL = false;
    static char line[30];

    while (!EOL) {
        char c = file[index];
        switch (c) {
            case '\0':
                return NULL;
            case '\n':
                line[i] = 0;
                i = 0;
                EOL = true;
                break;
            default:
                line[i] = c;
                i++;
                break;
        }
        index++;
    }
    return line;
}

MenuItem* generateMenu(char* input) {
    uint8_t step = 0;
    uint8_t prevPos = 0;
    uint8_t maxSize = 0;

    MenuItem* currMenu;

    char* line;
    while ((line = readLine(input)) != NULL) {
        uint8_t pos = line[0] - '0';
        uint8_t size = line[1] - '0';
        uint8_t i = line[2] - '0';
        uint8_t type = line[3] - '0';

        uint8_t n = 5;
        while (line[n] != '\0') n++;

        char* name = new char[n - 3];
        sprintf(name, line + 4);

        if (type == 0) {
            maxSize = size;
            currMenu = creatMenu(size, NULL);
        } else if (type == MENU_ITEM_SUB_MENU) {
            prevPos = pos + 1;

            if (i == 1)
                currMenu[step][prevPos] =
                    ItemSubMenu(name, creatMenu(size, currMenu));
            else
                currMenu[pos + 1] =
                    ItemSubMenu(name, creatMenu(size, currMenu));
        } else {
            if (pos == 0) ++step;

            step = step > maxSize ? step - 1 : step;

            if (i == 2)
                currMenu[step - 1][prevPos][pos + 1] = MenuItem(name);
            else
                currMenu[step][pos + 1] = MenuItem(name);
        }

        // Serial.print(pos, DEC);
        // Serial.print(' ');
        // Serial.print(size, DEC);
        // Serial.print(' ');
        // Serial.print(i, DEC);
        // Serial.print(' ');
        // Serial.print(type, DEC);
        // Serial.print(F(" | "));
        // Serial.print(prevPos, DEC);
        // Serial.print(' ');
        // Serial.println(step, DEC);
    }
    index = 0;
    return currMenu;
}

#endif