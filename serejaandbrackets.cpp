#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define vi vector<int>
#define vli vector<ll>
#define vvi vector<vi>
#define vvli vector<vli>
#define pii pair<int, int>
#define pli pair<ll, ll>
#define vii vector<pii>
#define vll vector<pli>
#define pb push_back
#define ppb pop_back
#define F first
#define S second
#define MM INT_MAX
#define MN INT_MIN
#define vb vector<bool>
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i,a,b) for(int i=a;i>b;i--)
#define M 1000000007
#define all(x) (x).begin(),(x).end()
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return (mod_mul(a, mminvprime(b, m), m) + m) % m;}  //only for prime m

class info{
    public:
    int open,close,full;
    public:
    info(){
        open=0;
        close=0;
        full=0;
    }
    info(int _op,int _cl, int _fl){
        open=_op;
        close=_cl;
        full=_fl;
    }
};
info merge(info left, info right){
    info ans=info(0,0,0);
    ans.full=left.full+right.full+min(left.open,right.close);
    ans.open=left.open+right.open-min(left.open,right.close);
    ans.close=left.close+right.close -min(left.open,right.close);
    return ans;
}
void build(int ind,int low,int high,string s,info seg[]){
    if(low==high){
        seg[ind].open=s[low]=='(';
        seg[ind].close=s[low]==')';
        seg[ind].full=0;
        return;
    }
    int mid=(low+high)/2;
    build(2*ind+1,low,mid,s,seg);
    build(2*ind+2,mid+1,high,s,seg);
    seg[ind]=merge(seg[2*ind+1],seg[2*ind+2]);
}
info query(int ind,int low,int high,int l,int r, info seg[]){
    if(r<low||high<l)return info();
    if(low>=l && high<=r)return seg[ind];
    int mid=(low+high)/2;
    info left=query(2*ind+1,low,mid,l,r,seg);
    info right=query(2*ind+2,mid+1,high,l,r,seg);
    return merge(left,right);
}
void solve(){
    string s;
    cin>>s;
    int n=s.size();
    info seg[4*n];
    build(0,0,n-1,s,seg);
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        l--,r--;
        info ans=query(0,0,n-1,l,r,seg);
        cout<<ans.full*2<<endl;
    }
}