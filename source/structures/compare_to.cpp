#include "compare_to.h"

int string_compare_to(const char *a, const char *b)
{
	for(;;) {
		if(a[0] == '\0')  {
			if(b[0] == '\0')
				return 0;

			return -1;
		}
		else if(b[0] == '\0')
			return 1;
		else if(a[0] != b[0])  {
			if(a[0] < b[0])
				return -1;
			else
				return 1;
		}

		a++;
		b++;
	}
}

