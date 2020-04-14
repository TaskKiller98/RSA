//
// Created by Георгий Ярдухин on 02.03.2020.
//

#include "BigInteger.h"

#include <utility>


//TODO fix 0 to common case



BigInteger::BigInteger() {
    size_ = 1024;
    data_.reserve(size_);
    base_ = CHAR_MAX;
}

BigInteger::BigInteger(size_t size, int base) {
    size_ = size;
    data_.reserve(size);
    this->base_ = base;
}

BigInteger::BigInteger(size_t size, int base, const std::vector<int> &data) {
    size_ = size;
    data_.reserve(size);
    this->base_ = base;
    data_ = data;
}

BigInteger::BigInteger(size_t size, int base, char a) {
    size_ = size;
    data_.reserve(size);
    this->base_ = base;
    data_.push_back(a);
}


BigInteger::BigInteger(size_t size, int base, const std::string& data_str) {
    size_ = size;
    data_.reserve(size);
    this->base_ = base;
    for (char a : data_str) {
        data_.push_back(a - '0');
    }
    std::reverse(data_.begin(), data_.end());
}

bool BigInteger::operator==(BigInteger right) {
    if (right.GetSize() != data_.size()) {
        return false;
    }
    for (size_t i = 0; i < data_.size(); ++i) {
        if (data_[i] != right.GetNumByPos(i)) {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator>=(BigInteger right) {
    if (right.GetSize() > data_.size()) {
        return false;
    } else if (right.GetSize() < data_.size()) {
        return true;
    }
    for (int i = data_.size() - 1; i >= 0; --i) {
        if (data_[i] < right.GetNumByPos(i)) {
            return false;
        } else if (data_[i] > right.GetNumByPos(i)) {
            return true;
        }
    }
    return true;
}

std::string BigInteger::GetAsString() {
    std::string res;
    for (int i = data_.size() - 1; i >= 0; --i) {
        res += char(data_[i] + '0');
    }
    return res;
}


BigInteger BigInteger::operator+(BigInteger right) {
    int buff = 0;
    std::vector<int> res;
    if (right.GetSize() > GetSize()) {
        for (size_t i = 0; i < GetSize(); ++i) {
            res.push_back((data_[i] + right.GetNumByPos(i) + buff) % base_);
            buff = (data_[i] + right.GetNumByPos(i) + buff) / base_;
        }
        for (size_t i = GetSize(); i < right.GetSize(); ++i) {
            res.push_back((right.GetNumByPos(i) + buff) % base_);
            buff = (right.GetNumByPos(i) + buff) / base_;
        }
    } else {
        for (size_t i = 0; i < right.GetSize(); ++i) {
            res.push_back((data_[i] + right.GetNumByPos(i) + buff) % base_);
            buff = (data_[i] + right.GetNumByPos(i) + buff) / base_;
        }
        for (size_t i = right.GetSize(); i < GetSize(); ++i) {
            res.push_back((data_[i] + buff) % base_);
            buff = (data_[i] + buff) / base_;
        }
    }
    if (buff) {
        res.push_back(buff);
    }
    return BigInteger(size_, base_, res);
}



BigInteger BigInteger::operator-(BigInteger right) {
    if (right == *this){
        return BigInteger(size_, base_, ZERO);
    }
    if (right >= *this) {
        //return BigInteger(size_, base_, ZERO);
        throw std::invalid_argument("Illegal data");
    }
    int buff = 0;
    std::vector<int> res;
    for (size_t i = 0; i < right.GetSize(); ++i) {
        res.push_back((base_ + data_[i] - right.GetNumByPos(i) - buff) % base_);
        buff = 1 - (base_ + data_[i] - right.GetNumByPos(i) - buff) / base_;
    }
    for (size_t i = right.GetSize(); i < GetSize(); ++i) {
        res.push_back((base_ + data_[i] - buff) % base_);
        buff = 1 - (base_ + data_[i] - buff) / base_;
    }
    while (res[res.size() - 1] == 0) {
        res.pop_back();
    }
    return BigInteger(size_, base_, res);
}

BigInteger BigInteger::operator*(BigInteger right) {
    BigInteger res(size_, base_, ZERO);
    size_t ind = 0;
    std::vector<int> cur;
    for (size_t i = 0; i < GetSize(); ++i) {
        cur.clear();
        for (size_t j = 0; j < ind; ++j) {
            cur.push_back(0);
        }
        int buff = 0;
        for (size_t j = 0; j < right.GetSize(); ++j) {
            cur.push_back((data_[i] * right.GetNumByPos(j) + buff) % base_);
            buff = (data_[i] * right.GetNumByPos(j) + buff) / base_;
        }
        if (buff) {
            cur.push_back(buff);
        }
        res = res + BigInteger(size_, base_, cur);
        ind++;
    }
    return res;
}

BigInteger BigInteger::operator%(BigInteger right) {
    BigInteger mod(size_, base_, ZERO);
    BigInteger div(size_, base_, ZERO);
    DivMod(*this, std::move(right), div, mod);
    return mod;
}

BigInteger BigInteger::operator/(BigInteger right) {
    BigInteger mod(size_, base_, ZERO);
    BigInteger div(size_, base_, ZERO);
    DivMod(*this, std::move(right), div, mod);
    return div;
}

void BigInteger::AddToEnd(int number, bool is_new = false) {
    if (is_new) {
        data_.clear();
    }
    data_.insert(data_.begin(), number);
}

void BigInteger::DivMod(BigInteger a, BigInteger b, BigInteger &div, BigInteger &mod) {
    if (a == b){
        div = BigInteger(size_, base_, UNO);
        mod = BigInteger(size_, base_, ZERO);
        return;
    }
    if (b >= a) {
        div = BigInteger(size_, base_, ZERO);
        mod = a;
        return;
    }
    BigInteger uno(size_, base_, UNO);
    BigInteger zero(size_, base_, ZERO);
    int cnt = 0;
    bool flag = true;
    for (int i = a.GetSize() - 1; i >= 0; i--) {
        mod.AddToEnd(a.GetNumByPos(i), mod == zero);
        if (a.GetNumByPos(i) == 0) {
            cnt++;
        }
        if (mod >= b) {
            cnt = 0;
            BigInteger multi(size_, base_, UNO);
            while (mod >= b * multi) {
                multi = multi + uno;
            }
            multi = multi - uno;
            div.AddToEnd(multi.GetNumByPos(0), flag);
            flag = false;
            mod = mod - b * multi;
        } else if (!flag) {
            div.AddToEnd(0, flag);
        }
    }
//    for (int i = 0; i < cnt; ++i) {
//        div.AddToEnd(0, flag);
//    }
}

int BigInteger::GetAsInt() {
    int res = 0;
    for (int i = GetSize() - 1; i >= 0; i--) {
        res *= 10;
        res += data_[i];
    }
    return res;
}





