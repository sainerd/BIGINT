
#include <algorithm>
#include <cmath>
using namespace std;




#include <iostream>
#include <cctype> // isdigit function prototype
#include <cstring> // strlen function prototype
using namespace std;

class HugeInt
{
    friend ostream& operator<<(ostream&, const HugeInt&);
public:
    static const int digits = 30;
    HugeInt(long = 0); // conversion/default constructor
    HugeInt(const char*); // conversion constructor
    bool negetive(const HugeInt&)const;
    HugeInt normalsub(const HugeInt&)const;

    // addition operator; HugeInt + HugeInt
    HugeInt operator+(const HugeInt&) const;
    HugeInt operator-(const HugeInt&) const;
    HugeInt operator>(const HugeInt&) const;
    HugeInt operator>=(const HugeInt&) const;
    HugeInt operator<=(const HugeInt&) const;
    HugeInt operator==(const HugeInt&) const;
    HugeInt operator!=(const HugeInt&) const;
    
    // addition operator; HugeInt + int
    HugeInt operator+(int) const;
    
    // addition operator;
    // HugeInt + string that represents large integer value
    HugeInt operator-(int) const;
    HugeInt operator+(const char*) const;
    HugeInt operator-(const char*) const;
    int getLength() const;
private:
    short integer[digits];
}; // end class HugeInt


HugeInt::HugeInt(long t) {
    if (t == 0) {
        integer[0] = 0;
        integer[1] = -1;

    }else{
        
        int n = (int)log10(abs(t)) + 1;//获取t的位数n
        int dig = 0;//初始化变量dig（节数）
        
        if (n % 4 == 0) {
            dig = n / 4;//如果n是4的整数则dig=n/4
        }
        else {
            dig = n / 4 + 1;//如果n不是4的整数则整除加一
        }
        if (dig > 1) {
            integer[0] = abs(t) / std::pow(10, 4 * (dig - 1));
            long last = abs(t);
            for (int i = 1; i < dig; i++) {

                last = last - integer[(i - 1)] * std::pow(10, 4 * (dig - i));
                integer[i] = last / std::pow(10, 4 * (dig - i - 1));
            }
        }
        if (dig == 1) {
            integer[0] = t;
        }
        if (t < 0) {
            integer[0] = -integer[0];
        }
        /* for (int j = 0; j < dig; j++) { cout << integer[j] << endl; }*/
        integer[dig] = -n;
    }
    
}
HugeInt::HugeInt(const char* str) {

    int n = strlen(str);
    int dig = 0;
    if (n % 4 == 0) {
        dig = n / 4;//如果n是4的整数则dig=n/4
    }
    else {
        dig = n / 4 + 1;//如果n不是4的整数则整除加一
    }
    if (dig == 1) {
        integer[0] = atoi(str);
    }
    if (dig > 1)
    {
        int start = n - 4 * (dig - 1);
        char str1[5] = {0};
        str1[start] = '\0';
        memcpy(str1, str, start);
        const char* p{ str1 } ;
        integer[0] = atoi(p);
        
        
        for (int i = 1; i < dig; i++) {
            char stri[5] = {0};
            stri[4] = '\0';
            memcpy(stri, str+start+4*(i-1), 4);
            
            const char* p{ stri };
            integer[i] = atoi(p);
           
        }
    }
    integer[dig] = -n;
    /*for (int j = 0; j < dig; j++) { cout << integer[j] << endl; }*/
};

int HugeInt::getLength() const {
    int i = 1;
    int length = 0;
    while (integer[i] >= 0) {
        i++;
    }
    length = -integer[i];
    return length;
};
int Getdig(int n) {
    
    int dig = 0;
    if (n % 4 == 0) {
        dig = n / 4;//如果n是4的整数则dig=n/4
    }
    else {
        dig = n / 4 + 1;//如果n不是4的整数则整除加一
    }
    return dig;
}
int compare(int a, int b) {
    if (a > b) {
        return a;
    }
    else return b;
}

