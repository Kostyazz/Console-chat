#pragma once
#include <string>

using namespace std;
class User
{
private:
	const string _login;
	string _password;
	string _name;
public:
	User(const string& login, string& password, string& name) : _login(login), _password(password), _name(name) {}
	const string getLogin() const { return _login; }
	string getPassword() const { return _password; }
	string getName() const { return _name; }
	// void setPassword()
	// void setName()
};
