#include <iostream>
#include <bitset>
#include <cmath>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

string charToBin(char temp);//十六进制转二进制串
int stringToDouble(string temp);//二进制串到double（整数）--求阶码
double BenToDex(string temp);//二进制串到double（小数）
double HexToDouble(string temp);//十六进制字符串到double类型
string readFileIntoString(char * filename);


int main()

{
    char * fn = "data.txt";
    string str;
    str = readFileIntoString(fn);
    return 0;
}

double HexToDouble(string temp)
{
    string S_Bin = "";//转化后的二进制字符串
    for (int i = 0;i < temp.length();i++)
    {
        char temp1 = temp.at(i);
        S_Bin = S_Bin+charToBin(temp1);
    }


    int sign = 0;//符号位
    if (S_Bin.at(0) == '1')
    {
        sign = 1;
    }

    string exponent = "";
    for (int i = 1;i < 12;i++)
    {
        if (S_Bin.at(i) == '1')
        {
            exponent = exponent + '1';
        }
        else
            exponent = exponent + '0';
    }

    int exponent_double = 0;//阶码
    exponent_double = stringToDouble(exponent);
    exponent_double = exponent_double - 1023;


    string mantissa_temp = "";
    for (int i = 12;i < 64;i++)
    {
        if (S_Bin.at(i) == '1')
        {
            mantissa_temp = mantissa_temp + '1';
        }
        else
            mantissa_temp = mantissa_temp + '0';
    }
    double mantissa = 0;
    mantissa = BenToDex(mantissa_temp);
    mantissa = mantissa+1.0;


    double res = 0;
    double a,c;
    a = pow((-1),sign);
    c = pow(2,exponent_double);
    res = a * mantissa * c;


    return res;
}
string charToBin(char temp)//十六进制转二进制串
{
    switch (temp)
    {
    case '0':
        return "0000";
        break;
    case '1':
        return "0001";
        break;
    case '2':
        return "0010";
        break;
    case '3':
        return "0011";
        break;
    case '4':
        return "0100";
        break;
    case '5':
        return "0101";
        break;
    case '6':
        return "0110";
        break;
    case '7':
        return "0111";
        break;
    case '8':
        return "1000";
        break;
    case '9':
        return "1001";
        break;
    case 'A':
    case 'a':
        return "1010";
        break;
    case 'B':
    case 'b':
        return "1011";
        break;
    case 'C':
    case 'c':
        return "1100";
        break;
    case 'D':
    case 'd':
        return "1101";
        break;
    case 'E':
    case 'e':
        return "1110";
        break;
    case 'F':
    case 'f':
        return "1111";
        break;
    default:
        return "WRONG!";
    }
}
int stringToDouble(string temp)//二进制串到double（整数）
{
    double res = 0;
    for   (int i = 0;i < temp.length();i++)
    {
        res=res * 2 + (temp[i] - '0');
    }
    return res;
}

double BenToDex(string temp)//二进制串到double（小数）
{
    int m = temp.length();
    double res = 0;
    for (int i = 0;i < m;i++)
    {
        res = res + (temp[i] - '0')*pow(2, -i - 1);
    }
    return res;
}

string readFileIntoString(char * filename)
{
    ifstream ifile(filename);
    ostringstream buf;
    string string_;
    char ch;
    int time = 0;
//    union
//    {
//        u_int64_t u64;
//        char u8[8];
//        double d;
//    } v;
    int index = 0;
    while(buf&&ifile.get(ch))
    {
        buf.put(ch);
        if(ch != ' ') {
            string_.push_back(ch);
        }

        if(ch == char(10))
        {
            if (string_.size() == 1)
            {
                string_.clear();
            }
            else
            {


                if (time == 3 )
                {
                    cout<<endl;
                    time = 0;
                }
                time++;

                double a = HexToDouble(string_);
                cout<<a<<endl;
                string_.clear();
            }
        }
    }
    //返回与流对象buf关联的字符串
    return buf.str();
}
