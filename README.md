# Strategy Base

Example of adding strategies of differing type which conform to a `concept`.

```

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

```