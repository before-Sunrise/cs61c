#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void lfsr_calculate(uint16_t *reg) {
    // calculate the leftmost bit
    uint16_t bit = ((*reg >> 0) & 0x01) ^ ((*reg >> 2) & 0x01) 
    ^ ((*reg >> 3) & 0x01) ^ ((*reg >> 5));
    // set the mask code
    bit = bit << 15 ;
    // shift right one bit
    *reg = *reg >> 1;
    // reset the right bit to the desired bit
    *reg = bit | (*reg & ( ~(1<<15) ) ); 
}

int main() {
  int8_t *numbers = (int8_t*) malloc(sizeof(int8_t) * 65535);
  if (numbers == NULL) {
    printf("Memory allocation failed!");
    exit(1);
  }

  memset(numbers, 0, sizeof(int8_t) * 65535);
  uint16_t reg = 0x1;
  uint32_t count = 0;
  int i;

  do {
    count++;
    numbers[reg] = 1;
    if (count < 24) {
      printf("My number is: %u\n", reg);
    } else if (count == 24) {
      printf(" ... etc etc ... \n");
    }
    for (i = 0; i < 32; i++)
      lfsr_calculate(&reg);
  } while (numbers[reg] != 1);

  printf("Got %u numbers before cycling!\n", count);

  if (count == 65535) {
    printf("Congratulations! It works!\n");
  } else {
    printf("Did I miss something?\n");
  }

  free(numbers);

  return 0;
}
