#ifndef KEY_HPP
#define KEY_HPP
#include <bits/stdc++.h>

static constexpr int B = 5;  
static constexpr int R = 32; 


static constexpr int C = 10;
static constexpr int N = 50;

#define ALPHABET "abcdefghijklmnopqrstuvwxyz012345"
typedef std::array<char, C> word_type;

static word_type to_string(const std::string &s)
{
    word_type w;
    int j;
    for (int i = 0; i < C; ++i)
    {
        for (j = 0; j < R; ++j)
        {
            if (s[i] == ALPHABET[j])
            {
                w[i] = j;
                break;
            }
        }
    }
    return w;
}

class Key
{

public:
    word_type m_digit;

    Key();

    Key(const std::string &);

    Key(const word_type &);

    int bit(int) const;

    Key &operator=(const Key &);
    Key &operator+=(const Key &);

    bool operator==(const Key &) const;
    bool operator<(const Key &) const;

    void show() const;

    void set_string(const std::string &);

    Key subset_sum(const std::vector<Key> &);
};

int Key::bit(int i) const
{
    return (m_digit[i / B] >> (B - 1 - i % B)) & 1;
}

Key::Key()
{
    std::fill(m_digit.begin(), m_digit.end(), 0);
}

Key::Key(const std::string &s)
{
    m_digit=to_string(s);
}

Key::Key(const word_type &w) : m_digit(w) {}

Key &Key::operator=(const Key &other)
{
    std::copy(other.m_digit.begin(), other.m_digit.end(), m_digit.begin());
    return *this;
}

void Key::set_string(const std::string &s)
{
    m_digit = to_string(s);
}

bool Key::operator==(const Key &other) const
{
    return m_digit == other.m_digit;
}

bool Key::operator<(const Key &other) const
{
    return m_digit < other.m_digit;
}

Key &Key::operator+=(const Key &other)
{
    int t;
    int carry = 0;
    for (int i = C - 1; i >= 0; --i)
    {
        t = m_digit[i];
        m_digit[i] = (t + other.m_digit[i] + carry) % R;
        carry = (t + other.m_digit[i] + carry) >= R;
    }
    return *this;
}

bool operator!=(const Key &k1, const Key &k2)
{
    return !(k1 == k2);
}

Key operator+(const Key &lhs, const Key &rhs)
{
    Key c;
    int carry = 0;
    for (int i{C - 1}; i >= 0; --i)
    {
        c.m_digit[i] = (lhs.m_digit[i] + rhs.m_digit[i] + carry) % R;
        carry = (lhs.m_digit[i] + rhs.m_digit[i] + carry) >= R;
    }
    return c;
}

Key &operator++(Key &k)
{
    int i{C - 1};
    unsigned char one{1};
    unsigned char dig{0};
    int carry;
    dig = (k.m_digit[i] + one) % R;
    carry = (k.m_digit[i] + one) >= R;
    k.m_digit[i] = dig;
    for (i = C - 2; i >= 0; --i)
    {
        if (!carry)
            break;
        dig = (k.m_digit[i] + carry) % R;
        carry = (k.m_digit[i] + carry) >= R;
        k.m_digit[i] = dig;
    }
    return k;
}

Key operator++(Key &k, int)
{
    Key temp = k;
    ++k;
    return temp;
}

Key operator-(const Key &lhs, const Key &rhs)
{
    Key c;
    int carry = 0;

    for (int i{C - 1}; i >= 0; --i)
    {
        c.m_digit[i] = (lhs.m_digit[i] - rhs.m_digit[i] + carry) % R;
        // std::cout << c.m_digit[i] <<std::endl;
        if ((lhs.m_digit[i] - rhs.m_digit[i] + carry) < 0)
        {
            carry = -1;
            c.m_digit[i] += R;
        }
        else
            carry = 0;
    }

    return c;
}

Key Key::subset_sum(const std::vector<Key> &T)
{
    Key sum;
    for (int i = 0; i < N; ++i)
    {
        if (bit(i))
        {
            sum += T[i];
        }
    }
    return sum;
}

std::ostream &operator<<(std::ostream &os, const Key &k)
{
    for (auto i : k.m_digit)
        os << ALPHABET[i];
    // os << "  ";
    // for (int i : k.m_digit)
    //    os << setw(2) << i << " ";
    // os << "  ";
    // for (int i{0}; i < N; i++)
    //    os << k.bit(i);

    return os;
}

void Key::show() const
{
    std::for_each(m_digit.begin(), m_digit.end(), [](const char &c)
                  { std::cout << ALPHABET[c]; });
    std::cout << "  ";
    std::for_each(m_digit.begin(), m_digit.end(), [](const char &c)
                  { std::cout << std::setw(2) << static_cast<int>(c) << ' '; });
    std::cout << "  ";
    // for (int i = 0; i < N; ++i)
    // {
    //     // std::cout << bit(i) << std::flush;
    // }
    std::cout << '\n';
}

#endif
