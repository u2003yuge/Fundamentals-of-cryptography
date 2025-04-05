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
int K_test[100][8];
int T_test[100][1001];
int ans[4][1001];
signed main(){
	srand(time(0));
//	int T=300;
	freopen("test.txt","w",stdout); 
	int same1,same2;
	int p1,p2,p3,p4;
	int XX;
	int KNUM=100,TNUM=100,MAXT=250;
	for(int i=0;i<KNUM;i++)
		for(int j=0;j<8;j++)
			K_test[i][j]=rand()%16;
	for(int T=10;T<=MAXT;T++){
		for(int i=0;i<TNUM;i++){
			mp.clear();
			int x;
			for(int j=0;j<T;j++){
				x=get();
				while(mp.find(x)!=mp.end())
					x=get();
				mp[x]=true;
				T_test[i][j]=x;
			}
		}
	}
	
		
	for(int type=0;type<3;type++){
		if(type==0){
			same1=0b1010,same2=0b1010;
			p1=1;p2=3;p3=0;p4=2;
			XX=0b0000000000000011;
		}
		else if(type==1){
			same1=0b0110,same2=0b0110;
			p1=1;p2=3;p3=0;p4=2;
			XX=0b0000101100000000;
		}
		else if(type==2){
			same1=0b1000,same2=0b1000;
			p1=1;p2=3;p3=0;p4=2;
			XX=0b1011000010110000;
		}
		for(int T=10;T<=MAXT;T++){
			for(int kk=0;kk<KNUM;kk++){
				for(int i=0;i<8;i++)
					K[i]=K_test[kk][i];
				int x,x_,y,y_;
				int count=0;
				int maxp1=0,maxp2=0;
				for(int tt=0;tt<TNUM;tt++){
					for(int L1=0;L1<(1<<4);L1++)
						for(int L2=0;L2<(1<<4);L2++)
							cnt[L1][L2]=0;
					for(int i=0;i<T;i++){
	//					x=get();
	//					while(mp.find(x)!=mp.end())
	//						x=get();
	//					mp[x]=true;
						x=T_test[tt][i];
						x_=x^XX;
						y=encrypt(x);
						y_=encrypt(x_);
						encode(y);
						for(int i=0;i<4;i++)
							Y[i]=temp[i];
						encode(y_);
						for(int i=0;i<4;i++)
							Y_[i]=temp[i];
						
						if(Y[p3]!=Y_[p3] || Y[p4]!=Y_[p4])
							continue;	
						count++;
						for(int L1=0;L1<(1<<4);L1++)
							for(int L2=0;L2<(1<<4);L2++)
								if((simple_decrypt(Y[p1],L1)^simple_decrypt(Y_[p1],L1))==same1&&(simple_decrypt(Y[p2],L2)^simple_decrypt(Y_[p2],L2))==same2){
									cnt[L1][L2]++;
								}
					}
					for(int L1=0;L1<(1<<4);L1++){
						for(int L2=0;L2<(1<<4);L2++){
							if(cnt[L1][L2]>cnt[maxp1][maxp2]){
								maxp1=L1;maxp2=L2;
							}
						}
					}
					if(maxp1==K[p1+4]&&maxp2==K[p2+4])
						ans[type][T]++;
				}

			}
		}
	}
	for(int i=0;i<3;i++){
		for(int j=10;j<=MAXT;j++)
			printf("%d ",ans[i][j]);
		puts("");
	}
		
	return 0;
} 
