/*
1010 Radix

Given a pair of positive integers, for example, 6 and 110, can this equation 6 = 110 be true? The answer is "yes", if 6 is a decimal number and 110 is a binary number.

Now for any pair of positive integers N1 and N2, your task is to find the radix of one number while that of the other is given.

Input Specification:

Each input file contains one test case. Each case occupies a line which contains 4 positive integers:
N1 N2 tag radix
Here N1 and N2 each has no more than 10 digits. A digit is less than its radix and is chosen from the set {0-9, a-z} where 0-9 represent the decimal numbers 0-9, and a-z represent the decimal numbers 10-35. The last number "radix" is the radix of N1 if "tag" is 1, or of N2 if "tag" is 2.

Output Specification:

For each test case, print in one line the radix of the other number so that the equation N1 = N2 is true. If the equation is impossible, print "Impossible". If the solution is not unique, output the smallest possible radix.

Sample Input 1:
6 110 1 10
Sample Output 1:
2
Sample Input 2:
1 ab 1 2
Sample Output 2:
Impossible

*/

#include <cstdio>
#include <cctype>
#include <vector>
#define LENGTH 15

using namespace std;

int getValue(char ch)
{
    return isdigit(ch) ? (ch - '0') : (ch - 'a' + 10);
}

long long convertRadix2Decimal(char* num, long long radix)
{
    long long ans = 0; // suppose the largest is 2^63 - 1
    while(*num)
    {
        ans = ans * radix + getValue(*num++);
        if(ans < 0)
            break;
    }
    return ans;
}

long long getLowestRadix(char* p)
{
    long long lowest = 2;
    while(*p)
    {
        int value = getValue(*p++);
        lowest = (value >= lowest) ? value + 1: lowest;
    }
    return lowest;
}

int main()
{
    char n1[LENGTH];
    char n2[LENGTH];
    int tag;
    long long radix;
    scanf("%s %s %d %lld", n1, n2, &tag, &radix);

    char* p1;
    char* p2;
    if(tag == 1)
    {
        p1 = n1;
        p2 = n2;
    }
    else
    {
        p1 = n2;
        p2 = n1;
    }

    long long target = convertRadix2Decimal(p1, radix);
    long long low = getLowestRadix(p2);
    long long high = target + 1;
    // because n1 and n2 has at least one "digit",
    // so high >= target + 1, so set high = target + 1(so if n2 = 1, the radix of n2 is at least target + 1)

    long long mid;
    long long tmp;
    bool flag = false;
    while(low <= high)
    {
        mid = (low + high) >> 1;
        tmp = convertRadix2Decimal(p2, mid);
        if(tmp < 0 || tmp > target)
            high = mid - 1;
        else if(tmp < target)
            low = mid + 1;
        else
        {
            flag = true;
            break;
        }
    }

    if(flag)
        printf("%lld\n", mid);
    else
        printf("Impossible\n");
    return 0;
}

