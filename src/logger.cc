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

void Logger::addMessage(std::string message)
{
	LogData.log.push_back(message);
}

void Logger::flush()
{
	while (!LogData.log.empty())
	{
		std::cout << "[LOG] : " << LogData.log.back() << std::endl;
		LogData.log.pop_back();
	}
}
