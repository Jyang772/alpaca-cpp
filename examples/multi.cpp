#include <iostream>
#include <thread>
#include <vector>

void threadFunc() {
	std::cout << "Worker thread: "
		  << std::this_thread::get_id()
		  << std::endl;
}

int main() {

	const size_t n = std::thread::hardware_concurrency();
	std::vector<std::thread> vt(n);
	for(size_t i=0; i<n; i++)
		vt[i] = std::thread(threadFunc);
	
	std::cout << "Main thread " << std::endl;

	for(size_t i=0; i<n; i++)
		vt[i].join();

	std::cout << "Completed\n";
	return 0;
}

