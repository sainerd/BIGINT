
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cctype> // isdigit function prototype
#include <cstring> // strlen function prototype
#include <iomanip>
using namespace std;
class TeamWorkBigInt
{
    friend ostream& operator<<(ostream&, const TeamWorkBigInt&);
public:
    static const int digits =30;
    
    TeamWorkBigInt(int = 0); // conversion/default constructor
    TeamWorkBigInt(const char*); // conversion constructor
    TeamWorkBigInt recopy(int first, int last)const;
    void move(int step);

    bool whethernegetive(const TeamWorkBigInt&)const;
    TeamWorkBigInt normalsub(const TeamWorkBigInt&)const;
    TeamWorkBigInt operator+(const TeamWorkBigInt&) const;
    TeamWorkBigInt div(const TeamWorkBigInt&) const;
    TeamWorkBigInt operator-(const TeamWorkBigInt&) const;
    TeamWorkBigInt operator-(int) const;
    TeamWorkBigInt operator+(int) const;
    TeamWorkBigInt operator+(const char*) const;
    TeamWorkBigInt operator-(const char*) const;
    int getLength() const;
    int getdigits() const;
    bool operator>(const TeamWorkBigInt&) const;
    bool operator>=(const TeamWorkBigInt&) const;
    bool operator<=(const TeamWorkBigInt&) const;
    bool operator<(const TeamWorkBigInt&) const;
    bool operator==(const TeamWorkBigInt&) const;
    bool operator!=(const TeamWorkBigInt&) const;
    TeamWorkBigInt operator*(const TeamWorkBigInt&) const;
    TeamWorkBigInt operator/(const TeamWorkBigInt&) const;
    TeamWorkBigInt normaldiv(const TeamWorkBigInt&) const;
    TeamWorkBigInt& operator/=(const TeamWorkBigInt&) const;
    TeamWorkBigInt& operator+=(const TeamWorkBigInt&) const;
    TeamWorkBigInt operator*(int) const;
    TeamWorkBigInt operator/(int) const;
    TeamWorkBigInt& operator/=(int) const;
    TeamWorkBigInt& operator+=(int) const;
    friend TeamWorkBigInt pow(const TeamWorkBigInt&, int times);
private:
    short integer[digits] = {0};
    int length = 0;
    int dig = 0;
}; // end class HugeInt

void TeamWorkBigInt::move(int step) {
    if (length == 0) {
        
    }else{
        for (int i = 0; i < step; i++) {
            for (int j = 0; j < dig; j++) {
                integer[digits - dig - 1 + j - i] = integer[digits - dig + j - i];

            }
            integer[digits - i - 1] = 0;

        }
        length = getLength();
        dig = getdigits();
    }
    
};

TeamWorkBigInt TeamWorkBigInt::recopy(int first, int last)const {
    TeamWorkBigInt temp(0);
    temp.dig = last - first;
    int i = 0;

    while (i <temp.dig) {
        temp.integer[digits - temp.dig + i] = integer[digits - dig + i + first - 1];
        i++;
    }
    temp.length = temp.getLength();
    temp.dig = temp.getdigits();
    return temp;
};
TeamWorkBigInt TeamWorkBigInt::operator*(int t) const {
    TeamWorkBigInt temp(t);
    temp = *this * temp;
    return temp;
    temp.length = temp.getLength();
    temp.dig = temp.getdigits();
}
TeamWorkBigInt TeamWorkBigInt::operator/(int t) const {
    TeamWorkBigInt temp(t);
    temp = *this / temp;
    return temp;
}
TeamWorkBigInt& TeamWorkBigInt::operator/=(int t) const {
    TeamWorkBigInt temp(t);
    temp = *this / temp;
    return temp;
}
TeamWorkBigInt& TeamWorkBigInt::operator+=(int t) const {
    TeamWorkBigInt temp(t);
    temp = temp + *this;
    return temp;
}
TeamWorkBigInt TeamWorkBigInt::operator *(const TeamWorkBigInt& num) const {
    TeamWorkBigInt ticker(1);
    TeamWorkBigInt temp(0);
    TeamWorkBigInt plus(1);
    while (ticker <= num) {
        temp = temp + *this;
        ticker = ticker + plus;

    }
    return temp;
}
TeamWorkBigInt TeamWorkBigInt::div(const TeamWorkBigInt&num) const {
    int i = 1;
    TeamWorkBigInt last(0);
    TeamWorkBigInt temp(0);
    TeamWorkBigInt copy(0);
    TeamWorkBigInt lastcopy = 0;
    while (i <= dig - num.dig + 1) {
        copy = recopy(i, i + num.dig) + lastcopy;
        last = copy.normaldiv(num);
        lastcopy = copy - last * num;
        lastcopy.move(1);
        last.move(dig - num.dig - i + 1);
        temp = temp + last;
        i++;
    }
    return temp;
};
TeamWorkBigInt TeamWorkBigInt::operator/(const TeamWorkBigInt& num) const {
    if (integer[digits - dig] * num.integer[digits - num.dig] < 0) {
        if (integer[digits - dig] < 0) {
            TeamWorkBigInt temp = *this;
            temp.integer[temp.digits - temp.dig] = -temp.integer[temp.digits - temp.dig];
            temp = temp.div(num);
            temp.integer[temp.digits - temp.dig] = -temp.integer[temp.digits - temp.dig];
            return temp;
        }
        else if (num.integer[digits - num.dig] < 0) {
            TeamWorkBigInt temp = num;
            temp.integer[temp.digits - temp.dig] = -temp.integer[temp.digits - temp.dig];
            temp = div(temp);
            temp.integer[temp.digits - temp.dig] = -temp.integer[temp.digits - temp.dig];
            return temp;
        }
    }

    else {
        if (integer[digits - dig] < 0) {
            TeamWorkBigInt temp = *this;
            temp.integer[temp.digits - temp.dig] = -temp.integer[temp.digits - temp.dig];
            TeamWorkBigInt temp2 = num;
            temp2.integer[temp2.digits - temp2.dig] = -temp2.integer[temp2.digits - temp2.dig];
            temp = temp.div(temp2);
            return temp;
        }
        return div(num);
    }
    


}

