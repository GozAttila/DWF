#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <curl/curl.h>

const std::string API_URL = "https://fapi.binance.com/fapi/v1/aggTrades?symbol=BTCUSDT";
const std::string LOG_FILE = "log.txt";

extern std::string buffer;
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    buffer.append((char*)contents, totalSize);
    return totalSize;
}

CURL* init_curl() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        log_error("Failed to initialize cURL");
        return nullptr;
    }
    curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, nullptr);
    return curl;
}

std::string trim_incomplete_json(const std::string& data) {
    size_t last_bracket = data.find_last_of("]}");
    if (last_bracket != std::string::npos) {
        return data.substr(0, last_bracket + 1);
    }
    return "";
}

void log_error(const std::string& message) {
    std::ofstream log(LOG_FILE, std::ios::app);
    if (log.is_open()) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        log << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S")
            << " - " << message << std::endl;
        log.close();
    } else {
        std::cerr << "Failed to open log file!" << std::endl;
    }
}
