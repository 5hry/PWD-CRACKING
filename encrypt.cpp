
#include <bits/stdc++.h>
#include "key.hpp"

std::string password;


int main()
{
    int i;
    std::string buffer;
    std::vector<Key> T(N); // the table key T
    Key ssum;

    std::cin >> password;
    Key passkey((std::string(password)));

    std::fstream input("input.txt");
    for (i = 0; i < N; i++)
    {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();

    ssum = passkey.subset_sum(T);
    ssum.show();

    return 0;
}
