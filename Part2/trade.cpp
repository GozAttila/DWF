#include "trade.hpp"
#include "json.hpp"
#include <iostream>
#include <chrono>

using json = nlohmann::json;
using namespace std::chrono;

// Counters for testing and optimalization
extern microseconds total_parse_duration;

void parse_trades(const std::string& json_data) {
    try {
        auto response = json::parse(json_data);
        
        if (response.contains("code")) {
            int error_code = response["code"].get<int>();
            std::string error_message = response["msg"].get<std::string>();
            std::cerr << "API error: Code " << error_code << " - " << error_message << std::endl;
            return;
        }

        for (const auto& trade : response) {
            auto start = high_resolution_clock::now();
            
            Trade t {
                trade["a"].get<int64_t>(),
                std::stod(trade["p"].get<std::string>()),
                std::stod(trade["q"].get<std::string>()),
                trade["f"].get<int64_t>(),
                trade["l"].get<int64_t>(),
                trade["T"].get<int64_t>(),
                trade["m"].get<bool>()
            };

            std::cout << "[\n"
                      << "  {\n"
                      << "    \"a\": " << t.aggregate_trade_id << ",\n"
                      << "    \"p\": \"" << t.price << "\",\n"
                      << "    \"q\": \"" << t.quantity << "\",\n"
                      << "    \"f\": " << t.first_trade_id << ",\n"
                      << "    \"l\": " << t.last_trade_id << ",\n"
                      << "    \"T\": " << t.timestamp << ",\n"
                      << "    \"m\": " << (t.buyer_is_maker ? "true" : "false") << "\n"
                      << "  }\n"
                      << "]" << std::endl;

            
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            std::cout << "Time taken to parse this trade: " << duration.count() << " microseconds\n";
            
            // Counters for testing and optimalization
            total_parse_duration += duration;
        }
    } catch (const std::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }
}
