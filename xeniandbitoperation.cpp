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

/*codeforces xenia and bitoperations*/
void build(int ind,int low, int high,int arr[], int seg[], bool isor){
    if(low==high){
        seg[ind]=arr[low];
        return;
    }
    int mid=(low+high)/2;
    build(2*ind+1,low,mid,arr,seg,!isor);
    build(2*ind+2,mid+1,high,arr,seg,!isor);
    if(isor)seg[ind]=seg[2*ind+1]|seg[2*ind+2];
    else seg[ind]=seg[2*ind+1]^seg[2*ind+2];
}
void update(int ind,int low,int high,int seg[],bool isor, int i, int val){
    if(low==high){
        seg[ind]=val;return;
    }
    int mid=(low+high)/2;
    if(i<=mid)update(2*ind+1,low,mid,seg,!isor,i,val);
    else update(2*ind+2,mid+1,high,seg,!isor,i,val);
    if(isor)seg[ind]=seg[2*ind+1]|seg[2*ind+2];
    else seg[ind]=seg[2*ind+1]^seg[2*ind+2];
}
void solve(){
    int n,q;
    cin>>n>>q;
    int el=pow(2,n);
    int arr[el];
    rep(i,0,el)cin>>arr[i];
    int seg[4*el];
    if(n%2==0)build(0,0,el-1,arr,seg,0);
    else build(0,0,el-1,arr,seg,1);
    while(q--){
        int i,val;
        cin>>i>>val;
        i--;
        if(n%2==0)update(0,0,el-1,seg,0,i,val);
        else update(0,0,el-1,seg,1,i,val);
        cout<<seg[0]<<endl;
    }
}