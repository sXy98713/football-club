#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
class staff {
protected:
	string name;//名字
	int age;//年龄
	int ability;//能力
	int salary;//年薪
public:
	staff(const string & name = "None", int age = 0, int ability = 0, int salary = 0) {};
	~staff() {};
	staff(ifstream &infile) {
		infile >> name >> age >> ability >> salary;
	}
	string getname() { return name; };
	int getage() { return age; };
	int getab() { return ability; };
	int getsa() { return salary; };
	void changestaff(string & new_name, int new_age, int new_ability, int new_salary) {
		name = new_name;
		age = new_age;
		ability = new_ability;
		salary = new_salary;
	}
	void changename(string &new_name) { name = new_name; };
	void changeage(int new_age) { age = new_age; };
	void changeab(int new_ability) { ability = new_ability; };
	void changesa(int new_salary) { salary = new_salary; };
	bool compareage(int cmpage, char cmp) {
		if (cmp == '>') {
			if (age > cmpage) return true;
			else return false;
		}
		else if (cmp == '<') {
			if (age < cmpage) return true;
			else return false;
		}
		else {
			if (age == cmpage) return true;
			else return false;
		}
	}
	bool compareab(int cmpab, char cmp) {
		if (cmp == '>') {
			if (ability > cmpab) return true;
			else return false;
		}
		else if (cmp == '<') {
			if (ability < cmpab) return true;
			else return false;
		}
		else {
			if (ability == cmpab) return true;
			else return false;
		}
	}
	bool comparesa(int cmpsa, char cmp) {
		if (cmp == '>') {
			if (salary > cmpsa) return true;
			else return false;
		}
		else if (cmp == '<') {
			if (salary < cmpsa) return true;
			else return false;
		}
		else {
			if (salary == cmpsa) return true;
			else return false;
		}
	}
	virtual void print()const {
		cout <<  name << '\t' << age << '\t' << ability << '\t' << salary <<"w"<<'\t' << endl;
	};
	virtual void file_print(ofstream &outfile) const {
		outfile  << name << '\t' << age << '\t' << ability << '\t' << salary <<'\t' << endl;
	}
};
class player :public staff {
private:
	int kick;//进球总数
	int year;//年限
	int fee;//转会费
public:
	player(const string& name = "None", int age = 0, int ability = 0, int salary = 0, int kick = 0, int year = 0, int fee = 0) {};
	~player() {};
	player(ifstream &infile) {
		infile >> name >> age >> ability >> salary >> kick >> year >> fee;
	}
	int getkick() { return kick; };
	int getyear() { return year; };
	int getfee() { return fee; };
	void changeplayer(string & new_name, int new_age, int new_ability, int new_salary, int new_kick, int new_year, int new_fee) {
		name = new_name;
		age = new_age;
		ability = new_ability;
		salary = new_salary;
		kick = new_kick;
		year = new_year;
		fee = new_fee;
	}
	void changekick(int new_kick) { kick = new_kick; };
	void changeyear(int new_year) { year = new_year; };
	void changefee(int new_fee) { fee = new_fee; };
	bool compareage(int cmpage, char cmp) {
		if (cmp == '>') {
			if (age > cmpage) return true;
			else return false;
		}
		else if (cmp == '<') {
			if (age < cmpage) return true;
			else return false;
		}
		else {
			if (age == cmpage) return true;
			else return false;
		}
	}
	bool compareab(int cmpab, char cmp) {
		if (cmp == '>') {
			if (ability > cmpab) return true;
			else return false;
		}
		else if (cmp == '<') {
			if (ability < cmpab) return true;
			else return false;
		}
		else {
			if (ability == cmpab) return true;
			else return false;
		}
	}
	bool comparesa(int cmpsa, char cmp) {
		if (cmp == '>') {
			if (salary > cmpsa) return true;
			else return false;
		}
		else if (cmp == '<') {
			if (salary < cmpsa) return true;
			else return false;
		}
		else {
			if (salary == cmpsa) return true;
			else return false;
		}
	}
	bool comparekick(int cmpkick, char cmp) {
		if (cmp == '>') {
			if (kick > cmpkick) return true;
			else return false;
		}
		else if (cmp == '<') {
			if (kick < cmpkick) return true;
			else return false;
		}
		else {
			if (kick == kick) return true;
			else return false;
		}
	}
	bool compareyear(int cmpyear, char cmp) {
		if (cmp == '>') {
			if (year > cmpyear) return true;
			else return false;
		}
		else if (cmp == '<') {
			if (year< cmpyear) return true;
			else return false;
		}
		else {
			if (year == cmpyear) return true;
			else return false;
		}
	}
	bool comparefee(int cmpfee, char cmp) {
		if (cmp == '>') {
			if (fee > cmpfee) return true;
			else return false;
		}
		else if (cmp == '<') {
			if (fee < cmpfee) return true;
			else return false;
		}
		else {
			if (fee == cmpfee) return true;
			else return false;
		}
	}
	bool comparename(string cmpname) {
		if (name.find(cmpname) !=name.npos) {
			return true;
		}
		else return false;
		/*int i = 0, j = 0;
		int n = name.size();
		int m = cmpname.size();
		int *next = { 0 };
		int k = 0;
		while (j < m) {
			if ((k == 0) || (cmpname[k] == cmpname[j])) {
				next[++j] = ++k;
			}
			else k = next[k];
		}
		j = 0;
		while ((i <= n) && (j <= m)) {
			if ((name[i] == cmpname[i]) || j == 0) {
				i++;
				j++;
			}
			else
				j = next[j];
		}
		if (j == m + 1)
			return true;
		else
			return false;*/
	}
	virtual void print()const {
		cout <<std::left<<setw(10) <<name<< '\t'<< age << '\t' << ability << '\t' << salary << "w"<<'\t' << kick << '\t' << year << '\t' << fee <<"w"<< endl;
	};
	virtual void file_print(ofstream &outfile) {
		outfile << std::left<<setw(10)<<name << '\t' << age << '\t' << ability << '\t' << salary << '\t' << kick << '\t' << year << '\t' << fee << endl;
	}
}; 
