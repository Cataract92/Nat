/**
 * Nico Feld - 1169233
 */

#include <cstdint>
#include <vector>

class Nat {

private:

    std::vector<uint32_t>* vector = new std::vector<uint32_t>;

    explicit Nat(std::vector<uint32_t>* v);

public:
    virtual ~Nat();

public:
    static uint32_t r;

    explicit Nat(uint32_t n);
    Nat* add(Nat* y);
    Nat* add(uint32_t y);
    Nat* shift(uint32_t n);
    void print();
};
