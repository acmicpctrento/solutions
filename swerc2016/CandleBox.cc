//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5668

#include<iostream>
using namespace std;

int solve(int D, int R, int T) {
    int eta;
    for(int i = D; D < 150; i++) {
        if(2*i*i+2*i*(1-D)+D*D-D-18 == 2*(R+T)) { eta = i; break; }
    }
    return R - ((eta*(eta+1) - 12)/2);
}

int main() {
    int D, R, T;
    while(cin>>D>>R>>T) {
        cout<<solve(D, R, T)<<endl;
    }
    return 0;
}
