//
// Created by Георгий Ярдухин on 02.03.2020.
//

#include "Key.h"

Key::Key() {
    this->module_ = this->key_ = BigInteger();
}

Key::Key(BigInteger module, BigInteger key) {
    this->key_ = key;
    this->module_ = module;
}

std::string Key::GetAsString() {
    return "Key is " + key_.GetAsString() + "\nModule is " + module_.GetAsString();
}
