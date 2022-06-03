#include <bits/stdc++.h>
#include "key.hpp"
#include "timer.hpp"


class Symbol
{
public:
    std::vector<Key> T;
    Symbol(const std::string &);
    void decrypt(const std::string &);
};
Symbol::Symbol(const std::string &filename)
{
    T.resize(N);
    std::string buffer;
    std::fstream input(filename.c_str());
    for (int i = 0; i < N; i++)
    {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
}

class key_hash
{
public:
    long operator()(const Key &x) const
    {
        long hash = 0;

        for (int i{N - 1}; i >= 0; i--)
        {
            hash = hash | x.bit(i) << i;
        }
        return hash;
    }
};

void Symbol::decrypt(const std::string &encrypted)
{

    std::unordered_map<Key, std::vector<Key>, key_hash> first_h_keys;
    std::vector<Key> temp_keys;
    Key encryp = Key(encrypted);
    Key counter;

    while (counter.m_digit[C / 2 - 1] == 0)
    {
        Key subset = counter.subset_sum(T);

        if (first_h_keys.count(subset) == 1)
        {
            first_h_keys[subset].push_back(counter);
        }
        else
        {
            std::vector<Key> temp = {counter};
            first_h_keys.insert(make_pair(subset, temp));
        }
        counter++;
    }

    Key max_first_half = counter;
    if (first_h_keys.count(encrypted) == 1)
    {
        for (unsigned int i = 0; i < first_h_keys[encrypted].size(); ++i)
        {
            std::cout << first_h_keys[encrypted][i] << std::endl;
        }
    }
    Key zero;

        while (counter != zero)
        {
            Key temp = encryp - counter.subset_sum(T);

            if (first_h_keys.count(temp) == 1)
            {
                for (unsigned int i = 0; i < first_h_keys[temp].size(); ++i)
                {
                    // std::cout << first_h_keys[temp].size() <<"\n";
                    std::cout << counter + first_h_keys[temp][i] << std::endl;
                }
            }
            counter = counter + max_first_half;
        }
}

int main()
{
    std::string encrypted;
    std::cin >> encrypted;

    TIMEUSE ti;
    ti.st();
    Symbol b(""gentb" + std::to_string(encrypted.size()) + ".txt"");

    b.decrypt(encrypted);
    ti.fi();
    std::cout << "\n";
    std::cout << ti.time_use();
    // a.show();
    return 0;
}
