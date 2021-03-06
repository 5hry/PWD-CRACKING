
#include <bits/stdc++.h>
#include "key.hpp"

std::string password;


int main()
{
    int i;
    std::string temp;
    std::vector<Key> T(N); // the table T
    Key ssum;

    std::cin >> password;
    Key passkey((std::string(password)));

    std::fstream input("gentb" + std::to_string(password.size()) + ".txt");
    for (i = 0; i < N; i++)
    {
        std::getline(input, temp);
        T[i].set_string(temp);
    }
    input.close();

    ssum = passkey.subset_sum(T);
    ssum.show();

    return 0;
}
