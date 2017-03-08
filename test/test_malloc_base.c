#include "malloc.h"

int main()
{
	int i;
	char *addr;

	write(1, "Start\n", 6);
	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		if (addr) {
			addr[0] = 42;
		} else {
			write(1, "caca\n", 5);
		}
		i++;
	}
	return (0);
}
