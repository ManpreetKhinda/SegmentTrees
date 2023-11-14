#include<bits/stdc++.h>
using namespace std;
int a[1000001], seg[4*1000001];
int lazy[4*1000001];

void build(int ind, int low, int high){
    if(low==high){
        seg[ind]=a[low];
        return;
    }
    int mid=(low+high)/2;
    build(2*ind+1, low,mid);
    build(2*ind+2, mid+1,high);
    seg[ind]=max(seg[2*ind+1],seg[2*ind+2]);
}
int query(int ind, int low, int high, int l ,int r){
    if(low>=l&& high<=r)return seg[ind];
    if(high<l ||low>r)return INT_MIN;
    int mid=(low+high)/2;
    int left=query(2*ind+1,low, mid, l,r);
    int right=query(2*ind+2, mid+1,high, l,r);
    return max(left,right);
}

/*single point update for a sum query segment treee*/
void point_update(int ind , int low, int high, int node, int val){
    if(low==high)seg[low]+=val;
    else {
        int mid=(low+high)/2;
        if(node<=mid && node>=low) point_update(2*ind+1, low, mid, node,val);
        else point_update(2*ind+2,mid+1,high,node,val);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
}
void rangeupdate(int ind, int low, int high, int l, int r, int val){
    if(lazy[ind]!=0){
        seg[ind]+=(high-low+1)*lazy[ind];
        if(low!=high){
            lazy[2*ind+1]+=lazy[ind];
            lazy[2*ind+2]+=lazy[ind];
        }
        lazy[ind]=0;
    }
    if(r<low||l>high||low>high)return ;
    if(low>=l &&high<=r){
        seg[ind]+=(high-low+1)*val;
        if(low!=high){
            lazy[2*ind+1]+=lazy[ind];
            lazy[2*ind+2]+=lazy[ind];
        }
        return;
    }
    int mid=(low+high)/2;
    rangeupdate(2*ind+1,low,mid,l,r,val);
    rangeupdate(2*ind+2,mid+1,high,l,r,val);
    seg[ind]=seg[2*ind+1]+seg[2*ind+2];
}
int querysumlazy(int ind, int low, int high, int l, int r, int val){
    if(lazy[ind]!=0){
        seg[ind]+=(high-low+1)*lazy[ind];
        if(low!=high){
            lazy[2*ind+1]+=lazy[ind];
            lazy[2*ind+2]+=lazy[ind];
        }
        lazy[ind]=0;
    }
    if(r<low||l>high||low>high)return 0;
    if(low>=l &&high<=r){
        return seg[ind];
    }
    int mid=(low+high)/2;
    return querysumlazy(2*ind+1,low,mid,l,r,val)+querysumlazy(2*ind+2,mid+1,high,l,r,val);
}
int main(){
    int n;cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    build(0,0,n-1);
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<query(0,0,n-1,l,r)<<endl;
    }
}