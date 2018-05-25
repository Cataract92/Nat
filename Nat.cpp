/**
 * Nico Feld - 1169233
 *
 * To Compile: g++ -std=c++11 Nat.cpp -o nat.exe
 */

#include <iostream>
#include <cmath>
#include "Nat.h"

uint32_t Nat::r = 4096;

Nat::Nat(int64_t n) {
    
    int i = 0;
    while (abs(n) >= static_cast<uint64_t >(pow(Nat::r,i)))
    {
        i++;
    }
    i--;

    if ( n == -0 || n < 0)
    {
        n = pow(Nat::r,i+1) - abs(n);
        isNegativ = true;
    }

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

        if (static_cast<int32_t>(v1->size() - i) >= 0)
        {
            v1value = (v1->at(v1->size()-i));
        }
        else
            if (this->isNegativ)
                v1value = r-1;
            else   
                v1value = 0;
        
        if (static_cast<int32_t>(v2->size() - i) >= 0)
        {
            v2value = (v2->at(v2->size()-i));
        }
        else
            if (y->isNegativ)
                v2value = r-1;
            else   
                v2value = 0;


        if (v1value + v2value + carry >= r)
        {
            newVector->insert(newVector->begin(),(v1value + v2value + carry) % r);
            carry = 1;
        } else {
            newVector->insert(newVector->begin(),v1value + v2value + carry);
            carry = 0;
        }
    }

    Nat* ret = nullptr;

    bool isRetNegativ = false;

    if (this->isNegativ != y->isNegativ)
    {
        if (carry == 0)
            isRetNegativ = true;
    } else 
    {
        if (this->isNegativ)
        {
            if (carry == 1)
                newVector->insert(newVector->begin(),r-carry);

            isRetNegativ = true;
        } else
            if (carry == 1)
                newVector->insert(newVector->begin(),carry);
    }
    
    ret = new Nat(newVector);
    ret->isNegativ = isRetNegativ;
    return ret;
}

void Nat::print() {
    std::cout << "(";
    if (isNegativ)
        std::cout << "1 ";
    else
        std::cout << "0 ";
    for (std::vector<uint32_t >::const_iterator v = vector->begin(); v != vector->end(); ++v)
        std::cout << *v << ' ';

    std::cout << ")_" << r;
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

Nat *Nat::add(int64_t y) {
    auto tmp = new Nat(y);
    auto ret = add(tmp);
    delete(tmp);
    return ret;
}

Nat *Nat::sub(int64_t y) {
    auto tmp = new Nat(-y);
    auto ret = add(tmp);
    delete(tmp);
    return ret;
}

Nat *Nat::sub(Nat* y) {
    return nullptr;
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

    auto a = -4;
    auto b = -3;
    auto n1 = new Nat(a);
    auto n2 = new Nat(b);
    auto n3 = n1->add(n2);
    std::cout << a << " + " << b << " = " << a+b << "\n";
    n1->print();
    std::cout << " - ";
    n2->print();
    std::cout << " = ";
    n3->print();
    std::cout << "\n\n";

    a = 4;
    b = -7;
    n1 = new Nat(a);
    n2 = new Nat(b);
    n3 = n1->add(n2);
    std::cout << a << " + " << b << " = " << a+b << "\n";
    n1->print();
    std::cout << " - ";
    n2->print();
    std::cout << " = ";
    n3->print();
    std::cout << "\n\n";

    a = -3;
    b = 4;
    n1 = new Nat(a);
    n2 = new Nat(b);
    n3 = n1->add(n2);
    std::cout << a << " + " << b << " = " << a+b << "\n";
    n1->print();
    std::cout << " - ";
    n2->print();
    std::cout << " = ";
    n3->print();
    std::cout << "\n\n";

    a = 4;
    b = 4093;
    n1 = new Nat(a);
    n2 = new Nat(b);
    n3 = n1->add(n2);
    std::cout << a << " + " << b << " = " << a+b << "\n";
    n1->print();
    std::cout << " - ";
    n2->print();
    std::cout << " = ";
    n3->print();
    std::cout << "\n\n";

    return 0;
}
