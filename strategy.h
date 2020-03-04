#pragma once

#include <memory>
#include <vector>

enum Side {Buy, Sell};
struct Order { Side side; int qty; double price;};
struct book_t{};
struct instrument_t{};
struct order_manager_t {
    void send(const Order&) {}
};
struct trade_t{};

struct strategy_t {
    template<typename T>
    strategy_t(T t): value_(new model_t<T>(std::move(t))) {}
    strategy_t(const strategy_t& s): value_(s.value_->copy()) {}
    strategy_t(strategy_t&& s) noexcept = default;
    strategy_t& operator=(const strategy_t& s) {
        strategy_t tmp(s);
        *this = std::move(tmp);
        return *(this);
    }
    strategy_t& operator=(strategy_t&& s) noexcept = default;

    friend void on_book(const strategy_t& s, const instrument_t& i, const book_t& b) {
        s.value_->on_book(i, b);
    }
    friend void on_trade(const strategy_t& s, const instrument_t& i, const trade_t& t) {
        s.value_->on_trade(i, t);
    }
private:
    struct interface_t {
        virtual void on_book(const instrument_t&, const book_t&) = 0;
        virtual void on_trade(const instrument_t&, const trade_t&) = 0;
        virtual interface_t* copy() const = 0;
        virtual ~interface_t() = default;
    };
    template<typename T>
    struct model_t: public interface_t {
        model_t(T t):t_(std::move(t))  {}
        interface_t* copy() const {
            return new model_t(*this);
        }
        ~model_t() override {}
        void on_book(const instrument_t& i, const book_t& b) override {
            t_.on_book(i, b);
        }
        void on_trade(const instrument_t& i, const trade_t& t) override {
            t_.on_trade(i, t);
        }
    private:
        T t_;
    };
    std::unique_ptr<interface_t> value_;
};

using strategy_pool_t = std::vector<strategy_t>;
