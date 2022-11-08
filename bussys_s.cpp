#include "bussys.h"

bool bus_system::menu()
{
	std::cout << "Welcome to our automated bus route selection system!欢迎来到查询系统！" << std::endl;
	int a;
	bool j;
	do
	{
		std::cout << "1线路查询" << std::endl;
		std::cout << "2车次查询" << std::endl;
		std::cout << "3管理员权限" << std::endl;
		std::cout << "请输入对应序号开始" << std::endl;//普通用户菜单
		std::cin >> a;
		if (a == 1)//线路查询
		{
			std::string start;
			std::string end;
			std::string str1[2];
			std::cout << "请输入出发地与目的地" << std::endl;
			std::cin >> start;
			std::cin >> end;
			int b = line_query(start, end, str1);
			if (b == -1)
			{
				std::cout << "找不到站点，请检查输入是否正确" << std::endl;
			}
			if (b == 0)
			{
				std::cout << "无可到达路线" << std::endl;
			}
			if (b == 1)
			{
				std::cout << "换乘最少线路与站数最少路线相同,如下" << std::endl;
				std::cout << str1[0] << std::endl;
			}
			if (b == 2)
			{
				std::cout << "换乘最少线路与站数最少路线不同,如下" << std::endl;
				std::cout << str1[0] << std::endl;
				std::cout << str1[1] << std::endl;
			}
		}
		if (a == 2)//车次查询
		{
			std::cout << "请输入需要查询的公交车次" << std::endl;
			std::string line1;
			std::string str2;
			std::cin >> line1;
			int d = line_showsingle(line1, &str2);
			if (d == 0)
			{
				std::cout << "无此车次" << std::endl;
			}
			if (d == 1)
			{
				std::cout << "所查询的车次路线如下" << std::endl;
				std::cout << str2 << std::endl;
			}
		}
		if (a == 3)//管理员权限
		{
			std::cout << "当前权限为" << std::endl;
			std::cout << admin << std::endl;
			bool e;
			std::cout << "是否切换权限？0是，其他数字否" << std::endl;
			std::cin >> e;
			if (e == 0)
			{
				switch_privilege();
			}
			if (admin == true)//检查是否为管理员
			{
				int f;
				bool i;
				std::cout << "Hello,admin!欢迎进入管理菜单" << std::endl;
				do {
					std::string* all = NULL;
					all = new std::string[line_list.size()];
					line_showall(all);
					std::cout << "当前所有线路如下" << std::endl;
					int k, l;
					l = line_list.size();
					for (k = 0; k < l; k++)
					{
						std::cout << all[k] << std::endl;
					}
					std::cout << "1新增线路" << std::endl;
					std::cout << "2删除线路" << std::endl;
					std::cout << "3修改线路" << std::endl;
					std::cout << "请输入对应序号开始" << std::endl;//管理员菜单
					std::cin >> f;
					if (f == 1)
					{
						std::string addli;
						std::cout << "请输入新增线路" << std::endl;
						std::getline(std::cin,addli) ;
						line_add(addli);
					}
					if (f == 2)
					{
						std::cout << "请输入删除线路序号" << std::endl;
						int g;
						std::cin >> g;
						line_delete(g);
					}
					if (f == 3)
					{
						std::cout << "请输入将序号为几的线路改为什么" << std::endl;
						int h;
						std::string newli;
						std::cin >> h;
						std::getline(std::cin,newli);
						line_update(h, newli);
					}
					if (f != 1 && f != 2 && f != 3)
					{
						std::cout << "请重新输入" << std::endl;
					}
					std::cout << "输入0继续管理,输入其他数字退出" << std::endl;
					std::cin >> i;
					delete[] all;
				} while (i == 0);
			}
			else
			{
				std::cout << "你没有管理员权限！" << std::endl;
			}
		}
		if (a != 1 && a != 2 && a != 3)
		{
			std::cout << "请输入正确序号" << std::endl;
		}
		std::cout << "输入0继续查询,输入其他数字退出" << std::endl;
		std::cin >> j;
	} while (j == 0);
	return true;
}