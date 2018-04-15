#include <iostream>
#include <map>
#include <cmath>
#include <cstdlib>
using namespace std;
#define SIZE 2
bool debug = true;

void printMatrix(double mat[SIZE][SIZE]){
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			cout<<(mat[i][j])<<" ";
		}
		cout<<endl;
	}
}

void printMatrix1D(double mat[SIZE][1]){
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<1;j++){
			cout<<(mat[i][j])<<" ";
		}
		cout<<endl;
	}
}

void createMat(string key, double mat[SIZE][SIZE]){
	int l = key.length();
	int i=0; 
	map<double,double> mp;
	for( i=0;i<l;i++){
		mat[(i/SIZE)][(i%SIZE)] = key[i] - 65;
		mp[key[i]-65]=1;
	}

	int k=0;
	for(i;i<SIZE * SIZE;i++){
		while(mp[k]==1)
			k++;
		mat[(i/SIZE)][(i%SIZE)] = k;
		k++;
	}
}

void createMat1D(string pladoubleext, double mat[SIZE][1]){
	for(int i=0;i<SIZE;i++){
		mat[i][0] = pladoubleext[i] - 65;
	}
}

void multiply(double key[SIZE][SIZE], double text[SIZE][1]){
	double C[SIZE][1];
	for (int i = 0; i < SIZE; i++){
        	for (int j = 0; j < 1; j++){
            		C[i][j] = 0;
            		for (int k = 0; k < SIZE; k++){
                		C[i][j] += key[i][k] * text[k][j];
            		}
        	}
    	}
	for(int i=0;i<SIZE;i++){
		text[i][0] = C[i][0];
	}
}

void mod(double data[SIZE][1], int val){
	for(int i=0;i<SIZE;i++){
		data[i][0] = fmod(data[i][0], val);
	}
}

string convert(double mat[SIZE][1]){
	string s = "";
	for(int i=0; i<SIZE; i++){
		s = s + char(floor(mat[i][0]) + 'A');
	}
	return s;
}

void getCofactor(double A[SIZE][SIZE], double temp[SIZE][SIZE], int p, int q, int n){
    int i = 0, j = 0;
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            if (row != p && col != q){
                temp[i][j++] = A[row][col];
                if (j == n - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double determinant(double A[SIZE][SIZE], int n){
    double D = 0;
    if (n == 1)
        return A[0][0];
    double temp[SIZE][SIZE];
    int sign = 1;
    for (int f = 0; f < n; f++){
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return D;
}
 
void adjodouble(double A[SIZE][SIZE],double adj[SIZE][SIZE]){
    int sign = 1;
    double temp[SIZE][SIZE];
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            getCofactor(A, temp, i, j, SIZE);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp, SIZE-1));
        }
    }
}

int modulo(int n, int p) {
    int r = n%p;
    if(((p > 0) && (r < 0)) || ((p < 0) && (r > 0)))
        r += p;
    return r;
}

int modInverse(int n, int p) {
    n = modulo(n, p);
    for(int x = 1; x < p; x++) {
        if(modulo(n*x, p) == 1) return x;
    }
    return 0;
}

bool getInverse(double A[SIZE][SIZE]){
    double inverse[SIZE][SIZE];
    double det = determinant(A, SIZE);
    if (det == 0){
        cout << "Singular matrix, can't find its inverse";
        return false;
    }
 
    double adj[SIZE][SIZE];
    adjodouble(A, adj);
	if (debug){
		cout<<"Determinant: "<<det<<endl;
		cout<<modInverse(det, 26)<<endl;
	}
	for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            A[i][j] = modulo(adj[i][j]*modInverse(det, 26), 26);
			if (debug)
				cout<<A[i][j]<<" ";
		}
		if (debug)
			cout<<endl;
	}

    return true;
}

string encrypt(double eMat[SIZE][SIZE], string pladoubleext){
	double pMat[SIZE][1];
	double keyMat[SIZE][SIZE];
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			keyMat[i][j] = eMat[i][j];
		}
	}
	if (debug){
		cout<<"Creating Plain Text Matrix"<<endl;
	}
	createMat1D(pladoubleext, pMat);
	
	if (debug){
		printMatrix1D(pMat);
	}

	multiply(keyMat, pMat);
	mod(pMat, 26);
	string encryptedData = convert(pMat);
	return encryptedData;
}

string decrypt(double eMat[SIZE][SIZE], string encryptedData){

	double eData[SIZE][1];
	double keyMat[SIZE][SIZE];
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			keyMat[i][j] = eMat[i][j];
		}
	}

	if (debug){
		cout<<"Creating Plain Text Matrix"<<endl;
	}
	createMat1D(encryptedData, eData);
	
	if (debug){
		printMatrix1D(eData);
	}
	bool x = getInverse(keyMat);
	if (!x){
		cout<<"\nInverse doesn't exist"<<endl;
		exit(0);
	}
	multiply(keyMat, eData);
	mod(eData, 26);
	string decryptedData = convert(eData);
	return decryptedData;
}

int main(){
	int option;
	cout<<"Do You Have 1.String Key or 2.Matrix Key (1/2)?"<<endl;
	cin>>option;
	double eMat[SIZE][SIZE];
	if(option == 1){
		string key;
		cout<<"Enter Key: "<<endl;
		cin>>key;

		if (debug){
			cout<<"Creating Key Matrix"<<endl;
		}
		
		createMat(key, eMat);

		if (debug){
			printMatrix(eMat);
		}
	}else{
		cout<<"Enter Matrix Key: "<<endl;
		for(int i=0; i<SIZE * SIZE; i++){
			cin>>eMat[i/SIZE][i%SIZE];
		}
	}

	string pladoubleext;
	cout<<"Enter Plain text: "<<endl;
	cin>>pladoubleext;


	cout<<"Key: "<<endl;
	printMatrix(eMat);
	cout<<"Plain Text: "<<pladoubleext<<endl;
	string s = "", encryptedData = "", decryptedData = "";	
	
	for(int i=0; i < pladoubleext.length(); i++){
		s = s + pladoubleext[i];
		if((i+1)%SIZE == 0){
			encryptedData += encrypt(eMat, s);
			s = "";	
		}
	}
	int l = s.length();
	if (l>0){
		for(int i=0; i < SIZE-l; i++){
			s+="Z";
		}
		encryptedData += encrypt(eMat, s);
	}
	cout<<"EncryptedData: "<<encryptedData<<endl;
	s = "";
	for(int i=0; i < encryptedData.length(); i++){
		s = s + encryptedData[i];
		if((i+1)%SIZE == 0){
			decryptedData += decrypt(eMat, s);
			s = "";	
		}
	}
	cout<<"DecryptedData: "<<decryptedData<<endl;
}
