#include <stdio.h>
#include <draw.h>

int test_draw(int argc,char **argv);
int new_test( int argc, char *argv[]);

int main(int argc, const char *argv[])
{
//	new_test(argc, argv);
	test();
//	test_draw(argc, argv);
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
