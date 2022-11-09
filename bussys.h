#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>

class bus_system
{
	using All_line = std::vector<std::vector<int>>;
	using Line = std::vector<int>;

private:
	class bus_stop
	{
	public:
		std::string name;//站点名
		std::vector<int> connect_to_number;//所有能直接到达站点序号

		bool found = false;//用于标记是否已发现

		bus_stop(std::string na, std::vector<int> ctn) :name(std::move(na)), connect_to_number(std::move(ctn)) {}
	};

	class bus_line
	{
	public:
		class time
		{
		public:
			unsigned hour;
			unsigned minute;

			bool operator>(const time& t)const;
			bool operator<(const time& t)const;
			time operator+(const time& t)const;
			time& operator+=(const time& t) { *this = *this + t; return *this; }

			time() :hour(0), minute(0) {}
			time(unsigned m) { hour = m / 60; minute = m % 60; }
			time(unsigned h, unsigned m) { hour = h + m / 60; minute = m % 60; }

			operator std::string()const { return std::to_string(hour) + ":" + std::to_string(minute); }
			//实验性质，待检验
			//friend std::ostream& operator<<(std::ostream& o, const time& t) { o << t.hour << ':' << t.minute; return o; }
		};

	public:
		std::string name;//线路名
		std::vector<int> line;//所有站点下标
		std::vector<time> estimated_time;//两站点间预估时间
		time first;//首班车时间
		time last;//末班车时间

		bus_line(std::string na, std::vector<int> li, std::vector<time> et, time f, time l) :name(std::move(na)), line(std::move(li)), estimated_time(std::move(et)), first(f), last(l) {}

		unsigned line_check(const Line& li, time& t, unsigned u = 0)const;//给定某一线路li，返回该线路从第u个站点开始的前n个站点位于本线路中，将时间存入t中
	};

private:
	std::vector<bus_line> line_list;
	std::vector<bus_stop> stop_list;

private:
	bool admin;//管理员权限
	bool admin_menu();
	bool user_menu();
public:
	bus_system(const std::string& str = "bus_system.txt", bool ad = false) :file_name(str)
	{
		get_stop_name_list();
		creat_line_list();
		creat_stop_list();
	}//str为站点线路txt文件，默认存储及读取位置为bus_system.txt

public:
	void menu();//显示主菜单

	bool switch_privilege() { admin = !admin; return admin; }//切换管理员权限/普通用户权限
	bool show_privilege()const { return admin; }//返回管理员权限

	int line_query(const std::string& start, const std::string& end, std::string* str);//查询两站点间线路，将换乘最少的线路、站数最少的线路及其预估总时间和首末班车时间存入str中，str是一个指向包含两个string元素数组的指针。返回0无可到达路线，1两路线相同，2两路线不同，-1找不到站点，-2始末点相同
	bool line_showsingle(const std::string& li, std::string* str)const;//将某线路所有站点存入str中，str是一个指向包含一个string元素数组的指针
	bool line_showall(std::string* str)const;//将所有线路所有站点存入str中，str是一个指向至少包含line_list.size()个string元素数组的指针

private:
	//新成员函数放这里
	int get_stop_subscript(const std::string& st)const;//返回站点st在内存中的下标，不存在则返回-1
	int get_line_subscript(const std::string& li)const;//返回线路li在内存中的下标，不存在则返回-1
	bool find_end(int stn, int edn, All_line& all_line, Line& temp_line);//寻找从下标stn到edn的所有可能路线，追加到all_line末尾，调用后需把stop_list[stn].found置为false
	int handle_transfer(const Line& li, int u = 0)const;//返回路线li从第u项开始的最小换乘数（贪心算法）
	bool final_plan(const Line& li, std::string* str, int u = 0, bus_line::time ti = { 0,0 })const;//将路线li的最终乘车方案（贪心算法）追加到str末尾
	std::string get_stop_name(int sub)const;//返回下标sub对应的站点名
	std::string get_line_name(int sub)const;//返回下标sub对应的路线名

	const std::string file_name;
	std::vector<std::string>stop_name_list;
	bool get_stop_name_list();
	bool creat_line_list();
	bool creat_stop_list();
	bool write_bus_line_list();
	bool stop_update();//全体更新
	bool line_add(const std::string& li);// li为符合要求的字符串，仅管理员
	bool line_delete(unsigned u);//删除下标为u的线路，仅管理员
	bool line_update(unsigned u, const std::string& li);//将下标为u的线路改为li，仅管理员
	bool read_string_to_bus_line_add(const std::string& li, bus_line*& p);
};