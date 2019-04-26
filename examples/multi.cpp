#include <iostream>
#include <thread>
#include <vector>
#include <functional>

void threadFunc(int* x) {
	*x = 10;
	std::cout << "Worker thread: "
		  << std::this_thread::get_id()
		  << " holding: "
		  << *x
		  << std::endl;
}

int main() {

	const size_t n = std::thread::hardware_concurrency();
	std::vector<std::thread> vt(n);
	int x = 5;
	int* p = &x;
	for(size_t i=0; i<n; i++)
		vt[i] = std::thread(threadFunc,p); //must explicitly make a reference using ref(x)
	
	std::cout << "Main thread " << std::endl;

	for(size_t i=0; i<n; i++)
		vt[i].join();

	std::cout << "x: " << x << std::endl;
	std::cout << "Completed\n";
	return 0;
}

