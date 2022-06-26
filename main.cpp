#include <iostream>
#include <fstream>
#include "math.hpp"

int main() {
    int len = 0;
    std::cout<<"Key length: ";
    std::cin >> len;
    std::cout<<std::endl;
    len /= 16;
    unsigned long long p[len], q[len], n[len], phi[len], e[len],d[len];
    int i;
    for(i=0; i<len; ++i) {
        p[i]=0; q[i]=0; n[i]=0; phi[i]=0; e[i]=0; d[i]=0;
    }
    e[len-1] = 65537;
    for (i = 0; i < len/4; ++i) {
        p[len-i-1] = std::rand() * std::rand();
        q[len-i-1] = std::rand() * std::rand();
    }
    math::multiply(p,q,n,len);          // получение n
    p[len-1] -= 1;
    q[len-1] -= 1;
    math::multiply(p,q,phi,len);        // получение функции эйлера от n
    unsigned long long x[len+1], y[len+1];
    for(i=0; i<len+1; ++i) {
        x[i]=0; y[i]=0;
    }
    math::bezout(phi, e, y, x, len);   // коэффициенты безу
    if (x[0] == 0) {
        for (i=0; i<len; ++i) d[i]=x[i+1];
    } else {
        x[0] = 0;
        unsigned long long m[len+1], x1[len+1];
        m[0] = 0;
        for (i=0; i<len; ++i) m[i+1]=phi[i];
        math::sub(m,x,x1,len);
        for (i=0; i<len; ++i) d[i]=x1[i+1];
    }
    std::cout<<std::hex;
    std::cout<<"Public exp:"<<std::endl;
    for (i=len/2; i<len; ++i) std::cout<<e[i]<<" ";
    std::cout<<std::endl;
    std::cout<<"Private exp:"<<std::endl;
    for (i=len/2; i<len; ++i) std::cout<<d[i]<<" ";
    std::cout<<std::endl;
    std::cout<<"Module"<<std::endl;
    for (i=len/2; i<len; ++i) std::cout<<n[i]<<" ";
    return 0;
}
