#include"player.h"
using namespace std;
class club {
private:
	vector<staff> staffs;//员工
	vector<player> players;//球员
	int cash;//现金
	string clubname;//名称
public:
	club() {
		staffs.clear();
		players.clear();
		cash = 0;
		clubname = "None";
	};
	club(ifstream &infile) {
		staffs.clear();
		players.clear();
		infile >> clubname >> cash;
		int staff_size;
		infile >> staff_size;
		for (int i = 0; i < staff_size; i++) {
			staff new_staff(infile);
			staffs.push_back(new_staff);
		}
		int player_size;
		infile >> player_size;
		for (int i = 0; i < player_size; i++) {
			player new_player(infile);
			players.push_back(new_player);
		}
	}
	~club() {};
	int getcash() { return cash; };
	string getclubname() { return clubname; };
	int getstaffnum() { return staffs.size(); }
	int getplayernum() { return players.size(); };
	void changecash(int Cash) { cash = Cash; };
	void changeclubname(string Name) { clubname = Name; };
	staff getstaff(int i) {
		return staffs[i];
	};
	player getplayer(int i) {
		return players[i];
	};
	void addstaff() {
		staff new_staff;
		string staff_name;
		int age, ability, salary;
		cout << "请输入员工姓名：";
		cin >> staff_name;
		cout << "请输入员工年龄(18~60):";
		cin >> age;
		while (1) {
			if (age > 60 || age < 18) {
				cout << "输入年龄范围有误，请重新输入:" << endl;
				cin >> age;
			}
			else break;
		}
		cout << "请输入员工能力值(0~100)：";
		cin >> ability;
		while (1) {
			if (ability > 100 || ability< 0) {
				cout << "输入能力值范围有误，请重新输入:" << endl;
				cin >> age;
			}
			else break;
		}
		cout << "请输入员工年薪(10~1000)(单位为万)：";
		cin >> salary;
		while (1) {
			if (salary > 1000 || salary< 10) {
				cout << "输入年薪范围有误，请重新输入:" << endl;
				cin >> salary;
			}
			else break;
		}
		new_staff.changestaff(staff_name, age, ability, salary);
		staffs.push_back(new_staff);
	}
	void addplayer(player new_player) {
		players.push_back(new_player);
	}
	void addplayer() {
		player new_player;
		string player_name;
		int age, ability, salary, kick, year, fee;
		cout << "请输入球员姓名：";
		cin >> player_name;
		cout << "请输入球员年龄(18~45):";
		cin >> age;
		while (1) {
			if (age > 45 || age < 18) {
				cout << "输入年龄范围有误，请重新输入:" << endl;
				cin >> age;
			}
			else break;
		}
		cout << "请输入球员能力值(0~100)：";
		cin >> ability;
		while (1) {
			if (age > 100 || age < 0) {
				cout << "输入年龄范围有误，请重新输入:" << endl;
				cin >> ability;
			}
			else break;
		}
		cout << "请输入球员年薪(10~5000)（单位为万）：";
		cin >> salary;
		while (1) {
			if (salary> 5000 || salary< 10) {
				cout << "输入年薪范围有误，请重新输入:" << endl;
				cin >> salary;
			}
			else break;
		}
		cout << "请输入球员总进球数：";
		cin >> kick;
		while (1) {
			if (kick<0) {
				cout << "输入进球数范围有误，请重新输入:" << endl;
				cin >> kick;
			}
			else break;
		}
		cout << "请输入球员服役年限(0~20):";
		cin >> year;
		while (1) {
			if (year > 20 || year <0) {
				cout << "输入服役年限范围有误，请重新输入:" << endl;
				cin >> year;
			}
			else break;
		}
		cout << "请输入球员转会费（10~10000）（单位为万）:";
		cin >> fee;
		while (1) {
			if (fee > 10000 || fee < 10) {
				cout << "输入转会费范围有误，请重新输入:" << endl;
				cin >> fee;
			}
			else break;
		}
		new_player.changeplayer(player_name, age, ability, salary, kick, year, fee);
		players.push_back(new_player);
	}
	void deleteplayer(int i) { players.erase(players.begin() + i); };
	void deletestaff(int i) { staffs.erase(staffs.begin() + i); };
	void changeplayer(int i) {
		int j;
		cout << "请选择该球员要修改的内容:" << endl;
		cout << "1.名称\t2.年龄\t3.能力\t4.年薪\t5.进球总数\t6.服役年限\t7.转会费" << endl;
		cin >> j;
		switch (j) {
		case 1: {
			string name;
			cout << "请输入修改后的名称" << endl;
			cin >> name;
			players[i].changename(name);
			cout << "修改成功" << endl;
			break;
		}
		case 2: {
			int age;
			cout << "请输入修改后的年龄" << endl;
			cin >> age;
			while (1) {
				if (age > 45 || age < 18) {
					cout << "输入年龄范围有误，请重新输入:" << endl;
					cin >> age;
				}
				else break;
			}

			players[i].changeage(age);
			cout << "修改成功" << endl;
			break;
		}
		case 3: {
			int ability;
			cout << "请输入修改后的能力值" << endl;
			cin >> ability;
			while (1) {
				if (ability > 100 || ability < 0) {
					cout << "输入能力值范围有误，请重新输入:" << endl;
					cin >> ability;
				}
				else break;
			}
			players[i].changeab(ability);
			cout << "修改成功" << endl;
			break;
		}
		case 4: {
			int salary;
			cout << "请输入修改后年薪" << endl;
			cin >> salary;
			while (1) {
				if (salary> 2000 || salary< 10) {
					cout << "输入年薪范围有误，请重新输入:" << endl;
					cin >> salary;
				}
				else break;
			}
			players[i].changesa(salary);
			cout << "修改成功" << endl;
			break;
		}
		case 5: {
			int kick;
			cout << "请输入修改后的总进球数" << endl;
			cin >> kick;
			while (1) {
				if (kick<0) {
					cout << "输入进球数范围有误，请重新输入:" << endl;
					cin >> kick;
				}
				else break;
			}
			players[i].changekick(kick);
			cout << "修改成功" << endl;
			break;
		}
		case 6: {
			int year;
			cout << "请输入修改后的服役年限" << endl;
			cin >> year;
			while (1) {
				if (year > 20 || year <0) {
					cout << "输入服役年限范围有误，请重新输入:" << endl;
					cin >> year;
				}
				else break;
			}
			players[i].changeyear(year);
			cout << "修改成功" << endl;
			break;
		}
		case 7: {
			int fee;
			cout << "请输入修改后的转会费" << endl;
			cin >> fee;
			while (1) {
				if (fee > 10000 || fee < 10) {
					cout << "输入转会费范围有误，请重新输入:" << endl;
					cin >> fee;
				}
				else break;
			} 
			players[i].changefee(fee);
			cout << "修改成功" << endl;
			break;
		}
		}
	}
	void changestaff(int i) {
		int j;
		cout << "请选择该员工要修改的内容:" << endl;
		cout << "1.名称\t2.年龄\t3.能力\t4.年薪" << endl;
		cin >> j;
		switch (j) {
		case 1: {
			string name;
			cout << "请输入修改后的名称" << endl;
			cin >> name;
			staffs[i].changename(name);
			cout << "修改成功" << endl;
			break;
		}
		case 2: {
			int age;
			cout << "请输入修改后的年龄（18~60）" << endl;
			cin >> age;
			while (1) {
				if (age > 60 || age < 18) {
					cout << "输入年龄范围有误，请重新输入:" << endl;
					cin >> age;
				}
				else break;
			}
			staffs[i].changeage(age);
			cout << "修改成功" << endl;
			break;
		}
		case 3: {
			int ability;
			cout << "请输入修改后的能力值（0~100）" << endl;
			cin >> ability;
			while (1) {
				if (ability > 100 || ability < 0) {
					cout << "输入能力值范围有误，请重新输入:" << endl;
					cin >> ability;
				}
				else break;
			}
			staffs[i].changeab(ability);
			cout << "修改成功" << endl;
			break;
		}
		case 4: {
			int salary;
			cout << "请输入修改后年薪（10~200）" << endl;
			cin >> salary;
			while (1) {
				if (salary> 200 || salary< 10) {
					cout << "输入年薪范围有误，请重新输入:" << endl;
					cin >> salary;
				}
				else break;
			}
			staffs[i].changesa(salary);
			cout << "修改成功" << endl;
			break;
		}
		}
	}
	virtual void print() {
		cout << "俱乐部:" << clubname << endl;
		unsigned int i;
		cout << "现金：" << cash << 'w' << endl;
		cout << "员工:";
		for (i = 0; i < staffs.size(); i++) {
			cout << setw(10) << staffs[i].getname();
		}
		cout << endl << "球员:";
		for (i = 0; i < players.size(); i++) {
			cout << setw(10) << players[i].getname();
		}
		cout << endl;
	}
	virtual void file_print(ofstream &outfile) {
		outfile << clubname << '\t' << cash << endl;
		unsigned int i;
		outfile << staffs.size() << endl;
		for (i = 0; i < staffs.size(); i++) {
			staffs[i].file_print(outfile);
		}
		outfile << players.size() << endl;
		for (i = 0; i < players.size(); i++) {
			players[i].file_print(outfile);
		}
	}
}; 
struct cmp {
	char ch;
	int cmpdata;
	string kind;
	string cmpclubname;
};
