#include<iostream>
#include"Storage.hpp"
#include"Path.hpp"
#include<string>
#include<fstream>
#include<vector>
#include<list>
#include<functional>

using namespace std;

std::shared_ptr<Storage> Storage::m_instance = NULL;
Storage::Storage() {
	m_dirty = false;
	m_userList.clear();
	m_meetingList.clear();
	readFromFile();
}
Storage::~Storage() {
	m_dirty = false;
	writeToFile();
}
bool Storage::sync(void) {
	return  writeToFile();
}

bool Storage::readFromFile(void) {
	/*
	string s;
	ifstream input;
	input.open(Path::userPath);
	if (!input) return false;
	while (getline(input , s)) {
		string name = "", password = "", email = "", phone = "";
		int pos = s.find("\",\"");
		name = s.substr(1, pos - 1);
		s = s.substr(pos + 2);
		pos = s.find("\",\"");
		password = s.substr(1, pos - 1);
		s = s.substr(pos + 2);
		pos = s.find("\",\"");
		email = s.substr(1, pos - 1);
		s = s.substr(pos + 3);
		pos = s.find("\"");
		phone = s.substr(0, pos);
		User user(name, password, email, phone);
		m_userList.push_back(user);
		s.clear();
	}
	input.close();
	s.clear();
	input.open(Path::meetingPath);
	if (!input) return false;
	while (getline(input, s)) {
		string sponsor, startdate, enddate, title;
		std::vector<string> v;
		int pos = s.find("\",\"");
		sponsor = s.substr(1, pos - 1);
		s = s.substr(pos + 3);
		while (s.find("&") != string::npos) {
			pos = s.find("&");
			string ss = "";
			ss = s.substr(0, pos);
			v.push_back(ss);
			s = s.substr(pos + 1);
		}
		pos = s.find("\",\"");
		string sss = s.substr(0, pos);
		v.push_back(sss);
		s = s.substr(pos + 2);
		pos = s.find("\",\"");
		startdate = s.substr(1, pos - 1);
		s = s.substr(pos + 2);
		pos = s.find("\",\"");
		enddate = s.substr(1, pos - 1);
		s = s.substr(pos + 3);
		pos = s.find("\"");
		title = s.substr(0, pos);
		Date startDate(startdate);
		Date endDate(enddate);
		Meeting meeting(sponsor, v, startDate, endDate, title);
		m_meetingList.push_back(meeting);
		s.clear();
	}
	input.close();
	s.clear();
	return true;
	*/
	ifstream in_file;
	in_file.open(Path::userPath);
	while (!in_file.eof()) {
		string user, name, password, email, phone;
		getline(in_file, user);
		if (user.empty()) break;
		int pos = 1;
		int length = user.length();
		for (int i = pos; i < length; i++) {
			if (user[i] == '"') {
				name = user.substr(pos, i - pos);
				pos = i + 3;
				break;
			}
		}
		for (int i = pos; i < length; i++) {
			if (user[i] == '"') {
				password = user.substr(pos, i - pos);
				pos = i + 3;
				break;
			}
		}
		for (int i = pos; i < length; i++) {
			if (user[i] == '"') {
				email = user.substr(pos, i - pos);
				pos = i + 3;
				break;
			}
		}
		for (int i = pos; i < length; i++) {
			if (user[i] == '"') {
				phone = user.substr(pos, i - pos);
				pos = i + 3;
				break;
			}
		}
		User user1(name, password, email, phone);
		m_userList.push_back(user1);
	}
		in_file.close();
		ifstream in_file1;
		in_file1.open(Path::meetingPath);
		while (!in_file1.eof()) {
			string meet, sponsor, sdate, edate, title, par;
			vector<string> participator;
			getline(in_file1, meet);
			if(meet.empty()) break;
			int pos = 1, length = meet.length();
			for (int i = pos; i < length; i++) {
				if (meet[i] == '"') {
					sponsor = meet.substr(pos, i - pos);
					pos = i + 3;
					break;
				}
			}
			for (int i = pos; i < length; i++) {
				if (meet[i] == '"') {
					par = meet.substr(pos, i - pos);
					int pos_ = 0;
					for (int j = 0; i < par.length(); j++) {
						if (par[j] == '&') {
							participator.push_back(par.substr(pos_, j - pos_));
							pos_ = j + 1;
						}
					}
					participator.push_back(par.substr(pos_, par.length() - pos_));
					pos = i + 3;
					break;
				}
			}
			for (int i = pos; i < length; i++) {
			if (meet[i] == '"') {
				sdate = meet.substr(pos, i - pos);
				pos = i + 3;
				break;
				}
			}
			for (int i = pos; i < length; i++) {
			if (meet[i] == '"') {
				edate = meet.substr(pos, i - pos);
				pos = i + 3;
				break;
				}
			}
			for (int i = pos; i < length; i++) {
			if (meet[i] == '"') {
				title = meet.substr(pos, i - pos);
				pos = i + 3;
				break;
				}
			}
			Date startDate(sdate);
			Date endDate(edate);
			m_meetingList.push_back(Meeting(sponsor, participator, startDate, endDate, title));
		}
		in_file1.close();
}
bool Storage::writeToFile(void) {
	ofstream output;
	output.open(Path::userPath);
	if (!output) return false;
	for (auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		output << "\"" << iter->getName() << "\","
		 << "\"" << iter->getPassword() << "\","
		  << "\"" << iter->getEmail() << "\","
		   << "\"" << iter->getPhone() << "\"" << endl;
	}
	output.close();
	output.clear();
	output.open(Path::meetingPath);
	if (!output) return false;
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
		output << "\"" << iter->getSponsor() << "\",\"";
		vector<string> v = iter->getParticipator();
		for (auto iter_ = v.begin(); iter_ != v.end(); ++iter_) {
			auto flag = --v.end();
			output << (*iter_);
			if (iter_ != flag) {
				output << "&";
			}
		}
		output << "\",\"" << Date::dateToString(iter->getStartDate()) << "\",\""
		<< Date::dateToString(iter->getEndDate()) << "\",\"" << iter->getTitle() << "\"" << endl;
	}
	output.close();
	return true;
}
int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
	int output = 0;
	for (list<Meeting>::iterator iter = m_meetingList.begin(); iter !=  m_meetingList.end();) {
		if (filter(*iter)) {
				iter = m_meetingList.erase(iter);
				output++;
		} else {
				iter++;
		}
	}
	m_dirty = true;
	sync();
	return output;
}
int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
	int output = 0;
	for (list<Meeting>::iterator iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
			if (filter(*iter)) {
				switcher(*iter);
				output++;
			}
	}
	sync();
	return output;
}
void Storage::createMeeting(const Meeting & t_meeting) {
	m_meetingList.push_back(t_meeting);
	sync();
	m_dirty = true;
}
std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
	list<Meeting> output;
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
		if (filter(*iter)) {
			output.push_back(*iter);
		}
	}
	return output;
}
int Storage::deleteUser(std::function<bool(const User &)> filter) {
	int output = 0;
	for (auto iter = m_userList.begin(); iter != m_userList.end();) {
		if (filter(*iter)) {
				iter = m_userList.erase(iter);
				output++;
		} else {
				iter++;
		}
	}
	m_dirty = true;
	sync();
	return output;
}
int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
	int output = 0;
	for (list<User>::iterator iter = m_userList.begin(); iter != m_userList.end(); iter++) {
			if (filter(*iter)) {
				switcher(*iter);
				output++;
			}
	}
	sync();
	return output;
}
std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
	list<User> output;
	for (auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
		if (filter(*iter)) {
			output.push_back(*iter);
		}
	}
	return output;
}
void Storage::createUser(const User & t_user) {
	m_userList.push_back(t_user);
	sync();
	m_dirty = true;
}

 std::shared_ptr<Storage> Storage::getInstance(void) {
 	if (m_instance == NULL) {
 		m_instance = std::shared_ptr<Storage>(new Storage);
 	}
 	return m_instance;
}
