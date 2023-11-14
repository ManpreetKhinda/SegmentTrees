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

/*given array of coins at with each query some coins may be flipped count no of heads*/
class ST{
    vi seg,lazy;
    public:
    ST(int n){
        seg.resize(4*n+1);
        lazy.resize(4*n+1);
    }
    void build(int ind, int low, int high, int arr[]){
        if(low==high){
            seg[ind]=arr[low];
            return;
        }
        int mid=(low+high)/2;
        build(2*ind+1,low,mid,arr);
        build(2*ind+2,mid+1,high,arr);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    void update(int ind, int low,int high,int l,int r, int val){
        if(lazy[ind]!=0){
            seg[ind]=(high-low+1)-seg[ind];
            if(low!=high){
                lazy[2*ind+1]=!lazy[2*ind+1];
                lazy[2*ind+2]=!lazy[2*ind+2];
            }
            lazy[ind]=0;
        }
        if(high<l || r<low)return;
        if(low>=l && high<=r){
            seg[ind]=(high-low+1)-val;
            if(low!=high){
                lazy[2*ind+1]=!lazy[2*ind+1];
                lazy[2*ind+2]=!lazy[2*ind+2];
            }
            return;
        }
        int mid=(low+high)/2;
        update(2*ind+1,low,mid,l,r,val);
        update(2*ind+2,mid+1,high,l,r,val);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    int query(int ind, int low, int high, int l, int r){
        if(lazy[ind]!=0){
            seg[ind]=(high-low+1)-seg[ind];
            if(low!=high){
                lazy[2*ind+1]=!lazy[2*ind+1];
                lazy[2*ind+2]=!lazy[2*ind+2];
            }
            lazy[ind]=0;
        }
        if(high<l ||r<low)return 0;
        if(low>=l && high<=r)return seg[ind];
        int mid=(low+high)/2;
        int left=query(2*ind+1,low,mid,l,r);
        int right=query(2*ind+2, mid+1,high,l,r);
        return left+right;
    }
};