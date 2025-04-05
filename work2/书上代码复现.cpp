#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<random>
#include<unordered_map> 
#include<ctime>
using namespace std;
const int N=100010;
int S[16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};
int S_[16]={14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5};
int P[17]={0,1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};
char s[N];
int in[N];
int w[N];
int u[N];
int v[N];
int K[N]={0b0011,0b1010,0b1001,0b0100,0b1101,0b0110,0b0011,0b1111};
int nr,n;
int Y[4],Y_[4];
void print(int x){
	printf("%04d",((x&8)>>3)*1000+((x&4)>>2)*100+((x&2)>>1)*10+(x&1));
}
int temp[4];
void encode(int x){
	for(int i=0;i<4;i++)
		temp[3-i]=(x>>(4*i))%16;
}
int decode(){
	int ret=0;
	for(int i=0;i<4;i++)
		ret|=(temp[3-i]<<(4*i));	
	return ret;
}
int encrypt(int x){
	n=4;//strlen(in);
//	nr=8;//strlen(K);
	encode(x);
	for(int i=0;i<4;i++)
		in[i]=temp[i];
//	for(int i=0;i<nr;i++)
//		K[i+nr]=K[i];
	for(int i=0;i<n;i++)
		w[i]=in[i];
	nr=n+1;
	for(int r=0;r<nr-2;r++){
		for(int i=0;i<n;i++){
			u[i]=w[i]^K[r+i];
		}
		for(int i=0;i<n;i++)
			v[i]=S[u[i]];
		for(int i=0;i<n;i+=4){
			for(int j=0;j<4;j++){
				w[j]=0;
			}
			for(int j=1;j<=16;j++)
				w[(P[j]-1)/4+i]|=(((v[(j-1)/4+i]>>((4-j%4)%4))&1)<<((4-P[j]%4)%4)); 
		}
	}
	for(int i=0;i<n;i++)
		u[i]=w[i]^K[i+nr-2];
	for(int i=0;i<n;i++)
		v[i]=S[u[i]];
	for(int i=0;i<n;i++)
		w[i]=v[i]^K[i+nr-1];
//	int y=0;
	for(int i=0;i<4;i++)
		temp[i]=w[i];
	return decode();
//	return ret;
//	for(int i=0;i<n;i++)
//		y|=(w[i]<<(4*i));
//	for(int i=0;i<n;i++)
//		print(w[i]);
}
int simple_decrypt(int y,int k){
	return S_[k^y];
}
int cnt[1<<4][1<<4];
int maxp1,maxp2;
unordered_map<int,bool>mp;
int get(){
	return rand()*rand()%(1<<16);
}
signed main(){
	srand(time(0));
	int T=300;
	int XX=0b0000101100000000;//0000101100001011;//0b0110000011110000;//0b1011101100001011;//
	int x,x_,y,y_;
	int count=0;
	for(int t=0;t<T;t++){
		x=get();
		while(mp.find(x)!=mp.end())
			x=get();
		mp[x]=true;
		x_=x^XX;
		y=encrypt(x);
		y_=encrypt(x_);
		encode(y);
		for(int i=0;i<4;i++)
			Y[i]=temp[i];
		encode(y_);
		for(int i=0;i<4;i++)
			Y_[i]=temp[i];
		if(Y[0]!=Y_[0] || Y[2]!=Y_[2])
			continue;
		count++;
//		printf("%d\n",count);
		int same1=0b0110;//0b0001;//0b1001;//0b0110
		int same3=0b0110;//0b1010;//0b0110
		for(int L1=0;L1<(1<<4);L1++)
			for(int L2=0;L2<(1<<4);L2++)
				if((simple_decrypt(Y[1],L1)^simple_decrypt(Y_[1],L1))==same1&&(simple_decrypt(Y[3],L2)^simple_decrypt(Y_[3],L2))==same3){
//					printf("%d %d\n",L1,L2); 
					cnt[L1][L2]++;
				}
	}
	for(int L1=0;L1<(1<<4);L1++){
		for(int L2=0;L2<(1<<4);L2++){
			if(cnt[L1][L2]>cnt[maxp1][maxp2]){
//				printf("%d\n",cnt[L1][L2]);
				maxp1=L1;maxp2=L2;
			}}}
	print(maxp1);
	print(maxp2);
	return 0;
} 
