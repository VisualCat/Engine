#include <logger.h>

using namespace VC;

static struct {
	std::vector<std::string> log;
}LogData;

 

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::addMessage(std::string mesage)
{
	LogData.log.push_back(mesage);
}

void Logger::flush()
{
	while (!LogData.log.empty())
	{
		std::cout << "[LOG] : " << LogData.log.back() << std::endl;
		LogData.log.pop_back();
	}
}
