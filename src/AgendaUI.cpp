#include"AgendaUI.hpp"
#include<iostream>
#include<string>
#include<iomanip>
#include<list>
#include<vector>

using namespace std;

AgendaUI::AgendaUI() {

}
void AgendaUI::OperationLoop(void) {
	startAgenda();
	while (1) {
		if (m_agendaService.userLogIn(m_userName, m_userPassword)) {
		cout << "----------------------- Agenda -------------------------------" << endl;
		cout << "Action :" << endl;
		cout << "o   - log out Agenda" << endl;
		cout << "dc  - delete Agenda account" << endl;
		cout << "lu  - list all Agenda user" << endl;
		cout << "cm  - create a meeting" << endl;
		cout << "la  - list all meetings" << endl;
		cout << "las - list all sponsor meetings" << endl;
		cout << "lap - list all participate meetings" << endl;
		cout << "qm  - query meeting by title" << endl;
		cout << "qt  - query meeting by time internal" << endl;
		cout << "dm  - delete meeting by title" << endl;
		cout << "da  - delete all meetings" << endl;
		cout << "Agenda@" << m_userName << " : # ";
		} else {
			cout << "----------------------- Agenda -------------------------------" << endl;
		cout << "Action :" << endl;
		cout << "l   - log in Agenda by user name and password" << endl;
		cout << "r   - register an Agenda account" << endl;
		cout << "q   - quit Agenda" << endl;
		cout << "--------------------------------------------------------------" << endl;
		cout << endl;
		cout << "Agenda : ~$ ";
		}
	executeOperation(getOperation());
	}
}
void AgendaUI::startAgenda(void) {
	cout << "----------------------- Agenda -------------------------------" << endl;
	cout << "Action :" << endl;
	cout << "l   - log in Agenda by user name and password" << endl;
	cout << "r   - register an Agenda account" << endl;
	cout << "q   - quit Agenda" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << endl;
}
std::string AgendaUI::getOperation() {
	string output;
	cin >> output;
	return output;
}
bool AgendaUI::executeOperation(std::string t_operation) {
	if (m_agendaService.userLogIn(m_userName, m_userPassword)) {
			if (t_operation == "o") {userLogOut(); return true;}
			if (t_operation == "dc") {deleteUser(); return true;}
			if (t_operation == "lu") {listAllUsers(); return true;}
			if (t_operation == "cm") {createMeeting(); return true;}
			if (t_operation == "la") {listAllMeetings(); return true;}
			if (t_operation == "las") {listAllSponsorMeetings(); return true;}
			if (t_operation == "lap") {listAllParticipateMeetings(); return true;}
			if (t_operation == "qm") {queryMeetingByTitle(); return true;}
			if (t_operation == "qt") {queryMeetingByTimeInterval(); return true;}
			if (t_operation == "dm") {deleteMeetingByTitle(); return true;}
			if (t_operation == "da") {deleteAllMeetings(); return true;}
	} else {
			if (t_operation == "l") {userLogIn(); return true;}
			if (t_operation == "r") {userRegister(); return true;}
			if (t_operation == "q") {quitAgenda(); return true;}
	}
	return false;
}
void AgendaUI::userLogIn(void) {
	cout << "[log in] [user name] [password]" << endl;
	cout << "[log in] ";
	cin >> m_userName >> m_userPassword;
	if (m_agendaService.userLogIn(m_userName, m_userPassword)) {
		cout << "----------------------- Agenda -------------------------------" << endl;
		cout << "Action :" << endl;
		cout << "o   - log out Agenda" << endl;
		cout << "dc  - delete Agenda account" << endl;
		cout << "lu  - list all Agenda user" << endl;
		cout << "cm  - create a meeting" << endl;
		cout << "la  - list all meetings" << endl;
		cout << "las - list all sponsor meetings" << endl;
		cout << "lap - list all participate meetings" << endl;
		cout << "qm  - query meeting by title" << endl;
		cout << "qt  - query meeting by time internal" << endl;
		cout << "dm  - delete meeting by title" << endl;
		cout << "da  - delete all meetings" << endl;
	} else {
		cout << "[error] log in fail!" << endl;
	}

}
void AgendaUI::userRegister(void) {
		string name, password, email, phone;
		cout << "[register] [user name] [password] [email] [phone]" << endl;
		cout << "[register] ";
		cin >> name >> password >> email >> phone;
		if (m_agendaService.userRegister(name, password, email, phone)) {
			cout << "[register] succeed!" << endl;
		} else {
			cout << "[error] register fail!" << endl;
		}
}
void AgendaUI::quitAgenda(void) {
	exit(0);
}
void AgendaUI::userLogOut(void) {
	m_userName = "";
	m_userPassword = "";
	startAgenda();
}
void AgendaUI::deleteUser(void) {
	if (m_agendaService.deleteUser(m_userName,m_userPassword)) {
		cout << "[delete agenda account] succeed!" <<endl;
	}
}
void AgendaUI::listAllUsers(void) {
	cout << "[list all users]" << endl;
	list<User> userlist = m_agendaService.listAllUsers();
	cout << endl;
	cout << left << setw(20) << "name" << left << setw(20) << "email" << left << setw(20) << "phone" << endl;
	for (auto i = userlist.begin(); i != userlist.end(); i++) {
		cout << left << setw(20) << i->getName() << left << setw(20) << i->getEmail() << left << setw(20) << i->getPhone() << endl;
	}
}
void AgendaUI::createMeeting(void) {
	string title, startdate, enddate;
	int num;
	std::vector<string> participatorsv;
	 cout << "[creat meeting] [the number of participators]" << endl;
	 cout << "[create meeting] ";
	 cin >> num;
	 for (int i = 0; i < num; i++) {
	 	string temp = "";
	 	cout << "[create meeting] please enter the participator " << i + 1 << " ]" << endl;
	 	cout << "[create meeting] " ;
	 	cin >>  temp;
	 	participatorsv.push_back(temp);
	 }
	 cout << "[create meeting] [title][start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
	 cout << "[create meeting] ";
	 cin >> title >> startdate >> enddate;
	 if (m_agendaService.createMeeting(m_userName, title, startdate, enddate, participatorsv)) {
	 	cout << "[create meeting] succeed!" << endl;
	 } else {
	 	cout << "[create meeting] error!" << endl;
	 }

}
void AgendaUI::listAllMeetings(void) {
	cout << "[list all meetings]" << endl;
	cout << endl;
	cout << left << setw(20) << "title" << left << setw(20) << "sponsor" << left << setw(20) <<
	"start time" << left << setw(20) << "end time" << left << setw(20) << "participators" << endl;
	list<Meeting> m = m_agendaService.listAllMeetings(m_userName);
	printMeetings(m);
}
void AgendaUI::listAllSponsorMeetings(void) {
	cout << "[list all sponsor meetings]" << endl;
	cout << left << setw(20) << "title" << left << setw(20) << "sponsor" << left << setw(20) <<
	"start time" << left << setw(20) << "end time" << left << setw(20) << "participators" << endl;
	list<Meeting> m = m_agendaService.listAllSponsorMeetings(m_userName);
	printMeetings(m);
}
void AgendaUI::listAllParticipateMeetings(void) {
	cout << "[list all participator meetings]" << endl;
	cout << left << setw(20) << "title" << left << setw(20) << "sponsor" << left << setw(20) <<
	"start time" << left << setw(20) << "end time" << left << setw(20) << "participators" << endl;
	list<Meeting> m = m_agendaService.listAllParticipateMeetings(m_userName);
	printMeetings(m);
}
void AgendaUI::queryMeetingByTitle(void) {
	cout << "[query meeting] [title]:" <<endl;
	cout << "[query meeting] ";
	string title;
	cin >> title;
	list<Meeting> m = m_agendaService.meetingQuery(m_userName, title);
	printMeetings(m);
}
void AgendaUI::queryMeetingByTimeInterval(void) {
	cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
	cout << "[query meeting] ";
	string sdate, edate;
	cin >> sdate >> edate;
	cout << "[query meeting]" << endl;
	list<Meeting> m = m_agendaService.meetingQuery(m_userName, sdate, edate);
	printMeetings(m);
}
void AgendaUI::deleteMeetingByTitle(void) {
	cout << "[delete meeting] [title]" <<endl;
	cout << "[delete meeting] ";
	string m;
	cin >> m;
	if (m_agendaService.deleteMeeting(m_userName, m)) {
		cout << "[delete meeting by title secceed!]" << endl;
	} else {
		cout << "[error] delete meeting fail!" << endl;
	}
}
void AgendaUI::deleteAllMeetings(void) {
	if (m_agendaService.deleteAllMeetings(m_userName)) {
		cout << "[delete all meetings] succeed!" << endl;
	}
}
void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
	for (auto i = t_meetings.begin(); i != t_meetings.end(); i++) {
		cout << left << setw(20) << i->getTitle() << left << setw(20) << i->getSponsor() << left <<
		 setw(20) << Date::dateToString(i->getStartDate()) << left << setw(20) << Date::dateToString(i->getEndDate());
		 for (auto j = 0; j < (i->getParticipator()).size() - 1; j++) {
		 	cout << i->getParticipator()[j] << ",";
		 }
		 cout << i->getParticipator()[i->getParticipator().size() - 1] << endl;
	}
}
