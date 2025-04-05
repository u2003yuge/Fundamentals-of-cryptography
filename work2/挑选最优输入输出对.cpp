#include<bits/stdc++.h>
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
int K[N]={0,0,0,0,0,0,0,0,0,0,0,0,0};//{0b0011,0b1010,0b1001,0b0100,0b1101,0b0110,0b0011,0b1111};//;//{0,0,0,0,0,0,0,0};//
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
int encrypt_without_lastround(int x){
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
//	for(int i=0;i<n;i++)
//		v[i]=S[u[i]];
//	for(int i=0;i<n;i++)
//		w[i]=v[i]^K[i+nr-1];
//	int y=0;
	for(int i=0;i<4;i++)
		temp[i]=u[i];
	return decode();
//	return ret;
//	for(int i=0;i<n;i++)
//		y|=(w[i]<<(4*i));
//	for(int i=0;i<n;i++)
//		print(w[i]);
}
int ND[1<<16];
double RD[1<<16];
void get_prob(int XX){
	for(int i=0;i<(1<<16);i++)
		ND[i]=0;
	int y1,y2; 
	for(int i=0;i<(1<<16);i++){
		y1=encrypt_without_lastround(i);
		y2=encrypt_without_lastround(i^XX);
//		printf("%d\n",y1^y2);
		ND[y1^y2]++; 
	}
	for(int i=0;i<(1<<16);i++){
		RD[i]=1.0*ND[i];
//		printf("%.8lf\n",RD[i]);
		RD[i]=RD[i]/(1<<16);
	}
		
}
double get_DistEn(){
	double ret=0;
	for(int i=0;i<(1<<16);i++)
		fabs(RD[i])<1e-9?0:ret+=-RD[i]*log(RD[i]);
	return ret;
}
int get_max(){
	int ret=0;
	for(int i=0;i<(1<<16);i++)
		ret=ND[i]>ND[ret]?i:ret;
	return ret;
}
//int get_min(){
//	int ret=0;
//	for(int i=0;i<((1<<4)<<4);i++)
//		ret=RD[i]>RD[ret]?i:ret;
//	return ret;
//}
void get_best_dist(){
	int best=0b0000101100000000;
	get_prob(best);
	int maxn=get_max(); 
	printf("%d %d\n",maxn,ND[maxn]);
	double best_dist=get_DistEn();
	double dist;
	int x;
	for(int i=1;i<65536;i++){
//		if(i%100==0)
//			printf("%d\n",i);
//		x=rand()*rand()%(1<<16);
		x=i;	
		get_prob(i);
		dist=get_DistEn();

		if(i%100==0||dist<best_dist){
			if(dist<best_dist){
				best=x;
				best_dist=dist;	
			}
			printf("i:%d ",i);
			printf("best:%d",best);
			cout <<" bit:"<<bitset<16>(best);
			printf(" dist:%.6lf\n",best_dist);
		}

//		return 0.;
	}
	printf("best:%d",best);
	cout <<" bit:"<<bitset<16>(best);
	printf(" dist:%.6lf\n",best_dist);
	get_prob(best);
	maxn=get_max();
//	minn=get_min();
//	printf("min:%d %.6lf\n",minn,RD[minn]);
	printf("max:%d %.6lf\n",maxn,RD[maxn]);
}
int get_gap(){
	int ret=0;
	int ret2=1;
	if(ND[ret2]>ND[ret]){
		ret=1;ret2=0;
	}
		
	for(int i=2;i<(1<<16);i++){
		if(ND[i]>=ND[ret]){
			ret2=ret;ret=i;
		}
		else if(ND[i]>ND[ret2]){
			ret2=i;
		}
	}
	return ret;
}
int cal_gap(int x){
	int ret=0x3f3f3f3f;
	for(int i=0;i<(1<<16);i++){
		if(i==x)
			continue;
		ret=min(ret,ND[x]-ND[i]);
	}
	return ret;
}
void get_best_gap(){
	int best=0b1011000010110000;
	get_prob(best);
	int maxn=get_gap();
	int maxv=cal_gap(maxn);
	printf("%d %.6lf\n",maxn,RD[maxn]);
	int x,xn,xv;
	for(int i=1;i<65536;i++){
		x=i;	
		get_prob(i);
		xn=get_gap();
		xv=cal_gap(xn);
		if(i%100==0||xv>maxv){
			if(xv>maxv){
				maxv=xv;
				maxn=xn;
				best=i;	
			}
			printf("i:%d ",i);
			printf("best:%d",best);
			cout <<" bit:"<<bitset<16>(best);
			printf(" maxn:%d",maxn);
			
			printf(" maxgap:%d\n",maxv);
		}
	}
	printf("best:%d",best);
	cout <<" bit:"<<bitset<16>(best);
	printf(" maxn:%d",maxn);
	
	printf(" maxgap:%d\n",maxv);	
}
void get_best_max(){
	int best=1;//0b0000101100000000;
	get_prob(best);
	int maxn=get_max();
	int maxv=ND[maxn];
	printf("%d %d\n",maxn,ND[maxn]);
	printf("%d\n",ND[0b0000011000000110]);
//	double best_dist=get_max();//get_DistEn();
//	double dist;
	int x,xn,xv;
	for(int i=1;i<65536;i++){
//		if(i%100==0)
//			printf("%d\n",i);
//		x=rand()*rand()%(1<<16);
		x=i;	
		get_prob(i);
		xn=get_max();
		xv=ND[xn];
		if(i%100==0||xv>maxv){
			if(xv>maxv){
				maxv=xv;
				maxn=xn;
				best=i;	
			}
			printf("i:%d ",i);
			printf("best:%d",best);
			cout <<" bit:"<<bitset<16>(best);
			printf(" maxn:%d",maxn);
			
			printf(" maxv:%d\n",maxv);
		}

//		return 0.;
	}
//	printf("i:%d ",i);
	printf("best:%d",best);
	cout <<" bit:"<<bitset<16>(best);
	printf(" maxn:%d",maxn);
	
	printf(" maxv:%d\n",maxv);
}
int simple_decrypt(int y,int k){
	return S_[k^y];
}
int cnt[1<<4][1<<4];
int maxp1,maxp2;
unordered_map<int,bool>mp;
int get(){
	return rand()%(1<<16);
}
signed main(){
	get_best_max();
//	get_best_gap();
	return 0;
} 
