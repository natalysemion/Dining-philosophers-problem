#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>

const int num_philosophers = 5;
const int num_forks = num_philosophers;

std::vector<std::mutex> fork_locks(num_forks);
std::mutex mutex;

void philosopher(int index) {
    while (true) {
        std::cout << "Philosopher " << index << " is thinking" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(std::rand() % 5 + 1));

        mutex.lock();

        int left_fork_index = index;
        int right_fork_index = (index + 1) % num_forks;

        fork_locks[left_fork_index].lock();
        fork_locks[right_fork_index].lock();

        mutex.unlock();

        std::cout << "Philosopher " << index << " is eating" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(std::rand() % 5 + 1));

        fork_locks[left_fork_index].unlock();
        fork_locks[right_fork_index].unlock();
    }
}

int main() {
    std::vector<std::thread> philosopher_threads;
    for (int i = 0; i < num_philosophers; ++i) {
        philosopher_threads.push_back(std::thread(philosopher, i));
    }

    for (auto& thread : philosopher_threads) {
        thread.join();
    }

    return 0;
}
