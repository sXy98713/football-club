#include"club.h"
#include"Socket.h"
#include<Windows.h>
#include<stack>
using namespace std;
class league {
private:
	vector<club>clubs;
	vector<vector <int> >search;//�߼��������
	vector<vector <int> >fuzzysearch;//ģ���������
public:
	league() {/*file_input();*/};
	~league() {};
	club getclub(int i) { return clubs[i]; };
	void addclub(const club new_club) { clubs.push_back(new_club); };
	void deleteclub(int i) { clubs.erase(clubs.begin() + i - 1); };
	virtual void print() {
		for (unsigned int i = 0; i < clubs.size(); i++) {
			clubs[i].print();
		}
	}
	void file_input() {
		ifstream infile;
		#ifdef SERVER
		infile.open("FIFA(server).txt");
		#else
		infile.open("FIFA(client).txt");
		#endif 
		if (!infile)
			cout << "error";
		clubs.clear();
		int club_size;
		infile >> club_size;
		for (int i = 0; i < club_size; i++) {
			club new_club(infile);
			clubs.push_back(new_club);
		}
		infile.close();
	}
	friend int readnum(string str, unsigned int &i);
	friend void menu();
	friend void search_menu();
	friend void exchange_menu();
	void addclub() {//��Ӿ��ֲ�
		club new_club;
		string clubname;
		int cash;
		cout << "��������ֲ�����:";
		cin >> clubname;
		new_club.changeclubname(clubname);
		cout << "��������ֲ�ӵ�е��ֽ�����(0~20000)����λΪ��:";
		cin >> cash;
		while (1) {
			if (cash > 20000 || cash < 0) {
				cout << "�����ֽ�Χ��������������:" << endl;
				cin >> cash;
			}
			else break;
		}
		new_club.changecash(cash);
		while (1) {
			cout << "����Ӿ��ֲ�Ա��:" << endl;
			new_club.addstaff();
			cout << "�Ƿ�������Ա��:" << endl << "1.��\t2.��" << endl;
			int choose;
			cin >> choose;
			if (choose == 1) continue;
			else if (choose == 2) break;
		}
		while (1) {
			cout << "����Ӿ��ֲ���Ա:" << endl;
			new_club.addplayer();
			cout << "�Ƿ���������Ա:" << endl << "1.��\t2.��" << endl;
			int choose;
			cin >> choose;
			if (choose == 1) continue;
			else if (choose == 2) break;
		}
		clubs.push_back(new_club);
		file_print();
	}//��Ӿ��ֲ�
	void deleteclub() {
		cout << "������Ҫɾ�����ֲ������ƣ�" << endl;
		int flag = 1;
		string delete_name;
		do {
			cin >> delete_name;
			for (unsigned int i = 0; i < clubs.size(); i++) {
				if (delete_name == clubs[i].getclubname()) {
					deleteclub(i);
					flag = 0;
				}
				else {
					cout << "�������������,����������:" << endl;
					flag = 1;
				}
			}
		} while (flag);
	}
	void exchange() {
		int a = -1, b = -1, a_p = -1;
		unsigned int i;
	inputname:
		cout << "�������������ֲ����ƣ�" << endl;
		string name_a;
		cin >> name_a;
		cout << "�������������ֲ����۵���Ա���ƣ�" << endl;
		string name_a_player;
		cin >> name_a_player;
	inputname2:
		cout << "�������򷽾��ֲ����ƣ�" << endl;
		string name_b;
		cin >> name_b;
		for (i = 0; i < clubs.size(); i++) {
			if (clubs[i].getclubname() == name_a) a = i;
			if (clubs[i].getclubname() == name_b) b = i;
		}
		if (a == -1) { cout << "δ�ҵ����������ֲ�,����������" << endl; goto inputname; }
		if (b == -1) { cout << "δ�ҵ����򷽾��ֲ�������������" << endl; goto inputname2; }
		for (int i = 0; i < clubs[a].getplayernum(); i++) {
			if (clubs[a].getplayer(i).getname() == name_a_player) a_p = i;
		}
		if (clubs[b].getcash() >= clubs[a].getplayer(a_p).getfee()) {
			clubs[b].changecash(clubs[b].getcash() - clubs[a].getplayer(a_p).getfee());
			clubs[a].changecash(clubs[a].getcash() + clubs[a].getplayer(a_p).getfee());
			clubs[b].addplayer(clubs[a].getplayer(a_p));
			clubs[a].deleteplayer(a_p);
			cout << "���׳ɹ�" << endl;
		}
		else {
			cout << "���ֽ��㣬����ʧ��" << endl;
		}
	}
	void searchall() {//���ȫ����Ա��Ϣ
		int j = 0;
		unsigned int i = 0;
		cout << "������Ա��Ϣ����:" << endl;
		cout << std::left<<setw(10)<<"���ֲ�"<< std::left << setw(10) <<"����" <<'\t' << "����" << '\t'<<"����" << '\t'<< "��н" << '\t' << "������" << '\t' << "����" << '\t' << "ת���" << endl;
		for (i = 0; i < clubs.size(); i++) {
			for (j = 0; j < clubs[i].getplayernum(); j++) {
				cout <<std::left << setw(10) << clubs[i].getclubname();
				clubs[i].getplayer(j).print();
			}
		}
	}
	void changeclub() {//�޸ľ��ֲ�����
		string changeclub_name;
		int choose, j, flag, flag2;
		unsigned int i;
		flag = 1;
		flag2 = 1;
		cout << "��ѡ����Ҫ�޸ĵľ��ֲ�������" << endl;
		cin >> changeclub_name;
		for (i = 0; i < clubs.size(); i++) {
			if (changeclub_name == clubs[i].getclubname()) {
				flag2 = 0;
				cout << "��ѡ��þ��ֲ�Ҫ�޸ĵ�����:" << endl;
				cout << "1.����\t2.�ֽ�\t3.Ա��\t4.��Ա" << endl;
				cin >> choose;
				switch (choose) {
				case 1: {
					cout << "�������޸ĺ������:";
					string name;
					cin >> name;
					clubs[i].changeclubname(name);
					break;
				}
				case 2: {
					cout << "�������޸ĺ���ֽ������λΪ��)��";
					int cash;
					cin >> cash;
					clubs[i].changecash(cash);
					break;
				}
				case 3: {
					cout << "1.�޸�����\t2.���Ա��\t3.ɾ��Ա��" << endl;
					int choose1;
					cin >> choose1;
					switch (choose1) {
					case 1: {
						cout << "��ѡ����Ҫ�޸ĵ�Ա��������" << endl;
						string name;
						cin >> name;
						for (j = 0; j < clubs[i].getstaffnum(); j++) {
							if (name == clubs[i].getstaff(j).getname()) {
								flag = 0;
								clubs[i].changestaff(j);
							}
						}
						if (flag) {
							cout << "δ�ҵ���Ա��" << endl;
							flag = 0;
						}
						break;
					}
					case 2: {
						clubs[i].addstaff();
						break;
					}
					case 3: {
						cout << "������Ҫɾ����Ա��������" << endl;
						string delete_name;
						cin >> delete_name;
						for (j = 0; j < clubs[i].getstaffnum(); j++) {
							if (clubs[i].getstaff(j).getname() == delete_name) {
								clubs[i].deletestaff(j);
								flag = 0;
								cout << "ɾ���ɹ�" << endl;
							}
						}
						if (flag) cout << "δ�ҵ���Ա��" << endl;
						break;
					}
					}
					break;
				}
				case 4: {
					cout << "1.�޸�����\t2.�����Ա\t3.ɾ����Ա" << endl;
					int choose2;
					cin >> choose2;
					switch (choose2) {
					case 1: {
						cout << "��ѡ����Ҫ�޸ĵ���Ա������" << endl;
						string name;
						cin >> name;
						for (j = 0; j < clubs[i].getplayernum(); j++) {
							if (name == clubs[i].getplayer(j).getname()) {
								flag = 0;
								clubs[i].changeplayer(j);
							}
						}
						if (flag) {
							cout << "δ�ҵ�����Ա" << endl;
							flag = 0;
						}
						break;
					}
					case 2: {
						clubs[i].addplayer();
						break;
					}
					case 3: {
						cout << "������Ҫɾ������Ա������" << endl;
						string delete_name;
						cin >> delete_name;
						for (j = 0; j < clubs[i].getplayernum(); j++) {
							if (clubs[i].getplayer(j).getname() == delete_name)
								clubs[i].deleteplayer(j);
							flag = 0;
						}
						if (flag) cout << "δ�ҵ���Ա��" << endl;
						break;
					}
					}
					break;
				}
				}
			}
		}
		if (flag2) {
			cout << "δ�ҵ��þ��ֲ�" << endl;
		}
	}
	int advanced_search(string searchstring) {//�߼�����
		int k = 0, l;
		int flag_search = 0;
		unsigned int x, v, z;
		int y;
		unsigned int i;
		search.resize(clubs.size());
		for (i = 0; i < clubs.size(); i++) {
			search[i].resize(clubs[i].getplayernum());
			search[i].assign(clubs[i].getplayernum(), 0);
		}//������άvector
		stack<char> s1, s2;//�ݴ������ַ�
		vector<string>q1;//�洢�Ƚ���Ϣ�ַ�
		string buf, str, s3;
		vector<cmp> compareinfo;//�洢�Ƚ���Ϣ
		vector<int> compareresult;//�洢�ȽϽ��
		k = 0;
		for (i = 0; i < searchstring.size(); i++) {
			if ((searchstring[i] == '(') || (searchstring[i] == ')') || (searchstring[i] == '!')) s1.push(searchstring[i]);
			else if ((searchstring[i] == '&') && (searchstring[i + 1] == '&')) { s1.push('*'); i++; }
			else if ((searchstring[i] == '|') && (searchstring[i + 1] == '|')) { s1.push('+'); i++; }
			else if ((searchstring[i]) == '@') {
				s1.push(k + '0');
				k++;
			}
		}
		while (s1.size()) {
			s3.push_back(s1.top());
			s1.pop();
		}
		k = 0;
		buf.clear();
		q1.clear();
		for (i = 0; i < searchstring.size(); i++) {
			if ((searchstring[i] == '(') || (searchstring[i] == ')') || (searchstring[i] == '&') || (searchstring[i] == '|') || (searchstring[i] == '!')) {}
			else {
				buf.push_back(searchstring[i]);
			}
		}
		for (i = 0; i < buf.size(); i++) {
			if (buf[i] == '@') {
				if (k != 0) {
					q1.push_back(str);
					str.clear();
					l = 0;
				}
				else {
					str.clear();
					l = 0;
				}
				k++;
			}
			else {
				str.push_back(buf[i]);
			}
		}
		q1.push_back(str);
		compareinfo.clear();
		for (z = 0; z < q1.size(); z++) {
			cmp c;
			for (v = 0; v < q1[z].size(); v++) {
				if (q1[z].substr(v, 3) == "age") { v += 3; c.kind = "age"; }
				else if (q1[z].substr(v, 4) == "kick") { v += 4; c.kind = "kick"; }
				else if (q1[z].substr(v, 3) == "fee") { v += 3; c.kind = "fee"; }
				else if (q1[z].substr(v, 10) == "experience") { v += 10; c.kind = "experience"; }
				else if (q1[z].substr(v, 6) == "salary") { v += 6; c.kind = "salary"; }
				else if (q1[z].substr(v, 7) == "ability") { v += 7; c.kind = "ability"; }
				else if (q1[z].substr(v, 4) == "club") { v += 4; c.kind = "club"; }
				break;
			}
			c.ch = q1[z][v];
			v++;
			if (c.kind != "club") {
				c.cmpdata = readnum(q1[z], v);
			}
			else {
				c.cmpclubname = q1[z].substr(v);
			}
			compareinfo.push_back(c);
		}
		for (x = 0; x < clubs.size(); x++) {
			for (y = 0; y < clubs[x].getplayernum(); y++) {
				for (z = 0; z < compareinfo.size(); z++) {
					if (compareinfo[z].kind == "age") {
						if (clubs[x].getplayer(y).compareage(compareinfo[z].cmpdata, compareinfo[z].ch)) compareresult.push_back(1);
						else compareresult.push_back(0);
					}
					else if (compareinfo[z].kind == "kick") {
						if (clubs[x].getplayer(y).comparekick(compareinfo[z].cmpdata, compareinfo[z].ch)) compareresult.push_back(1);
						else compareresult.push_back(0);
					}
					else if (compareinfo[z].kind == "fee") {
						if (clubs[x].getplayer(y).comparefee(compareinfo[z].cmpdata, compareinfo[z].ch)) compareresult.push_back(1);
						else compareresult.push_back(0);
					}
					else if (compareinfo[z].kind == "experience") {
						if (clubs[x].getplayer(y).compareyear(compareinfo[z].cmpdata, compareinfo[z].ch)) compareresult.push_back(1);
						else compareresult.push_back(0);
					}
					else if (compareinfo[z].kind == "salary") {
						if (clubs[x].getplayer(y).comparesa(compareinfo[z].cmpdata, compareinfo[z].ch)) compareresult.push_back(1);
						else compareresult.push_back(0);
					}
					else if (compareinfo[z].kind == "ability") {
						if (clubs[x].getplayer(y).compareab(compareinfo[z].cmpdata, compareinfo[z].ch)) compareresult.push_back(1);
						else compareresult.push_back(0);
					}
					else if (compareinfo[z].kind == "club") {
						if (clubs[x].getclubname() == compareinfo[z].cmpclubname) compareresult.push_back(1);
						else compareresult.push_back(0);
					}
				}
				i = 0;
				while (i < s3.size()) {
					if ((s3[i] <= '9') && (s3[i] >= '0')) {
						s2.push(compareresult[s3[i] - '0'] + '0');
					}
					else s2.push(s3[i]);
					i++;
				}
				int p, q;
				while (!((s2.size() == 0) && (s1.size() == 1))) {
					if (s2.top() == '(') {
						s1.push(s2.top());
						s2.pop();
					}
					else if (s2.top() == '!') {
						s1.push(s2.top());
						s2.pop();
					}
					else if ((s2.top() >= '0') && (s2.top() <= '9')) {
						if (!s1.empty()) {
							if (s1.top() == '!') {
								s1.pop();
								s2.pop();
								s2.push(!(p - '0') + '0');
							}
							else if (s1.top() == '*') {
								s1.pop();
								p = s1.top();
								q = s2.top();
								s1.pop();
								s2.pop();
								s2.push((p - '0')*(q - '0') + '0');
							}
							else if (s1.top() == '+') {
								s1.pop();
								p = s1.top();
								q = s2.top();
								s1.pop();
								s2.pop();
								s2.push(p + q - '0');
							}
							else {
								s1.push(s2.top());
								s2.pop();
							}
						}
						else {
							s1.push(s2.top());
							s2.pop();
						}
					}
					else if ((s2.top() == '*') || (s2.top() == '+')) {
						s1.push(s2.top());
						s2.pop();
					}
					else if (s2.top() == ')') {
						p = s1.top();
						s1.pop();
						s1.pop();
						s2.pop();
						s2.push(p);
					}
				}
				compareresult.clear();
				search[x][y] = s1.top() > '0' ? 1 : 0;
				s1.pop();
				//cout << search[x][y] << '\t'<<x << '\t' << y;
				//system("pause");
			}
		}
		cout << "�����������:" << endl;
		z = 0;
		//player_buf test;
		for (x = 0; x < clubs.size(); x++) {
			for (y = 0; y < clubs[x].getplayernum(); y++) {
				if (search[x][y] == 1) {
					if (z == 0) {
						cout << std::left << setw(10) << "���ֲ�" << std::left << setw(10) << "����" << '\t' << "����" << '\t' << "����" << '\t' << "��н" << '\t' << "������" << '\t' << "����" << '\t' << "ת���" << endl;
					}
					cout << std::left<< setw(10) << clubs[x].getclubname();
					clubs[x].getplayer(y).print();
					z++;
				}
			}
		}
		if (z == 0) {
			cout << "����û��������������Ա" << endl;
		}
		return z;
	}
	void name_search(string name) {//����׼ȷ����
		unsigned int i;
		int j, flag = 0;
		for (i = 0; i < clubs.size(); i++) {
			for (j = 0; j < clubs[i].getplayernum(); j++) {
				if (clubs[i].getplayer(j).getname() == name) {
					cout << "�Ѳ��ҵ�����Ա:" << endl;
					cout << "����:" << clubs[i].getplayer(j).getname() << '\t';
					cout << "�������ֲ���" << clubs[i].getclubname() << '\t' << "���䣺" << clubs[i].getplayer(j).getage() << '\t';
					cout << "����:" << clubs[i].getplayer(j).getab() << '\t';
					cout << "��н:" << clubs[i].getplayer(j).getsa() <<"w"<< '\t';
					cout << "����������" << clubs[i].getplayer(j).getkick() << '\t';
					cout << "��������:" << clubs[i].getplayer(j).getyear() << '\t';
					cout << "ת���:" << clubs[i].getplayer(j).getfee() <<"w"<< endl;
				}
			}
		}
	}
	int fuzzy_search(string searchstr){
		string cmpname;
		cmpname.clear();
		search.resize(clubs.size());
		unsigned int i;
		fuzzysearch.resize(clubs.size());
		for (i = 0; i < clubs.size(); i++) {
			fuzzysearch[i].resize(clubs[i].getplayernum());
			fuzzysearch[i].assign(clubs[i].getplayernum(), 0);
		}//������άvector
		int nameflag = 0, j = 0;
		for (i = 0; i < searchstr.size(); i++) {
			if (searchstr[i] == '~') {
				nameflag = 1;
				continue;
			}
			if (nameflag == 1) {
				cmpname.push_back(searchstr[i]);
			}
		}
		cout << "��ѯ�������:" << endl;
		int z = 0;
		for (i = 0; i < clubs.size(); i++) {
			for (j = 0; j < clubs[i].getplayernum(); j++) {
				if (clubs[i].getplayer(j).comparename(cmpname)) {
					if(z==0) cout << std::left << setw(10) << "���ֲ�" << std::left << setw(10) << "����" << '\t' << "����" << '\t' << "����" << '\t' << "��н" << '\t' << "������" << '\t' << "����" << '\t' << "ת���" << endl;
					cout << std::left << setw(10) << clubs[i].getclubname();
					clubs[i].getplayer(j).print();
					fuzzysearch[i][j] = 1;
					z++;
				}
			}
		}
		if(z==0) cout << "����û��������������Ա" << endl;
		return z;
	}
	void file_print() {
		ofstream outfile;
		#ifdef SERVER
		outfile.open("FIFA(server).txt");
		#else  
		outfile.open("FIFA(client).txt");
		#endif
		outfile << clubs.size() << endl;
		for (unsigned int i = 0; i < clubs.size(); i++) {
			clubs[i].file_print(outfile);
		}
		outfile.close();
	}
	//�����
	void s_run() {
		file_input();
		print();
		server S;
		if (S.server_listen()) {
			int choose, search_choose;
			while (1) {
				choose = atoi(S.server_receive());
				if (choose == 4) {//����
					while (1) {
						search_choose = atoi(S.server_receive());
						if (search_choose == 2) {//�߼�����
							string str(S.server_receive());
							cout << "�õ��߼��������ʽ" << str << endl;
							unsigned int x;
							int y;
							//����
							char buff[1024];
							memset(buff, '\0', 1024);
							int num;
							num = advanced_search(str);
							itoa(num, buff, 10);
							S.server_send(buff);//���������������
							for (x = 0; x < clubs.size(); x++) {
								for (y = 0; y < clubs[x].getplayernum(); y++) {
									if (search[x][y] == 1) {
										memset(buff, '\0', 1024);
										strcpy(buff, clubs[x].getplayer(y).getname().c_str());
										S.server_send(buff);//������Ա����
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										strcpy(buff, clubs[x].getclubname().c_str());
										S.server_send(buff);//������Ա���ھ��ֲ�
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getage(), buff, 10);
										S.server_send(buff);//��������
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getab(),buff,10);
										S.server_send(buff);//��������
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getsa(),buff,10);
										S.server_send(buff);//������н
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getkick(),buff,10);
										S.server_send(buff);//���ͽ�����
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getyear(),buff,10);
										S.server_send(buff);//��������
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getfee(),buff,10);
										S.server_send(buff);//����ת���
										Sleep(15);
										//cout << buff << endl;
										//system("pause");
									}
								}
							}
							while (1) {
								int k = atoi(S.server_receive());
								if (k == 1) {
									break;
								}
								else if (k == 2) {
									S.close();
									return;
								}
								else {
									continue;
								}
							}
							continue;
						}
						else if (search_choose == 3) {//����ģ������
							string str(S.server_receive());//�õ����ʽ
							unsigned int x;
							int y;
							char buff[1024];
							int num;
							num = fuzzy_search(str);
							itoa(num, buff, 10);
							S.server_send(buff);//���������������
							for (x = 0; x < clubs.size(); x++) {
								for (y = 0; y < clubs[x].getplayernum(); y++) {
									if (fuzzysearch[x][y] == 1) {
										memset(buff, '\0', 1024);
										strcpy(buff, clubs[x].getplayer(y).getname().c_str());
										S.server_send(buff);//������Ա����
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										strcpy(buff, clubs[x].getclubname().c_str());
										S.server_send(buff);//������Ա���ھ��ֲ�
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getage(), buff, 10);
										S.server_send(buff);//��������
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getab(), buff, 10);
										S.server_send(buff);//��������
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getsa(), buff, 10);
										S.server_send(buff);//������н
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getkick(), buff, 10);
										S.server_send(buff);//���ͽ�����
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getyear(), buff, 10);
										S.server_send(buff);//��������
										Sleep(20);
										//cout << buff << endl;
										//system("pause");
										memset(buff, '\0', 1024);
										itoa(clubs[x].getplayer(y).getfee(), buff, 10);
										S.server_send(buff);//����ת���
										Sleep(15);
										//cout << buff << endl;
										//system("pause");
									}
								}
							}
							while (1) {
								int k = atoi(S.server_receive());
								if (k == 1) {
									break;
								}
								else if (k == 2) {
									S.close();
									return ;
								}
								else {
									continue;
								}
							}
							continue;
						}
						else if (search_choose == 4) {
							break;
						}
						else continue;
					}
					continue;
				}
				else if (choose == 5) {//����
					while (1) {
						int exchange_choose = atoi(S.server_receive());
						if (exchange_choose == 2) {
							char buff[1024];
							string name, clubname;
							int cash;//���ֽ�
							clubname = S.server_receive();//������Ա���ھ��ֲ�����
							name = S.server_receive();//������Ա����
							cash = atoi(S.server_receive());//�������ֽ�
							unsigned int x;
							int y, flag=0;
							for (x = 0; x < clubs.size(); x++) {
								if (clubs[x].getclubname() == clubname) {
									for (y = 0; y < clubs[x].getplayernum(); y++) {
										if (clubs[x].getplayer(y).getname() == name) {
											if (cash >= clubs[x].getplayer(y).getfee()) {
												flag = 1;
												memset(buff, '\0', 1024);
												itoa(1, buff, 10);
												S.server_send(buff);//���ͽ��׳ɹ��ź�
												memset(buff, '\0', 1024);
												itoa(clubs[x].getplayer(y).getage(), buff, 10);
												S.server_send(buff);//��������
												Sleep(15);
												//cout << buff << endl;
												//system("pause");
												memset(buff, '\0', 1024);
												itoa(clubs[x].getplayer(y).getab(), buff, 10);
												S.server_send(buff);//��������
												Sleep(15);
												//cout << buff << endl;
												//system("pause");
												memset(buff, '\0', 1024);
												itoa(clubs[x].getplayer(y).getsa(), buff, 10);
												S.server_send(buff);//������н
												Sleep(15);
												//cout << buff << endl;
												//system("pause");
												memset(buff, '\0', 1024);
												itoa(clubs[x].getplayer(y).getkick(), buff, 10);
												S.server_send(buff);//���ͽ�����
												Sleep(15);
												//cout << buff << endl;
												//system("pause");
												memset(buff, '\0', 1024);
												itoa(clubs[x].getplayer(y).getyear(), buff, 10);
												S.server_send(buff);//��������
												Sleep(15);
												//cout << buff << endl;
												//system("pause");
												memset(buff, '\0', 1024);
												itoa(clubs[x].getplayer(y).getfee(), buff, 10);
												S.server_send(buff);//����ת���
												Sleep(15);
												clubs[x].deleteplayer(y);
												clubs[x].changecash(clubs[x].getcash() + cash);
											}
										}
									}
								}
							}
							memset(buff, '\0', 1024);
							itoa(0, buff, 10);
							if(!flag)
							S.server_send(buff);//���ͽ���ʧ���ź�
							file_print();
							while (1) {
								int k = atoi(S.server_receive());
								if (k == 1) {
									break;
								}
								else if (k == 2) {
									S.close();
									return;
								}
								else {
									continue;
								}
							}
						}
						else if (exchange_choose == 3) {
							break;
						}
						else {
							continue;
						}
					}
					continue;
				}
				else if (choose == 6) {
					break;
				}
			}
		}
	}
	//�ͻ���
	void c_run() {
		cout << "        ***************��ӭʹ��������ֲ�����ϵͳ***************" << endl;
		menu();
		cout << "        ********************************************************" << endl;
		client C;
		file_input();
		C.client_connect();
		int choose = 0;
		char buf[1024];
		cin >> choose;
		while (1) {
			if (choose == 1) {
				addclub();
				file_print();
				cout << "1.������һ��\t2.�˳�����" << endl;
				int x;
				cin >> x;
				while (1) {
					if (x == 1) {
						menu();
						break;
					}
					else if (x == 2) {
						return;
					}
					else {
						cout << "������������������" << endl;
						cin >> x;
						continue;
					}
				}
				cin >> choose;
				continue;
			}
			else if (choose == 2) {
				deleteclub();
				file_print();
				cout << "1.������һ��\t2.�˳�����" << endl;
				int x;
				cin >> x;
				while (1) {
					if (x == 1) {
						menu();
						break;
					}
					else if (x == 2) {
						return;
					}
					else {
						cout << "������������������" << endl;
						cin >> x;
						continue;
					}
				}
				cin >> choose;
				continue;
			}
			else if (choose == 3) {
				changeclub();
				file_print();
				cout << "1.������һ��\t2.�˳�����" << endl;
				int x;
				cin >> x;
				while (1) {
					if (x == 1) {
						menu();
						break;
					}
					else if (x == 2) {
						return;
					}
					else {
						cout << "������������������" << endl;
						continue;
					}
				}
				cin >> choose;
				continue;
			}
			else if (choose == 4) {
				itoa(choose, buf, 10);
				C.client_send(buf);
				search_menu();
				int search_choose = 0;
				while (1) {
					cin >> search_choose;
					if (search_choose == 1) {
						itoa(search_choose, buf, 10);
						C.client_send(buf);
						searchall();
						cout << "1.������һ��\t2.�˳�����" << endl;
						int x;
						while (1) {
							cin >> x;
							if (x == 1) {
								itoa(x, buf, 10);
								C.client_send(buf);
								break;
							}
							else if (x == 2) {
								itoa(x, buf, 10);
								C.client_send(buf);
								return;
							}
							else {
								itoa(x, buf, 10);
								C.client_send(buf);
								cout << "������������������" << endl;
								continue;
							}
						}
						search_menu();
						continue;
					}
					else if (search_choose == 2) {//�߼�����
						itoa(search_choose, buf, 10);
						C.client_send(buf);
						string str;
						int flag = 1;
						cout << "�������������ʽ:" << endl;
						cin >> str;
						advanced_search(str);
						memset(buf, '\0', 1024);
						strcpy(buf, str.c_str());
						C.client_send(buf);//���ͱ��ʽ
						cout << "����������������:" << endl;
						memset(buf, '\0', 1024);
						int num = atoi(C.cient_recv());//�����������
						if (num == 0) cout << "�����δ���ҵ���Ӧ��Ա" << endl;
						else cout<< "��������" << num << "����Ա��������" << endl;
						string name, clubname;
						for (int i = 0; i < num; i++) {
							int age, ab, sa, kick, year, fee;
							memset(buf, '\0', 1024);
							strcpy(buf, C.cient_recv());//������Ա����
							name =buf;
							memset(buf, '\0', 1024);
							strcpy(buf, C.cient_recv());//���ܾ��ֲ�����
							clubname = buf;
							age = atoi(C.cient_recv());
							ab = atoi(C.cient_recv());
							sa = atoi(C.cient_recv());
							kick = atoi(C.cient_recv());
							year = atoi(C.cient_recv());
							fee = atoi(C.cient_recv());
							if (flag == 1) cout << std::left << setw(10) << "���ֲ�" << std::left << setw(10) << "����" << '\t' << "����" << '\t' << "����" << '\t' << "��н" << '\t' << "������" << '\t' << "����" << '\t' << "ת���" << endl;
							cout << std::left << setw(10) << clubname << std::left << setw(10) << name << "\t" << age << "\t" << ab << "\t" << sa << "w\t" << kick << "\t" << year << "\t" << fee <<"w"<< endl;
							flag++;
						}
						cout << "1.������һ��\t2.�˳�����" << endl;
						int x;
						while (1) {
							cin >> x;
							if (x == 1) {
								itoa(x, buf, 10);
								C.client_send(buf);
								break;
							}
							else if (x == 2) {
								itoa(x, buf, 10);
								C.client_send(buf);
								return;
							}
							else {
								itoa(x, buf, 10);
								C.client_send(buf);
								cout << "������������������:" << endl;
								continue;
							}
						}
						search_menu();
						continue;
					}
					else if (search_choose == 3) {
						itoa(search_choose, buf, 10);
						C.client_send(buf);
						cout << "�������������ʽ" << endl;
						string str;
						int flag = 1;
						cin >> str;
						memset(buf, '\0', 1024);
						strcpy(buf, str.c_str());
						C.client_send(buf);
						fuzzy_search(str);
						cout << "����������������:" << endl;
						memset(buf, '\0', 1024);
						int num = 0;
						num=atoi(C.cient_recv());//�����������
						if (num == 0) cout << "�����δ���ҵ���Ӧ��Ա" << endl;
						else cout << "��������" << num << "����Ա��������" << endl;
						string name, clubname;
						for (int i = 0; i < num; i++) {
							int age, ab, sa, kick, year, fee;
							memset(buf, '\0', 1024);
							strcpy(buf, C.cient_recv());//������Ա����
							name = buf;
							memset(buf, '\0', 1024);
							strcpy(buf, C.cient_recv());//���ܾ��ֲ�����
							clubname = buf;
							age = atoi(C.cient_recv());
							ab = atoi(C.cient_recv());
							sa = atoi(C.cient_recv());
							kick = atoi(C.cient_recv());
							year = atoi(C.cient_recv());
							fee = atoi(C.cient_recv());
							if (flag == 1) cout << std::left << setw(10) << "���ֲ�" << std::left << setw(10) << "����" << '\t' << "����" << '\t' << "����" << '\t' << "��н" << '\t' << "������" << '\t' << "����" << '\t' << "ת���" << endl;
							cout << std::left << setw(10) << clubname << std::left << setw(10) << name << "\t" << age << "\t" << ab << "\t" << sa << "w\t" << kick << "\t" << year << "\t" << fee << "w" << endl;
							flag++;
						}
						cout << "1.������һ��\t2.�˳�����" << endl;
						int x;
						while (1) {
							cin >> x;
							if (x == 1) {
								itoa(x, buf, 10);
								C.client_send(buf);
								break;
							}
							else if (x == 2) {
								itoa(x, buf, 10);
								C.client_send(buf);
								return;
							}
							else {
								itoa(x, buf, 10);
								C.client_send(buf);
								cout << "������������������" << endl;
								continue;
							}
						}
						search_menu();
						continue;
					}
					else if (search_choose == 4) {
						itoa(search_choose, buf, 10);
						C.client_send(buf);
						break;
					}
					else {
						itoa(search_choose, buf, 10);
						C.client_send(buf);
						cout << "������������������" << endl;
						continue;
					}
				}
				menu();
				cin >> choose;
				continue;
			}
			else if (choose == 5) {
				itoa(choose, buf, 10);
				C.client_send(buf);
				memset(buf, '\0', sizeof(buf));
				exchange_menu();
				int exchange_choose = 0;
				while (1) {
					cin >> exchange_choose;
					if (exchange_choose == 1) {
						exchange();
						file_print();
						cout << "1.������һ��\t2.�˳�����" << endl;
						int x;
						cin >> x;
						while (1) {
							if (x == 1) {
								break;
							}
							else if (x == 2) {
								return;
							}
							else {
								cout << "������������������" << endl;
								cin >> x;
								continue;
							}
						}
						exchange_menu();
						continue;
					}
					else if (exchange_choose == 2) {
						itoa(exchange_choose, buf, 10);
						C.client_send(buf);
						int a = -1, b = -1, c = -1;
						unsigned int i;
					inputname:
						cout << "�������������ֲ����ƣ�" << endl;
						string name_a;
						cin >> name_a;
						memset(buf, '/0', sizeof(buf));
						strcpy(buf, name_a.c_str());
						C.client_send(buf);//�����������ֲ�����
						cout << "�������������ֲ����۵���Ա���ƣ�" << endl;
						string name_a_player;
						cin >> name_a_player;
						memset(buf, '/0', sizeof(buf));
						strcpy(buf, name_a_player.c_str());
						C.client_send(buf);//������Ա����
					inputname2:
						cout << "�������򷽾��ֲ����ƣ�" << endl;
						string name_b;
						cin >> name_b;
						for (i = 0; i < clubs.size(); i++) {
							if (clubs[i].getclubname() == name_b) c = i;
						}
						if (c == -1) {
							cout << "δ�ҵ��򷽾��ֲ�������������" << endl;
							goto inputname2;
						}
						memset(buf, '\0', sizeof(buf));
						itoa(clubs[c].getcash(), buf, 10);
						C.client_send(buf);//�����򷽾��ֲ��ֽ�
						if (atoi(C.cient_recv()) == 1) {
							int age, ab, sa, kick, year, fee;
							age = atoi(C.cient_recv());
							ab = atoi(C.cient_recv());
							sa = atoi(C.cient_recv());
							kick = atoi(C.cient_recv());
							year = atoi(C.cient_recv());
							fee = atoi(C.cient_recv());
							player new_p;
							new_p.changeplayer(name_a_player, age, ab, sa, kick, year, fee);
							clubs[c].addplayer(new_p);
							clubs[c].changecash(clubs[c].getcash() - fee);
							file_print();
							cout << "���׳ɹ�" << endl;
						}
						else {
							cout << "����ʧ��" << endl;
						}
						cout << "1.������һ��\t2.�˳�����" << endl;
						int x;
						while (1) {
							cin >> x;
							if (x == 1) {
								itoa(x, buf, 10);
								C.client_send(buf);
								break;
							}
							else if (x == 2) {
								itoa(x, buf, 10);
								C.client_send(buf);
								return;
							}
							else {
								itoa(x, buf, 10);
								C.client_send(buf);
								cout << "������������������" << endl;
								continue;
							}
						}
						exchange_menu();
						cin >> exchange_choose;
						memset(buf, '\0', sizeof(buf));
						itoa(exchange_choose, buf, 10);
						C.client_send(buf);
						continue;
					}
					else if (exchange_choose == 3) {
						itoa(exchange_choose, buf, 10);
						C.client_send(buf);
						break;
					}
					else {
						itoa(exchange_choose, buf, 10);
						C.client_send(buf);
						cout << "������������������" << endl;
						continue;
					}
				}
				menu();
				cin >> choose;
				continue;
			}
			else if (choose == 6) {
				memset(buf, '\0', sizeof(buf));
				itoa(choose, buf, 10);
				C.client_send(buf);
				C.close();
				break;
			}
			else {
				itoa(choose, buf, 10);
				C.client_send(buf);
				cout << "������������������" << endl;
				cin >> choose;
				continue;
			}
		}
	}
};
int readnum(string str, unsigned int& i) {
	int num = 0;
	while (str[i] <= '9'&&str[i] >= '0'&&i<str.size()) {
		num = num * 10 + str[i] - '0';
		i++;
	}
	return num;
}
void menu() {
	cout << "        * 1.��Ӿ��ֲ�                                         *" << endl;
	cout << "        * 2.ɾ�����ֲ�                                         *" << endl;
	cout << "        * 3.�޸ľ��ֲ�                                         *" << endl;
	cout << "        * 4.��Ա����                                           *" << endl;
	cout << "        * 5.��Ա����                                           *" << endl;
	cout << "        * 6.�˳�                                               *" << endl;
}
void search_menu() {
	cout << "1.�鿴ȫ����Ա\t2.�߼�����" << endl;
	cout << "3.����ģ������\t4.������һ��" << endl;
}
void exchange_menu() {
	cout << "1.������Ա����" << endl;
	cout << "2.������Ա����" << endl;
	cout << "3.������һ��" << endl;
}