//
// Created by Георгий Ярдухин on 02.03.2020.
//

#include "RSA.h"

#include <utility>

RSA::RSA(size_t size, size_t base) {
    this->size_ = size;
    this->base_ = base;
}

Key RSA::GenerateKeys() {
//    BigInteger p = prime[N - 1];
//    BigInteger q = prime[N - 4];
    BigInteger p = BigInteger(size_, base_, "170141183460469231731687303715884105727");
    BigInteger q = BigInteger(size_, base_, "524287");
    BigInteger uno(size_, base_, UNO);
    BigInteger n = p * q;
    BigInteger fi = p - uno;
    fi = fi * (q - uno);
    BigInteger e = CreateRandomValue(fi);
    private_key_ = Key(n, GetInverseNumber(fi, e));
    return Key(n, e);
}

BigInteger RSA::EncodeMessage(const Key& public_key, std::string& message) {
    BigInteger big_msg(size_, base_, message);
    return Pow(big_msg, public_key.GetKey(), public_key.GetModule());
}

std::string RSA::DecodeMessage(const BigInteger& cipher) {
    return Pow(cipher, private_key_.GetKey(), private_key_.GetModule()).GetAsString();
}


BigInteger RSA::CreateRandomValue(BigInteger fi) {
    std::vector<BigInteger> prime = GetFirstNPrimeNumbers(1000);
    int n = prime.size();
    int ind;
    BigInteger check, zero(size_, base_, ZERO);
    do {
        ind = rand() % n;
        check = prime[ind];
    } while (check >= fi || fi % check == zero);
    return check;
}
//TODO
BigInteger RSA::GetInverseNumber(BigInteger& fi, BigInteger e) {
    BigInteger x, y;
    GetNOD (std::move(e), fi, x, y, fi);
    return (x % fi + fi) % fi;
}

//std::vector<> RSA::GetFirstNPrimeNumbers(int N) {
//    std::vector<int> lp(N+1, 0);
//    std::vector<int> pr;
//
//    for (int i=2; i<=N; ++i) {
//        if (lp[i] == 0) {
//            lp[i] = i;
//            pr.push_back (i);
//        }
//        for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=N; ++j)
//            lp[i * pr[j]] = pr[j];
//    }
//    return pr;
//}

BigInteger RSA::GetNOD(BigInteger a, BigInteger b, BigInteger &x, BigInteger &y, BigInteger& mod) {
    BigInteger zero(size_, base_, ZERO);
    BigInteger uno(size_, base_, UNO);
    if (a == zero) {
        x = zero; y = uno;
        return b;
    }
    BigInteger x1, y1;
    BigInteger d = GetNOD (b%a, a, x1, y1, mod);
    x = (y1 + mod) - ((b / a) * x1) % mod;
    y = x1;
    return d;
}

BigInteger RSA::Pow(const BigInteger& a, BigInteger pow, const BigInteger& mod) {
    if (pow == BigInteger(size_, base_, ZERO))
        return BigInteger(size_, base_, UNO);
    if (pow % BigInteger(size_, base_, TWO) == BigInteger(size_, base_, UNO))
        return (Pow(a, pow - BigInteger(size_, base_, UNO), mod) * a) % mod;
    else {
        BigInteger b = Pow(a, pow / BigInteger(size_, base_, TWO), mod);
        return (b * b) % mod;
    }
}

std::vector<BigInteger> RSA::GetFirstNPrimeNumbers(int N) {
    BigInteger zero(size_, base_, ZERO);
    BigInteger uno(size_, base_, UNO);
    BigInteger n(size_, base_, std::to_string(N));
    // BigInteger uno(size_, base_, UNO);
    std::vector<BigInteger> lp(N+1, zero);
    std::vector<BigInteger> pr;
    BigInteger ind(size_, base_, TWO);
    while (N >= (ind).GetAsInt()) {
        int i = ind.GetAsInt();
        if (lp[i] == zero) {
            lp[i] = ind;
            pr.push_back (ind);
        }
        for (int j=0; j<(int)pr.size() && lp[i] >= pr[j] && N >= (ind * pr[j]).GetAsInt(); ++j) {
            int e = (ind * pr[j]).GetAsInt();
            lp[e] = pr[j];
        }
        ind = ind + uno;
    }
    return pr;
}
