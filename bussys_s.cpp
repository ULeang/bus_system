#include "bussys.h"
#include<Windows.h>
using std::getline;
bool bus_system::admin_menu()
{
	//bool i;

	std::cout << "Hello,admin!��ӭ�������˵�" << std::endl;
	while (true) {
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
		std::string f;
		std::cin >> f;
		std::cout << "##############\n";
		if (f == "1")
		{
			std::string addli;
			std::cout << "������������·" << std::endl;
			getchar();
			getline(std::cin, addli);
			line_add(addli);
		}
		else if (f == "2")
		{
			std::cout << "r�������ع���Ա����\n";
			std::cout << "������ɾ����·���" << std::endl;
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
					for (size_t i = 0; i < g.length(); i++)//����Ƿ��з������ַ���������flag��Ϊ0��
					{
						if (int(g[i]) < 48 || int(g[i]) > 57)
						{
							flag = 0;
							std::cout << "���������,������\n";
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
			std::cout << "�������޸�·�ߵ����" << std::endl;
			int h;
			std::string newli;
			std::cin >> h;
			getchar();
			std::cout << "�����޸ĺ����·" << std::endl;
			getline(std::cin, newli);
			line_update(h, newli);
		}
		else if (f == "q") {
			delete[] all;
			getchar();

			std::cout << "���˳�\n";
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
			std::cout << "����������" << std::endl;
		}

	}

}
bool bus_system::user_menu()
{
	std::cout << "Welcome to our automated bus route selection system!��ӭ������ѯϵͳ��" << std::endl;
	std::string a;
	while (true)
	{
		std::cout << "*****************************\n";
		std::cout << "0��������ԱȨ��" << std::endl;
		std::cout << "1������·��ѯ" << std::endl;
		std::cout << "2�������β�ѯ" << std::endl;
		std::cout << "q�����˳�" << std::endl;
		std::cout << "�������Ӧ��ſ�ʼ" << std::endl;//��ͨ�û��˵�
		getline(std::cin, a);
		std::cout << "##############\n";
		if (a == "1")//��·��ѯ
		{
			std::string start;
			std::string end;
			std::string str1[2];
			std::cout << "�������������Ŀ�ĵ�" << std::endl;
			std::cin >> start;
			std::cin >> end;
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
		}
		else if (a == "2")//���β�ѯ
		{
			std::cout << "��������Ҫ��ѯ�Ĺ�������" << std::endl;
			std::string line1;
			std::string str2;
			std::cin >> line1;
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
		}
		else if (a == "0")//����ԱȨ��
		{
			std::cout << "��ǰȨ��Ϊ" << std::endl;
			std::cout << (admin ? "����Ա" : "��ͨ�û�") << std::endl;
			std::string e;
			std::cout << "�Ƿ��л�Ȩ�ޣ�[Y/N]" << std::endl;
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

				//std::cout << "��������ȷ���" << std::endl;
				getchar();
				std::cout << "���˳�\n";
				std::system("pause");
				return 0;
			}
			else
			{
				std::cout << "����������\n";
			}

			//std::cout << "����0������ѯ,�������������˳�" << std::endl;
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