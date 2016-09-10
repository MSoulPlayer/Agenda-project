#include<iostream>
#include<list>
#include"AgendaService.hpp"
#include"Storage.hpp"
#include<string>
#include<memory>
#include<set>

using namespace std;

AgendaService::AgendaService() {
	startAgenda();
}
AgendaService::~AgendaService() {
	quitAgenda();
}
bool AgendaService::userLogIn(const std::string userName, const std::string password) {
	function<bool(const User&)> filter = [userName, password](const User& user) {
		if (user.getName() == userName && user.getPassword() == password) return true;
		return false;
	};
	list<User> output = m_storage->queryUser(filter);
	return !output.empty();
}
bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone) {
	function<bool(const User&)> filter = [userName](const User& user) {
		if (user.getName() == userName) return true;
		return false;
	};
	list<User> output = m_storage->queryUser(filter);
	User user(userName, password, email, phone);
	if (output.empty()) {
		m_storage->createUser(user);
		return true;
	}
	return false;
}
bool AgendaService::deleteUser(const std::string userName, const std::string password) {
	function<bool(const User&)> filter_1 = [userName, password](const User& user) {
		return user.getName() == userName && user.getPassword() == password;
	};
	function<bool(const Meeting&)> filter_2 = [userName](const Meeting& meeting) {
		if (meeting.getSponsor() == userName) return true;
		for (int i = 0; i < meeting.getParticipator().size(); ++i)
			{
				if (meeting.getParticipator()[i] == userName) return true;
			}
			return false;
	};
	m_storage->deleteMeeting(filter_2);
	if (!m_storage->deleteUser(filter_1)) return false;
	return true;
}
std::list<User> AgendaService::listAllUsers(void) const {
	function<bool(const User&)> filter = [](const User& user) {
		return true;
	};
	return m_storage->queryUser(filter);
}
bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> participator) {
	Date startdate = Date::stringToDate(startDate);
	Date enddate = Date::stringToDate(endDate);
	if(!Date::isValid(startdate)) return false;
	if(!Date::isValid(enddate)) return false;
	if(startdate >= enddate) return false;
	/*
	function<bool(const User&)> l1 = [participator, userName] (const User& user) {
		for (int i = 0; i < participator.size(); i++) {
			if (participator[i] == user.getName()) return true;
		}
		if (user.getName() == userName) return true;
		return false;
	};

	if ((m_storage->queryUser(l1)).empty()) return false;
	function<bool(const Meeting&)> same_title = [title](const Meeting& m) {
		if (m.getTitle() == title) return true;
		return false;
	};
	if (!(m_storage->queryMeeting(same_title)).empty()) return false;
	function<bool(const Meeting&)> filter = [userName, title, participator] (const Meeting& meeting_) {
		if (meeting_.getSponsor() == userName) return true;
		for (int i = 0; i < participator.size(); i++) {
			if (participator[i] == userName) return true;
		}
		bool flag1 = false;
		for (auto i = participator.begin(); i != participator.end(); i++) {
			if ((*i) == meeting_.getSponsor()) {flag1 = true;
			break;
			}
		}
		if (flag1 == true) return true;
		for (int i = 0; i < participator.size(); i++) {
			if (participator[i] == meeting_.getSponsor()) return true;
		}
		
		for (int i = 0; i < participator.size(); i++) {
			for (int j = 0; j < meeting_.getParticipator().size(); j++) {
				if (participator[i] == meeting_.getParticipator()[j]) return true;
			}
		}
		return false;
	};
	list<Meeting> parti_invol = m_storage->queryMeeting(filter);
	for (auto i = parti_invol.begin(); i != parti_invol.end(); i++) {
		if (i->getStartDate() > enddate) continue;
		if (i->getEndDate() < startdate) continue;
		return false;
	}
	Meeting output(userName, participator, startdate, enddate, title);
	m_storage->createMeeting(output);
	return true;
	*/
	set<std::string> str;
	for (int i = 0; i < participator.size(); i++) {
		str.insert(participator[i]);
	}
	if (str.size() != participator.size()) {
		return false;
	}
	if (str.find(userName) != str.end()) {
		return false;
	}
	str.insert(userName);
	auto getUsers = [=](const User& user1) -> bool {
		return true;
	};
	auto allusers = m_storage->queryUser(getUsers);
	set<string> alluserset;
	for (auto it = allusers.begin(); it != allusers.end(); it++) {
		alluserset.insert(it->getName());
	}
	for (auto iter = str.begin(); iter != str.end(); iter++) {
		if (alluserset.find(*iter) == alluserset.end()) return false;
	}
	auto getMeetings = [=](const Meeting& meeting1) -> bool {
		return true;
	};
	function<bool(const Meeting&)> same_title = [title](const Meeting& m) {
		if (m.getTitle() == title) return true;
		return false;
	};
	if (!(m_storage->queryMeeting(same_title)).empty()) return false;
	auto filter = [=](const Meeting& m) -> bool {
		if (!(enddate <= m.getStartDate() || startdate >= m.getEndDate())) {
			if (userName == m.getSponsor()) {
				return true;
			}
			if (m.isParticipator(userName)) return true;
			for (auto i = 0; i < participator.size(); i++) {
				if (participator[i] == m.getSponsor()) return true;
				if (m.isParticipator(participator[i])) return true;
			}
		}
		return false;
	};
	if (!m_storage->queryMeeting(filter).empty()) return false;
	Meeting output(userName, participator, startdate, enddate, title);
	m_storage->createMeeting(output);
	return true;

}
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const {
	function<bool(const Meeting&)> filter = [userName, title] (const Meeting& meeting_) {
		if (meeting_.getSponsor() == userName && meeting_.getTitle() == title) return true;
		/*
		for (auto i = meeting_.getParticipator().begin(); i != meeting_.getParticipator().end(); i++) {
			if ((*i) == userName) return true;
		}*/
		for (int i = 0; i < meeting_.getParticipator().size(); i++) {
			if (title == meeting_.getTitle() && userName == meeting_.getParticipator()[i]) return true;
		}
		return false;
	};
	return m_storage->queryMeeting(filter);
}
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const {
	Date startdate = Date::stringToDate(startDate);
	Date enddate = Date::stringToDate(endDate);
	function<bool(const Meeting&)> filter = [userName, startdate, enddate] (const Meeting& meeting) {
		if (startdate > enddate) return false;
		for (int i = 0; i < meeting.getParticipator().size(); i++) {
			if (meeting.getParticipator()[i] == userName) {
				if (!(enddate < meeting.getStartDate() || startdate > meeting.getEndDate())) return true;
			}
		}
		if (meeting.getSponsor() == userName) {
			if (!(enddate < meeting.getStartDate() || startdate > meeting.getEndDate())) return true;
		}

		return false;
	};
	return m_storage->queryMeeting(filter);
}
std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
	function<bool(const Meeting&)> filter = [userName](const Meeting& meeting) {
		/*for (auto i = meeting.getParticipator().begin(); i != meeting.getParticipator().end(); i++) {
			if ((*i) == userName) return true;
		}*/
			if (meeting.getSponsor() == userName) return true;
			for (int i = 0; i < meeting.getParticipator().size(); i++)
			{
				if (meeting.getParticipator()[i] == userName) return true;
			}
			return false;
	};
	list<Meeting> output = m_storage->queryMeeting(filter);
	return output;
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
	function<bool(const Meeting&)> filter = [userName](const Meeting& meeting) {
		if (meeting.getSponsor() == userName) return true;
		return false;
	};
	return m_storage->queryMeeting(filter);
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string userName) const {
	function<bool(const Meeting&)> filter = [userName](const Meeting& meeting) {
		for (int i = 0; i < meeting.getParticipator().size(); i++) {
				if (meeting.getParticipator()[i] == userName) return true;
			}
			return false;
	};
	return m_storage->queryMeeting(filter);
}
bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {
	function<bool(const Meeting&)> filter = [userName, title](const Meeting& meeting) {
		if (userName == meeting.getSponsor() && title == meeting.getTitle()) return true;
		return false;
	};
	int flag = m_storage->deleteMeeting(filter);
	return flag > 0;
}
bool AgendaService::deleteAllMeetings(const std::string userName) {
	function<bool(const Meeting&)> filter = [userName](const Meeting& meeting) {
		if (meeting.getSponsor() == userName) return true;
		return false;
	};
	int flag = m_storage->deleteMeeting(filter);
	return flag > 0;
}
void AgendaService::startAgenda(void) {
	m_storage = Storage::getInstance();
}
void AgendaService::quitAgenda(void) {
}
