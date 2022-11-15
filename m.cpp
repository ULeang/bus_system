#include "bussys.h"

int main(void)
{
	system("chcp 936");//设置输出控制台编码为gbk（936）/gb(2312)
	bus_system bs;
	bs.menu();
	system("pause >nul");
	return 0;
}