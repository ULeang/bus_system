#include "bussys.h"

bool bus_system::bus_line::time::operator>(const time& t) const
{
	if (hour == t.hour)
		return minute > t.minute;
	else
		return hour > t.hour;
}

bool bus_system::bus_line::time::operator<(const time& t) const
{
	if (hour == t.hour)
		return minute < t.minute;
	else
		return hour < t.hour;
}

bus_system::bus_line::time bus_system::bus_line::time::operator+(const time& t) const
{
	unsigned m = minute + t.minute;
	unsigned h = hour + t.hour + m / 60;
	m %= 60;
	return time{ h, m };
}

unsigned bus_system::bus_line::line_check(const Line& li, time& t, unsigned u) const
{
	unsigned n = 0;
	t = { 0,0 };
	for (int i = 0; i < line.size() && u < li.size(); ++i)
	{
		if (li[u] == line[i])
		{
			t += (n ? estimated_time[i - 1] : time{ 0,0 });
			++n; ++u;
		}
		else if (n)
			break;
	}
	return n;
}

int bus_system::line_query(const std::string& start, const std::string& end, std::string* str)
{
	int st = get_stop_subscript(start), ed = get_stop_subscript(end);
	if (st == -1 || ed == -1)
		return -1;

	if (st == ed)
		return -2;

	All_line al; Line li;
	find_end(st, ed, al, li);
	stop_list[st].found = false;
	if (al.size() == 0)
		return 0;

	//换乘最少
	int subscript_t = -1, transfer_num = 65535;
	for (int i = 0; i < al.size(); ++i)
		if (handle_transfer(al[i]) < transfer_num)
		{
			subscript_t = i;
			transfer_num = handle_transfer(al[i]);//懒得优化了，应该没事的吧
		}

	//站数最少
	int subscript_s = -1, stop_num = 65535;
	for (int i = 0; i < al.size(); ++i)
		if (al[i].size() < stop_num)
		{
			subscript_s = i;
			stop_num = al[i].size();
		}

	final_plan(al[subscript_t], str);
	if (subscript_t == subscript_s)
		return 1;

	final_plan(al[subscript_s], str + 1);
	return 2;
}

bool bus_system::line_showsingle(const std::string& li, std::string* str) const
{
	int lin = get_line_subscript(li);
	if (lin == -1)
		return false;

	*str = li + ":";
	for (auto x : line_list[lin].line)
		*str = *str + stop_list[x].name + "*";
	*str = *str + std::string(line_list[lin].first) + "-" + std::string(line_list[lin].last);
	return true;
}

bool bus_system::line_showall(std::string* str) const
{
	for (int i = 0; i < line_list.size(); ++i)
	{
		*(str + i) = std::to_string(i) + "@" + line_list[i].name + ":";
		for (int j = 0; j < line_list[i].line.size() - 1; ++j)
			*(str + i) = *(str + i) + stop_list[line_list[i].line[j]].name + " " + std::string(line_list[i].estimated_time[j]) + " ";
		*(str + i) = *(str + i) + stop_list[*(line_list[i].line.end() - 1)].name + " # " + std::string(line_list[i].first) + "-" + std::string(line_list[i].last);
	}
	return true;
}

int bus_system::get_stop_subscript(const std::string& st) const

{
	int subscript = -1;
	for (int i = 0; i < stop_list.size(); ++i)
		if (stop_list[i].name == st)
		{
			subscript = i;
			break;
		}

	return subscript;
}

int bus_system::get_line_subscript(const std::string& li) const
{
	int subscript = -1;
	for (int i = 0; i < line_list.size(); ++i)
		if (line_list[i].name == li)
		{
			subscript = i;
			break;
		}

	return subscript;
}

bool bus_system::find_end(int stn, int edn, All_line& all_line, Line& temp_line)
{
	temp_line.push_back(stn);
	if (stn == edn)
	{
		all_line.push_back(temp_line);
		temp_line.pop_back();
		return true;
	}

	stop_list[stn].found = true;
	for (int i = 0; i < stop_list[stn].connect_to_number.size(); ++i)
	{
		if (!stop_list[stop_list[stn].connect_to_number[i]].found)
		{
			find_end(stop_list[stn].connect_to_number[i], edn, all_line, temp_line);
			stop_list[stop_list[stn].connect_to_number[i]].found = false;
		}
	}
	temp_line.pop_back();
	return false;
}

int bus_system::handle_transfer(const Line& li, int u) const
{
	int max_stop_num = -1, stop_num = 0;
	bus_line::time ti;
	for (int i = 0; i < line_list.size(); ++i)
		if ((stop_num = line_list[i].line_check(li, ti, u)) > max_stop_num)
			max_stop_num = stop_num;
	if (u + max_stop_num == li.size())
		return 1;
	else
		return 1 + handle_transfer(li, u + max_stop_num - 1);
}

bool bus_system::final_plan(const Line& li, std::string* str, int u, bus_line::time ti) const
{
	int subscript = -1;
	bus_line::time t, tt;
	int max_stop_num = -1, stop_num = 0;
	for (int i = 0; i < line_list.size(); ++i)
		if ((stop_num = line_list[i].line_check(li, tt, u)) > max_stop_num)
		{
			max_stop_num = stop_num;
			subscript = i;
			t = tt;
		}
	*str = *str + stop_list[li[u]].name + "—" + line_list[subscript].name + "线" + std::to_string(max_stop_num - 1) + "站—>";
	if (u + max_stop_num == li.size())
	{
		*str = *str + stop_list[*(li.end() - 1)].name + "#" + std::string(ti + t);
		return true;
	}
	else
	{
		final_plan(li, str, u + max_stop_num - 1, ti + t);
		return false;
	}
}

std::string bus_system::get_stop_name(int num) const
{
	for (int i = 0; i < stop_list.size(); ++i)
		if (i == num)
			return stop_list[i].name;
	return "null";
}

std::string bus_system::get_line_name(int num) const
{
	for (int i = 0; i < stop_list.size(); ++i)
		if (i == num)
			return line_list[i].name;
	return "null";
}