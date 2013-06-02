#include "hash_functions.h"

int file_hash(const char *string)
{
  int hash_code, sum1 = 0, sum2 = 0;

  const char *pointer = string;

  for(;;) {
    if(pointer[0] == '\0')
      break;
    else if(pointer[0] == '.')
      sum1 = sum1 << 4;
    else if(pointer[0] == '/')
      sum1 = sum1 << 5;
    else
      sum1 += pointer[ 0 ];

    if(pointer[1] == '\0')
      break;
    else if(pointer[1] == '.')
      sum2 = sum2 << 4;
    else if(pointer[1] == '/')
      sum2 = sum2 << 5;
    else
      sum2 += pointer[1];

    pointer += 2;
  }

  return sum1 + (sum2 << 8);
}

