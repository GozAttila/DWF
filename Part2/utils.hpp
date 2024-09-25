#pragma once

#include <string>
#include <curl/curl.h>

CURL* init_curl();

std::string trim_incomplete_json(const std::string& data);

void log_error(const std::string& message);

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

extern std::string buffer;