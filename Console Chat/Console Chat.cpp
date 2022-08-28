#include <iostream>
#include "Chat.h"

using namespace std;

int main()
{
	Chat chat;
	chat.initialize();
	while (true) {
		chat.loginMenu();
	}
}