TeamWorkBigInt TeamWorkBigInt::normaldiv(const TeamWorkBigInt& num) const {

    TeamWorkBigInt ticker(0);
    TeamWorkBigInt temp(*this);
    TeamWorkBigInt plus(1);

    while (temp >= num) {
        temp = temp - num;
        ticker = ticker + plus;
    }
    ticker.length = ticker.getLength();
    ticker.dig = ticker.getdigits();
    return ticker;
}
TeamWorkBigInt& TeamWorkBigInt::operator/=(const TeamWorkBigInt& num) const {
    TeamWorkBigInt temp = *this / num;
    return temp;
}
TeamWorkBigInt& TeamWorkBigInt::operator+=(const TeamWorkBigInt& num) const {
    TeamWorkBigInt temp = *this + num;
    return temp;
}
bool TeamWorkBigInt::operator>(const TeamWorkBigInt& num) const {
    TeamWorkBigInt temp("0");
    temp = *this - num;
    if (temp.integer[digits - dig] > 0) {
        return 1;
    }
    else {
        return 0;
    }
}
bool TeamWorkBigInt::operator<=(const TeamWorkBigInt& num) const {
    return !(num.whethernegetive(*this));
}
bool TeamWorkBigInt::operator<(const TeamWorkBigInt& num) const {
    TeamWorkBigInt temp(0);
    temp = num - *this;
    if (temp.integer[digits - dig] > 0) {
        return 1;
    }
    else {
        return 0;
    }
}
bool TeamWorkBigInt::operator>=(const TeamWorkBigInt& num) const {
    return !(whethernegetive(num));
}
bool TeamWorkBigInt::operator==(const TeamWorkBigInt& num) const {
    TeamWorkBigInt temp(0);
    temp = num - *this;
    if (temp.integer[digits - dig] == 0) {
        return 1;
    }
    else {
        return 0;
    }
}
bool TeamWorkBigInt::operator!=(const TeamWorkBigInt& num) const {
    return !(*this == num);
}
int TeamWorkBigInt::getdigits() const {
    int digg = 0;
    if (length % 4 == 0) {
        digg = length / 4;//如果n是4的整数则dig=n/4
    }
    else {
        digg = length / 4 + 1;//如果n不是4的整数则整除加一
    }
    return digg;
};
int TeamWorkBigInt::getLength() const {
    int i = 0;
    while (integer[i] == 0) {
        i++;
    }
    int len = 0;
    if (i != digits) {
        
   
        len = (int)log10(abs(integer[i]))+1 + 4 * (digits-i-1);
    }
    
    return len;
};
TeamWorkBigInt::TeamWorkBigInt(int t) {
    
    if (t == 0) {
        length = 1;
        dig = 1;
    }else{
        length = (int)log10(abs(t)) + 1;//获取t的位数n


        if (length % 4 == 0) {
            dig = length / 4;//如果n是4的整数则dig=n/4
        }
        else {
            dig = length / 4 + 1;//如果n不是4的整数则整除加一
        }

        integer[digits - dig] = abs(t) / std::pow(10, 4 * (dig - 1));
        long last = abs(t);
        for (int i = 1; i < dig; i++) {
            last = last - integer[(digits - dig + i - 1)] * std::pow(10, 4 * (dig - i));
            integer[digits - dig + i] = last / std::pow(10, 4 * (dig - i - 1));
        }
        
    }
    if (t < 0) {
        integer[digits - dig] = -integer[digits - dig];
    }
       

}
TeamWorkBigInt::TeamWorkBigInt(const char* str) {

    length = strlen(str);
    if (length % 4 == 0) {
        dig = length / 4;//如果n是4的整数则dig=n/4
    }
    else {
        dig = length / 4 + 1;//如果n不是4的整数则整除加一
    }
    if (dig == 1) {
        integer[digits-1] = atoi(str);
    }
    if (dig > 1)
    {
        int start = length - 4 * (dig - 1);
        char str1[5] = { 0 };
        str1[start] = '\0';
        memcpy(str1, str, start);
        const char* p{ str1 };
        integer[digits- dig] = atoi(p);


        for (int i = 1; i < dig; i++) {
            char stri[5] = { 0 };
            stri[4] = '\0';
            memcpy(stri, str + start + 4 * (i - 1), 4);

            const char* p{ stri };
            integer[digits-dig+i] = atoi(p);

        }
    }
};
TeamWorkBigInt TeamWorkBigInt::operator-(const TeamWorkBigInt& num) const {
    TeamWorkBigInt temp;
    if (num.integer[digits- num.dig] < 0) {
        temp = num;
        temp.integer[digits - temp.dig] = -temp.integer[digits - temp.dig];
        temp = temp + *this;

        return temp;
    }
    if (whethernegetive(num) == 1) {
        temp = num.normalsub(*this);
        temp.integer[digits - dig] = -temp.integer[digits - dig];
        return temp;
    }
    else {
        return normalsub(num);
    }
};
bool TeamWorkBigInt::whethernegetive(const TeamWorkBigInt& num)const {
    int i = 1;
    int lastovermax = 0;
    if (length < num.length) {
        return 1;
    }
    while ((dig - i) >=-1 || (num.dig - i) >=-1) {
        int tempnum = integer[digits-i] - num.integer[digits - i] + lastovermax;
        int overmax = 0;
        if (tempnum >= 0)
        {
            overmax = 0;
        }
        else {
            overmax = -1;
            tempnum = tempnum + 10000;
        }
        lastovermax = overmax;
        i++;
    }
    
    if (lastovermax == -1) {
        return 1;
    }
    else return 0;
};
TeamWorkBigInt TeamWorkBigInt::normalsub(const TeamWorkBigInt& num)const {
    TeamWorkBigInt temp;
    int i = 1;
    int lastovermax = 0;
    while ((dig - i) >= -1 || (num.dig - i) >=-1) {
        int tempnum = integer[digits - i] - num.integer[digits - i] + lastovermax;
        int overmax = 0;
        if (tempnum >= 0)
        {
            overmax = 0;
        }
        else {
            overmax = -1;
            tempnum = tempnum + 10000;
        }

        temp.integer[digits - i] = tempnum;
        lastovermax = overmax;
        i++;
    }
    temp.length = temp.getLength();
    temp.dig = temp.getdigits();
    return temp;
};
TeamWorkBigInt TeamWorkBigInt::operator+(const TeamWorkBigInt& num) const {
    TeamWorkBigInt temp;
    if (num.integer[digits - num.dig] < 0) {
        temp = num;
        temp.integer[digits - temp.dig] = -temp.integer[digits - temp.dig];
        temp = *this - temp;

        return temp;
    }
    int i = 1;
    int lastovermax = 0;
    while ((dig - i) >=-1 || (num.dig - i) >= -1) {
        int tempnum = integer[digits - i] + num.integer[digits - i] + lastovermax;
        int overmax = 0;

        if (tempnum <= 9999)
        {
            overmax = 0;
        }
        else {
            overmax = 1;
            tempnum = tempnum - 10000;
        }

        temp.integer[digits-i] = tempnum ;
        lastovermax = overmax;
        i++;
    }
    temp.length = temp.getLength();
    temp.dig = temp.getdigits();
    return temp;
};
TeamWorkBigInt pow(const TeamWorkBigInt& num, int times) {
    TeamWorkBigInt temp(num);
    for (int i = 1; i < times; i++) {
        temp = temp * num;
    }
    return temp;
};

