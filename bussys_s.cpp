#include "bussys.h"
#include<Windows.h>
using std::getline;
bool bus_system::admin_menu()
{
	//bool i;

	std::cout << "Hello,admin!欢迎进入管理菜单" << std::endl;
	while (true) {
		bool flag = 1;
		if (flag)
		{
			std::cout << "*****************************\n";
			std::string* all = NULL;
			all = new std::string[line_list.size()];
			line_showall(all);
			std::cout << "当前所有线路如下：\n" << std::endl;
			for (size_t k = 0; k < line_list.size(); k++)
			{
				std::cout << all[k] << std::endl;
			}
			std::cout << "\n0——切换管理员权限（返回用户菜单）\n";
			std::cout << "1——新增线路" << std::endl;
			std::cout << "2——删除线路" << std::endl;
			std::cout << "3——修改线路" << std::endl;
			std::cout << "请输入对应序号开始" << std::endl;//管理员菜单
			delete[] all;
		}
		std::string f;
		getline(std::cin, f);
		std::cout << "##############\n";
		if (f == "1")
		{
			std::cout << "r——返回管理员界面\n";
			std::string addli;
			std::cout << "请输入新增线路" << std::endl;
			getline(std::cin, addli);
			if (addli == "r")
			{
				flag = 1;
			}
			else
			{
				while (line_add(addli))
				{
					getline(std::cin, addli);			
				}
				flag = 1;
			}
		}
		else if (f == "2")
		{
			std::string g;

			std::cout << "请输入删除线路序号" << std::endl;
			std::cout << "r——返回管理员界面\n";
			getline(std::cin, g);
			if (g == "r")
			{
				flag = 1;
				break;
			}
			else
			{
				while (true)
				{
					if (checkthis(g))
					{
						int n = stoi(g);
						line_delete(n);
						break;
					}
					else
					{
						getline(std::cin, g);
					}
				}
				flag = 1;
			}

		}
		else if (f == "3")
		{
			std::string  h;


			std::cout << "请输入修改路线的序号" << std::endl;
			std::cout << "r——返回管理员界面\n";
			getline(std::cin, h);
			if (h == "r")
			{
				flag = 1;
				break;
			}
			else
			{
				while (1)
				{
					if (checkthis(h))
					{
						int m = stoi(h);
						std::string newli;
						std::cout << "输入修改后的线路" << std::endl;
						getline(std::cin, newli);
						line_update(m, newli);
						break;
					}
					else
					{
						getline(std::cin, h);
					}
				}
				flag = 1;
			}

		}
		else if (f == "q")
		{
			
			std::cout << "已退出\n";
			std::system("pause");
			return 0;
		}
		else if (f == "0")
		{
			switch_privilege();
			return 1;
		}
		else
		{
			std::cout << "请重新输入" << std::endl;
			flag = 0;
		}

	}

}
bool bus_system::user_menu()
{
	std::cout << "Welcome to our automated bus route selection system!欢迎来到查询系统！" << std::endl;
	std::string a;
	bool flag = 1;
	while (true)
	{
		if (flag)
		{
			std::cout << "*****************************\n";
			std::cout << "0——管理员权限" << std::endl;
			std::cout << "1——线路查询" << std::endl;
			std::cout << "2——车次查询" << std::endl;
			std::cout << "q——退出" << std::endl;
			std::cout << "请输入对应序号开始" << std::endl;//普通用户菜单
		}
		getline(std::cin, a);
		std::cout << "##############\n";
		if (a == "1")//线路查询
		{
			std::string start;
			std::string end;
			std::string str1[2];
			std::cout << "请输入出发地" << std::endl;
			getline(std::cin, start);
			std::cout << "请输入目的地" << std::endl;
			getline(std::cin, end);
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
			flag = 1;
			system("pause");
		}
		else if (a == "2")//车次查询
		{
			std::cout << "请输入需要查询的公交车次" << std::endl;
			std::string line1;
			std::string str2;
			getline(std::cin, line1);
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
			flag = 1;
		}
		else if (a == "0")//管理员权限
		{
			std::cout << "当前权限为" << std::endl;
			std::cout << (admin ? "管理员" : "普通用户") << std::endl;
			std::string e;
			std::cout << "是否切换权限？[Y/N]" << std::endl;
			getline(std::cin, e);
			if (e == "y" || e == "Y")
			{
				switch_privilege();
				return 1;
			}
			else if (e == "n" || e == "N")
			{

			}
			flag = 1;
		}
		else if (a == "q")
		{
			std::cout << "已退出\n";
			system("pause >nul");
			return 0;
		}
		else
		{
			std::cout << "请重新输入\n";
			flag = 0;
		}
	}
}
void bus_system::menu()
{
	while (true)
	{
		if (admin)
		{
			if (!admin_menu())
			{
				return;
			}
		}
		else
		{
			if (!user_menu())
			{
				return;
			}
		}
	}
}
bool bus_system::checkthis(const std::string& g)
{
	for (size_t i = 0; i < g.length(); i++)//检查是否有非数字字符，若有则将flag改为0；
	{
		if (int(g[i]) < 48 || int(g[i]) > 57)
		{
			std::cout << "错误的输入,请重试\n";
			return false;
		}
	}
	return true;
}