import ctypes
import sys

KEYEVENTF_KEYDOWN = 0x0000
KEYEVENTF_KEYUP = 0x0002
IME_ON = 0x16
IME_OFF = 0x1A
ESC = 0x1B

def press_vk(vk_code, debug=False):
    ctypes.windll.user32.keybd_event(vk_code, 0, KEYEVENTF_KEYDOWN, 0)
    ctypes.windll.user32.keybd_event(vk_code, 0, KEYEVENTF_KEYUP, 0)
    if debug:
        print(f"pressd: {vk_code}")


def main():
    hex_key_action = None
    is_debug = False
    try:
        arguments = sys.argv[1:]
        if "debug" in arguments:
            is_debug = True
        for argument in arguments:
            if argument == "IME_ON":
                hex_key_action = IME_ON
            elif argument == "IME_OFF":
                hex_key_action = IME_OFF
            elif argument == "ESC":
                hex_key_action = ESC
            else:
                sys.exit(1)

            press_vk(hex_key_action, debug=is_debug)

    except IndexError:
        sys.exit(1)


if __name__ == "__main__":
    main()
    sys.exit(0)