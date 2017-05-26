#include "ClientData.hpp"

ClientData::ClientData()
	: mutex(std::unique_ptr<std::mutex>(new std::mutex))
{
	mutex->lock();
}

void ClientData::addRequest(const std::shared_ptr<Message> &request)
{
	this->request = request;
}

std::shared_ptr<Message> ClientData::getRequest()
{
	return request;
}

void ClientData::addResponse(const std::shared_ptr<Message> &response)
{
	this->response = response;
}

std::shared_ptr<Message> ClientData::getResponse()
{
	return response;
}

void ClientData::lockClient()
{
	mutex->lock();
}

void ClientData::unlockClient()
{
	mutex->unlock();
}