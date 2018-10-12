#include <iostream>
#include <cmath>
#include <utility>

using namespace std;

int gcd(int a, int b){
	if (a==0) return b;
	else gcd(b%a,a);
}

int modInverse(int e, int phi) { 
    for (int x=2*phi; x>1; x--) 
       if ((e*x) % phi == 1) 
          return x; 
} 

int d;

pair<int,int>* keys(){
	int p =89,q=97;
	int n = p*q;
	int e = 2;
	int phi = (p-1)*(q-1);
	while(e<phi){
		if (gcd(phi,e)==1) break;
		else e++;
	}
	pair<int,int>* pubKey = new pair<int,int>(e,n);
	d = modInverse(e,phi);
	return pubKey;
}

int modpow(int base, int exp, int modulus) {
  base %= modulus;
  int result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

int arrLength;

int* encodeMsg(pair<int,int>* pubKey, string msg){
	int* arr = new int[msg.length()];
	arrLength = msg.length();
	for (int i = 0; i < msg.length(); ++i){
		arr[i]=modpow(msg[i],pubKey->first,pubKey->second);
	}
	return arr;
}

string decodeMsg(int* encodedMsg, pair<int,int>* pubKey){
	char* decodedMsg = new char[arrLength];
	for (int i = 0; i < arrLength ; ++i){
		decodedMsg[i] = modpow(encodedMsg[i],d,pubKey->second);
	}
	return decodedMsg;
}

int main(){
	pair<int,int>* pubKey = keys();
	cout<<"Public Key is "<<pubKey->first<<" "<<pubKey->second<<endl;
	cout<<"Enter msg: ";
	string msg;
	getline(cin,msg);
	int* encodedMsg = encodeMsg(pubKey,msg);
	cout<<"Encoded Msg is: ";
	for (int i = 0; i < arrLength; ++i){
		cout<<encodedMsg[i]<<" ";
	}
	cout<<endl;
	string decodedMsg = decodeMsg(encodedMsg,pubKey);
	cout<<"Decoded Msg is: "<<decodedMsg;
}