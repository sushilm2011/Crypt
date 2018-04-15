#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cassert>
using namespace std;
typedef long long ll;

bool isPrime(ll n){
	if(n%2==0)
		return false;
	for(int i=3;i<=sqrt(n);i+=2){
		if(n%i == 0){
			return false;
		}
	}
	return true;
}

bool rangeInside(ll n){
	return n>256;
}

ll gcd(ll a, ll b){
	ll temp;
	while (true){
		temp = a%b;
		if (temp == 0)
		  	return b;
		a = b;
		b = temp;
	}
}

ll modInverse(ll a, ll m){
    ll m0 = m;
    ll y = 0, x = 1;
 
    if (m == 1)
      return 0;
 
    while (a > 1){
        ll q = a / m;
        ll t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
       x += m0;
 
    return x;
}

ll getE(ll totient, ll p, ll q){
	ll e = 2;
	while(true){
		if(gcd(e,totient) == 1 && e!=p && e!=q && isPrime(e)){
			return e;
		}
		e+=1;
	}
}

ll getD(ll e, ll totient){
	return modInverse(e, totient);
}

vector<ll> encrypt(int *msgInt, int msgLength, ll e, ll n){
	ll k;
 	vector<ll> en;
	for(int i = 0; i < msgLength; i++){
		k = 1;
		for(int j = 0; j<e; j++){
			k=(k*(msgInt[i]))%n;
		}
		en.push_back(k);
	}
	return en;
}


 
vector<ll> decrypt(vector<ll> en, ll d, ll n) {
	ll k;
	vector<ll> de;
	for(int i = 0; i<en.size(); i++){
		k = 1;
		for(int j=0;j<d;j++){
			k = (k*(en[i]))%n;
		}
		de.push_back(k);
	}
 	return de;
}

int main() {
	string msg;
	int msgLength;
	ll e, n, d, p, q, totient;
	cout<<"Enter two prime numbers: "<<endl;
	cin>>p>>q;
	assert(isPrime(p) && "Choose two prime numbers");
	assert(isPrime(q) && "Choose two prime numbers");
	assert(p!=q && "Choose two different prime numbers");
	n=p*q;
	assert(rangeInside(n) && "Choose larger prime numbers");
	cout<<"Enter the message: "<<endl;
	cin>>msg;
	msgLength = msg.length();
	int msgInt[msgLength];
	for (int i=0; i<msgLength ;i++)
		msgInt[i]=msg[i];
	totient=(p-1)*(q-1);
	e=getE(totient, p, q);
	d=getD(e, totient);
	cout<<"Value of e: "<<e<<" and Value of d: "<<d<<endl;
	vector<ll> en = encrypt(msgInt, msgLength, e, n);
	cout<<"Encrypted String: "<<endl;
	for(int i = 0;i<en.size();i++){
		cout<<(char)en[i];
	}
	cout<<endl;
	vector<ll> de = decrypt(en, d, n);
	cout<<"Decrypted String: "<<endl;
	for(int i = 0;i<de.size();i++){
		cout<<(char)de[i];
	}
	cout<<endl;
}
