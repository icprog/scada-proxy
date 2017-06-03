#include "ClientThread.hpp"

ClientThread::ClientThread(const std::shared_ptr<Configuration> &configuration,
			 const std::shared_ptr<Buffer> &buffer,
			 const std::shared_ptr<Logger> &logger)
	: Thread(configuration, buffer, logger), data(std::make_shared<ClientData>())
{}

void ClientThread::run() {
	while (receiveRequest()) {
		buffer->pushBack(data);

		data->lockClient();
		sendResponse();
	}

	close(socketDescriptor);
}

void ClientThread::setAddress(const std::string &address) {
	this->address = address;
}

bool ClientThread::receiveRequest()
{
	auto message = readFromSocket();
	if (!message)
		return false;

	data->addRequest(message);
	logger->saveRequest(data.get(), address);

	return true;
}

void ClientThread::sendResponse()
{
	auto message = data->getResponse();
	logger->saveResponse(data.get(), address);
	auto sentBytes = write(socketDescriptor, message->getContent(), message->getContentLength());
	if (sentBytes < message->getContentLength())
		logger->saveWarning("Sent less data than expected");
}
