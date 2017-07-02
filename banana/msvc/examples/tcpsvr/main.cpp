#include "basic.h"
#include "selector.h"
#include "all.h"
#include "glog/logging.h"

#ifdef _WIN32
#pragma comment(lib , "ws2_32.lib")
#endif // _WIN32



int main(int argc, char** argv)
{
	google::InitGoogleLogging(argv[0]);  //参数为自己的可执行文件名  

	google::SetLogDestination(google::GLOG_INFO, "./core");

	//return tcpsvr::Runbasic();
	//return tcpsvr::RunSelect();
	return tcpsvr::RunCore();
}
