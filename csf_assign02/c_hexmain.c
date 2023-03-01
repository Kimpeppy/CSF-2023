
// C implementation of hexdump main function

#include "hexfuncs.h" // this is the only header file which may be included!

void helper_call_format_as_hex(char data_buf[], char sbuf[], unsigned temp);

int main(void)
{

  char data_buf[17];
  char sbuf[9];
  data_buf[16] = '\0';

  // Reference
  char colon[2] = {':', '\0'};
  char space[2] = {' ', '\0'};
  char newLine[2] = {'\n', '\0'};

  // Variables to read the input
  unsigned temp = hex_read(data_buf);
  data_buf[temp] = '\0';
  unsigned counter = 0;
  while (temp != 0)
  {
    // Get the first line of position and write it
    hex_format_offset(counter, sbuf);
    hex_write_string(sbuf);
    // Separate the position from the hexadecimal
    hex_write_string(colon);
    hex_write_string(space);
    // Print out the set of hexadecimal
    helper_call_format_as_hex(data_buf, sbuf, temp);
    hex_write_string(data_buf);
    hex_write_string(newLine);
    temp = hex_read(data_buf);
    data_buf[temp] = '\0';
    counter += 16;
  }
}

void helper_call_format_as_hex(char data_buf[], char sbuf[], unsigned temp)
{
  char space[2] = {' ', '\0'}; // space

  for (unsigned i = 0; i < temp; i++)
  {                                              // Loop through the amount of char read
    hex_format_byte_as_hex(data_buf[i], sbuf);   // Get the char i and convert it to hexadecimal
    hex_write_string(sbuf);                      // Write the hexadecimal
    data_buf[i] = hex_to_printable(data_buf[i]); // Replace the character with a "." if its not printable
    hex_write_string(space);                     // Print space
  }
  unsigned i = temp;
  // Print out only space if there isn't enough characters
  while (i < 16)
  {
    hex_write_string(space);
    hex_write_string(space);
    hex_write_string(space);
    i++;
  }
  hex_write_string(space);
}