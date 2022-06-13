#include"Server.h"
#include"DatabaseContext.h"
int main()
{
	try
	{
		Server serv(15000);
		serv.openConnection();
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}