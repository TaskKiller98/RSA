//
// Created by Георгий Ярдухин on 02.03.2020.
//

#ifndef RSA_KEY_H
#define RSA_KEY_H


#include "BigInteger.h"

class Key {
public:
    Key();

    Key(BigInteger module_, BigInteger key_);

    [[nodiscard]] BigInteger GetModule() const { return module_;}

    [[nodiscard]] BigInteger GetKey() const { return key_;}

    std::string GetAsString();

private:
    BigInteger module_;
    BigInteger key_;
};


#endif //RSA_KEY_H
