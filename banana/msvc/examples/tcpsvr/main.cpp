#include "basic.h"
#include "selector.h"

#ifdef _WIN32
#pragma comment(lib , "ws2_32.lib")
#endif // _WIN32



int main(int argc, char** argv)
{
	//return tcpsvr::Runbasic();
	return tcpsvr::RunSelect();
}
