#include "bussys.h"
#include <iostream>
#include <fstream>
#include <direct.h>
#include <vector>
#include <math.h>

using namespace std;
bool bus_system::get_stop_name_list()
{
	ifstream bus_data_file;
	bus_data_file.open(file_name, ios::in);
	if (!bus_data_file.is_open())
	{
		char* cwd = _getcwd(NULL, 0);
		cout << "δ�ɹ����ļ���" << cwd << file_name << "�����ļ��Ƿ����" << endl;
		return 1;
	}
	string temp;
	char* p_flush = new char[256];
	while (!bus_data_file.eof())
	{
		bus_data_file >> temp;
		if (temp == "#")
		{
			bus_data_file.getline(p_flush, 256);
			if (bus_data_file.eof())
			{
				break;
			}
			bus_data_file >> temp;
		}
		bus_data_file >> temp;
		stop_name_list.push_back(temp);
		for (int i = 0; i < stop_name_list.size() - 1; i++)//ȥ���ظ�
		{
			if (temp == stop_name_list[i])
			{
				stop_name_list.pop_back();
				break;
			}
		}
	}
	delete[] p_flush;
	p_flush = NULL;
	bus_data_file.close();//��ȡ����վ������
	return 0;
}
bool bus_system::creat_line_list()
{
	if (stop_name_list.empty())
	{
		cout << "����" << file_name << "�Ƿ�Ϊ��" << endl;
	}
	string line_name;
	string temp_stop_name;
	ifstream bus_data_file;
	bus_data_file.open(file_name, ios::in);
	if (!bus_data_file.is_open())
	{
		char* cwd = _getcwd(NULL, 0);
		cout << "δ�ɹ����ļ���" << cwd << file_name << "�����ļ��Ƿ����" << endl;
		return 1;
	}
	while (!bus_data_file.eof())
	{
		vector<int>stop_number;
		vector<bus_line::time>estimated_time;
		bus_data_file >> line_name;
		string temp_time;
		while (true)
		{
			unsigned time = 0;
			bus_data_file >> temp_stop_name;
			for (int i = 0; i < stop_name_list.size(); i++)
			{
				if (temp_stop_name == stop_name_list[i]) {
					stop_number.push_back(i);
				}
			}
			bus_data_file >> temp_time;
			if (temp_time == "#") {
				break;
			}
			else {
				for (int k = 0; k < temp_time.length(); k++)
				{
					time = time * 10 + int(temp_time[k]) - 48;
				}
			}
			estimated_time.push_back(bus_line::time(time));
		}
		unsigned first_time_1 = 0;
		unsigned first_time_2 = 0;
		unsigned last_time_1 = 0;
		unsigned last_time_2 = 0;
		bus_data_file >> temp_time;
		int g = 0;
		for (int j = 0; j < temp_time.length(); j++)
		{
			if (temp_time[j] != ':')
			{
				first_time_1 = first_time_1 * 10 + int(temp_time[j]) - 48;
			}
			else
			{
				g = j;
				break;
			}
		}
		for (int j = g + 1; j < temp_time.length(); j++)
		{
			if (temp_time[j] != ':')
			{
				first_time_2 = first_time_2 * 10 + int(temp_time[j]) - 48;
			}
			else
			{
				break;
			}
		}
		bus_data_file >> temp_time;
		//��5��55����ʽת��Ϊ����unsigned���͵���,������first_temp��last_temp
		for (int j = 0; j < temp_time.length(); j++)
		{
			if (temp_time[j] != ':')
			{
				last_time_1 = last_time_1 * 10 + int(temp_time[j]) - 48;
			}
			else
			{
				g = j;
				break;
			}
		}
		for (int j = g + 1; j < temp_time.length(); j++)
		{
			if (temp_time[j] != ':')
			{
				last_time_2 = last_time_2 * 10 + int(temp_time[j]) - 48;
			}
			else
			{
				break;
			}
		}
		bus_line::time first_temp(first_time_1, first_time_2);
		bus_line::time last_temp(last_time_1, last_time_2);
		bus_line Temp(line_name, stop_number, estimated_time, first_temp, last_temp);
		char* p_flush = new char[256];
		bus_data_file.getline(p_flush, 256);
		delete[] p_flush;
		p_flush = NULL;
		line_list.push_back(Temp);
	}
	bus_data_file.close();
	return 0;
}
bool bus_system::creat_stop_list()
{
	if (line_list.empty())
	{
		cout << "line_listΪ�գ������Ƿ񴴽�line_list" << endl;
		return 1;
	}
	for (int i = 0; i < stop_name_list.size(); i++)
	{
		bus_stop temp(stop_name_list[i], vector<int>());
		stop_list.push_back(temp);
	}
	for (int i = 0; i < line_list.size(); i++)
	{
		for (int j = 0; j < line_list[i].line.size() - 1; j++)
		{
			int number1 = line_list[i].line[j];
			int number2 = line_list[i].line[j + 1];
			stop_list[number1].connect_to_number.push_back(number2);
		}
	}
	return 0;
}
bool bus_system::write_bus_line(ofstream& file, bus_line line)
{
	file << line.name + " ";
	for (int i = 0; i < line.line.size(); i++)
		file << stop_list[line.line[i]].name + " ";
	file << "# " << line.first.hour << ":" << line.first.minute << " " << line.last.hour << ":" << line.last.minute << " #\n";
	return 0;
}
bus_system::bus_system(const char* str, bool ad)
{
	file_name = str;
	get_stop_name_list();
	creat_line_list();
	creat_stop_list();
}
bus_system::bus_line bus_system::read_string_to_bus_line_add(const string& li)
{
	vector<string> temp_list;
	string temp_string;
	string line_name;
	for (int i = 0; i < li.length(); i++)//�Կհ׷��ָ��ַ���
	{
		if (li[i] != ' ')
		{
			temp_string = temp_string + li[i];
		}
		else
		{
			temp_list.push_back(temp_string);
			temp_string = "";
		}
	}
	for (int i = 1; i < temp_list.size() - 4; i += 2)//�޸�stop_name_list;
	{
		stop_name_list.push_back(temp_list[i]);
		for (int j = 0; j < stop_name_list.size() - 1; j++)//ȥ���ظ�
		{
			if (temp_list[i] == stop_name_list[i])
			{
				stop_name_list.pop_back();
				break;
			}
		}
	}
	//����line_list
	int n = 0;
	vector<int>stop_number;
	vector<bus_line::time>estimated_time;
	line_name = temp_list[n++];
	string temp_time;
	string temp_stop_name;
	while (true)
	{
		unsigned time = 0;
		temp_stop_name = temp_list[n++];
		for (int i = 0; i < stop_name_list.size(); i++)
		{
			if (temp_stop_name == stop_name_list[i]) {
				stop_number.push_back(i);
			}
		}
		temp_time = temp_list[n++];
		if (temp_time == "#") {
			break;
		}
		else {
			for (int k = 0; k < temp_time.length(); k++)
			{
				time = time * 10 + int(temp_time[k]) - 48;
			}
		}
		estimated_time.push_back(bus_line::time(time));
	}
	unsigned first_time_1 = 0;
	unsigned first_time_2 = 0;
	unsigned last_time_1 = 0;
	unsigned last_time_2 = 0;
	temp_time = temp_list[n++];
	int g = 0;
	for (int j = 0; j < temp_time.length(); j++)
	{
		if (temp_time[j] != ':')
		{
			first_time_1 = first_time_1 * 10 + int(temp_time[j]) - 48;
		}
		else
		{
			g = j;
			break;
		}
	}
	for (int j = g + 1; j < temp_time.length(); j++)
	{
		if (temp_time[j] != ':')
		{
			first_time_2 = first_time_2 * 10 + int(temp_time[j]) - 48;
		}
		else
		{
			break;
		}
	}
	temp_time = temp_list[n++];
	//��5��55����ʽת��Ϊ����unsigned���͵���,������first_temp��last_temp
	for (int j = 0; j < temp_time.length(); j++)
	{
		if (temp_time[j] != ':')
		{
			last_time_1 = last_time_1 * 10 + int(temp_time[j]) - 48;
		}
		else
		{
			g = j;
			break;
		}
	}
	for (int j = g + 1; j < temp_time.length(); j++)
	{
		if (temp_time[j] != ':')
		{
			last_time_2 = last_time_2 * 10 + int(temp_time[j]) - 48;
		}
		else
		{
			break;
		}
	}
	bus_line::time first_temp(first_time_1, first_time_2);
	bus_line::time last_temp(last_time_1, last_time_2);
	bus_line Temp(line_name, stop_number, estimated_time, first_temp, last_temp);
	return Temp;
}
bool bus_system::line_delete(unsigned u)
{
	if (u <= line_list.size())
	{
		vector<bus_line>::iterator it = line_list.begin() + u - 1;
		line_list.erase(it);
	}
	else
	{
		cout << "error: line_delete(unsigned u)��u>=line_list.size" << endl;
		return 1;
	}
	ofstream bus_data_file;
	bus_data_file.open("srt", ios::out);
	for (int i = 0; i < line_list.size(); i++)
	{
		write_bus_line(bus_data_file, line_list[i]);
	}
	bus_data_file.close();
	stop_update();
	return 0;
}
bool bus_system::line_update(unsigned u, const std::string& li)
{
	if (u <= line_list.size())
	{
		line_list[u - 1] = read_string_to_bus_line_add(li);
	}
	else
	{
		cout << "error: line_update(unsigned u)��u>=line_list.size" << endl;
		return 1;
	}
	ofstream data_bus_file;
	data_bus_file.open(file_name, ios::app);
	write_bus_line(data_bus_file, line_list[line_list.size()]);
	data_bus_file.close();
	stop_update();
	return 0;
}
bool bus_system::line_add(const string& li)
{
	line_list.push_back(read_string_to_bus_line_add(li));
	ofstream data_bus_file;
	data_bus_file.open(file_name, ios::app);
	write_bus_line(data_bus_file, line_list[line_list.size()]);
	data_bus_file.close();
	stop_update();
	return 0;
}
bool bus_system::stop_update()
{
	stop_name_list.clear();
	line_list.clear();
	stop_list.clear();
	get_stop_name_list();
	creat_line_list();
	creat_stop_list();
	return 0;
}
