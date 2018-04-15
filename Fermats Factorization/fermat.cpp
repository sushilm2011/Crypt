#include <iostream>
#include <cmath>
#include <assert.h>
#include <sys/time.h>
using namespace std;

bool isSquare(long long n){
	long long p = static_cast<long long>(sqrt(n));
	return ((p*p == n) || ((p+1)*(p+1) == n));
}

void trialDivision(long long N, long long &p, long long &q){
	assert(N>1);
	assert(N%2!=0);
	long long a, b2, b;
	a = 3;
	while (a <= N){
		if (N % a == 0){
		    break;
		}
		else{
		    a += 1;
		}   
	}
	b = N/a;
	p = a;
	q = b;
}

void fermatFactor(long long N, long long &p, long long &q){
	assert(N>1);
	assert(N%2!=0);
	long long a, b2, b;
	a = ceil(sqrt(N));
	b2 = a*a - N;
	while(!isSquare(b2)){
		a++;
		b2 = a*a - N;
	}
	b = sqrt(b2);
	p = a - b;
	q = a + b;
}

int main(){
	long long N, p, q;
	cout<<"Enter N:"<<endl;
	cin>>N;
	struct timeval t_start, t_end;
	gettimeofday(&t_start, NULL);
	fermatFactor(N,p,q);
	gettimeofday(&t_end, NULL);
    cout<<"Fermat Factorization Time in sec: "<<t_end.tv_sec - t_start.tv_sec<<" and microseconds: "<<t_end.tv_usec-t_start.tv_usec<<endl;
	gettimeofday(&t_start, NULL);
	trialDivision(N,p,q);
	gettimeofday(&t_end, NULL);
    cout<<"Trial Division Time in sec: "<<t_end.tv_sec - t_start.tv_sec<<" and microseconds: "<<t_end.tv_usec-t_start.tv_usec<<endl;
	cout<<p<<"*"<<q<<"="<<N;
	return 0;
}
