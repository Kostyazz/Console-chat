#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<unordered_map>
#include "User.h"
#include "Message.h"

using namespace std;
class Chat
{
private:
	string currentUserName = "";
	unordered_map< string, pair<string, string> > users;
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