HugeInt HugeInt::operator+(const HugeInt& num) const {
    HugeInt temp("0");
    if (num.integer[0] < 0) {
        temp = num;
        temp.integer[0] = -temp.integer[0];
        temp = *this - temp;
        
        return temp;
    }
    int dig1 = Getdig(getLength());
    int dig2 = Getdig(num.getLength());
    int dig = 0;
    
    if (dig1 > dig2) {
        dig = dig1;
        
        for (int j = 0; j < dig1 - dig2; j++) {
            temp.integer[j] = integer[j];
        }
    }
    else if(dig1<dig2){
        dig = dig2;
        for (int j = 0; j < dig2 - dig1; j++) {
            temp.integer[j] =num.integer[j];
        }
    }
    else if (dig1 = dig2) {
        dig = dig1;
        
    }
    int i = 0;
    int lastovermax = 0;
    while ((dig1 - i) != 0 && (dig2 - i) != 0) {
        int tempnum = integer[dig1 - i - 1] + num.integer[dig2 - i - 1];
        int overmax = 0;
        
        if (tempnum < 9999)
        {
            overmax = 0;
        }
        else{ overmax = 1; 
        tempnum = tempnum - 10000;
        }

        temp.integer[dig - i - 1] = tempnum+lastovermax;
        lastovermax = overmax;
        i++;
    }
    if (lastovermax == 1) {
        if(dig1==dig2){
            for (int i = 0; i < dig; i++) {
                temp.integer[dig - i] = temp.integer[dig - i - 1];

            }
            temp.integer[0] = 1;
            dig++;
            temp.integer[dig] = -(4 * dig - 3);
        }
        else {
            int k = 1;
            
            while (k<= abs(dig1 - dig2)){
                int tempnum = temp.integer[abs(dig1 - dig2) - k] + lastovermax;
                int overmax = 0;
                if (tempnum < 9999)
                {
                    overmax = 0;
                }
                else {
                    overmax = 1;
                    tempnum = tempnum - 10000;
                }
                temp.integer[abs(dig1 - dig2) - k] = tempnum ;
                lastovermax = overmax;
                k++;

            }
            if (lastovermax == 1) {
                for (int i = 0; i < dig; i++) {
                    temp.integer[dig - i] = temp.integer[dig - i - 1];

                }
                temp.integer[0] = 1;
                dig++;
                temp.integer[dig] = -(4 * dig - 3);
            }
            
            
            
        }
       
    }
    temp.integer[dig] = -((int)log10(temp.integer[0]) + 1 + 4 * (dig - 1));
    /*for (int j = 0; j < dig; j++) { cout << temp.integer[j] << endl; }
    cout << temp.getLength();*/
    return temp;
};
HugeInt HugeInt::normalsub(const HugeInt& num)const {
    HugeInt temp("0");
    int dig1 = Getdig(getLength());
    int dig2 = Getdig(num.getLength());
    int dig = 0;

    if (dig1 > dig2) {
        dig = dig1;

        for (int j = 0; j < dig1 - dig2; j++) {
            temp.integer[j] = integer[j];
        }
    }
    else if (dig1 < dig2) {
        dig = dig2;
        for (int j = 0; j < dig2 - dig1; j++) {
            temp.integer[j] = num.integer[j];
        }
    }
    else if (dig1 = dig2) {
        dig = dig1;

    }
    int i = 0;
    int lastovermax = 0;
    while ((dig1 - i) != 0 && (dig2 - i) != 0) {
        int tempnum = integer[dig1 - i - 1] - num.integer[dig2 - i - 1];
        int overmax = 0;

        if (tempnum >= 0)
        {
            overmax = 0;
            if (tempnum + lastovermax < 0) {
                tempnum = tempnum + lastovermax + 10000;
                overmax = -1;
                lastovermax = 0;
            }
        }
        else {
            overmax = -1;
            tempnum = tempnum + 10000;
        }

        temp.integer[dig - i - 1] = tempnum + lastovermax;
        lastovermax = overmax;
        i++;
    }
    while (temp.integer[0] == 0) {
        
    for (int j = 0; j < dig; j++) {
        temp.integer[j] = temp.integer[j + 1];
        
    }
    dig--;
    }
    temp.integer[dig] = -((int)log10(temp.integer[0]) + 1 + 4 * (dig - 1));
    return temp;




};
bool HugeInt::negetive(const HugeInt& num)const {
    HugeInt temp("0");
    int dig1 = Getdig(getLength());
    int dig2 = Getdig(num.getLength());
    int dig = 0;

    if (dig1 > dig2) {
        dig = dig1;

        for (int j = 0; j < dig1 - dig2; j++) {
            temp.integer[j] = integer[j];
        }
    }
    else if (dig1 < dig2) {
        dig = dig2;
        for (int j = 0; j < dig2 - dig1; j++) {
            temp.integer[j] = num.integer[j];
        }
    }
    else if (dig1 = dig2) {
        dig = dig1;

    }
    int i = 0;
    int lastovermax = 0;
    while ((dig1 - i) != 0 && (dig2 - i) != 0) {
        int tempnum = integer[dig1 - i - 1] - num.integer[dig2 - i - 1];
        int overmax = 0;

        if (tempnum >= 0)
        {
            overmax = 0;
        }
        else {
            overmax = -1;
            tempnum = tempnum + 10000;
        }

        temp.integer[dig - i - 1] = tempnum + lastovermax;
        lastovermax = overmax;
        i++;
    }
    if (lastovermax == -1) {
        return 1;
    }
    else return 0;



}
HugeInt HugeInt::operator-(const HugeInt& num) const {
    
    HugeInt temp("0");
    if (num.integer[0] < 0) {
        temp = num;
        temp.integer[0] = -temp.integer[0];
        temp = temp + *this;
        
        return temp;
    }
    if(negetive(num)==1){
        temp = num.normalsub(*this);
        temp.integer[0] = -temp.integer[0];
        return temp;
    }else{
        return normalsub(num);
    }
    
}

HugeInt HugeInt::operator+(int t) const {
    HugeInt temp(t);
    temp = temp + *this;
    return temp;

};
HugeInt HugeInt::operator+(const char* t) const{
    HugeInt temp(t);
    temp = temp + *this;
    return temp;
}
HugeInt HugeInt::operator-(int t) const {
    HugeInt temp(t);
    temp = *this - temp;
    return temp;

};
HugeInt HugeInt::operator-(const char* t) const {
    HugeInt temp(t);
    temp = *this - temp;
    return temp;
}
ostream& operator<<(ostream& out, const HugeInt& t) {
    int dig= Getdig(t.getLength());
    for (int j = 0; j < dig; j++) { 
        if(t.integer[j]!=0){ out << t.integer[j]; }
        else {
            if (j != 0) {
                out << "0000";
        }
            else{ out << t.integer[j]; }
        }
    }
    return out;

};
