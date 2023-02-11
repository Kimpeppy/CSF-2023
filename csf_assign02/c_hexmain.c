// C implementation of hexdump main function

#include "hexfuncs.h"  // this is the only header file which may be included!

int main(void) {
  // TODO: implement the main function
  char *data_buf = malloc(sizeof(char) * 17);
  char sbuf[8];
  
  // Reference to characters
  char colon[1] = {':'};
  char space[1] = {' '};
  char newline[1] = {'\n'};

  // Variables to read the input
  unsigned temp = hex_read(data_buf);
  unsigned counter = 0;
  while (temp != 0) {
    // Get the first line of position and write it
    hex_format_offset(counter, sbuf);
    hex_write_string(sbuf);
    // Seperate the position from the hexadecimal
    hex_write_string(colon);
    hex_write_string(space);
    // Print out the set of hexadecimal
    helper_call_format_as_hex(data_buf, sbuf);
    hex_write_string(data_buf);
    hex_write_string(newline);
    temp = hex_read(data_buf);
  }
  free(data_buf);
}

void helper_call_format_as_hex(char data_buf[], char sbuf[]) {
  int i = 0;
  char space[1] = {' '};
  while (data_buf[i] != '\0') {
    hex_format_byte_as_hex(data_buf[i], sbuf);
    hex_write_string(sbuf);
    hex_write_string(space);
    i++;
  }
}
