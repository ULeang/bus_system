#include "bussys.h"

int main(void)
{
	system("chcp 936");//�����������̨����Ϊgbk��936��/gb(2312)
	bus_system bs;
	bs.menu();
	system("pause >nul");
	return 0;
}