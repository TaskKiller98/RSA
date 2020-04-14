#include <iostream>
#include <functional>
#include "Key.h"
#include "RSA.h"
#include <map>

int gcd (int a, int b, int & x, int & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd (b%a, a, x1, y1);
    x = y1 + 221 - (b / a) * x1 % 221;
    std::cout << x << "\n";
    y = x1;
    return d;
}

void test() {
//    using namespace std;
//    BigInteger a(1024, 9, "15");
//    BigInteger b(1024, 9, "3");
//    int x = 0;
//    int y = 0;
//    //int d = gcd(61, 221, x, y);
//    cout << (a % b).GetAsString();
}



int main() {
    test();
    std::cout << "Hello, please input a message" << std::endl;
    std::string message;
    std::getline(std::cin,message);
    std::hash<std::string> hash_fn;
    size_t str_hash = hash_fn(message);
    std::map<std::string, std::string> mp;
    std::string new_msg = std::to_string(str_hash);
    mp[new_msg] = message;
    std::cout << "message hash = " << new_msg << std::endl;
    RSA rsa_A(1024, 10);
    RSA rsa_B(1024, 10);
    Key public_key = rsa_A.GenerateKeys();
    std::cout << "Alisa public key is\n" << public_key.GetAsString() << std::endl;
    BigInteger cipher = rsa_B.EncodeMessage(public_key, new_msg);
    std::cout << "Cipher is " << cipher.GetAsString() << std::endl;
    std::cout << "Bob recive " << mp[rsa_A.DecodeMessage(cipher)] << std::endl;
    return 0;
}