#include "pch.h"
#include "ThreadController.h"
#include "Connection.h"

ThreadController::ThreadController(std::shared_ptr<ThreadRepository> threadsRepo) : threadsRepository_(threadsRepo)
{
}

bool ThreadController::createThread(const std::string& title, int creatorId, const std::string& uuid)
{
	std::string errorMessage;
	if (!ThreadsValidator::validateCreate(title, uuid, creatorId, errorMessage))
	{
		return false;
	}
	
	if (!threadsRepository_->userSearch(creatorId))
	{
		return false;
	}
	
	return threadsRepository_->createThread(title, creatorId, uuid);
}

bool ThreadController::deleteThread(std::string& threadId)
{
	std::string errorMessage;
	if (!ThreadsValidator::validateDelete(threadId, errorMessage))
	{
		return false;
	}
	
	return threadsRepository_->deleteThread(threadId);
}

bool ThreadController::updateTitleThread(const std::string& threadId, const std::string& newTitle)
{
	std::string errorMessage;
	if (!ThreadsValidator::validateUpdateRename(threadId, newTitle, errorMessage))
	{
		return false;
	}
	
	return threadsRepository_->updateThread(threadId, newTitle);
}
