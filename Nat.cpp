/**
 * Nico Feld - 1169233
 *
 * To Compile: g++ -std=c++11 Nat.cpp -o nat.exe
 */

#include <iostream>
#include <cmath>
#include "Nat.h"

uint32_t Nat::r = 4096;

Nat::Nat(uint32_t n) {
    int i = 0;
    while (n >= static_cast<uint64_t >(pow(Nat::r,i)))
    {
        i++;
    }
    i--;

    while (i >= 0)
    {
        vector->push_back(static_cast<uint32_t >(n / static_cast<uint64_t >(pow(r,i))));
        n = static_cast<uint32_t >((n % static_cast<uint64_t >(pow(r,i))));
        i--;
    }
}

Nat::Nat(std::vector<uint32_t>* v) {
    delete(vector);
    vector = v;
}

Nat* Nat::add(Nat* y) {

    auto newVector = new std::vector<uint32_t>;

    auto v1 = this->vector;
    auto v2 = y->vector;

    auto maxLength = v1->size() > v2->size() ? v1->size() : v2->size();

    uint32_t carry = 0;
    for (uint32_t i = 1; i <= maxLength ; i++)
    {
        auto v1value = 0;
        auto v2value = 0;

        try{
            v1value = (v1->at(v1->size()-i));
        } catch (...)
        {
            v1value = 0;
        }
        try{
            v2value = (v2->at(v2->size()-i));
        } catch (...)
        {
            v2value = 0;
        }

        if (v1value + v2value + carry >= r)
        {
            newVector->insert(newVector->begin(),(v1value + v2value + carry) % r);
            carry = 1;
        } else {
            newVector->insert(newVector->begin(),v1value + v2value + carry);
            carry = 0;
        }
    }

    if (carry != 0)
        newVector->insert(newVector->begin(),carry);

    return new Nat(newVector);
}

void Nat::print() {
    std::cout << "(";
    for (std::vector<uint32_t >::const_iterator v = vector->begin(); v != vector->end(); ++v)
        std::cout << *v << ' ';

    std::cout << ")_" << r << "\n";
}

Nat* Nat::shift(uint32_t n) {
    if (n == 0)
        return this;

    auto tmp = this->add(this);
    for (uint32_t i = 1; i < n ; i++)
    {
        auto tmp2 = tmp->add(tmp);
        delete(tmp);
        tmp = tmp2;
    }
    return tmp;
}

Nat *Nat::add(uint32_t y) {
    return add(new Nat(y));
}

Nat::~Nat() {
    delete(vector);
}

int main(int argn, char *argv[]) {
    if (argn != 2){
        std::cout << "Usage: nat.exe base (e.g 10). Using 4096 as a Base.\n";
    } else {
        Nat::r = strtoul(argv[1], nullptr, 0);
    }

    auto n1 = new Nat(1234567890);
    n1 = n1->shift(100);
    n1 = n1->add(1);
    std::cout << "\n1234567890 * 2^(100) + 1 is:\n";
    n1->print();

    return 0;
}
