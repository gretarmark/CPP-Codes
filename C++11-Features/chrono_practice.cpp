#include <iostream>
#include <chrono>
#include <thread> // For simulating a delay

// A practice program using C++'s <chrono> library to measure execution time and work with time points and durations.

int main() {
    auto now = std::chrono::system_clock::now();
    std::cout << "Current time in system_clock: " << now.time_since_epoch().count() << " ticks\n";


    // Using std::chrono to get the current time
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Starting a process..." << std::endl;

    // Simulate some work using std::this_thread::sleep_for
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Pause for 2 seconds

    // Measure the end time
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Process completed." << std::endl;

    // Calculate the duration of the process
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;

    // Demonstrating different chrono duration types
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);

    std::cout << "Elapsed time in milliseconds: " << milliseconds.count() << " ms" << std::endl;
    std::cout << "Elapsed time in microseconds: " << microseconds.count() << " µs" << std::endl;

    // Working with time points: get the current time, add some duration, and display
    auto current_time = std::chrono::system_clock::now();
    auto future_time = current_time + std::chrono::minutes(5); // 5 minutes later

    // Convert to time_t to display as a readable time
    std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);
    std::time_t future_time_t = std::chrono::system_clock::to_time_t(future_time);

    std::cout << "Current time: " << std::ctime(&current_time_t);
    std::cout << "Future time (5 minutes later): " << std::ctime(&future_time_t);


    return 0;
}
