#include <iostream>
#include <vector>
#include <queue>
#include <thread>

using namespace std;

const int inf = 20000;

struct Query{
    int w, d, idx;
};

const int num_threads = std::thread::hardware_concurrency()/2;

void solve(){
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> g(n);
    vector<vector<Query>> query(n);
    vector<int> ans(k);

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
    vector<thread> threads;
    for(int t_id = 0; t_id < num_threads; t_id++){
        threads.emplace_back([&, t_id](){
            int dist[n][2];
            queue<pair<int,int>> q;
            for(int i = t_id; i < n; i += num_threads){
                if(query[i].empty()) continue;
                for(int j = 0; j < n; j++){
                    dist[j][0] = inf;
                    dist[j][1] = inf;
                }
                q.push({i, 0});
                dist[i][0] = 0;
                while(!q.empty()){
                    auto [w, p] = q.front();
                    int d = dist[w][p];
                    int np = p ^ 1;
                    q.pop();
                    for(int v : g[w]){
                        if(d+1 < dist[v][np]){
                            dist[v][np] = d+1;
                            q.push({v, np});
                        }
                    }
                }
                for(auto x : query[i]){
                    ans[x.idx] = x.d >= dist[x.w][x.d%2];
                }
            }
        });
    }
    for(auto& th : threads) th.join();
    for(bool b : ans) cout << (b ? "TAK\n" : "NIE\n");
}
int main(){
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}