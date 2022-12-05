#include<iostream>
#include<math.h>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;
#define MAX 10000000
int arr[MAX];//prime numbers array in Eratosthenes.txt file 
int encryptKey[MAX];// values array in encryptKey.txt file
void deleteElement(int arr[], int &n, int x)
{
    int i;
    for (i=0; i<n; i++)
    if (arr[i] == x)
        break;
 
    // If x found in array
    if (i < n)
    {
    // reduce size of array and move all
    // elements on space ahead
        n = n - 1;
        for (int j=i; j<n; j++)
            arr[j] = arr[j+1];
    }      
}

int powMod(int b, int e, int n){//pow(M,e) mod n
    int r = 1;
    while(e != 0){
        if(e % 2 == 1){
            r = (r*b) %n;            
        }
        e = e /2;
        b = b * b % n;
    }
    return r;


}
void writeData(int e[], int n){
    ofstream o;
    o.open("encryptKey.txt");
    for (int i = 0; i < n; i++){
        o<<e[i]<<" ";
    }
    o.close();		   
}

int readData(){
    ifstream in;
    in.open("Eratosthenes.txt");
    int size;
    int i = 0;
    while(!in.eof()){
        in >> arr[i];
        i++;
    }
    size = i;
    in.close();
    return size;
}
int readData_2(){
    ifstream in;
    in.open("encryptKey.txt");
    int size;
    int i = 0;
    while(!in.eof()){
        in >> encryptKey[i];
        i++;
    }
    size = i;
    in.close();
    return size;
}

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

int random(int min, int max){
    
    int res = min + rand() % (max - min + 1) ;
    return res;
}
class RSAdemo{
    private:
        int p;
        int q;
    public:
        int text;
    //constructor
    public:
        RSAdemo(int p1, int p2){
            p = p1;
            q = p2;
        }
    // get, set methods
    public:
        void setP(int p1){
            p = p1;
        }

        void setQ(int p2){
            q = p2;
        }


        int getP(){
            return p;
        }

        int setQ(){
            return q;
        }
    //methods
    
        long long getN(){
            return p*q;
        }

        long long getPhi(){
            return (p-1)*(q-1);
        }

        void generateE(int n){//n parameter will be phi(n)
            int e[n-2];
            int j = 0;
            for(int i = 2; i < n; i++){
                e[j] = i;
                j++;
            }
            int size = sizeof(e)/sizeof(e[0]);
            int temp;
            //delete some elements which have gcd not equal 1
            for(int i = 0; i < size; i++){
                if(gcd(n, e[i] != 1)){
                    temp = e[i];
                    deleteElement(e, size, temp);
                }
            }
            writeData(e, size);
        } 

        int generateD(int e, int n){ // e is encryption key, n is phi(n) 
            int k = 1;
            double d;
            while(true){
                d= ((k*n)+1)*1.0/e;
                if(d == (int)d){
                    (int)d;
                    break;
                }
                k++;
            }
            return d;
        }

        int encryption(int msg, int e, int n){
           int cipher = powMod(msg, e, n);
           return cipher;
        }
        int decryption(int cipher, int d, int n){
            int msg = powMod(cipher, d, n);
            return msg;
        }


};

int main(){
    
    int prime[2];
    srand(time(NULL));
    for(int i = 0; i < 2; i++){
        prime[i] = arr[random(0, readData())];
    }
    cout<<"Two prime numbers: ";
    for(int i = 0; i < 2; i++){
        cout<<prime[i]<<" ";
    }
    cout<<"\n";
    RSAdemo key = RSAdemo(prime[0],prime[1]);
    int e, d, n, phi;
    n = key.getN();
    phi = key.getPhi();
    cout <<"n = "<<n<<"\n";
    cout <<"phi(n) = "<<phi<<"\n";

    key.generateE(phi);
    e = encryptKey[random(0, readData_2())];
    cout<<"Public key: "<<e<<" ,"<< n <<"\n"; 
    d = key.generateD(e, phi);
    cout<<"Private key: "<<d<<" ,"<< n <<"\n";

    int plain = 88;
    key.text = plain;
    int cipher = key.encryption(plain, e, n);
    int decipher = key.decryption(cipher, d, n);
    cout<<"Plain text value: "<< plain<<"\n";
    cout<<"Encrypt value: "<< cipher<<"\n";
    cout<<"Decrypt value: "<< decipher<<"\n";

    return 0;
}
 