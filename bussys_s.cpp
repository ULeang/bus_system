#include "bussys.h"
//#include<Windows.h>
using std::getline;
bool bus_system::admin_menu()
{
	//bool i;
	bool flag = 1;//�ж��Ƿ�������ʾ·��
	std::cout << "========================" << std::endl;
	std::cout << "Hello,admin!��ӭ�������˵�" << std::endl;
	std::cout << "------------------------------------------\n";
	while (true) {
		if (flag)
		{
			std::string* all = NULL;
			all = new std::string[line_list.size()];
			line_showall(all);
			std::cout << "��ǰ������·���£�\n" << std::endl;
			for (size_t k = 0; k < line_list.size(); k++)
			{
				std::cout << all[k] << std::endl;
			}
			std::cout << "\n0�����л�����ԱȨ�ޣ������û��˵���\n";
			std::cout << "1����������·" << std::endl;
			std::cout << "2����ɾ����·" << std::endl;
			std::cout << "3�����޸���·" << std::endl;
			std::cout << "q�����˳�����" << std::endl;
			std::cout << "�������Ӧ��ſ�ʼ" << std::endl;//����Ա�˵�
			delete[] all;
		}
		std::string f;
		getline(std::cin, f);
		std::cout << "==================\n";
		if (f == "1")
		{
			while (true)
			{
				std::cout << "���� r ���ع���Ա����\n";
				std::string addli;
				std::cout << "������������·" << std::endl;
				getline(std::cin, addli);
				std::cout << "==================\n";
				if (addli == "r")
				{
					break;
				}
				else
				{
					while (check_string_to_busline(addli) || line_add(addli))//û�д���ʱ��ִ�и�ѭ��
					{
						std::cout << "��ԭ��·���������ʽ����,������\n";
						std::cout << "���� r ���ع���Ա����\n";
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
				std::cout << "�Ƿ��������·��[Y/N]\n";
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
						std::cout << "���������,����������\n";
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
				std::cout << "������ɾ����·���" << std::endl;
				std::cout << "���� r ���ع���Ա����\n";
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
								std::cout << "��Ź���,������\n";
								std::cout << "���� r ���ع���Ա����\n";
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
							std::cout << "���������,������\n";
							std::cout << "���� r ���ع���Ա����\n";
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
				std::cout << "�Ƿ����ɾ��[Y/N]\n";
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
						std::cout << "���������,����������\n";
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
				std::cout << "�������޸�·�ߵ����" << std::endl;
				std::cout << "���� r ���ع���Ա����\n";
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
								std::cout << "�������ų�����Χ������������\n";
								getline(std::cin, h);
								std::cout << "==================\n";
							}
							else
							{
								std::cout << "�����޸ĺ����·" << std::endl;
								std::cout << "���� r ���ع���Ա����\n";
								std::cout << "����p���������޸�·�����\n";
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
											std::cout << "����������������������\n";
										}

									}
									else
									{
										std::cout << "�����ϸ�ʽ�����룬����������\n";
									}
								}
								break;
							}
						}
						else
						{
							std::cout << "���������,������\n";
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
					std::cout << "�Ƿ�����޸�[Y/N]\n";
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
							std::cout << "���������,����������\n";
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
			std::cout << "���˳�\n";
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
			std::cout << "����������" << std::endl;
			flag = 0;
		}

	}

}
bool bus_system::user_menu()
{
	std::cout << "Welcome to our automated bus route selection system!��ӭ������ѯϵͳ��" << std::endl;
	std::cout << "==================\n";
	std::string a;
	bool flag = 1;
	while (true)
	{
		if (flag)
		{
			std::cout << "0��������ԱȨ��" << std::endl;
			std::cout << "1������·��ѯ" << std::endl;
			std::cout << "2�������β�ѯ" << std::endl;
			std::cout << "q�����˳�����" << std::endl;
			std::cout << "�������Ӧ��ſ�ʼ" << std::endl;//��ͨ�û��˵�
		}
		getline(std::cin, a);
		std::cout << "==================\n";
		if (a == "1")//��·��ѯ
		{
			while (true)
			{
				std::string start;
				std::string end;
				std::string str1[2];
				std::cout << "���� r �����û�����\n";
				std::cout << "�����������" << std::endl;
				getline(std::cin, start);
				if (start == "r")
				{
					break;
				}
				std::cout << "-------------------\n";
				std::cout << "���� r �����û�����\n";
				std::cout << "������Ŀ�ĵ�" << std::endl;
				getline(std::cin, end);
				if (end == "r")
				{
					break;
				}
				int b = line_query(start, end, str1);
				if (b == -2)
				{
					std::cout << "ʼĩ����ͬ,��������" << std::endl;
				}
				else if (b == -1)
				{
					std::cout << "�Ҳ���վ�㣬���������Ƿ���ȷ" << std::endl;
				}
				else if (b == 0)
				{
					std::cout << "�޿ɵ���·��" << std::endl;
				}
				else if (b == 1)
				{
					std::cout << "����������·��վ������·����ͬ,����" << std::endl;
					std::cout << str1[0] << std::endl;
				}
				else if (b == 2)
				{
					std::cout << "����������·��վ������·�߲�ͬ,����" << std::endl;
					std::cout << str1[0] << std::endl;
					std::cout << str1[1] << std::endl;
				}

				//system("pause");
				std::cout << "�Ƿ����²�ѯ[Y/N]\n";
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
						std::cout << "���������,����������\n";
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
		else if (a == "2")//���β�ѯ
		{
			while (true)
			{
				std::cout << "��������Ҫ��ѯ�Ĺ�������" << std::endl;
				std::cout << "���� r �˳���ѯ\n";
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
					std::cout << "�޴˳���" << std::endl;
				}
				if (d == 1)
				{
					std::cout << "����ѯ�ĳ���·������" << std::endl;
					std::cout << str2 << std::endl;
				}
				std::cout << "�Ƿ������ѯ[Y/N]\n";
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
						std::cout << "���������,����������\n";
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
		else if (a == "0")//����ԱȨ��
		{
			std::cout << "��ǰȨ��Ϊ" << std::endl;
			std::cout << (admin ? "����Ա" : "��ͨ�û�") << std::endl;
			std::string e;
			std::cout << "�Ƿ��л�Ȩ�ޣ�[Y/N]" << std::endl;
			while (true)
			{
				getline(std::cin, e);
				if (e == "y" || e == "Y")
				{
					std::string password;
					std::cout << "���������Ա����" << std::endl;
					getline(std::cin, password);
					if (password == "123456")
					{
						switch_privilege();
						return 1;
					}
					else
					{
						std::cout << "���������Ϊ�������û�����\n";
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
					std::cout << "��Ч�����룬������\n";
					std::cout << "==================\n";
				}
			}
		}
		else if (a == "q")
		{
			std::cout << "���˳�\n";
			//system("pause >nul");
			return 0;
		}
		else
		{
			std::cout << "����������\n";
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
	for (size_t i = 0; i < g.length(); i++)//����Ƿ��з������ַ���������flag��Ϊ0��
	{
		if (int(g[i]) < 48 || int(g[i]) > 57)
		{
			//std::cout << "���������,������\n";
			return false;
		}
	}
	return true;
}