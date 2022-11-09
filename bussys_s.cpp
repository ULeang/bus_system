#include "bussys.h"
#include<Windows.h>
using std::getline;
bool bus_system::admin_menu()
{
	//bool i;

	std::cout << "Hello,admin!��ӭ�������˵�" << std::endl;
	while (true) {
		bool flag = 1;
		if (flag)
		{
			std::cout << "*****************************\n";
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
			std::cout << "�������Ӧ��ſ�ʼ" << std::endl;//����Ա�˵�
			delete[] all;
		}
		std::string f;
		getline(std::cin, f);
		std::cout << "##############\n";
		if (f == "1")
		{
			std::cout << "r�������ع���Ա����\n";
			std::string addli;
			std::cout << "������������·" << std::endl;
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

			std::cout << "������ɾ����·���" << std::endl;
			std::cout << "r�������ع���Ա����\n";
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


			std::cout << "�������޸�·�ߵ����" << std::endl;
			std::cout << "r�������ع���Ա����\n";
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
						std::cout << "�����޸ĺ����·" << std::endl;
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
			
			std::cout << "���˳�\n";
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
			std::cout << "����������" << std::endl;
			flag = 0;
		}

	}

}
bool bus_system::user_menu()
{
	std::cout << "Welcome to our automated bus route selection system!��ӭ������ѯϵͳ��" << std::endl;
	std::string a;
	bool flag = 1;
	while (true)
	{
		if (flag)
		{
			std::cout << "*****************************\n";
			std::cout << "0��������ԱȨ��" << std::endl;
			std::cout << "1������·��ѯ" << std::endl;
			std::cout << "2�������β�ѯ" << std::endl;
			std::cout << "q�����˳�" << std::endl;
			std::cout << "�������Ӧ��ſ�ʼ" << std::endl;//��ͨ�û��˵�
		}
		getline(std::cin, a);
		std::cout << "##############\n";
		if (a == "1")//��·��ѯ
		{
			std::string start;
			std::string end;
			std::string str1[2];
			std::cout << "�����������" << std::endl;
			getline(std::cin, start);
			std::cout << "������Ŀ�ĵ�" << std::endl;
			getline(std::cin, end);
			int b = line_query(start, end, str1);
			if (b == -1)
			{
				std::cout << "�Ҳ���վ�㣬���������Ƿ���ȷ" << std::endl;
			}
			if (b == 0)
			{
				std::cout << "�޿ɵ���·��" << std::endl;
			}
			if (b == 1)
			{
				std::cout << "����������·��վ������·����ͬ,����" << std::endl;
				std::cout << str1[0] << std::endl;
			}
			if (b == 2)
			{
				std::cout << "����������·��վ������·�߲�ͬ,����" << std::endl;
				std::cout << str1[0] << std::endl;
				std::cout << str1[1] << std::endl;
			}
			flag = 1;
			system("pause");
		}
		else if (a == "2")//���β�ѯ
		{
			std::cout << "��������Ҫ��ѯ�Ĺ�������" << std::endl;
			std::string line1;
			std::string str2;
			getline(std::cin, line1);
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
			flag = 1;
		}
		else if (a == "0")//����ԱȨ��
		{
			std::cout << "��ǰȨ��Ϊ" << std::endl;
			std::cout << (admin ? "����Ա" : "��ͨ�û�") << std::endl;
			std::string e;
			std::cout << "�Ƿ��л�Ȩ�ޣ�[Y/N]" << std::endl;
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
			std::cout << "���˳�\n";
			system("pause >nul");
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
			std::cout << "���������,������\n";
			return false;
		}
	}
	return true;
}