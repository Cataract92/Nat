/**
 * Nico Feld - 1169233
 */

#include <cstdint>
#include <vector>

class Nat {

private:

    std::vector<uint32_t>* vector = new std::vector<uint32_t>;

    explicit Nat(std::vector<uint32_t>* v);

    bool isNegativ = false;

public:
    virtual ~Nat();

public:
    static uint32_t r;

    explicit Nat(int64_t n);
    Nat* add(Nat* y);
    Nat* add(int64_t y);
    Nat* sub(Nat* y);
    Nat* sub(int64_t y);
    Nat* shift(uint32_t n);
    void print();
};
