#include "bussys.h"
#include <direct.h>

using namespace std;
//return 0;��ʾ0 error��reutrn 1; ��ʾ����
bool bus_system::get_name_to_stop_list()
{
	ifstream bus_data_file;
	bus_data_file.open(file_name, ios::in);
	//if (!bus_data_file.is_open())
	//{
	//	char* cwd = _getcwd(NULL, 0);
	//	cout << "δ�ɹ����ļ���" << cwd<<"\\" << file_name << "\n�����ļ��Ƿ���ڻ������Ա����·���Դ����ļ�" << endl;
	//	return 1;
	//}
	
	//��ʱ����վ��
	string temp_stop_name;
	string p_flush;
	while (!bus_data_file.eof())
	{
		bus_data_file >> temp_stop_name;
		if (temp_stop_name == "#")
		{
			getline(bus_data_file, p_flush);//����վ�����ļ�ָ��������һ��
			if (bus_data_file.eof())
			{
				break;
			}
			bus_data_file >> temp_stop_name;//������һ����·�����ƶ��ļ�ָ��
			if (bus_data_file.eof())
			{
				break;
			}
		}
		else if (temp_stop_name.length() == 0)
		{
			break;
		}
		bus_data_file >> temp_stop_name;//��ʱȷ��temp_stop_name�����Ϊվ��
		stop_list.push_back(bus_stop(temp_stop_name, vector<int>()));
		for (size_t i = 0; i < stop_list.size() - 1; i++)//ȥ���ظ�
		{
			if (temp_stop_name == stop_list[i].name)
			{
				stop_list.pop_back();
				break;
			}
		}
		//��������bus_stop�Ƿ���ں�֮ǰ�������������Ƴ�stop_list
	}
	bus_data_file.close();
	return 0;
}
bool bus_system::creat_line_list()
{
	if (stop_list.empty())
	{
		//cout << "����" << file_name << "�Ƿ�Ϊ��" << endl;
	}

	ifstream bus_data_file;
	bus_data_file.open(file_name, ios::in);
	if (!bus_data_file.is_open())
	{
		//char* cwd = _getcwd(NULL, 0);
		//cout << "δ�ɹ����ļ���" << cwd <<"\\" << file_name << "�����ļ��Ƿ����" << endl;
		return 1;
	}

	string line_name;
	string temp_stop_name;
	while (!bus_data_file.eof())
	{
		vector<int>stop_number;//�����·�ߵ�����վ�����
		vector<bus_line::time>estimated_time;//�����·������վ��վֱ�ӵ�Ԥ��ʱ��
		
		bus_data_file >> line_name;
		if (bus_data_file.eof())
		{
			break;
		}

		string temp_time;
		while (true)
		{
			unsigned time = 0;

			bus_data_file >> temp_stop_name;//��ȡվ��

			for (size_t i = 0; i < stop_list.size(); i++)
			{
				if (temp_stop_name == stop_list[i].name)
				{
					stop_number.push_back(i);
				}
			}
			//վ����ת��Ϊ��Ӧ���

			bus_data_file >> temp_time;//��ȡԤ��ʱ��

			if (temp_time == "#") 
			{
				break;
			}
			else 
			{
				time = stoi(temp_time);
			}
			estimated_time.push_back(bus_line::time(time));
		}
		//��ȡ·��������վ����ת��Ϊ��Ӧ��ţ��Ѿ�����վ��Ԥ��ʱ��
		
			unsigned time_1 = 0;
			unsigned time_2 = 0;
			int g = 0;

			bus_data_file >> temp_time;

			g = temp_time.find(":");
			time_1 = stoi(temp_time.substr(0, g));
			time_2 = stoi(temp_time.substr(g + 1, temp_time.length() - 1 - g));
			bus_line::time first_temp(time_1, time_2);

			bus_data_file >> temp_time;

			g = temp_time.find(":");
			time_1 = stoi(temp_time.substr(0, g));
			time_2 = stoi(temp_time.substr(g + 1, temp_time.length() - 1 - g));
			bus_line::time last_temp(time_1, time_2);
		//��ȡ�װ೵��ĩ�೵ʱ��

		line_list.push_back(bus_line(line_name, stop_number, estimated_time, first_temp, last_temp));

		string p;
		getline(bus_data_file, p);
	}
	bus_data_file.close();
	return 0;
}
bool bus_system::creat_stop_list()
{
	if (line_list.empty())
	{
		//cout << "line_listΪ�գ������Ƿ񴴽�line_list" << endl;
		return 1;
	}
	for (size_t i = 0; i < line_list.size(); i++)
	{
		for (size_t j = 0; j < line_list[i].line.size() - 1; j++)
		{
			int number1 = line_list[i].line[j];
			int number2 = line_list[i].line[j + 1];
			stop_list[number1].connect_to_number.push_back(number2);
		}
	}
	//Ϊÿ��bus_stop��connect_to_number��ֵ
	return 0;
}
bool bus_system::write_bus_line_list()
{
	ofstream data_bus_file;
	data_bus_file.open(file_name, ios::out);
	for (size_t  j = 0; j < line_list.size(); j++)
	{
		if (j != 0)
		{
			data_bus_file << "\n" + line_list[j].name + " ";
		}
		else
		{
			data_bus_file << line_list[j].name + " ";
		}
		for (size_t i = 0; i < line_list[j].line.size(); i++)
		{
			data_bus_file << stop_list[line_list[j].line[i]].name + " ";
			if (i < line_list[j].estimated_time.size())
			{
				data_bus_file << 60 * (line_list[j].estimated_time[i].hour) + line_list[j].estimated_time[i].minute << " ";
			}
		}
		data_bus_file << "# " << line_list[j].first.hour << ":" << line_list[j].first.minute << " " << line_list[j].last.hour << ":" << line_list[j].last.minute << " #";

	}
	data_bus_file.close();
	return 0;
}
bool bus_system::read_string_to_bus_line_add(const string& li, bus_line*& p)
{
	vector<string> temp_list;
	string temp_string = "";
	for (size_t i = 0; i < li.length(); i++)//�Կհ׷��ָ��ַ���
	{
		if (li[i] != ' ')
		{
			temp_string = temp_string + li[i];
		}
		else
		{
			if (temp_string.length() != 0)
			{
				temp_list.push_back(temp_string);
				temp_string = "";
			}
		}
	}
	//�޸�stop_list;
	for (size_t i = 1; i < temp_list.size() - 3; i += 2)
	{
		stop_list.push_back(bus_stop(temp_list[i], vector<int>()));
		for (size_t j = 0; j < stop_list.size() - 1; j++)//ȥ���ظ�
		{
			if (temp_list[i] == stop_list[j].name)
			{
				stop_list.pop_back();
				break;
			}
		}
	}
	int n = 0;
	vector<int>stop_number;
	vector<bus_line::time>estimated_time;
	string line_name;
	string temp_time;
	string temp_stop_name;

	line_name = temp_list[n++];
	while (true)
	{
		unsigned time = 0;
		temp_stop_name = temp_list[n++];
		for (size_t i = 0; i < stop_list.size(); i++)
		{
			if (temp_stop_name == stop_list[i].name) 
			{
				stop_number.push_back(i);
			}
		}
		temp_time = temp_list[n++];
		if (temp_time == "#") 
		{
			break;
		}
		else 
		{
			time = stoi(temp_time);
		}
		estimated_time.push_back(bus_line::time(time));
	}
	
		unsigned time_1 = 0;
		unsigned time_2 = 0;
		int g = 0;

		temp_time = temp_list[n++];

		g = temp_time.find(":");
		time_1 = stoi(temp_time.substr(0, g));
		time_2 = stoi(temp_time.substr(g + 1, temp_time.length() - 1 - g));
		bus_line::time first_temp(time_1, time_2);

		temp_time = temp_list[n++];

		g = temp_time.find(":");

		time_1 = stoi(temp_time.substr(0, g));
		time_2 = stoi(temp_time.substr(g + 1, temp_time.length() - 1 - g));
		bus_line::time last_temp(time_1, time_2);
	
	p = new bus_line(line_name, stop_number, estimated_time, first_temp, last_temp);
	return false;
}//ָ��p�������ɵ�bus_line����
bool bus_system::line_delete(const unsigned& u)
{
	if (u < line_list.size())
	{
		vector<bus_line>::iterator it = line_list.begin() + u;
		line_list.erase(it);//��line_list��ɾ����Ӧbus_line
	}
	else
	{
		cout << "������ų�����Χ��������" << endl;
		return 1;
	}
	write_bus_line_list();
	stop_update();
	return 0;
}
bool bus_system::line_update(const unsigned& u, const std::string& li)
{
	if (u < line_list.size())
	{
		bus_line* p = nullptr;
		read_string_to_bus_line_add(li, p);
		for (size_t i = 0; i < line_list.size(); i++)
		{
			if (p->name == line_list[i].name && i != u)
			{
				cout << "������������������" << endl;
				delete p;
				return true;
			}
		}
		line_list[u] = *p;
		delete p;
	}
	else
	{
		cout << "������ų�����Χ��������" << endl;
		return 1;
	}
	write_bus_line_list();
	stop_update();
	return 0;
}
bool bus_system::line_add(const string& li)
{

	bus_line* p = nullptr;
	read_string_to_bus_line_add(li, p);
	for (size_t i = 0; i < line_list.size(); i++)
	{
		if (p->name == line_list[i].name)
		{
			//cout << "������������������" << endl;
			delete p;
			return true;
		}
	}
	line_list.push_back(*p);
	delete p;
	write_bus_line_list();
	stop_update();
	return 0;
}
bool bus_system::stop_update()
{
	stop_list.clear();
	line_list.clear();
	get_name_to_stop_list();
	creat_line_list();
	creat_stop_list();
	return 0;
}
bool bus_system::check_string_to_busline(const string & check_string)
{
	vector<string> temp_list;
	string temp_string = "";
	for (size_t i = 0; i < check_string.length(); i++)
	{
		if (check_string[i] != ' ')
		{
				temp_string = temp_string + check_string[i];
		}
		else
		{
			if (temp_string.length() != 0)
			{
				temp_list.push_back(temp_string);
				temp_string = "";
			}
		}
	}
	//�Կհ׷�Ϊ�ָ���ָ�check_string,���������temp_list��
	if (temp_list.size() < 9)
	{
		return 1;
	}
	//������վ��·��������Ҫ
	size_t pos = 0;//�����һ��#������λ��
	for (size_t i = 0; i < temp_list.size(); i++)
	{
		if (temp_list[i] == "#")
		{
			pos = i;
			break;
		}
	}
	//��ȡ��һ��#������λ��
	if (!pos)
	{
		return 1;
	}
	//�������λ��Ϊ0�򷵻ش���
	if (temp_list.size() - 1 < pos+3)
	{
		if (temp_list.size() - 1 != pos + 2)
		{
			return 1;
		}
		else
		{
			if (temp_string[0] != '#')
			{
				return 1;
			}
		}

	}
	else
	{
		if (temp_list[pos + 3][0] != '#')
		{
			return 1;
		}
	}
	//��֤��һ��#�ź�������ַ����ĵ�һ���ַ��Ƿ�Ϊ#��
	for (size_t i = 2; i < pos; i+=2)
	{
		if (!checkthis(temp_list[i]))
		{
			return 1;
		}
	}
	//���Ԥ��ʱ��λ�����Ƿ��Ϊ������
	if (pos % 2 != 0)
	{
		return  1;
	}
	//�Ϸ�������pos��ֻ��Ϊż��
	for (int i = 1; i <3; i++)
	{
		size_t  _pos_ = 0;//����':'����λ��
		_pos_ = temp_list[pos + i].find(':');
		if (_pos_ == string::npos)
		{
			return 1;
		}
		else
		{
			if (!checkthis(temp_list[pos + i].substr(0, _pos_)) || temp_list[pos + i].substr(0, _pos_).length() > 2|| temp_list[pos + i].substr(0, _pos_).length()<1)
			{
				return 1;
			}
			if (!checkthis(temp_list[pos + i].substr(_pos_ + 1, temp_list[pos + i].length() - 1 - _pos_)) || temp_list[pos + i].substr(_pos_ + 1, temp_list[pos + i].length() - 1 - _pos_).length() > 2|| temp_list[pos + i].substr(_pos_ + 1, temp_list[pos + i].length() - 1 - _pos_).length()<1)
			{
				return 1;
			}
		}		
	}
	//����װ೵ʱ����ĩ�೵ʱ���Ƿ����Ҫ��
	return 0;
}
bool bus_system::check_file()
{
	ifstream bus_data_file;
	bus_data_file.open(file_name, ios::in);
	if (!bus_data_file.is_open())
	{
		char* cwd = _getcwd(NULL, 0);
		cout << "δ�ɹ����ļ���" << cwd << "\\" << file_name << "\n�����ļ��Ƿ���ڻ������Ա����·���Դ����ļ�" << endl;
		return 1;
	}
	while (!bus_data_file.eof())
	{
		string file_line = "";
		getline(bus_data_file, file_line);
		if (bus_data_file.eof())
		{
			break;
		}
		if (check_string_to_busline(file_line))
		{
			std::cout << "�ļ��г��ִ����ʽ�����ݣ����ݶ�ȡʧ�ܣ��ļ����Զ����\n";
			bus_data_file.close();
			ofstream bus_data_file;
			bus_data_file.open(file_name, ios::out);
			bus_data_file.close();
			return 1;
		}
	}
	bus_data_file.close();
	return 0;
}