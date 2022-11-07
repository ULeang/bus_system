#include "bussys.h"
#include <iostream>
#include <fstream>
#include <direct.h>
#include <vector>
#include <math.h>

using namespace std;

vector<string> bus_system::get_stop_name_list()
{
	vector<string>stop_name_vector;
	ifstream bus_data_file;
	bus_data_file.open("bus_system.txt", ios::in);
	if (!bus_data_file.is_open())
	{
		char* cwd = _getcwd(NULL, 0);
		cout << "未成功打开文件：" << cwd << "\\bus_system.txt" << "请检查文件是否存在" << endl;
		return stop_name_vector;
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
		stop_name_vector.push_back(temp);
		for (int i = 0; i < stop_name_vector.size() - 1; i++)//去除重复
		{
			if (temp == stop_name_vector[i])
			{
				stop_name_vector.pop_back();
				break;
			}
		}
	}
	delete[] p_flush;
	p_flush = NULL;
	bus_data_file.close();//获取所有站点名称
	return stop_name_vector;
}
vector<bus_system::bus_line> bus_system::creat_line_list(vector<string> stop_name_list)
{
	vector<bus_line> line_list;
	int m = 0;
	string line_name;
	string temp_stop_name;
	vector<int>stop_number;
	vector<bus_line::time>estimated_time;
	ifstream bus_data_file;
	bus_data_file.open("bus_system.txt", ios::in);
	if (!bus_data_file.is_open())
	{
		char* cwd = _getcwd(NULL, 0);
		cout << "未成功打开文件：" << cwd << "\\bus_system.txt" << "请检查文件是否存在" << endl;
		return vector<bus_system::bus_line>();
	}
	while (!bus_data_file.eof())
	{
		estimated_time.clear();
		stop_number.clear();
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
		//将5；55的形式转换为两个unsigned类型的数,并创建first_temp和last_temp
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
		bus_line Temp(m, line_name, stop_number, estimated_time, first_temp, last_temp);
		m++;
		char* p_flush = new char[256];
		bus_data_file.getline(p_flush, 256);
		delete[] p_flush;
		p_flush = NULL;
		line_list.push_back(Temp);
	}
	bus_data_file.close();
	return line_list;
}
vector<bus_system::bus_stop>bus_system::creat_stop_list(vector<string> stop_name_list, vector<bus_system::bus_line>line_list)
{
	vector<bus_system::bus_stop>stop_list;
	for (int i = 0; i < stop_name_list.size(); i++)
	{
		bus_stop temp(i, stop_name_list[i], vector<int>());
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
	return stop_list;
}
bus_system::bus_system(const char* str, bool ad)
{
	vector<string>stop_name_list = get_stop_name_list();
	line_list = creat_line_list(stop_name_list);
	stop_list = creat_stop_list(stop_name_list, line_list);
}