
#include <iostream>
#include "strategy.h"

struct strategy_a {
    void set_order_manager(order_manager_t& ord_mgr) {
        ord_mgr_ = ord_mgr;
    }
    void on_book(const instrument_t&, const book_t&) {
        std::cout << "strategy a on book called" << std::endl;
        ord_mgr_.send({Side::Buy, 10, 13000.0});
    }
    void on_trade(const instrument_t, const trade_t&) {
        std::cout << "strategy a on book called" << std::endl;
    }
private:
    order_manager_t ord_mgr_;
};

struct strategy_b {
    void set_order_manager(order_manager_t&) {}
    void on_book(const instrument_t&, const book_t&) {
        std::cout << "strategy b on book called" << std::endl;
    }
    void on_trade(const instrument_t, const trade_t&) {
        std::cout << "strategy b on book called" << std::endl;
    }
};

int main() {

    strategy_pool_t pool;
    pool.push_back(strategy_a{});
    pool.push_back(strategy_b{});

    for(auto& s: pool) {
        on_book(s, instrument_t{}, book_t{});
        on_trade(s, instrument_t{}, trade_t{});
    }
    return 0;
}
