//
// Created by Георгий Ярдухин on 21.03.2020.
//

#ifndef RSA_KEYS_H
#define RSA_KEYS_H

#include "Key.h"

class Keys {
public:
    Keys(Key public_key, Key private_key) {
        this->public_key_ = public_key;
        this->private_key_ = private_key;
    }

    [[nodiscard]] Key GetPrivateKey() const { return private_key_;}

    [[nodiscard]] Key GetPublicKey() const { return public_key_;}

private:
    Key private_key_;
    Key public_key_;
};

#endif //RSA_KEYS_H
