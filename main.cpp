#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <exception>
class movie {
public:
	std::string name;
	std::string review;
	movie() {
		name = "noname";
		review = "";
		id = rand() % 100;
	}
	movie(std::string _name, std::string _review, int _id) {
		name = _name;
		review = _review;
		id = _id;

	}
	bool operator!=(movie obj) {
		return this->name != obj.name;
	}
	bool operator==(movie obj) {
		return this->name == obj.name;
	}
	friend std::ostream& operator<<(std::ostream& out, movie obj);

	int id;
};
std::ostream& operator<<(std::ostream& out, movie obj) {
	return out << "{ID: " << obj.id << ", Name: \"" << obj.name << "\", Review: \"" << obj.review << "\"} ";
}

namespace test {
	std::vector <std::pair<std::string, std::string>>data;
	void process(std::string path1, std::string path2) {
		std::ifstream in;
		try {
			std::cout << "open file: " << path1 << std::endl;
			in.open(path1);
			if (in.is_open())std::cout << "OK " << std::endl;
			else {
				std::cout << "ERROR " << path1 << std::endl;
				return;
			}
			std::string s;
			in >> s;
			for (int i = 1; in; i++) {

				int pos = s.find('=');
				if (pos != -1) {
					std::cout << "#" << i << ": param: \"" << s.substr(0, pos) << "\", value: \"" << s.substr(pos + 1, s.length() - pos - 1) << "\"" << std::endl;
					data.push_back(std::make_pair(s.substr(0, pos), s.substr(pos + 1, s.length() - pos - 1)));
				}
				else throw std::exception("empty param");
				in >> s;
			}
		}
		catch (std::exception ex) {
			std::cout << "exception " << ex.what();
		}

		std::ofstream out;

		try {
			std::cout << "open file: " << path2 << std::endl;
			out.open(path2);
			if (out.is_open())std::cout << "OK " << std::endl;
			else {
				std::cout << "ERROR " << path1 << std::endl;
				return;
			}
			std::vector <std::pair<std::string, std::string>>::iterator i;
			for (i = data.begin(); i != data.end(); i++) {
				out << "param: \"" << (*i).first << "\", value: \"" << (*i).second << "\"" << std::endl;
			}
		}
		catch (std::exception ex) {
			std::cout << "exception " << ex.what();
		}
	}

	std::list<movie> SELECT(std::string WHERE, std::list<movie>::iterator begin, std::list<movie>::iterator end) {
		std::list<movie> tmp;
		std::string name = "";
		std::string review = "";
		int id = 0;

		int pos = WHERE.find("name=") + 5;
		if (pos >= 5)
			for (int i = pos; i < WHERE.length() && WHERE[i] != ' '; i++)
				name += WHERE[i];

		pos = WHERE.find("review=") + 7;
		if (pos >= 7)
			for (int i = pos; i < WHERE.length() && WHERE[i] != ' '; i++)
				review += WHERE[i];

		pos = WHERE.find("id=") + 3;
		if (pos >= 3)
			for (int i = pos; i < WHERE.length() && WHERE[i] != ' '; i++)
				if (WHERE[i] >= '0' && WHERE[i] <= '9')id = id * 10 + WHERE[i] - '0';


		std::list<movie>::iterator iter;
		for (iter = begin; iter != end; ++iter)
		{
			if (((*iter).name == name || name == "") &&
				((*iter).review == review || review == "") &&
				((*iter).id == id || id == 0)) {
				//std::cout << *iter << std::endl;
				tmp.push_back(*iter);
			}
		}
		return tmp;
	}

	movie FIRST(std::string WHERE, std::list<movie>::iterator begin, std::list<movie>::iterator end) {
		return SELECT(WHERE, begin, end).front();
	}

	void DELETE(std::string WHERE, std::list<movie>& L, std::list<movie>::iterator begin, std::list<movie>::iterator end) {
		std::string name = "";
		std::string review = "";
		int id = 0;

		int pos = WHERE.find("name=") + 5;
		if (pos >= 5)
			for (int i = pos; i < WHERE.length() && WHERE[i] != ' '; i++)
				name += WHERE[i];

		pos = WHERE.find("review=") + 7;
		if (pos >= 7)
			for (int i = pos; i < WHERE.length() && WHERE[i] != ' '; i++)
				review += WHERE[i];

		pos = WHERE.find("id=") + 3;
		if (pos >= 3)
			for (int i = pos; i < WHERE.length() && WHERE[i] != ' '; i++)
				if (WHERE[i] >= '0' && WHERE[i] <= '9')id = id * 10 + WHERE[i] - '0';


		std::list<movie>::iterator iter;
		for (iter = begin; iter != end; ++iter)
		{
			if (((*iter).name == name || name == "") &&
				((*iter).review == review || review == "") &&
				((*iter).id == id || id == 0)) {
				iter = L.erase(iter);
				//std::cout << *iter << std::endl;
			}
		}

	}
}
int main()
{	
	std::list<movie> res;
	std::list<movie> L;
	movie a("test1","good",1);
	movie b("test2", "baad", 2);
	movie c("test3", "normal", 3);
	movie d("test4", "normal", 4);

	L.push_back(a);
	L.push_back(b);
	L.push_back(c);
	L.push_back(d);

	res = test::SELECT("review=normal", L.begin(), L.end());
	std::cout<< test::FIRST("review=normal", L.begin(), L.end())<<"\n";
	test::DELETE("name=test1", L, L.begin(), L.end());
	test::process("input.txt","output.txt");
}
