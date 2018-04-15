#include <iostream>
#include <cmath>
#include <assert.h>
#include <vector>
#include <sys/time.h>
using namespace std;


void trialDivision(long long N, long long &p, long long &q){
	assert(N>1);
	assert(N%2!=0);
	long long a, b2, b;
	a = 3;
	while (a < sqrt(N)){
		if (N % a == 0){
		    break;
		}
		else{
		    a += 2;
		}   
	}
	b = N/a;
	p = a;
	q = b;
}

int main(){
	long long N,p,q;
	cout<<"Enter N:"<<endl;
	cin>>N;
	struct timeval t_start, t_end;
	gettimeofday(&t_start, NULL);
	trialDivision(N,p,q);
	gettimeofday(&t_end, NULL);
    cout<<"Time in sec: "<<t_end.tv_sec - t_start.tv_sec<<" and microseconds: "<<t_end.tv_usec-t_start.tv_usec<<endl;
	cout<<p<<"*"<<q<<"="<<N;
	return 0;
}
