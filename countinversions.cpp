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

class SGTree{
    public:
    vi seg;
    public:
    SGTree(int n){
        seg.resize(4*n+1);
    }
    void build(int ind,int low,int high,int arr[]){
        if(low==high){
            seg[ind]=arr[low];
            return ;
        }
        int mid=(low+high)/2;
        build(2*ind+1,low,mid,arr);
        build(2*ind+2,mid+1,high,arr);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    int query(int ind,int low,int high, int l,int r){
        if(r<low||high<l)return 0;
        if(low>=l &&high<=r)return seg[ind];
        int mid=(low+high)/2;
        int left=query(2*ind+1,low,mid,l,r);
        int right=query(2*ind+2,mid+1,high,l,r);
        return left+right;
    }
    void update(int ind,int low,int high,int i,int val){
        if(low==high){
            seg[ind]+=val;
            return;
        }
        int mid=(low+high)/2;
        if(i<=mid)update(2*ind+1,low,mid,i,val);
        else update(2*ind+2,mid+1,high,i,val);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
};
void solve(){
    int n;
    cin>>n;
    int arr[n];
    int mx=-1;
    rep(i,0,n){
        cin>>arr[i];
        mx=max(mx,arr[i]);
    }
    mx++;
    int freq[mx];
    memset(freq,0,sizeof(freq));
    rep(i,0,n)freq[arr[i]]++;
    SGTree st(mx);
    st.build(0,0,mx-1,freq);
    int cnt=0;
    rep(i,0,n){
        freq[arr[i]]--;
        st.update(0,0,mx-1,arr[i],-1);
        cnt+=st.query(0,0,mx-1,1,arr[i]-1);
    }
    cout<<cnt<<endl;
}