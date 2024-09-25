#pragma once

#include <cstdint>
#include <string>

struct Trade {
    int64_t aggregate_trade_id;
    double price;
    double quantity;
    int64_t first_trade_id;
    int64_t last_trade_id;
    int64_t timestamp;
    bool buyer_is_maker;
};

void parse_trades(const std::string& json_data);
