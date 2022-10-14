#include "Chat.h"
#include <fstream>
#include <exception>

Chat::~Chat()
{
	users.clear();
	messages.clear();
}

void Chat::initialize()
{
	//fill users array with login credentials from "Login.txt"
	//separator is ' '
	try {
		ifstream loginFile;
		loginFile.open("Login.txt");
		if (! loginFile.is_open()) {
			throw runtime_error("ERROR: Login file not found");
		}
		while (loginFile) {
			string login;
			string password;
			string name;
			loginFile >> login >> password >> name;
			loginFile.ignore();
			for (char c : login) {
				if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && (c < '0' || c > '9')) {
					throw runtime_error("ERROR: bad credentials in the file");
				}
			}
			for (char c : name) {
				if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && (c < '0' || c > '9')) {
					throw runtime_error("ERROR: bad credentials in the file");
				}
			}
			if (name.empty()) {
				throw runtime_error("ERROR: bad credentials in the file");
			}
			users[login] = make_pair(password, name);
		}
	}
	catch (runtime_error& ex) {
		cerr << ex.what() << endl;
		exit(1);
	}
}

void Chat::loginMenu()
{
	char command = 0;
	// Successful loginResult is 0;
	int loginResult = -1; 
	do {
		cout << "Please enter l to login, s to sign up, q to quit" << endl;
		cin >> command;
		switch (command) {
			case 'l':
				loginResult = login();
				break;
			case 's':
				loginResult = signUp();
				break;
			case 'q':
				exit(0);
				break;
			default:
				break;
		}
	} while (loginResult);
	cout << "Welcome, " << currentUserName << endl;
	chatMenu();
}

void Chat::chatMenu()
{
	showChat();
	cout << "Enter a message to send it to all. Enter '/dm <username> <message>' to send direct message to another user. Enter '/logout' to logout" << endl;
	cin.ignore();
	while (true) {
		string msg;
		string command;
		string arg;
		string to = "";
		string text = "";
		getline(cin, msg);
		if (msg[0] != '/') {
			to = channel;
			text = msg;
		}
		else {
			//split the input string by first two ' ': command, arg - its argument, text - rest of the input
			size_t space1 = msg.find(' ');
			size_t space2 = msg.find(' ', space1 + 1);
			command = msg.substr(0, space1);
			arg = msg.substr(space1 + 1, space2 - space1 - 1);
			text = msg.substr(space2 + 1, msg.size());
			if (command == "/logout") {
				logout();
				break;
			}
			else if (command == "/dm") {
				for (auto user : users) {
					if (user.second.second == arg) {
						to = arg;
						break;
					}
				}
			}
		}
		if (to.empty()) {
			cout << "target user not found" << endl;
		} else {
			addMessage(new Message(currentUserName, to, text));
		}
	}
}

void Chat::showChat()
{
	for (auto msg : messages) {
		if (msg->getFrom() == currentUserName || msg->getTo() == currentUserName || msg->getTo() == channel) {
			cout << msg->getFrom() << " to " << msg->getTo() << ": " << msg->getText() << endl;
		}
	}
}

int Chat::login()
{
	string login;
	string password;
	cout << "Login: ";
	cin >> login;
	cout << "Password: ";
	cin >> password;
	if (users[login].first == password) {
		currentUserName = users[login].second;
		return 0;
	}
	cout << "Pair login-password not found" << endl;
	return 1;
}

void Chat::logout()
{
	currentUserName.clear();
}

int Chat::signUp()
{
	string login;
	string password;
	string name;
	cout << "Please enter your login. Only digits and latin symbols allowed: ";
	cin >> login;
	for (char c : login) {
		if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && (c < '0' || c > '9')) {
			cout << "Only digits and latin symbols allowed" << endl;
			return 2;
		}
	}
	cout << "Please enter your password. Space symbol not allowed: ";
	cin >> password;
	for (char c : login) {
		if (c == ' ') {
			cout << "Space symbol not allowed" << endl;
			return 2;
		}
	}
	cout << "Please enter your chat name. Only digits and latin symbols allowed: ";
	cin >> name;
	for (char c : name) {
		if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && (c < '0' || c > '9')) {
			cout << "Only digits and latin symbols allowed" << endl;
			return 2;
		}
	}
	for (auto user : users) {
		if (user.first == login) {
			cout << "This login is taken" << endl;
			return 1;
		}
		if (user.second.second == name) {
			cout << "This name is taken" << endl;
			return 1;
		}

	}
	users[login] = make_pair(password, name);
	try {
		ofstream loginFile;
		loginFile.open("Login.txt", ios::app);
		if (!loginFile.is_open()) {
			throw runtime_error("ERROR: Login file not found");
		}
		loginFile << endl << login << " " << password << " " << name;
		
	}
	catch (runtime_error& ex) {
		cerr << ex.what() << endl;
		exit(1);
	}

	currentUserName = name;
	return 0;
}

void Chat::addMessage(Message* msg)
{
	messages.push_back(msg);
}
