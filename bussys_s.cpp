#include "bussys.h"
//#include<Windows.h>
using std::getline;
bool bus_system::admin_menu()
{
	//bool i;
	bool flag = 1;//判断是否重新显示路线
	std::cout << "========================" << std::endl;
	std::cout << "Hello,admin!欢迎进入管理菜单" << std::endl;
	std::cout << "------------------------------------------\n";
	while (true) {
		if (flag)
		{
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
			std::cout << "q——退出程序" << std::endl;
			std::cout << "请输入对应序号开始" << std::endl;//管理员菜单
			delete[] all;
		}
		std::string f;
		getline(std::cin, f);
		std::cout << "==================\n";
		if (f == "1")
		{
			while (true)
			{
				std::cout << "输入 r 返回管理员界面\n";
				std::string addli;
				std::cout << "请输入新增线路" << std::endl;
				getline(std::cin, addli);
				std::cout << "==================\n";
				if (addli == "r")
				{
					break;
				}
				else
				{
					while (check_string_to_busline(addli) || line_add(addli))//没有错误时不执行该循环
					{
						std::cout << "与原有路线重名或格式错误,请重试\n";
						std::cout << "输入 r 返回管理员界面\n";
						getline(std::cin, addli);
						std::cout << "==================\n";
						if (addli == "r")
						{
							break;
						}
					}
					if (addli == "r")
					{
						break;
					}
				}
				std::cout << "是否继续新增路线[Y/N]\n";
				std::string command;
				while (true)
				{
					getline(std::cin, command);
					if (command == "y" || command == "Y")
					{
						break;
					}
					else if (command == "n" || command == "N")
					{
						break;
					}
					else
					{
						std::cout << "错误的输入,请重新输入\n";
						std::cout << "==================\n";
					}
				}
				if (command == "n" || command == "N")
				{
					break;
				}

			}
			flag = 1;
		}
		else if (f == "2")
		{
			while (true)
			{
				std::string g;
				std::cout << "请输入删除线路序号" << std::endl;
				std::cout << "输入 r 返回管理员界面\n";
				getline(std::cin, g);
				std::cout << "==================\n";
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
							size_t n = stoi(g);
							if (n < line_list.size())
							{
								line_delete(n);
								break;
							}
							else
							{
								std::cout << "序号过大,请重试\n";
								std::cout << "输入 r 返回管理员界面\n";
								getline(std::cin, g);
								std::cout << "==================\n";
								if (g == "r")
								{
									break;
								}
							}
						}
						else
						{
							std::cout << "错误的输入,请重试\n";
							std::cout << "输入 r 返回管理员界面\n";
							getline(std::cin, g);
							std::cout << "==================\n";
							if (g == "r")
							{
								break;
							}
						}
					}
					if (g == "r")
					{
						break;
					}
				}
				std::cout << "是否继续删除[Y/N]\n";
				std::string command;
				while (true)
				{
					getline(std::cin, command);
					if (command == "y" || command == "Y")
					{
						break;
					}
					else if (command == "n" || command == "N")
					{
						break;
					}
					else
					{
						std::cout << "错误的输入,请重新输入\n";
						std::cout << "==================\n";
					}
				}
				if (command == "n" || command == "N")
				{
					break;
				}
			}
			flag = 1;
		}
		else if (f == "3")
		{
			while (true)
			{
				std::string  h;
				std::cout << "请输入修改路线的序号" << std::endl;
				std::cout << "输入 r 返回管理员界面\n";
				getline(std::cin, h);
				std::cout << "==================\n";
				std::string newli = "";
				if (h == "r")
				{
					break;
				}
				else
				{
					while (true)
					{
						if (checkthis(h))
						{
							size_t m = stoi(h);
							if (m > line_list.size() - 1)
							{
								std::cout << "输入的序号超出范围，请重新输入\n";
								getline(std::cin, h);
								std::cout << "==================\n";
							}
							else
							{
								std::cout << "输入修改后的线路" << std::endl;
								std::cout << "输入 r 返回管理员界面\n";
								std::cout << "输入p重新输入修改路线序号\n";
								while (true)
								{
									getline(std::cin, newli);
									std::cout << "==================\n";
									if (newli == "r" || newli == "p")
									{
										break;
									}
									else if (!check_string_to_busline(newli))
									{
										if (!line_update(m, newli))
										{
											break;
										}
										else
										{
											std::cout << "存在重名现象，请重新输入\n";
										}

									}
									else
									{
										std::cout << "不符合格式的输入，请重新输入\n";
									}
								}
								break;
							}
						}
						else
						{
							std::cout << "错误的输入,请重试\n";
							getline(std::cin, h);
							std::cout << "==================\n";
						}
					}
				}
				if (newli == "r")
				{
					break;
				}
				if (newli != "p")
				{
					std::cout << "是否继续修改[Y/N]\n";
					std::string command;
					while (true)
					{
						getline(std::cin, command);
						if (command == "y" || command == "Y")
						{
							break;
						}
						else if (command == "n" || command == "N")
						{
							break;
						}
						else
						{
							std::cout << "错误的输入,请重新输入\n";
							std::cout << "==================\n";
						}
					}
					if (command == "n" || command == "N")
					{
						break;
					}
				}
			}
			flag = 1;
		}
		else if (f == "q")
		{
			std::cout << "已退出\n";
			//std::system("pause");
			return 0;
		}
		else if (f == "0")
		{
			switch_privilege();
			return 1;
		}
		else
		{
			std::cout << "==================\n";
			std::cout << "请重新输入" << std::endl;
			flag = 0;
		}

	}

}
bool bus_system::user_menu()
{
	std::cout << "Welcome to our automated bus route selection system!欢迎来到查询系统！" << std::endl;
	std::cout << "==================\n";
	std::string a;
	bool flag = 1;
	while (true)
	{
		if (flag)
		{
			std::cout << "0——管理员权限" << std::endl;
			std::cout << "1——线路查询" << std::endl;
			std::cout << "2——车次查询" << std::endl;
			std::cout << "q——退出程序" << std::endl;
			std::cout << "请输入对应序号开始" << std::endl;//普通用户菜单
		}
		getline(std::cin, a);
		std::cout << "==================\n";
		if (a == "1")//线路查询
		{
			while (true)
			{
				std::string start;
				std::string end;
				std::string str1[2];
				std::cout << "输入 r 返回用户界面\n";
				std::cout << "请输入出发地" << std::endl;
				getline(std::cin, start);
				if (start == "r")
				{
					break;
				}
				std::cout << "-------------------\n";
				std::cout << "输入 r 返回用户界面\n";
				std::cout << "请输入目的地" << std::endl;
				getline(std::cin, end);
				if (end == "r")
				{
					break;
				}
				int b = line_query(start, end, str1);
				if (b == -2)
				{
					std::cout << "始末点相同,错误输入" << std::endl;
				}
				else if (b == -1)
				{
					std::cout << "找不到站点，请检查输入是否正确" << std::endl;
				}
				else if (b == 0)
				{
					std::cout << "无可到达路线" << std::endl;
				}
				else if (b == 1)
				{
					std::cout << "换乘最少线路与站数最少路线相同,如下" << std::endl;
					std::cout << str1[0] << std::endl;
				}
				else if (b == 2)
				{
					std::cout << "换乘最少线路与站数最少路线不同,如下" << std::endl;
					std::cout << str1[0] << std::endl;
					std::cout << str1[1] << std::endl;
				}

				//system("pause");
				std::cout << "是否重新查询[Y/N]\n";
				std::string command;
				while (true)
				{
					getline(std::cin, command);
					if (command == "y" || command == "Y")
					{
						break;
					}
					else if (command == "n" || command == "N")
					{
						break;
					}
					else
					{
						std::cout << "错误的输入,请重新输入\n";
						std::cout << "==================\n";
					}
				}
				if (command == "n" || command == "N")
				{
					break;
				}
			}
			flag = 1;
		}
		else if (a == "2")//车次查询
		{
			while (true)
			{
				std::cout << "请输入需要查询的公交车次" << std::endl;
				std::cout << "输入 r 退出查询\n";
				std::string line1;
				std::string str2;
				getline(std::cin, line1);
				std::cout << "==================\n";
				if (line1 == "r")
				{
					break;
				}
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
				std::cout << "是否继续查询[Y/N]\n";
				std::string command;
				while (true)
				{
					getline(std::cin, command);
					std::cout << "==================\n";
					if (command == "y" || command == "Y")
					{
						break;
					}
					else if (command == "n" || command == "N")
					{
						break;
					}
					else
					{
						std::cout << "错误的输入,请重新输入\n";
						std::cout << "==================\n";
					}
				}
				if (command == "n" || command == "N")
				{
					break;
				}
				flag = 1;
			}
		}
		else if (a == "0")//管理员权限
		{
			std::cout << "当前权限为" << std::endl;
			std::cout << (admin ? "管理员" : "普通用户") << std::endl;
			std::string e;
			std::cout << "是否切换权限？[Y/N]" << std::endl;
			while (true)
			{
				getline(std::cin, e);
				if (e == "y" || e == "Y")
				{
					std::string password;
					std::cout << "请输入管理员密码" << std::endl;
					getline(std::cin, password);
					if (password == "123456")
					{
						switch_privilege();
						return 1;
					}
					else
					{
						std::cout << "密码错误，已为您返回用户界面\n";
						std::cout << "==================\n";
						flag = 1;
						break;
					}
				}
				else if (e == "n" || e == "N")
				{
					flag = 1;
					break;
				}
				else
				{
					std::cout << "无效的输入，请重试\n";
					std::cout << "==================\n";
				}
			}
		}
		else if (a == "q")
		{
			std::cout << "已退出\n";
			//system("pause >nul");
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
			//std::cout << "错误的输入,请重试\n";
			return false;
		}
	}
	return true;
}