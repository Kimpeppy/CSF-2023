/*
 * String functions for multithreaded client/server calculator program
 * CSF Assignment 1
 * Michael Kim
 * mkim225@jh.edu
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
  // TODO: implement
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
  // TODO: implement
  result.data[0] = data[0];
  result.data[1] = data[1];
  result.data[2] = data[2];
  result.data[3] = data[3];
  return result;
}

// Create a UInt256 value from a string of hexadecimal digits.
UInt256 uint256_create_from_hex(const char *hex) {
  UInt256 result;
  // TODO: implement
  return result;
}

// Return a dynamically-allocated string of hex digits representing the
// given UInt256 value.
char *uint256_format_as_hex(UInt256 val) {
  char *hex = NULL;
  // TODO: implement
  return hex;
}

// Get 64 bits of data from a UInt256 value.
// Index 0 is the least significant 64 bits, index 3 is the most
// significant 64 bits.
uint64_t uint256_get_bits(UInt256 val, unsigned index) {
  uint64_t bits;
  // TODO: implement
  bits = val.data[index];
  return bits;
  
}

// Compute the sum of two UInt256 values.
UInt256 uint256_add(UInt256 left, UInt256 right) {
  UInt256 sum;
  // TODO: implement
  sum.data[0] = left.data[0] + right.data[0];
  sum.data[1] = left.data[1] + right.data[1];
  if (sum.data[0] < left.data[0]) {
    sum.data[1] += 1U;
  }
  sum.data[2] = left.data[2] + right.data[2];
  if (sum.data[1] < left.data[1]) {
    sum.data[2] += 1U;
    if (sum.data[2] < left.data[2]) {
      sum.data[3] += 1U;
    }
  }
  sum.data[3] = left.data[3] + right.data[3];
  if (sum.data[2] < left.data[2]) {
    sum.data[3] += 1U;
  }
  if (sum.data[3] < left.data[3]) {
    sum.data[0] = 0U;
    sum.data[1] = 0U;
    sum.data[2] = 0U;
    sum.data[3] = 0U;
  }
  return sum;
}

// Compute the difference of two UInt256 values.
UInt256 uint256_sub(UInt256 left, UInt256 right) {
  UInt256 result;
  // TODO: implement
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
  // TODO: implement
  return product;
}
