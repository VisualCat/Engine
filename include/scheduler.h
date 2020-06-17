#ifndef __VC_SCHEDULER__
#define __VC_SCHEDULER__ 1

#include <atomic>
#include <functional>
#include <thread>
#include <platform_types.h>

namespace VC {

	class Scheduler
	{
	public:

		//TODO create TASK, Worker and Sync classes
		//The scheduler controls the workers
		//	struct Worker {
		//		std::thread thread;
		//		Task actual_task
		//	};
		//the workers have tasks
		//	struct Task {
		//		std::function<void()> func;
		//		Sync sync; OPTIONAL
		//	};
		// OPTIONAL
		//the sync should controls the queue of tasks for the workers, example by priority, on sync 1 we have 4 workers in sync 2 we have 2 workers
		// so the tasks on sync 1 will be done faster than sync 2
		//	struct Sync {
		//		u8 ID;
		//	};
		//	

		Scheduler(u8 num_of_threads);
		~Scheduler();

		void AddTask(std::function<void()> task /*Sync sync*/);




	private:
		u16 num_of_threads_;			// num OS threads created 
		u16 max_running_threads = 0;	// 0 = all threads
		u16 max_attempts = 0;			// num of attempts before set a worker to sleep 
		u16 ms_between_attempts = 0;	// num of ms or microseconds between attempts 


	};

}

#endif