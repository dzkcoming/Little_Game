#include <stdio.h>
#include <draw.h>

int main(int argc, const char *argv[])
{
#ifdef WUZIQI
	wuziqi();
#else
	;
#endif

	return 0;
}
