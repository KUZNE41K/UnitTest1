#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <memory>
#include <string>
#include "threadsRepository.h"
#include "threadsValidator.h"

class ThreadController : public ThreadsValidator
{
public:
	ThreadController(std::shared_ptr<ThreadRepository> threadsRepo);
	bool createThread(const std::string& title, int creatorId, const std::string& uuid);
	bool deleteThread( std::string& threadId);
	bool updateTitleThread(const std::string& threadId, const std::string& newTitle);

private:
	std::shared_ptr<ThreadRepository> threadsRepository_;
};

#endif // !THREADCONTROLLER_H

