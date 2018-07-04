#include"player.h"
using namespace std;
class club {
private:
	vector<staff> staffs;//Ա��
	vector<player> players;//��Ա
	int cash;//�ֽ�
	string clubname;//����
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
		cout << "������Ա��������";
		cin >> staff_name;
		cout << "������Ա������(18~60):";
		cin >> age;
		while (1) {
			if (age > 60 || age < 18) {
				cout << "�������䷶Χ��������������:" << endl;
				cin >> age;
			}
			else break;
		}
		cout << "������Ա������ֵ(0~100)��";
		cin >> ability;
		while (1) {
			if (ability > 100 || ability< 0) {
				cout << "��������ֵ��Χ��������������:" << endl;
				cin >> age;
			}
			else break;
		}
		cout << "������Ա����н(10~1000)(��λΪ��)��";
		cin >> salary;
		while (1) {
			if (salary > 1000 || salary< 10) {
				cout << "������н��Χ��������������:" << endl;
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
		cout << "��������Ա������";
		cin >> player_name;
		cout << "��������Ա����(18~45):";
		cin >> age;
		while (1) {
			if (age > 45 || age < 18) {
				cout << "�������䷶Χ��������������:" << endl;
				cin >> age;
			}
			else break;
		}
		cout << "��������Ա����ֵ(0~100)��";
		cin >> ability;
		while (1) {
			if (age > 100 || age < 0) {
				cout << "�������䷶Χ��������������:" << endl;
				cin >> ability;
			}
			else break;
		}
		cout << "��������Ա��н(10~5000)����λΪ�򣩣�";
		cin >> salary;
		while (1) {
			if (salary> 5000 || salary< 10) {
				cout << "������н��Χ��������������:" << endl;
				cin >> salary;
			}
			else break;
		}
		cout << "��������Ա�ܽ�������";
		cin >> kick;
		while (1) {
			if (kick<0) {
				cout << "�����������Χ��������������:" << endl;
				cin >> kick;
			}
			else break;
		}
		cout << "��������Ա��������(0~20):";
		cin >> year;
		while (1) {
			if (year > 20 || year <0) {
				cout << "����������޷�Χ��������������:" << endl;
				cin >> year;
			}
			else break;
		}
		cout << "��������Աת��ѣ�10~10000������λΪ��:";
		cin >> fee;
		while (1) {
			if (fee > 10000 || fee < 10) {
				cout << "����ת��ѷ�Χ��������������:" << endl;
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
		cout << "��ѡ�����ԱҪ�޸ĵ�����:" << endl;
		cout << "1.����\t2.����\t3.����\t4.��н\t5.��������\t6.��������\t7.ת���" << endl;
		cin >> j;
		switch (j) {
		case 1: {
			string name;
			cout << "�������޸ĺ������" << endl;
			cin >> name;
			players[i].changename(name);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		case 2: {
			int age;
			cout << "�������޸ĺ������" << endl;
			cin >> age;
			while (1) {
				if (age > 45 || age < 18) {
					cout << "�������䷶Χ��������������:" << endl;
					cin >> age;
				}
				else break;
			}

			players[i].changeage(age);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		case 3: {
			int ability;
			cout << "�������޸ĺ������ֵ" << endl;
			cin >> ability;
			while (1) {
				if (ability > 100 || ability < 0) {
					cout << "��������ֵ��Χ��������������:" << endl;
					cin >> ability;
				}
				else break;
			}
			players[i].changeab(ability);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		case 4: {
			int salary;
			cout << "�������޸ĺ���н" << endl;
			cin >> salary;
			while (1) {
				if (salary> 2000 || salary< 10) {
					cout << "������н��Χ��������������:" << endl;
					cin >> salary;
				}
				else break;
			}
			players[i].changesa(salary);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		case 5: {
			int kick;
			cout << "�������޸ĺ���ܽ�����" << endl;
			cin >> kick;
			while (1) {
				if (kick<0) {
					cout << "�����������Χ��������������:" << endl;
					cin >> kick;
				}
				else break;
			}
			players[i].changekick(kick);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		case 6: {
			int year;
			cout << "�������޸ĺ�ķ�������" << endl;
			cin >> year;
			while (1) {
				if (year > 20 || year <0) {
					cout << "����������޷�Χ��������������:" << endl;
					cin >> year;
				}
				else break;
			}
			players[i].changeyear(year);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		case 7: {
			int fee;
			cout << "�������޸ĺ��ת���" << endl;
			cin >> fee;
			while (1) {
				if (fee > 10000 || fee < 10) {
					cout << "����ת��ѷ�Χ��������������:" << endl;
					cin >> fee;
				}
				else break;
			} 
			players[i].changefee(fee);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		}
	}
	void changestaff(int i) {
		int j;
		cout << "��ѡ���Ա��Ҫ�޸ĵ�����:" << endl;
		cout << "1.����\t2.����\t3.����\t4.��н" << endl;
		cin >> j;
		switch (j) {
		case 1: {
			string name;
			cout << "�������޸ĺ������" << endl;
			cin >> name;
			staffs[i].changename(name);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		case 2: {
			int age;
			cout << "�������޸ĺ�����䣨18~60��" << endl;
			cin >> age;
			while (1) {
				if (age > 60 || age < 18) {
					cout << "�������䷶Χ��������������:" << endl;
					cin >> age;
				}
				else break;
			}
			staffs[i].changeage(age);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		case 3: {
			int ability;
			cout << "�������޸ĺ������ֵ��0~100��" << endl;
			cin >> ability;
			while (1) {
				if (ability > 100 || ability < 0) {
					cout << "��������ֵ��Χ��������������:" << endl;
					cin >> ability;
				}
				else break;
			}
			staffs[i].changeab(ability);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		case 4: {
			int salary;
			cout << "�������޸ĺ���н��10~200��" << endl;
			cin >> salary;
			while (1) {
				if (salary> 200 || salary< 10) {
					cout << "������н��Χ��������������:" << endl;
					cin >> salary;
				}
				else break;
			}
			staffs[i].changesa(salary);
			cout << "�޸ĳɹ�" << endl;
			break;
		}
		}
	}
	virtual void print() {
		cout << "���ֲ�:" << clubname << endl;
		unsigned int i;
		cout << "�ֽ�" << cash << 'w' << endl;
		cout << "Ա��:";
		for (i = 0; i < staffs.size(); i++) {
			cout << setw(10) << staffs[i].getname();
		}
		cout << endl << "��Ա:";
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
