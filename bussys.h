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
		std::string name;//վ����
		std::vector<int> connect_to_number;//������ֱ�ӵ���վ�����

		bool found = false;//���ڱ���Ƿ��ѷ���

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
			//ʵ�����ʣ�������
			//friend std::ostream& operator<<(std::ostream& o, const time& t) { o << t.hour << ':' << t.minute; return o; }
		};

	public:
		std::string name;//��·��
		std::vector<int> line;//����վ���±�
		std::vector<time> estimated_time;//��վ���Ԥ��ʱ��
		time first;//�װ೵ʱ��
		time last;//ĩ�೵ʱ��

		bus_line(std::string na, std::vector<int> li, std::vector<time> et, time f, time l) :name(std::move(na)), line(std::move(li)), estimated_time(std::move(et)), first(f), last(l) {}

		unsigned line_check(const Line& li, time& t, unsigned u = 0)const;//����ĳһ��·li�����ظ���·�ӵ�u��վ�㿪ʼ��ǰn��վ��λ�ڱ���·�У���ʱ�����t��
	};

private:
	std::vector<bus_line> line_list;
	std::vector<bus_stop> stop_list;

private:
	bool admin;//����ԱȨ��
	bool admin_menu();
	bool user_menu();
public:
	bus_system(const std::string& str = "bus_system.txt", bool ad = false) :file_name(str)
	{
		get_stop_name_list();
		creat_line_list();
		creat_stop_list();
	}//strΪվ����·txt�ļ���Ĭ�ϴ洢����ȡλ��Ϊbus_system.txt

public:
	void menu();//��ʾ���˵�

	bool switch_privilege() { admin = !admin; return admin; }//�л�����ԱȨ��/��ͨ�û�Ȩ��
	bool show_privilege()const { return admin; }//���ع���ԱȨ��

	int line_query(const std::string& start, const std::string& end, std::string* str);//��ѯ��վ�����·�����������ٵ���·��վ�����ٵ���·����Ԥ����ʱ�����ĩ�೵ʱ�����str�У�str��һ��ָ���������stringԪ�������ָ�롣����0�޿ɵ���·�ߣ�1��·����ͬ��2��·�߲�ͬ��-1�Ҳ���վ�㣬-2ʼĩ����ͬ
	bool line_showsingle(const std::string& li, std::string* str)const;//��ĳ��·����վ�����str�У�str��һ��ָ�����һ��stringԪ�������ָ��
	bool line_showall(std::string* str)const;//��������·����վ�����str�У�str��һ��ָ�����ٰ���line_list.size()��stringԪ�������ָ��

private:
	//�³�Ա����������
	int get_stop_subscript(const std::string& st)const;//����վ��st���ڴ��е��±꣬�������򷵻�-1
	int get_line_subscript(const std::string& li)const;//������·li���ڴ��е��±꣬�������򷵻�-1
	bool find_end(int stn, int edn, All_line& all_line, Line& temp_line);//Ѱ�Ҵ��±�stn��edn�����п���·�ߣ�׷�ӵ�all_lineĩβ�����ú����stop_list[stn].found��Ϊfalse
	int handle_transfer(const Line& li, int u = 0)const;//����·��li�ӵ�u�ʼ����С��������̰���㷨��
	bool final_plan(const Line& li, std::string* str, int u = 0, bus_line::time ti = { 0,0 })const;//��·��li�����ճ˳�������̰���㷨��׷�ӵ�strĩβ
	std::string get_stop_name(int sub)const;//�����±�sub��Ӧ��վ����
	std::string get_line_name(int sub)const;//�����±�sub��Ӧ��·����

	const std::string file_name;
	std::vector<std::string>stop_name_list;
	bool get_stop_name_list();
	bool creat_line_list();
	bool creat_stop_list();
	bool write_bus_line_list();
	bool stop_update();//ȫ�����
	bool line_add(const std::string& li);// liΪ����Ҫ����ַ�����������Ա
	bool line_delete(unsigned u);//ɾ���±�Ϊu����·��������Ա
	bool line_update(unsigned u, const std::string& li);//���±�Ϊu����·��Ϊli��������Ա
	bool read_string_to_bus_line_add(const std::string& li, bus_line*& p);
};