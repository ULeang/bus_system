#include "bussys.h"
#include<Windows.h>
using std::getline;
bool bus_system::admin_menu()
{
	//bool i;

	std::cout << "Hello,admin!欢迎进入管理菜单" << std::endl;
	while (true) {
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
		std::string f;
		std::cin >> f;
		std::cout << "##############\n";
		if (f == "1")
		{
			std::string addli;
			std::cout << "请输入新增线路" << std::endl;
			getchar();
			getline(std::cin, addli);
			line_add(addli);
		}
		else if (f == "2")
		{
			std::cout << "r——返回管理员界面\n";
			std::cout << "请输入删除线路序号" << std::endl;
			std::string g;
			getchar();
			while (true)
			{
				getline(std::cin, g);
				if (g == "r")
				{
					break;
				}
				else
				{
					bool flag = 1;
					for (size_t i = 0; i < g.length(); i++)//检查是否有非数字字符，若有则将flag改为0；
					{
						if (int(g[i]) < 48 || int(g[i]) > 57)
						{
							flag = 0;
							std::cout << "错误的输入,请重试\n";
							break;
						}
					}
					if (flag)
					{
						int number = 0;
						for (int i = 0; i < g.length(); i++)
						{
							number = number * 10 + int(g[i]) - 48;
						}
						if (!line_delete(number))
						{
							break;
						}
					}
				}
			}


		}
		else if (f == "3")
		{
			std::cout << "请输入修改路线的序号" << std::endl;
			int h;
			std::string newli;
			std::cin >> h;
			getchar();
			std::cout << "输入修改后的线路" << std::endl;
			getline(std::cin, newli);
			line_update(h, newli);
		}
		else if (f == "q") {
			delete[] all;
			getchar();

			std::cout << "已退出\n";
			std::system("pause");
			return 0;
		}
		else if (f == "0")
		{
			delete[] all;
			switch_privilege();
			return 1;
		}
		else
		{
			std::cout << "请重新输入" << std::endl;
		}

	}

}
bool bus_system::user_menu()
{
	std::cout << "Welcome to our automated bus route selection system!欢迎来到查询系统！" << std::endl;
	std::string a;
	while (true)
	{
		std::cout << "*****************************\n";
		std::cout << "0——管理员权限" << std::endl;
		std::cout << "1——线路查询" << std::endl;
		std::cout << "2——车次查询" << std::endl;
		std::cout << "q——退出" << std::endl;
		std::cout << "请输入对应序号开始" << std::endl;//普通用户菜单
		getline(std::cin, a);
		std::cout << "##############\n";
		if (a == "1")//线路查询
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
		else if (a == "2")//车次查询
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
		else if (a == "0")//管理员权限
		{
			std::cout << "当前权限为" << std::endl;
			std::cout << (admin ? "管理员" : "普通用户") << std::endl;
			std::string e;
			std::cout << "是否切换权限？[Y/N]" << std::endl;
			std::cin >> e;
			if (e == "y" || e == "Y")
			{
				switch_privilege();
				return 1;
			}
			else if (e == "n" || e == "N")
			{

			}
			else if (a == "q")
			{

				//std::cout << "请输入正确序号" << std::endl;
				getchar();
				std::cout << "已退出\n";
				std::system("pause");
				return 0;
			}
			else
			{
				std::cout << "请重新输入\n";
			}

			//std::cout << "输入0继续查询,输入其他数字退出" << std::endl;
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