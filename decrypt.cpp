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
    std::string temp;
    std::fstream input(filename.c_str());
    for (int i = 0; i < N; i++)
    {
        std::getline(input, temp);
        T[i].set_string(temp);
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

    std::unordered_map<Key, std::vector<Key>, key_hash> ri_keys;
    std::vector<Key> temp_keys;
    Key encryp = Key(encrypted);
    Key counter;

    while (counter.m_digit[C / 2 - 1] == 0)
    {
        Key subset = counter.subset_sum(T);

        if (ri_keys.count(subset))
        {
            ri_keys[subset].push_back(counter);
        }
        else
        {
            std::vector<Key> temp = {counter};
            ri_keys.insert(make_pair(subset, temp));
        }
        counter++;
    }

    Key min_lf_keys = counter;
    if (ri_keys.count(encrypted))
    {
        for (unsigned int i = 0; i < ri_keys[encrypted].size(); ++i)
        {
            std::cout << ri_keys[encrypted][i] << std::endl;
        }
    }
    Key zero;

    while (counter != zero)
    {
        Key temp = encryp - counter.subset_sum(T);

        if (ri_keys.count(temp))
        {
            for (unsigned int i = 0; i < ri_keys[temp].size(); ++i)
            {
                std::cout << counter + ri_keys[temp][i] << std::endl;
            }
        }
        counter = counter + min_lf_keys;
    }
}

int main()
{
    std::string encrypted;
    std::cin >> encrypted;

    TIMEUSE ti;
    ti.st();
    Symbol b("gentb" + std::to_string(encrypted.size()) + ".txt");

    b.decrypt(encrypted);
    ti.fi();
    std::cout << "\n";
    std::cout << ti.time_use();
    // a.show();
    return 0;
}
