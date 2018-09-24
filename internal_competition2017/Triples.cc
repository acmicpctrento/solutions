//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=656&page=show_problem&problem=4874

#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int n,m;
    while(cin>>m>>n) {
        int res = 0;
        int j = 2;
        for(long z=0;z<=m;z++) {
            for(long y=0;y<=z;y++) {
                for(long x=0;x<=y;x++) {
                    long a = x*x;
                    long b = y*y;
                    long c = z*z;
                    if(a+b == c) {
                        res++;
                    }
                }
            }
        }
        res = res + (m+1) * (n-2);
        cout<<res<<endl;
    }
    return 0;
}
