#include "bussys.h"

bool bus_system::menu()
{
	std::cout << "Welcome to our automated bus route selection system!��ӭ������ѯϵͳ��" << std::endl;
	int a;
	bool j;
	do
	{
		std::cout << "1��·��ѯ" << std::endl;
		std::cout << "2���β�ѯ" << std::endl;
		std::cout << "3����ԱȨ��" << std::endl;
		std::cout << "�������Ӧ��ſ�ʼ" << std::endl;//��ͨ�û��˵�
		std::cin >> a;
		if (a == 1)//��·��ѯ
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
		if (a == 2)//���β�ѯ
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
		if (a == 3)//����ԱȨ��
		{
			std::cout << "��ǰȨ��Ϊ" << std::endl;
			std::cout << admin << std::endl;
			bool e;
			std::cout << "�Ƿ��л�Ȩ�ޣ�0�ǣ��������ַ�" << std::endl;
			std::cin >> e;
			if (e == 0)
			{
				switch_privilege();
			}
			if (admin == true)//����Ƿ�Ϊ����Ա
			{
				int f;
				bool i;
				std::cout << "Hello,admin!��ӭ�������˵�" << std::endl;
				do {
					std::string* all = NULL;
					all = new std::string[line_list.size()];
					line_showall(all);
					std::cout << "��ǰ������·����" << std::endl;
					int k, l;
					l = line_list.size();
					for (k = 0; k < l; k++)
					{
						std::cout << all[k] << std::endl;
					}
					std::cout << "1������·" << std::endl;
					std::cout << "2ɾ����·" << std::endl;
					std::cout << "3�޸���·" << std::endl;
					std::cout << "�������Ӧ��ſ�ʼ" << std::endl;//����Ա�˵�
					std::cin >> f;
					if (f == 1)
					{
						std::string addli;
						std::cout << "������������·" << std::endl;
						std::getline(std::cin,addli) ;
						line_add(addli);
					}
					if (f == 2)
					{
						std::cout << "������ɾ����·���" << std::endl;
						int g;
						std::cin >> g;
						line_delete(g);
					}
					if (f == 3)
					{
						std::cout << "�����뽫���Ϊ������·��Ϊʲô" << std::endl;
						int h;
						std::string newli;
						std::cin >> h;
						std::getline(std::cin,newli);
						line_update(h, newli);
					}
					if (f != 1 && f != 2 && f != 3)
					{
						std::cout << "����������" << std::endl;
					}
					std::cout << "����0��������,�������������˳�" << std::endl;
					std::cin >> i;
					delete[] all;
				} while (i == 0);
			}
			else
			{
				std::cout << "��û�й���ԱȨ�ޣ�" << std::endl;
			}
		}
		if (a != 1 && a != 2 && a != 3)
		{
			std::cout << "��������ȷ���" << std::endl;
		}
		std::cout << "����0������ѯ,�������������˳�" << std::endl;
		std::cin >> j;
	} while (j == 0);
	return true;
}