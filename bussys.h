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

			friend std::ostream& operator<<(std::ostream& o, const time& t) { o << t.hour << ':' << t.minute; return o; }
		};

	public:
		int number;//���
		std::string name;//��·��
		std::vector<int> line;//����վ�����
		std::vector<time> estimated_time;//��վ���Ԥ��ʱ��
		time first;//�װ೵ʱ��
		time last;//ĩ�೵ʱ��

		bus_line(int n, std::string na, std::vector<int> li, std::vector<time> et, time f, time l) :number(n), name(std::move(na)), line(std::move(li)), estimated_time(std::move(et)), first(f), last(l) {}

		unsigned line_check(const Line& li, time& t, unsigned u = 0)const;//����ĳһ��·li�����ظ���·�ӵ�u��վ�㿪ʼ��ǰn��վ��λ�ڱ���·�У���ʱ�����t��
	};

private:
	std::vector<bus_line> line_list;
	std::vector<bus_stop> stop_list;

private:
	bool admin;//����ԱȨ��

public:
	bus_system(const char* str = "bus_system.txt", bool ad = false);//strΪվ����·txt�ļ���Ĭ�ϴ洢����ȡλ��Ϊbus_system.txt

public:
	bool menu();//��ʾ���˵�

	bool switch_privilege() { admin = !admin; return admin; }//�л�����ԱȨ��/��ͨ�û�Ȩ��
	bool show_privilege()const { return admin; }//���ع���ԱȨ��

	int line_query(const std::string& start, const std::string& end, std::string* str);//��ѯ��վ�����·�����������ٵ���·��վ�����ٵ���·����Ԥ����ʱ�����ĩ�೵ʱ�����str�У�str��һ��ָ���������stringԪ�������ָ�롣����0�޿ɵ���·�ߣ�1��·����ͬ��2��·�߲�ͬ��-1�Ҳ���վ�㣬-2ʼĩ����ͬ
	bool line_showsingle(const std::string& li, std::string* str)const;//��ĳ��·����վ�����str�У�str��һ��ָ�����һ��stringԪ�������ָ��
	bool line_showall(std::string* str)const;//��������·����վ�����str�У�str��һ��ָ�����line_list.size()��stringԪ�������ָ��
	bool line_add(std::string li) { return true; }//liΪ����Ҫ����ַ�����������Ա
	bool line_delete(unsigned u) { return true; }//ɾ�����Ϊu����·��������Ա
	bool line_update(unsigned u, std::string li) { return true; }//�����Ϊu����·��Ϊli��������Ա

private:
	bool stop_update() { return true; }//ȫ�����
	bool stop_update_add() { return true; }//��addʱ����

private:
	//�³�Ա����������
	int find_stop(const std::string& st)const;//����վ��st���ڴ��е��±꣬�������򷵻�-1
	int find_line(const std::string& li)const;//������·li���ڴ��е��±꣬�������򷵻�-1
	bool find_end(int stn, int edn, All_line& all_line, Line& temp_line);//Ѱ�Ҵ��±�stn��edn�����п���·�ߣ�׷�ӵ�all_lineĩβ
	int handle_transfer(const Line& li, int u = 0)const;//����·��li�ӵ�u�ʼ����С��������̰���㷨��
	bool final_plan(const Line& li, std::string* str, int u = 0, bus_line::time ti = { 0,0 })const;//��·��li�����ճ˳�������̰���㷨��׷�ӵ�strĩβ
	std::string get_stop_name(int num)const;//�������num��Ӧ��վ����
	int get_stop_subscript(int num)const;//�������num��Ӧ��վ���±�

	std::vector<std::string> get_stop_name_list();
	std::vector<bus_system::bus_line> creat_line_list(std::vector<std::string> stop_name_list);
	std::vector<bus_system::bus_stop>creat_stop_list(std::vector<std::string> stop_name_list, std::vector<bus_system::bus_line>line_list);
	//test
};