//
// Created by Георгий Ярдухин on 02.03.2020.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

#include "Key.h"
#include <vector>


class RSA {
public:
    RSA(size_t size, size_t base);

    Key GenerateKeys();

    BigInteger EncodeMessage(const Key& public_key, std::string& message);

    std::string  DecodeMessage(const BigInteger& cipher);

private:

    std::vector<BigInteger> GetFirstNPrimeNumbers(int N);

    BigInteger Pow(const BigInteger& a, BigInteger pow, const BigInteger& mod);

    BigInteger GetNOD(BigInteger a, BigInteger b, BigInteger& x, BigInteger& y, BigInteger& mod);

    BigInteger CreateRandomValue(BigInteger fi);

    BigInteger GetInverseNumber(BigInteger& fi, BigInteger e);

    size_t size_;
    size_t  base_;
    Key private_key_;
};


#endif //RSA_RSA_H
