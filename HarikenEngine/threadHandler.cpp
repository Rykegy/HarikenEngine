#include "stdafx.h"
#include "threadHandler.h"

using namespace HARIKEN;

std::unique_ptr<ThreadHandler> ThreadHandler::threadHandlerInstance = nullptr;

ThreadHandler* HARIKEN::ThreadHandler::GetInstance()
{
	if (threadHandlerInstance.get() == nullptr)
		threadHandlerInstance.reset(new ThreadHandler);

	return threadHandlerInstance.get();
}

std::future<void>* HARIKEN::ThreadHandler::createVoidThread()
{

	voidThreads.push_back(std::future<void>());

	return &voidThreads.back();

}

bool HARIKEN::ThreadHandler::checkThead(std::future<void>* thread)
{

	if(thread->wait_for(std::chrono::milliseconds(10)) != std::future_status::ready)
		return false;

	else {

		for (size_t i = 0; i < voidThreads.size(); i++)
			if (thread == &voidThreads[i])
				voidThreads.erase(voidThreads.begin() + i);

		return true;

	}

}

HARIKEN::ThreadHandler::ThreadHandler()
{
}

HARIKEN::ThreadHandler::~ThreadHandler()
{
}
