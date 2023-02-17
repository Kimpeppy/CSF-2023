// C implementation of hexdump main function

#include "hexfuncs.h"  // this is the only header file which may be included!

int main(void) {
  // TODO: implement the main function
  char data_buf[17];
  char sbuf[9];
  data_buf[17] = '\0';
  for (int i = 0; i < 17; i++) {
    data_buf[i] = '0';
  }
  for (int i = 0; i < 8; i++) {
    sbuf[i] = '0';
  }

  //Referance
  char colon[2] = {':', '\0'};
  char space[2] = {' ', '\0'};
  char newLine[2] = {'\n', '\0'};
  char period[2] = {'.', '\0'};
  


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
    hex_write_string(newLine);
    temp = hex_read(data_buf);
    counter += 16;
  }
  
}


void helper_call_format_as_hex(char data_buf[], char sbuf[]) {
  int i = 0;
  char space[2] = {' ', '\0'};
  while (data_buf[i] != '\0') {
    hex_format_byte_as_hex(data_buf[i], sbuf);
    hex_write_string(sbuf);
    data_buf[i] = hex_to_printable(data_buf[i]);
    hex_write_string(space);
    i++;
  }
  while (i < 16) {
    hex_write_string(space);
    hex_write_string(space);
    hex_write_string(space);
    i++;
  }
  hex_write_string(space);
}
