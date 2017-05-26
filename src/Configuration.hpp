#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

enum ConfigurationField
{
	SERVER_ADDRESS,
	SERVER_PORT,
	CLIENT_PORT,
	LOG_FILE,
	MAX_BUFFER_SIZE,
	VERBOSITY,
	Count
};

class Configuration
{
public:
	Configuration();
	Configuration(std::ifstream &data);

	const char *getServerAddress() const;
	int getServerPort() const;
	int getClientPort() const;
	std::string getLogFile() const;
	std::string getMaxBufferSize() const;
	bool isVerbose() const;

private:
	std::unordered_map<std::string, std::string> information;
	bool verbose;
};

#endif
