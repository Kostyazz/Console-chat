#include "Chat.h"

Chat::~Chat()
{
	users.clear();
	messages.clear();
}

void Chat::initialize()
{
	users.push_back(new User("Vasiliy", "1234", "Vasya"));
	users.push_back(new User("Petr", "1111", "King"));
	users.push_back(new User("a", "a", "a"));
	users.push_back(new User("b", "b", "b"));
}

void Chat::loginMenu()
{
	char command = 0;
	// Successful login is 0;
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
		}
	} while (loginResult);
	cout << "Welcome, " << currentUserName << endl;
	chatMenu();
}

void Chat::chatMenu()
{
	showChat();
	cout << "Just enter a message to send it to all. Enter '/dm <username> <message>' to send direct message to another user. Enter '/logout' to logout" << endl;
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
			text = msg.substr(space2 + 1, -1);
			if (command == "/logout") {
				logout();
				break;
			}
			else if (command == "/dm") {
				for (auto user : users) {
					if (user->getName() == arg) {
						to = arg;
						break;
					}
				}
			}
		}
		if (to == "") {
			cout << "target user not found" << endl;
		}
		else {
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
	for (auto user : users) {
		if (user->getLogin() == login && user->getPassword() == password) {
			currentUserName = user->getName();
			return 0;
		}
	}
	cout << "Pair login-password not found" << endl;
	return 1;
}

void Chat::logout()
{
	currentUserName = "";
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
	cout << "Please enter your password: ";
	cin >> password;
	cout << "Please enter your chat name: ";
	cin >> name;
	for (auto user : users) {
		if (user->getLogin() == login) {
			cout << "This login is taken" << endl;
			return 1;
		}
		if (user->getName() == name) {
			cout << "This name is taken" << endl;
			return 1;
		}

	}
	users.push_back(new User(login, password, name));
	currentUserName = name;
	return 0;
}

void Chat::addMessage(Message* msg)
{
	messages.push_back(msg);
}
