/*
 * String functions for multithreaded client/server calculator program
 * CSF Assignment 1
 * Michael Kim, Afaf Saqib Qureshi
 * mkim225@jh.edu, asaqibq1@jhu.edu
 */
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "uint256.h"

// Create a UInt256 value from a single uint64_t value.
// Only the least-significant 64 bits are initialized directly,
// all other bits are set to 0.
UInt256 uint256_create_from_u64(uint64_t val) {
  UInt256 result;
  
  result.data[0] = val;
  result.data[1] = 0U;
  result.data[2] = 0U;
  result.data[3] = 0U;
  return result;
}

// Create a UInt256 value from an array of 4 uint64_t values.
// The element at index 0 is the least significant, and the element
// at index 3 is the most significant.
UInt256 uint256_create(const uint64_t data[4]) {
  UInt256 result;
  
  result.data[0] = data[0];
  result.data[1] = data[1];
  result.data[2] = data[2];
  result.data[3] = data[3];
  return result;
}

// Afaf TODO:
// Create a UInt256 value from a string of hexadecimal digits.
UInt256 uint256_create_from_hex(const char *hex) {
  UInt256 result;
  uint64_t chunk;

  for (int i = 0; i < 4; i++) {
    result.data[i] = 0UL;
  }

  // We need to take the substring of the rightmost 64 characters.
  int length = strlen(hex);
  char* sixteen_char = malloc(sizeof(char) * 17);
  
  for (int i = 0; i < 4; i--) {
    if (length > 16) {
      strncpy(sixteen_char, hex + (length - 16), 16);
      chunk = strtoul(sixteen_char, NULL, 16);
      result.data[i] = chunk;
      length = length - 16;
    }
    else {
      // If here, we need the substring
      strncpy(sixteen_char, hex, length);
      chunk = strtoul(sixteen_char, NULL, 16);
      result.data[i] = chunk;
      break;
    }
  }
  
  return result;
  }
 
// Michael TODO:
// Return a dynamically-allocated string of hex digits representing the
// given UInt256 value.
char *uint256_format_as_hex(UInt256 val) {
  char *hex = NULL;
  char *buf = NULL;

  hex = malloc(sizeof(char) * 65);
  hex[0] = '\0';
  buf = malloc(sizeof(char) * 17);

  int i = 3;

  // If this is active, there is leading zeros
  int zeroFlag = 1;

  while (i >= 0) {
    uint64_t data = val.data[i];
    // We need to check if data is a zero and the zeroflag is activated
    if (i == 0 && zeroFlag && val.data[i] == 0U) {
      char temp[1] = "0";
      strcpy(hex, temp);
    }
    else if (data == 0U && zeroFlag) {
      // Do nothing
      i--;
      continue;
    }
    else if (data > 0U && zeroFlag) {
      // There won't be any leading zeros anymore but we need to 
      // sprintf without leading zeros
      zeroFlag = 0;
      sprintf(hex, "%lx", data);
      
    }
    else if (!zeroFlag) {
      // We can just print it normally since the zeroflag is deactivated
      sprintf(buf, "%016lx", data);
      strcat(hex, buf);
    }
    // Add the buf to the concatnate exit
    i--; 
  }
  
  return hex;
}

// Get 64 bits of data from a UInt256 value.
// Index 0 is the least significant 64 bits, index 3 is the most
// significant 64 bits.
uint64_t uint256_get_bits(UInt256 val, unsigned index) {
  uint64_t bits;
  
  bits = val.data[index];
  return bits;
  
}

// Compute the sum of two UInt256 values.
UInt256 uint256_add(UInt256 left, UInt256 right) {
  UInt256 sum;

  sum.data[0] = 0U;
  sum.data[1] = 0U;
  sum.data[2] = 0U;
  sum.data[3] = 0U;

  uint64_t carry = 0U;
  
  
  for (int i = 0; i < 4; i++) {
    // You add left data + right data
    sum.data[i] = left.data[i] + right.data[i];

    // Check if left and right overflows
    // If it overflow set the carry flag
    // After that if statement, the carry to the sum
    // If it overflow set the carry flag
    
    if (sum.data[i] < left.data[i]) {
      sum.data[i]+= carry;
      carry = 1U;
      continue;
    }

    else {
      sum.data[i] += carry;
      if (sum.data[i] < carry) {
        carry = 1U;
      }
      else {
        carry = 0U;
      }
    }
  }
  return sum;
}

// Compute the difference of two UInt256 values.
UInt256 uint256_sub(UInt256 left, UInt256 right) {
  UInt256 result;
  
  for (int i = 0; i < 4; i++) {
    right.data[i] = ~right.data[i];
  }
  right = uint256_add(right, uint256_create_from_u64(1U));
  result = uint256_add(left, right);

  return result;
}

// Compute the product of two UInt256 values.
UInt256 uint256_mul(UInt256 left, UInt256 right) {
  UInt256 product;

  product.data[0] = 0U;
  product.data[1] = 0U;
  product.data[2] = 0U;
  product.data[3] = 0U;

  // Do a for loop that goes over every bit on the left UInt256
  // Shift b amount of bit by a
  // Add the new shift value to the product
  for (int i = 0; i < 256; i++) {
    if (uint256_bit_is_set(left, i)) {
      UInt256 term = uint256_leftshift(right, i);
      product = uint256_add(product, term);
    }
  }
 
  return product;
}

// 1-256
// bitwise operations left shift and and operation
// 101 & 100 = 1 if 
int uint256_bit_is_set(UInt256 val, unsigned index) {
  uint64_t data;
  unsigned newIndex = index / 64; //Val.data[newIndex];
  unsigned bitIndex = index % 64; //the bit place

  data = val.data[newIndex];
  if (data & (1UL << bitIndex)) {
    return 1;
  }
  else {
    return 0;
  }

}

UInt256 uint256_leftshift(UInt256 val, unsigned shift) {
  int i = 0;
  unsigned numToShift = shift;
  uint64_t bitmask = 0UL;
  if (shift == 0) {
    return val;
  }
  while (i < 4) {
    // Copy the val.data for bitmask
    uint64_t temp = val.data[i];
    // If the value is greater than the bit size, shift the entire thing by 64 bits
    if (numToShift >= 64) {
      uint64_t temp2 = val.data[i];
      val.data[i] = 0UL;
      for (int j = i + 1; j < 4; j++) {
        uint64_t temp3 = val.data[j];
        val.data[j] = temp2;
        temp2 = temp3;

      }
      // Decrement the value
      numToShift -= 64;
    }
    else {
      // Shift the actual value
      if (numToShift == 0) {
        return val;
      }
      val.data[i] = val.data[i] << numToShift;
      // Apply bitmask
      val.data[i] = val.data[i] | bitmask;
      // Create bitmask
      temp = temp >> (64 - numToShift);
      bitmask = temp;
    }
    i++;
  }
  return val;
}
