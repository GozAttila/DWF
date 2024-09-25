#include <iostream>
#include <string>
#include <chrono>
#include <curl/curl.h>
#include "json.hpp"
#include "trade.hpp"
#include "utils.hpp"

using json = nlohmann::json;
using namespace std::chrono;

// Counters for testing and optimalization
high_resolution_clock::time_point program_start;
high_resolution_clock::time_point program_end;
microseconds total_parse_duration = microseconds(0);

std::string buffer;

int main() {
    program_start = high_resolution_clock::now();

    CURL* curl = init_curl();

    if (!curl) {
        std::cerr << "cURL initialization failed." << std::endl;
        return 1;
    }

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        log_error("cURL error: " + std::string(curl_easy_strerror(res)));
    } else {

        std::cout << "API request successful!" << std::endl;

        if (!buffer.empty()) {
            std::string trimmed_buffer = trim_incomplete_json(buffer);

            if (!trimmed_buffer.empty()) {
                parse_trades(trimmed_buffer);
            } else {
                std::cout << "No complete JSON to parse in the buffer, moving to the next chunk..." << std::endl;
            }
        } else {
            log_error("Buffer is empty, no data received.");
            std::cerr << "Buffer is empty, no data received." << std::endl;
        }
    }

    curl_easy_cleanup(curl);

    // Counters for testing and optimalization
    program_end = high_resolution_clock::now();
    auto full_running_time = duration_cast<microseconds>(program_end - program_start);
    auto other_time = full_running_time - total_parse_duration;

    std::cout << "Full running time: " << full_running_time.count() << " microseconds\n";
    std::cout << "Total parsing time: " << total_parse_duration.count() << " microseconds\n";
    std::cout << "Time spent on other processes: " << other_time.count() << " microseconds\n";
    std::cout << "Press a key to close the window..." << std::endl;
    std::cin.get();

    return 0;
}
