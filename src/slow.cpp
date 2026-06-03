#include <iostream>
#include <vector>
#include <queue>

using namespace std;

short int inf = 20000;

struct Query{
    int w, d, idx;
};

void solve(){
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> g(n);
    vector<vector<Query>> query(n);
    vector<bool> ans(k);

    for(int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }


    for(int i = 0; i < k; i++){
        int s, t, d;
        cin >> s >> t >> d;
        query[s-1].push_back({t-1, d, i});
    }


    for(int i = 0; i < n; i++){
        if(query[i].empty()) continue;
        queue<pair<short int,bool>> q;
        vector<vector<int>> dist(n, vector<int>(2, inf));
        q.push({i, 0});
        dist[i][0] = 0;
        while(!q.empty()){
            short int w = q.front().first;
            short int d = dist[w][q.front().second];
            q.pop();
            for(int v : g[w]){
                if(d+1 < dist[v][(d+1)%2]){
                    dist[v][(d+1)%2] = d+1;
                    q.push({v, (d+1)%2});
                }
            }
        }
        for(auto x : query[i]){
            ans[x.idx] = x.d >= dist[x.w][x.d%2];
        }
    }
    for(bool b : ans) cout << (b ? "TAK\n" : "NIE\n");
}
int main(){
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}