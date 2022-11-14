#include "bussys.h"
#include <direct.h>

using namespace std;
//return 0;表示0 error，reutrn 1; 表示报错
bool bus_system::get_name_to_stop_list()
{
	ifstream bus_data_file;
	bus_data_file.open(file_name, ios::in);
	//if (!bus_data_file.is_open())
	//{
	//	char* cwd = _getcwd(NULL, 0);
	//	cout << "未成功打开文件：" << cwd<<"\\" << file_name << "\n请检查文件是否存在或请管理员增加路线以创建文件" << endl;
	//	return 1;
	//}
	
	//临时储存站名
	string temp_stop_name;
	string p_flush;
	while (!bus_data_file.eof())
	{
		bus_data_file >> temp_stop_name;
		if (temp_stop_name == "#")
		{
			getline(bus_data_file, p_flush);//读完站名将文件指针跳到下一行
			if (bus_data_file.eof())
			{
				break;
			}
			bus_data_file >> temp_stop_name;//接收下一行线路名以移动文件指针
			if (bus_data_file.eof())
			{
				break;
			}
		}
		else if (temp_stop_name.length() == 0)
		{
			break;
		}
		bus_data_file >> temp_stop_name;//这时确认temp_stop_name储存的为站名
		stop_list.push_back(bus_stop(temp_stop_name, vector<int>()));
		for (size_t i = 0; i < stop_list.size() - 1; i++)//去除重复
		{
			if (temp_stop_name == stop_list[i].name)
			{
				stop_list.pop_back();
				break;
			}
		}
		//检查推入的bus_stop是否存在和之前的重名，有则推出stop_list
	}
	bus_data_file.close();
	return 0;
}
bool bus_system::creat_line_list()
{
	if (stop_list.empty())
	{
		//cout << "请检查" << file_name << "是否为空" << endl;
	}

	ifstream bus_data_file;
	bus_data_file.open(file_name, ios::in);
	if (!bus_data_file.is_open())
	{
		//char* cwd = _getcwd(NULL, 0);
		//cout << "未成功打开文件：" << cwd <<"\\" << file_name << "请检查文件是否存在" << endl;
		return 1;
	}

	string line_name;
	string temp_stop_name;
	while (!bus_data_file.eof())
	{
		vector<int>stop_number;//储存该路线的所有站点序号
		vector<bus_line::time>estimated_time;//储存该路线所有站与站直接的预估时间
		
		bus_data_file >> line_name;
		if (bus_data_file.eof())
		{
			break;
		}

		string temp_time;
		while (true)
		{
			unsigned time = 0;

			bus_data_file >> temp_stop_name;//获取站名

			for (size_t i = 0; i < stop_list.size(); i++)
			{
				if (temp_stop_name == stop_list[i].name)
				{
					stop_number.push_back(i);
				}
			}
			//站名并转换为对应序号

			bus_data_file >> temp_time;//获取预估时间

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
		//读取路线中所有站名并转换为对应序号，已经所有站间预估时间
		
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
		//获取首班车和末班车时间

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
		//cout << "line_list为空，请检查是否创建line_list" << endl;
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
	//为每个bus_stop的connect_to_number赋值
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
	for (size_t i = 0; i < li.length(); i++)//以空白符分割字符串
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
	//修改stop_list;
	for (size_t i = 1; i < temp_list.size() - 3; i += 2)
	{
		stop_list.push_back(bus_stop(temp_list[i], vector<int>()));
		for (size_t j = 0; j < stop_list.size() - 1; j++)//去除重复
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
}//指针p接收生成的bus_line对象
bool bus_system::line_delete(const unsigned& u)
{
	if (u < line_list.size())
	{
		vector<bus_line>::iterator it = line_list.begin() + u;
		line_list.erase(it);//从line_list中删除对应bus_line
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
		for (size_t i = 0; i < line_list.size(); i++)
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
	for (size_t i = 0; i < line_list.size(); i++)
	{
		if (p->name == line_list[i].name)
		{
			//cout << "存在重名现象，请重试" << endl;
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
	//以空白符为分割符分割check_string,结果储存在temp_list中
	if (temp_list.size() < 9)
	{
		return 1;
	}
	//有两个站的路线最少需要
	size_t pos = 0;//储存第一个#号所在位置
	for (size_t i = 0; i < temp_list.size(); i++)
	{
		if (temp_list[i] == "#")
		{
			pos = i;
			break;
		}
	}
	//获取第一个#号所在位置
	if (!pos)
	{
		return 1;
	}
	//如果＃号位置为0则返回错误
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
	//验证第一个#号后第三个字符串的第一个字符是否为#号
	for (size_t i = 2; i < pos; i+=2)
	{
		if (!checkthis(temp_list[i]))
		{
			return 1;
		}
	}
	//检查预估时间位置上是否均为纯数字
	if (pos % 2 != 0)
	{
		return  1;
	}
	//合法输入中pos中只能为偶数
	for (int i = 1; i <3; i++)
	{
		size_t  _pos_ = 0;//储存':'所在位置
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
	//检查首班车时间与末班车时间是否符合要求
	return 0;
}
bool bus_system::check_file()
{
	ifstream bus_data_file;
	bus_data_file.open(file_name, ios::in);
	if (!bus_data_file.is_open())
	{
		char* cwd = _getcwd(NULL, 0);
		cout << "未成功打开文件：" << cwd << "\\" << file_name << "\n请检查文件是否存在或请管理员增加路线以创建文件" << endl;
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
			std::cout << "文件中出现错误格式的数据，内容读取失败，文件已自动清空\n";
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