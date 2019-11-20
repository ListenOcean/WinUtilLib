#include "log.h"
//Any cpp include log.h and one need to call FileLoggerInit.
std::shared_ptr<spdlog::logger> file_logger;
bool isfile_loggerInit = false;

void FileLoggerInit(const char* fileName) {
	if (isfile_loggerInit) {
		return;
	}
	file_logger = spdlog::basic_logger_mt("log", fileName);
	spdlog::set_default_logger(file_logger);
	spdlog::flush_every(std::chrono::seconds(2));
	isfile_loggerInit = true;
	return;
}