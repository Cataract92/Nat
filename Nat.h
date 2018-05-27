/**
 * Nico Feld - 1169233
 */

#include <cstdint>
#include <vector>

class Nat {

private:

    std::vector<uint32_t>* vector = new std::vector<uint32_t>;

    explicit Nat(std::vector<uint32_t>* v, bool isNegativ);

    bool isNegativ = false;

    Nat* faml(Nat* y, uint32_t k, uint32_t m);
    Nat* multRec(Nat* y);
    Nat* low();
    Nat* high();

public:
    virtual ~Nat();

public:
    static uint32_t r;
    static uint32_t kara;
    

    explicit Nat(int32_t n);
    explicit Nat(Nat* n);
    Nat* operator+(Nat *y);
    Nat* operator-(Nat *y);
    Nat* operator*(Nat *y);
    Nat* add(int32_t y);
    Nat* multShort(Nat* y);
    Nat* mult(Nat* y);
    Nat* operator<<(uint32_t n);
    Nat* shift(uint32_t n);
    Nat* neq();
    void print();
};
