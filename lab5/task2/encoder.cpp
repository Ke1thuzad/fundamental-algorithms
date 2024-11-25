#include "main.h"

encoder::encoder(std::vector<std::byte> &key) {
    this->encoding_key = key;
    this->s_block.resize(256);

    this->KSA();
}

void encoder::KSA() {
    for (int i = 0; i < 256; ++i) {
        this->s_block[i] = static_cast<std::byte>(i);
    }

    int j = 0;

    for (int i = 0; i < 256; ++i) {
        j = (j + static_cast<unsigned char>(this->s_block[i]) +
             static_cast<unsigned char>(this->encoding_key[i % this->encoding_key.size()])) % 256;
        std::swap(this->s_block[i], this->s_block[j]);
    }
}

std::byte encoder::PRGA(int i, int j) {
    std::swap(this->s_block[i], this->s_block[j]);

    int t = (static_cast<unsigned char>(this->s_block[i]) + static_cast<unsigned char>(this->s_block[j])) % 256;

    return this->s_block[t];
}

void encoder::change_key(std::vector<std::byte> &new_key) {
    this->encoding_key = new_key;
    this->s_block.clear();

    this->KSA();
}

int encoder::encode(const std::string &in_path, const std::string &out_path) {
//    if (std::filesystem::equivalent(in_path, out_path)) TODO
//        return 1;

    std::ifstream in(in_path, std::ios::binary);
    if (!in.is_open())
        return 1;

    std::ofstream out(out_path, std::ios::binary);
    if (!out.is_open()) {
        in.close();
        return 1;
    }

    char ch;

    in.get(ch);

    int i = 0;
    int j = 0;

    while (!in.eof()) {
        std::cout << static_cast<int>(ch) << '\n';
        i = (i + 1) % 256;
        j = (j + static_cast<unsigned char>(this->s_block[i])) % 256;

        char outchar = ch ^ static_cast<unsigned char>(this->PRGA(i, j));
        std::cout << " outchar: " << static_cast<int>(ch) << '\n';

        out.put(outchar);

        in.get(ch);
    }

    in.close();
    out.close();

    return 0;
}
