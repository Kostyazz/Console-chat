#pragma once
#include <string>
#include <vector>
#include "User.h"
#include "Message.h"

using namespace std;
class Chat
{
private:
	string currentUserName;
	vector<User*> users;
	vector<Message*> messages;
public:
	
	void initialize();
	void loginMenu();
	void chatMenu();
	void showChat();
	void login();
	void logout();
	void signUp();
	void addMessage();
};
