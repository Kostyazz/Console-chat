#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Message.h"

using namespace std;
class Chat
{
private:
	string currentUserName = "";
	vector<User*> users;
	vector<Message*> messages;
	const string channel = "#all";
public:
	Chat() = default;
	~Chat();
	void initialize();
	void loginMenu();
	void chatMenu();
	void showChat();
	int login();
	void logout();
	int signUp();
	void addMessage(Message* msg);
};
