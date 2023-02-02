#include "keyboard.h"
#include "screen.h"

void print_scancode(SCANCODE scancode) {
    SCANCODE charcode = scancode;
    if (scancode > 0x80) {
        charcode -= 0x80;
    }
    switch (charcode) {
        case 0x01: print_string("esc ", WHITE_ON_BLACK); break;
        case 0x02: print_string("1   ", WHITE_ON_BLACK); break;
        case 0x03: print_string("2   ", WHITE_ON_BLACK); break;
        case 0x04: print_string("3   ", WHITE_ON_BLACK); break;
        case 0x05: print_string("4   ", WHITE_ON_BLACK); break;
        case 0x06: print_string("5   ", WHITE_ON_BLACK); break;
        case 0x07: print_string("6   ", WHITE_ON_BLACK); break;
        case 0x08: print_string("7   ", WHITE_ON_BLACK); break;
        case 0x09: print_string("8   ", WHITE_ON_BLACK); break;
        case 0x0a: print_string("9   ", WHITE_ON_BLACK); break;
        case 0x0b: print_string("0   ", WHITE_ON_BLACK); break;
        case 0x0c: print_string("-   ", WHITE_ON_BLACK); break;
        case 0x0d: print_string("=   ", WHITE_ON_BLACK); break;
        case 0x0e: print_string("bs  ", WHITE_ON_BLACK); break;
        case 0x0f: print_string("tab ", WHITE_ON_BLACK); break;
        case 0x10: print_string("q   ", WHITE_ON_BLACK); break;
        case 0x11: print_string("w   ", WHITE_ON_BLACK); break;
        case 0x12: print_string("e   ", WHITE_ON_BLACK); break;
        case 0x13: print_string("r   ", WHITE_ON_BLACK); break;
        case 0x14: print_string("t   ", WHITE_ON_BLACK); break;
        case 0x15: print_string("y   ", WHITE_ON_BLACK); break;
        case 0x16: print_string("u   ", WHITE_ON_BLACK); break;
        case 0x17: print_string("i   ", WHITE_ON_BLACK); break;
        case 0x18: print_string("o   ", WHITE_ON_BLACK); break;
        case 0x19: print_string("p   ", WHITE_ON_BLACK); break;
        case 0x1a: print_string("[   ", WHITE_ON_BLACK); break;
        case 0x1b: print_string("]   ", WHITE_ON_BLACK); break;
        case 0x1c: print_string("ent ", WHITE_ON_BLACK); break;
        case 0x1d: print_string("lct ", WHITE_ON_BLACK); break;
        case 0x1e: print_string("a   ", WHITE_ON_BLACK); break;
        case 0x1f: print_string("s   ", WHITE_ON_BLACK); break;
        case 0x20: print_string("d   ", WHITE_ON_BLACK); break;
        case 0x21: print_string("f   ", WHITE_ON_BLACK); break;
        case 0x22: print_string("g   ", WHITE_ON_BLACK); break;
        case 0x23: print_string("h   ", WHITE_ON_BLACK); break;
        case 0x24: print_string("j   ", WHITE_ON_BLACK); break;
        case 0x25: print_string("k   ", WHITE_ON_BLACK); break;
        case 0x26: print_string("l   ", WHITE_ON_BLACK); break;
        case 0x27: print_string(";   ", WHITE_ON_BLACK); break;
        case 0x28: print_string("'   ", WHITE_ON_BLACK); break;
        case 0x29: print_string("`   ", WHITE_ON_BLACK); break;
        case 0x2a: print_string("lsh ", WHITE_ON_BLACK); break;
        case 0x2b: print_string("\\  ", WHITE_ON_BLACK); break;
        case 0x2c: print_string("z   ", WHITE_ON_BLACK); break;
        case 0x2d: print_string("x   ", WHITE_ON_BLACK); break;
        case 0x2e: print_string("c   ", WHITE_ON_BLACK); break;
        case 0x2f: print_string("v   ", WHITE_ON_BLACK); break;
        case 0x30: print_string("b   ", WHITE_ON_BLACK); break;
        case 0x31: print_string("n   ", WHITE_ON_BLACK); break;
        case 0x32: print_string("m   ", WHITE_ON_BLACK); break;
        case 0x33: print_string(",   ", WHITE_ON_BLACK); break;
        case 0x34: print_string(".   ", WHITE_ON_BLACK); break;
        case 0x35: print_string("/   ", WHITE_ON_BLACK); break;
        case 0x36: print_string("rsh ", WHITE_ON_BLACK); break;
        case 0x37: print_string("k*  ", WHITE_ON_BLACK); break;
        case 0x38: print_string("lat ", WHITE_ON_BLACK); break;
        case 0x39: print_string("spc ", WHITE_ON_BLACK); break;
        case 0x3a: print_string("cpl ", WHITE_ON_BLACK); break;
        case 0x3b: print_string("f1  ", WHITE_ON_BLACK); break;
        case 0x3c: print_string("f2  ", WHITE_ON_BLACK); break;
        case 0x3d: print_string("f3  ", WHITE_ON_BLACK); break;
        case 0x3e: print_string("f4  ", WHITE_ON_BLACK); break;
        case 0x3f: print_string("f5  ", WHITE_ON_BLACK); break;
        case 0x40: print_string("f6  ", WHITE_ON_BLACK); break;
        case 0x41: print_string("f7  ", WHITE_ON_BLACK); break;
        case 0x42: print_string("f8  ", WHITE_ON_BLACK); break;
        case 0x43: print_string("f9  ", WHITE_ON_BLACK); break;
        case 0x44: print_string("f10 ", WHITE_ON_BLACK); break;
        case 0x45: print_string("nml ", WHITE_ON_BLACK); break;
        case 0x46: print_string("scl ", WHITE_ON_BLACK); break;
        case 0x47: print_string("k7  ", WHITE_ON_BLACK); break;
        case 0x48: print_string("k8  ", WHITE_ON_BLACK); break;
        case 0x49: print_string("k9  ", WHITE_ON_BLACK); break;
        case 0x4a: print_string("k-  ", WHITE_ON_BLACK); break;
        case 0x4b: print_string("k4  ", WHITE_ON_BLACK); break;
        case 0x4c: print_string("k5  ", WHITE_ON_BLACK); break;
        case 0x4d: print_string("k6  ", WHITE_ON_BLACK); break;
        case 0x4e: print_string("k+  ", WHITE_ON_BLACK); break;
        case 0x4f: print_string("k1  ", WHITE_ON_BLACK); break;
        case 0x50: print_string("k2  ", WHITE_ON_BLACK); break;
        case 0x51: print_string("k3  ", WHITE_ON_BLACK); break;
        case 0x52: print_string("k0  ", WHITE_ON_BLACK); break;
        case 0x53: print_string("k.  ", WHITE_ON_BLACK); break;
        case 0x57: print_string("f11 ", WHITE_ON_BLACK); break;
        case 0x58: print_string("f12 ", WHITE_ON_BLACK); break;
        default:   print_string("unknown key ", WHITE_ON_BLACK); break;
    }
    if (scancode > 0x80) {
        print_string(" released.\n", WHITE_ON_BLACK);
    } else {
        print_string(" pressed.\n", WHITE_ON_BLACK);
    }
}