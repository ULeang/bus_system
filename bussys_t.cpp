#include "bussys.h"
#include <iostream>
#include <fstream>
#include <direct.h>
#include <vector>

using namespace std;
bool bus_system::get_name_to_stop_list()
{
	ifstream bus_data_file;
	bus_data_file.open(file_name, ios::in);
	if (!bus_data_file.is_open())
	{
		char* cwd = _getcwd(NULL, 0);
		cout << "未成功打开文件：" << cwd<<"\\" << file_name << "请检查文件是否存在" << endl;
		return 1;
	}
	string temp;
	string p_flush;
	while (!bus_data_file.eof())
	{
		bus_data_file >> temp;
		if (temp == "#")
		{
			getline(bus_data_file, p_flush);
			if (bus_data_file.eof())
			{
				break;
			}
			bus_data_file >> temp;
		}
		else if (temp.length() == 0)
		{
			break;
		}
		bus_data_file >> temp;
		stop_list.push_back(bus_stop(temp, vector<int>()));
		for (int i = 0; i < stop_list.size() - 1; i++)//去除重复
		{
			if (temp == stop_list[i].name)
			{
				stop_list.pop_back();
				break;
			}
		}
	}
	bus_data_file.close();//获取所有站点名称
	return 0;
}
bool bus_system::creat_line_list()
{
	if (stop_list.empty())
	{
		cout << "请检查" << file_name << "是否为空" << endl;
	}

	string line_name;
	string temp_stop_name;
	ifstream bus_data_file;
	bus_data_file.open(file_name, ios::in);
	if (!bus_data_file.is_open())
	{
		char* cwd = _getcwd(NULL, 0);
		cout << "未成功打开文件：" << cwd <<"\\" << file_name << "请检查文件是否存在" << endl;
		return 1;
	}

	while (!bus_data_file.eof())
	{
		vector<int>stop_number;
		vector<bus_line::time>estimated_time;
		bus_data_file >> line_name;
		if (bus_data_file.eof())
		{
			break;
		}
		string temp_time;
		while (true)
		{
			unsigned time = 0;
			bus_data_file >> temp_stop_name;
			for (int i = 0; i < stop_list.size(); i++)
			{
				if (temp_stop_name == stop_list[i].name) {
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
		}//读取路线中所有站名并转换为对应序号，已经所有站间预估时间

		unsigned time_1 = 0;
		unsigned time_2 = 0;
		int g = 0;
		bus_data_file >> temp_time;
		g = temp_time.find(":");
		time_1 = stoi(temp_time.substr(0, g));
		time_2 = stoi(temp_time.substr(g + 1, temp_time.length() - 1 - g));
		bus_line::time first_temp(time_1,time_2);
		bus_data_file >> temp_time;
		g = temp_time.find(":");
		time_1= stoi(temp_time.substr(0,g));
		time_2 = stoi(temp_time.substr(g + 1, temp_time.length() -1-g));		
		bus_line::time last_temp(time_1, time_2);
		bus_line Temp(line_name, stop_number, estimated_time, first_temp, last_temp);
		string p;
		getline(bus_data_file, p);
		line_list.push_back(Temp);
		//获取首班车时间和末班车时间
	}
	bus_data_file.close();
	return 0;
}
bool bus_system::creat_stop_list()
{
	if (line_list.empty())
	{
		cout << "line_list为空，请检查是否创建line_list" << endl;
		return 1;
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
bool bus_system::write_bus_line_list()
{
	ofstream data_bus_file;
	data_bus_file.open(file_name, ios::out);
	for (int j = 0; j < line_list.size(); j++)
	{
		if (j != 0)
		{
			data_bus_file << "\n" + line_list[j].name + " ";
		}
		else
		{
			data_bus_file << line_list[j].name + " ";
		}
		for (int i = 0; i < line_list[j].line.size(); i++)
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
	string line_name;
	for (int i = 0; i < li.length(); i++)//以空白符分割字符串
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
	for (int i = 1; i < temp_list.size() - 3; i += 2)//修改stop_list;
	{
		stop_list.push_back(bus_stop(temp_list[i], vector<int>()));
		for (int j = 0; j < stop_list.size() - 1; j++)//去除重复
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
	line_name = temp_list[n++];

	string temp_time;
	string temp_stop_name;
	while (true)
	{
		unsigned time = 0;
		temp_stop_name = temp_list[n++];
		for (int i = 0; i < stop_list.size(); i++)
		{
			if (temp_stop_name == stop_list[i].name) {
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
	unsigned time_1 = 0;
	unsigned time_2 = 0;
	int g = 0;
	temp_time=temp_list[n++];
	g = temp_time.find(":");
	time_1 = stoi(temp_time.substr(0, g));
	time_2 = stoi(temp_time.substr(g + 1, temp_time.length() - 1 - g));
	bus_line::time first_temp(time_1, time_2);
	temp_time = temp_list[n++];
	g = temp_time.find(":");
	time_1 = stoi(temp_time.substr(0, g));
	time_2 = stoi(temp_time.substr(g + 1, temp_time.length() - 1 - g));
	bus_line::time last_temp(time_1, time_2);
	bus_line Temp(line_name, stop_number, estimated_time, first_temp, last_temp);
	p = new bus_line(line_name, stop_number, estimated_time, first_temp, last_temp);
	return false;
}//指针p接收生成的bus_line对象
bool bus_system::line_delete(const unsigned& u)
{
	if (u < line_list.size())
	{
		vector<bus_line>::iterator it = line_list.begin() + u;
		line_list.erase(it);
	}
	else
	{
		cout << "输入序号超出范围，请重试" << endl;
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
		for (int i = 0; i < line_list.size(); i++)
		{
			if (p->name == line_list[i].name && i != u)
			{
				cout << "存在重名现象，请重试" << endl;
				delete p;
				return true;
			}
		}
		line_list[u] = *p;
		delete p;
	}
	else
	{
		cout << "输入序号超出范围，请重试" << endl;
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
	for (int i = 0; i < line_list.size(); i++)
	{
		if (p->name == line_list[i].name)
		{
			cout << "存在重名现象，请重试" << endl;
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