//
// Created by Георгий Ярдухин on 02.03.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

#ifndef RSA_BIGINTEGER_H
#define RSA_BIGINTEGER_H

const char ZERO = '0' - '0';
const char UNO = '1' - '0';
const char TWO = '2' - '0';


//const char ZERO = '0';
//const char UNO = '1';
//const char TWO = '2';

class BigInteger {
public:
    BigInteger();

    BigInteger(size_t size, int base);

    BigInteger(size_t size, int base, const std::string& data);

    BigInteger(size_t size, int base, char a);

    BigInteger(size_t size, int base, const std::vector<int>& data);

    BigInteger operator*(BigInteger right);

    bool operator>=(BigInteger right);

    bool operator==(BigInteger right);

    BigInteger operator%(BigInteger right);

    BigInteger operator/(BigInteger right);

    BigInteger operator-(BigInteger right);

    BigInteger operator+(BigInteger right);

    std::string GetAsString();

    int GetAsInt();

    [[nodiscard]] int GetNumByPos(size_t pos) const { return data_[pos];}

    [[nodiscard]] size_t GetSize() const { return data_.size();}

    void AddToEnd(int number, bool is_new);

private:

    void DivMod(BigInteger a, BigInteger b, BigInteger &div, BigInteger& mod);

    std::vector<int> data_;
    int base_;
    size_t size_;
};


#endif //RSA_BIGINTEGER_H
