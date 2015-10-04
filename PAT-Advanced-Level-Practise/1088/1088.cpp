#include <iostream>
#include <string>
//#include <cassert>
#include <cmath>
#include <limits>

using namespace std;

long int calculate_gcd(long int a, long int b)
{
    // assert(a > 0 && b > 0);
    long int big;
    long int small;
    if(a > b) { big = a; small = b;}
    else if(a < b) { big = b; small = a;}
    else return a;
    while(big % small != 0) 
    { 
        long remainder = big % small; 
        big = small;
        small = remainder;
    }
    return small;
}

struct Rational;

struct SimpleRational
{
    // 假分数形式
    // integer == numeric_limits<long int>::max() 表示无穷大
    // integer == 0 && numerator == 0 表示0 （denominator必为0）

    long int integer;
    long int numerator;
    long int denominator;

    SimpleRational() 
    {
        this->integer = 0;
        this->numerator = 0;
        this->denominator = 0;
    };
    SimpleRational(long int numerator, long int denominator) 
    {
        // if(numerator != 0 && denominator != 0) assert(calculate_gcd(abs(numerator), abs(denominator)) == 1);   //互质
        // assert(denominator >= 0);
        if(numerator == 0)
        {
            this->integer = 0;
            this->numerator = 0;
            this->denominator = 0;
        }
        else if(denominator == 0)
        {
            this->integer = numeric_limits<long int>::max();    // Inf
            this->numerator = 0;
            this->denominator = 0;
        }
        else if(numerator / denominator == 0)
        {
            this->integer = 0;
            this->numerator = numerator;
            this->denominator = denominator;
        }
        else
        {
            this->integer = numerator / denominator;
            this->numerator = abs(numerator) % abs(denominator);
            
            if(this->numerator == 0)
            {
                this->denominator = 0;
                // assert(abs(denominator) == 1);
            }
            else
                this->denominator = abs(denominator);
        }
    };
};

struct Rational
{
    // numerator == 0 表示0 （denominator必为0）
    // numerator != 0 && denominator == 0 表示无穷大
    // 其余情况 numerator与denominator互质
    long int numerator;
    long int denominator;
    SimpleRational simple_rational;
    Rational():numerator(0), denominator(0) {}
    Rational(long int numerator, long int denominator)
    {
        if(numerator == 0)
        {
            this->numerator = 0;
            this->denominator = 0;
        }
        else if(denominator == 0)
        {
            this->numerator = numerator;
            this->denominator = 0;
        }
        else
        {
            long int gcd = calculate_gcd(abs(numerator), abs(denominator));
            this->numerator = numerator / gcd;
            this->denominator = denominator / gcd;
            if(this->denominator < 0)
            {
                this->numerator = -this->numerator;
                this->denominator = -this->denominator;
            }
        }
        simple_rational = SimpleRational(this->numerator, this->denominator);
    }
    
};

istream& operator >> (istream& in, Rational &rational)
{
    string number_str;
    in >> number_str;
    if(in)
    {
        string::size_type slash_postion = number_str.find_first_of('/');
        long int numerator = atol(number_str.substr(0, slash_postion).c_str());
        long int denominator = atol(number_str.substr(slash_postion + 1, number_str.length() - 1).c_str());
        rational = Rational(numerator, denominator);
    }
    else rational = Rational();
    return in;
}

ostream& operator << (ostream& out, const SimpleRational &simple_rational)
{
    bool is_negative = simple_rational.integer < 0 || (simple_rational.integer == 0 && simple_rational.numerator < 0);
    if(is_negative) out << "(";
    if(simple_rational.numerator == 0)
    {
        // assert(simple_rational.denominator == 0);
        if(simple_rational.integer == numeric_limits<long int>::max())
            out << "Inf";
        else
            out << simple_rational.integer;
    }
    else
    {
        if(simple_rational.integer != 0)
            out << simple_rational.integer << " ";
        out << simple_rational.numerator << "/" << simple_rational.denominator;
    }
    if(is_negative) out << ")";
    return out;
}

Rational operator + (const Rational &a, const Rational &b)
{
    if(a.numerator == 0)
        return b;
    else if(b.numerator == 0)
        return a;
    long int numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    long int denominator = a.denominator * b.denominator;
    return Rational(numerator, denominator);
}
Rational operator * (const Rational &a, const Rational &b);

Rational operator - (const Rational &a, const Rational &b)
{
    if(a.numerator == 0)
        return b * Rational(-1, 1);
    else if(b.numerator == 0)
        return a;
    long int numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    long int denominator = a.denominator * b.denominator;
    return Rational(numerator, denominator);
}

Rational operator * (const Rational &a, const Rational &b)
{
    long int numerator = a.numerator * b.numerator;
    long int denominator = a.denominator * b.denominator;
    return Rational(numerator, denominator);
}

Rational operator / (const Rational &a, const Rational &b)
{
    if(b.numerator == 0)
        return Rational(1, 0);
    long int numerator = a.numerator * b.denominator;
    long int denominator = a.denominator * b.numerator;
    return Rational(numerator, denominator);
}

int main()
{
    Rational num1, num2;
    cin >> num1 >> num2;
    cout << num1.simple_rational << " + " << num2.simple_rational << " = " << (num1 + num2).simple_rational << endl;
    cout << num1.simple_rational << " - " << num2.simple_rational << " = "  << (num1 - num2).simple_rational << endl;
    cout << num1.simple_rational << " * " << num2.simple_rational << " = "  << (num1 * num2).simple_rational << endl;
    cout << num1.simple_rational << " / " << num2.simple_rational << " = "  << (num1 / num2).simple_rational << endl;
    return 0;
}