//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4899

#include<vector>
#include<iostream>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

bool FindMatch(int i, const VVI &w, VI &mr, VI &mc, VI &seen) {
  for (int j = 0; j < w[i].size(); j++) {
    if (w[i][j] && !seen[j]) {
      seen[j] = true;
      if (mc[j] < 0 || FindMatch(mc[j], w, mr, mc, seen)) {
        mr[i] = j;
        mc[j] = i;
        return true;
      }
    }
  }
  return false;
}

int BipartiteMatching(const VVI &w, VI &mr, VI &mc) {
  mr = VI(w.size(), -1);
  mc = VI(w[0].size(), -1);

  int ct = 0;
  for (int i = 0; i < w.size(); i++) {
    VI seen(w[0].size());
    if (FindMatch(i, w, mr, mc, seen)) ct++;
  }
  return ct;
}


int main() {

  int N, M;
  while(cin>>N>>M) {
    VVI g;
    g.resize(N+1);
    for(int i=0;i<N+1;i++) g[i].resize(N+1);
      for(int i=0;i<M;i++) {
        int a, b;
        cin>>a>>b;
        g[a][b] = 1;
      }
      VI mr, mc;
      int res = BipartiteMatching(g, mr, mc);
      if(res == N) cout<<"YES"<<endl;
      else cout<<"NO"<<endl;
    }
    return 0;
  }
