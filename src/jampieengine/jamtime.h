#pragma once

#include <chrono>
#include <vector>
#include <thread>

namespace Jam {

	class Time {
	public:
		
		//The call to register a thread. Should only be called once from the created thread.
		static void registerThread();

		//The call to unregister the current thread. Should only be called once from the created thread.
		static void unregisterThread();

		//The update call. Should only be called once per frame
		static void update();

		//Sets the desierd FPS
		static void setFPS(int fps);

		//When a thread is ready for a new frame, it waits
		static void wait();

		//Get the delta time
		static double getDelta();

	private:

		//The ids of the threads we're currently having registerd
		static std::vector<std::thread::id> _registerdThreads;
		//A flag to make sure nothing bad happens with the threading
		static bool _accessingRegisterdThreads;

		//The ids of the threads we're currently having registerd
		static std::vector<bool> _readyThreads;
		//A flag to make sure nothing bad happens with the threading
		static bool _accessingReadyThreads;

		//The time stamp for the next thread
		static std::chrono::high_resolution_clock::time_point _nextFrame;
		//A flag to make sure nothing bad happens with the threading
		static bool _accessingNextFrame;

		//The desired delta of the frame 
		static std::chrono::duration<long, std::nano> _desiredDelta;
		//A flag to make sure nothing bad happens with the threading
		static bool _accessingDesiredDelta;

		//The delta of the current frame
		static double _delta;

	};
}