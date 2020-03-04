#include <memory>
#include <vector>
#include <iostream>

struct Book{};
struct Instrument{};

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

    friend void on_book(const strategy_t& s, const Instrument& i, const Book& b) {
        s.value_->on_book(i, b);
    }
private:
    struct interface_t {
        virtual void on_book(const Instrument&, const Book&) = 0;
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
        void on_book(const Instrument& i, const Book& b) override {
            t_.on_book(i, b);
        }
    private:
        T t_;
    };
    std::unique_ptr<interface_t> value_;
};

using strategy_pool_t = std::vector<strategy_t>;

struct strategy_a {
    void on_book(const Instrument&, const Book&) {
        std::cout << "strategy a on book" << std::endl;
    }
};

struct strategy_b {
    void on_book(const Instrument&, const Book&) {
        std::cout << "strategy b on book" << std::endl;
    }
};


int main() {

    strategy_pool_t pool;
    pool.push_back(strategy_a{});
    pool.push_back(strategy_b{});

    for(auto& s: pool) {
        on_book(s, Instrument{}, Book{});
    }
    return 0;
}
