/**
 * Nico Feld - 1169233
 *
 * To Compile: g++ -std=c++11 Nat.cpp -o nat.exe
 */

#include <iostream>
#include <cmath>
#include "Nat.h"

uint32_t Nat::r = 4096;
uint32_t Nat::kara = 4;

Nat::Nat(Nat* n)
{
    for (int i = 0; i < n->vector->size();i++)
        this->vector->push_back(n->vector->at(i));

    this->isNegativ = n->isNegativ;
}

Nat::Nat(int32_t n) {
    
    int i = 0;
    while (abs(n) >= static_cast<uint64_t>(pow(Nat::r,i)))
    {
        i++;
    }
    i--;

    if (n < 0)
    {
        n = pow(Nat::r,i+1) - abs(n);
        isNegativ = true;
    }

    while (i >= 0)
    {
        vector->push_back(static_cast<uint32_t>(n / static_cast<int64_t>(pow(r,i))));
        n = static_cast<uint32_t>(n % static_cast<uint64_t>(pow(r,i)));
        i--;
    }
}

Nat::Nat(std::vector<uint32_t>* v, bool isNegativ) {
    delete(vector);
    vector = v;
    this->isNegativ = isNegativ;
}

Nat* Nat::neq()
{
    auto n = new Nat(static_cast<int32_t>(0));

    for (int i = 0; i < vector->size(); i++)
    {
        n->vector->push_back(Nat::r - vector->at(i));
    }

    n = *n + new Nat(1);

    n->isNegativ = !this->isNegativ;

    return n;
}

Nat* Nat::operator-(Nat* y)
{
    return *this + y->neq();
}

Nat* Nat::operator+(Nat* y)
{
    auto newVector = new std::vector<uint32_t>;

    auto v1 = this->vector;
    auto v2 = y->vector;

    auto maxLength = v1->size() > v2->size() ? v1->size() : v2->size();

    uint32_t carry = 0;
    auto v1value = 0;
    auto v2value = 0;
    for (uint32_t i = 1; i <= maxLength ; i++)
    {

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
    
    ret = new Nat(newVector,isNegativ);
   
    return ret;
}

Nat* Nat::faml(Nat* y, uint32_t k, uint32_t m)
{
    if (m <= 0)
        return this;

    Nat* newY = nullptr;
    if (m != 1)
    {
        newY = *y+y;
        for (auto i = 2; i < m; i++)
        {
            newY = *newY + y;
        }
    } else {
        newY = y->add(static_cast<int32_t>(0));
    }

    newY = *newY << k;

    return *this + newY;
}

Nat* Nat::multShort(Nat* y)
{
    auto ret = new Nat(static_cast<int32_t>(0));
    auto v = y->vector;

    for (int i = 0; i < v->size(); i++)
    {
        ret = ret->faml(this,v->size()-1-i,v->at(i));
    }

    return ret;
}

Nat* Nat::operator*(Nat* y)
{
    if (vector->size() <= Nat::kara && y->vector->size() <= Nat::kara)
    {
        return multShort(y);
    }

    auto n1 = new Nat(this);
    auto n2 = new Nat(y);
    auto v1 = n1->vector;
    auto v2 = n2->vector;

    while (v1->size() != v2->size())
    {
        if (v1->size() > v2->size())
        {
            v2->insert(v2->begin(),0);
        } else {
            v1->insert(v1->begin(),0);
        }
    }

    if (v1->size() % 2 != 0)
    {
        v1->insert(v1->begin(),0);
        v2->insert(v2->begin(),0);
    }

    auto ret = n1->multRec(n2);

    delete(n1);
    delete(n2);

    return ret;
}

Nat* Nat::multRec(Nat* y)
{
    if (vector->size() <= Nat::kara)
    {
        return multShort(y);
    }

    auto n = vector->size()/2;

    auto vl = this->low();
    auto vh = this->high();
    auto wl = y->low();
    auto wh = y->high();

    auto vhmwh = vh->multRec(wh);
    auto vhmwl = vh->multRec(wl);
    auto vlmwh = vl->multRec(wh);
    auto vlmwl = vl->multRec(wl);

    auto a1 = *vhmwh << 2*n;
    auto a2 = *vhmwl << n;
    auto a3 = *vlmwh << n;

    auto e1 = *a1 + a2;
    auto e2 = *e1 + a3;
    auto ret = *e2 + vlmwl;

    delete(vl);
    delete(vh);
    delete(wl);
    delete(wh);
    delete(vhmwh);
    delete(vhmwl);
    delete(vlmwh);
    delete(vlmwl);
    delete(a1);
    delete(a2);
    delete(a3);
    delete(e1);
    delete(e2);

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

    std::cout << ")_" << r << "\n";
}

Nat* Nat::shift(uint32_t n) {
    if (n == 0)
        return this;

    auto tmp = *this + this;
    for (uint32_t i = 1; i < n ; i++)
    {
        auto tmp2 = *tmp + tmp;
        delete(tmp);
        tmp = tmp2;
    }
    return tmp;
}

Nat* Nat::operator<<(uint32_t n)
{
    auto ret = new Nat(this);
    for (int i = 0; i < n; i++)
        ret->vector->push_back(0);

    return ret;
}

Nat* Nat::high()
{
    auto vec = new std::vector<uint32_t>;
    for (auto i = 0; i < (vector->size() / 2) ; i++)
        vec->push_back(vector->at(i));

    return new Nat(vec,isNegativ);
}

Nat* Nat::low()
{
    auto vec = new std::vector<uint32_t>;
    for (auto i = (vector->size() / 2); i < vector->size() ; i++)
        vec->push_back(vector->at(i));

    return new Nat(vec,isNegativ);
}

Nat *Nat::add(int32_t y) {
    auto tmp = new Nat(y);
    auto ret = *this+tmp;
    delete(tmp);
    return ret;
}

Nat::~Nat() {
    delete(vector);
}

int main(int argn, char *argv[]) {
    if (argn <= 2){
        std::cout << "Usage: nat.exe base (e.g 10). Using 4096 as a Base.\n";
    } else {
        Nat::r = strtoul(argv[1], nullptr, 0);
    }

    auto a = 1234567890;
    auto b = 1234567890;
    auto n1 = new Nat(strtoul(argv[2], nullptr, 0));
    auto n2 = new Nat(strtoul(argv[3], nullptr, 0));

    if (atoi(argv[4]) == 1)
        auto n3 = *n1 * n2;
    else   
        auto n3 = n1->multShort(n2);

    return 0;
}
