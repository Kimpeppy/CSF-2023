// C implementation of hexdump functions

#include <unistd.h>  // this is the only system header file you may include!
#include "hexfuncs.h"

// TODO: add function implementations here

// Read up to 16 bytes from standard input into data_buf.
// Returns the number of characters read.
unsigned hex_read(char data_buf[]) {
    unsigned length = 0;
    while (data_buf[length] != '\0') {
        length++;
    }
    if (length == 16) {
        length = 0;
    }

    unsigned byte = read(0, data_buf + length, 16 - length);
    return byte;
}

// Write given nul-terminated string to standard output.
void hex_write_string(const char s[]) {
    unsigned length = 0;
    while (s[length] != '\0') {
        length++;
    }
    write(1, s, length);
}

// Format an unsigned value as an offset string consisting of exactly 8
// hex digits.  The formatted offset is stored in sbuf, which must
// have enough room for a string of length 8.
void hex_format_offset(unsigned offset, char sbuf[]) {
    // // Length of our string.
    // // We can calculating it by counting how many times we can divide it by 16.
    // // '0' + 30
    int temp;
    sbuf[8] = '\0';
    int pointer = 7;
    while (offset > 0) {
        temp = offset & 15;
        if (temp >= 0 && temp < 10) {
            sbuf[pointer] = temp + 48;
        }
        else {
            sbuf[pointer] = temp + 87;
        }
        offset = offset >> 4;
        pointer--;
    }
    while(pointer >= 0) {
        sbuf[pointer] = '0';
        pointer--;
    }


}

// Format a byte value (in the range 0-255) as string consisting
// of two hex digits.  The string is stored in sbuf.
void hex_format_byte_as_hex(unsigned char byteval, char sbuf[]) {
    char first;
    char second;
    sbuf[2] = '\0';
    first = byteval >> 4;
    second = byteval & 15;
    if (first >= 0 && first < 10) {
        sbuf[0] = first + 48;
    } 
    else {
        sbuf[0] = first + 87;
    }
    if (second >= 0 && second < 10) {
        sbuf[1] = second + 48;
    } 
    else {
        sbuf[1] = second + 87;
    }

}

// Convert a byte value (in the range 0-255) to a printable character
// value.  If byteval is already a printable character, it is returned
// unmodified.  If byteval is not a printable character, then the
// ASCII code for '.' should be returned.
char hex_to_printable(unsigned char byteval) {
    if (byteval > 31) {
        return byteval;
    } 
    else {
        return '.';
    }
}