#include <windows.h>
#include <iostream>
#include <string>

#define IME_ON  0x16
#define IME_OFF 0x1A
#define ESC     0x1B

void pressVk(WORD vkCode, bool debug = false) {
    INPUT input[2] = {};

    // Key down
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = vkCode;

    // Key up
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = vkCode;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT sent = SendInput(2, input, sizeof(INPUT));

    if (debug) {
        if (sent != 2) {
            std::cerr << "SendInput failed with error: " << GetLastError() << std::endl;
        } else {
            std::cout << "Sent key: 0x" << std::hex << vkCode << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    bool isDebug = false;
    WORD hexKeyAction = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "debug") {
            isDebug = true;
        } else if (arg == "IME_ON") {
            hexKeyAction = IME_ON;
        } else if (arg == "IME_OFF") {
            hexKeyAction = IME_OFF;
        } else if (arg == "ESC") {
            hexKeyAction = ESC;
        } else {
            return 1;
        }
        pressVk(hexKeyAction, isDebug); 
    }

    return 0;
}
