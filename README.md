# Strategy Base

Example of adding strategies of differing type which conform to a `concept`.

```

struct strategy_a {
    void on_book(const instrument_t&, const book_t&) {
        std::cout << "strategy a on book" << std::endl;
    }
};

struct strategy_b {
    void on_book(const instrument_t&, const book_t&) {
        std::cout << "strategy b on book" << std::endl;
    }
};


int main() {
    
    strategy_pool_t pool;
    pool.push_back(strategy_a{});
    pool.push_back(strategy_b{});

    for(auto& s: pool) {
        on_book(s, instrument_t{}, book_t{});
    }

    return 0;
}

```