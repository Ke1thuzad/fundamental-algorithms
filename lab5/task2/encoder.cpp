#include "main.h"

encoder::encoder(std::vector<std::byte> &key) {
    this->encoding_key = key;
    this->s_block.resize(256);
}

encoder &encoder::KSA() {
    for (int i = 0; i < 256; ++i) {
        this->s_block[i] = static_cast<std::byte>(i);
    }

    int j = 0;

    for (int i = 0; i < 256; ++i) {
        j = (j + static_cast<unsigned char>(this->s_block[i]) +
             static_cast<unsigned char>(this->encoding_key[i % this->encoding_key.size()])) % 256;
        std::swap(this->s_block[i], this->s_block[j]);
    }

    return *this;
}

std::byte &encoder::PRGA(int i, int j) {
    std::swap(this->s_block[i], this->s_block[j]);

    int t = (static_cast<unsigned char>(this->s_block[i]) + static_cast<unsigned char>(this->s_block[j])) % 256;

    return this->s_block[t];
}

void encoder::change_key(std::vector<std::byte> &new_key) {
    this->encoding_key = new_key;
    this->s_block.clear();
}

int encoder::encode(const std::string &in_path, const std::string &out_path) {
    auto fullpath1 = std::filesystem::weakly_canonical(std::filesystem::absolute(in_path));
    auto fullpath2 = std::filesystem::weakly_canonical(std::filesystem::absolute(out_path));

    if (fullpath1 == fullpath2)
        return 1;

    std::ifstream in(in_path, std::ios::binary);
    if (!in.is_open())
        return 1;

    std::ofstream out(out_path, std::ios::binary);
    if (!out.is_open()) {
        in.close();
        return 1;
    }

    this->KSA();

    char ch;

    in.get(ch);

    int i = 0;
    int j = 0;

    while (!in.eof()) {
        i = (i + 1) % 256;
        j = (j + static_cast<unsigned char>(this->s_block[i])) % 256;

        std::byte outchar = static_cast<std::byte>(ch) ^ this->PRGA(i, j);

        out.put(static_cast<char>(outchar));

        in.get(ch);
    }

    in.close();
    out.close();

    return 0;
}
