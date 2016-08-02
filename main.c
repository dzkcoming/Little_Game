#include <stdio.h>
#include <draw.h>

int main(int argc, const char *argv[])
{
	test();
#ifdef WUZIQI
	wuziqi();
#else
	;
#endif

	return 0;
}

void wuziqi(void)
{

}
