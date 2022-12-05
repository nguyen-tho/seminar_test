// C program for RSA asymmetric cryptographic
// algorithm. For demonstration values are
// relatively small compared to practical
// application
#include <bits/stdc++.h>
using namespace std;

// Returns gcd of a and b
int gcd(int a, int h)
{
	int temp;
	while (1) {
		temp = a % h;
		if (temp == 0)
			return h;
		a = h;
		h = temp;
	}
}
//public key in RSA encryption are 2 numbers n and e
double RSA_encrypt(int msg, int n, int e){
    // Encryption c = (msg ^ e) % n
    double c = pow(msg, e);
	c = fmod(c, n);

    return c;
}

bool isRelativePrime(int a, int b){
	if(gcd(a,b) == 1){
		return true;
	}
	else
		return false;
}

double RSA_decrypt(int cipher, int n, int d){
    // Decryption m = (c ^ d) % n
	double m = pow(cipher, d);
	m = fmod(m, n);

    return m;
}

// Code to demonstrate RSA algorithm
int main()
{
	// Two random prime numbers
	double p = 17;
	double q = 11;

	// First part of public key:
	double n = p * q;

	// Finding other part of public key.
	// e stands for encrypt
	double e = 7;
	double phi = (p - 1) * (q - 1);
	while (e < phi) {
		// e must be co-prime to phi and
		// smaller than phi.
		if (isRelativePrime(e,phi))
			break;
		else
			e++;
	}

	// Private key (d stands for decrypt)
	// choosing d such that it satisfies
	// d*e = 1 + k * totient
	//(d*e) mod phi = 1
	//d*e = 1 + k*phi  with 
	//d*e/phi = k

	//int k = 2; // A constant value
	double d;
	int k = 1;
	d = (1 + (phi*k)) / e;
	while (true){
		d = (1 + (phi*k)) / e;
		if(isRelativePrime(d,phi) && d<phi){
			break;
		}
		else{
			k++;
		}
	}
	
	
	//double d;

	// Message to be encrypted
	double msg = 88;

	printf("Message data = %lf", msg);

	
	double c = RSA_encrypt(msg, n, e);
	printf("\nEncrypted data = %lf", c);

	double m = RSA_decrypt(c, n, d);
	printf("\nOriginal Message Sent = %lf", m);

	return 0;
}
// This code is contributed by Akash Sharan.