ostream& operator<<(ostream& out, const TeamWorkBigInt& t) {
    
    for (int j = 0; j < t.dig; j++) {
        
            if (j ==0) {
                out << t.integer[t.digits - t.dig + j];
            }else{
                out << setfill('0') << setw(4) << t.integer[t.digits - t.dig + j];
            }
            
    }
    return out;

};
TeamWorkBigInt TeamWorkBigInt::operator+(int t) const {
    TeamWorkBigInt temp(t);
    temp = temp + *this;
    return temp;

};
TeamWorkBigInt TeamWorkBigInt::operator+(const char* t) const {
    TeamWorkBigInt temp(t);
    temp = temp + *this;
    return temp;
}
TeamWorkBigInt TeamWorkBigInt::operator-(int t) const {
    TeamWorkBigInt temp(t);
    temp = *this - temp;
    return temp;

};
TeamWorkBigInt TeamWorkBigInt::operator-(const char* t) const {
    TeamWorkBigInt temp(t);
    temp = *this - temp;
    return temp;
}



//StudybarCommentBegin
int main()
{
    int i, N;
    TeamWorkBigInt  n = 10, b, x1, x2, s, t, pi,k;

    cin >> N;
    N--;
    b = pow(n, N + 10);

    x1 = b * 4;
    x1=x1/ 5;
    x2 = b / -239;
    s = x1 + x2;

    for (i = 3; i <= N * 2; i += 2)
    {
        x1 /= -25;
        x2 /= -57121;
        t = (x1 + x2) / i;
        s += t;
    }
    pi = s * 4;
    k= pow(n, 10);
    cout << pi<<endl;
    cout << k;
    cout << (pi / k) << endl;
    return 0;
}
//StudybarCommentEnd


