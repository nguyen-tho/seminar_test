// C++ program to print all primes smaller than or equal to
// n using Sieve of Eratosthenes
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
int n = 1000;


void writeData(bool prime[], int n){
    ofstream o;
    o.open("Eratosthenes.txt");
    for (int p = 2; p <= n; p++){
		if (prime[p]){
            cout << p << " ";
            
            o<<p<<" ";
        }
    }		
    
}

void SieveOfEratosthenes(int n)
{
   // ofstream o;
   // o.open("Eratosthenes.txt");
	// Create a boolean array "prime[0..n]" and initialize
	// all entries it as true. A value in prime[i] will
	// finally be false if i is Not a prime, else true.
	bool prime[n + 1];
	memset(prime, true, sizeof(prime));

	for (int p = 2; p * p <= n; p++) {
		// If prime[p] is not changed, then it is a prime
		if (prime[p] == true) {
			// Update all multiples of p greater than or
			// equal to the square of it numbers which are
			// multiple of p and are less than p^2 are
			// already been marked.
			for (int i = p * p; i <= n; i += p)
				prime[i] = false;
		}
	}

	// Print all prime numbers
	writeData(prime, n);
}

// Driver Code
int main()
{
	
	cout << "Following are the prime numbers smaller "
		<< " than or equal to " << n << endl;
	SieveOfEratosthenes(n);
	return 0;
}
