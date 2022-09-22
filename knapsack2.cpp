#include <iostream>
#include <math.h>
using namespace std;
/*
int max(int x, int y) {
   return (x > y) ? x : y;
}
*/
void knapSack(int W, int w[], int v[], int n) {
   int i, wt;
   int K[n + 1][W + 1];
   for (i = 0; i <= n; i++) {
      for (wt = 0; wt <= W; wt++) {
         if (i == 0 || wt == 0)
         K[i][wt] = 0;
         else if (w[i - 1] <= wt)
            K[i][wt] = max(v[i - 1] + K[i - 1][wt - w[i - 1]], K[i - 1][wt]);
         else
        K[i][wt] = K[i - 1][wt];
      }
   }
   int cw = W, cn = n;// cw là khối lượng còn lại, cn là số vật còn lại
   cout<<"Item was selected: ";
   while(cw != 0 && cn != 0){
      if(K[cn][cw] != K[cn-1][cw] ){
         cout<<cn<<" ";
         cw = cw - w[cn-1];
      }
      cn--;
   }
   cout<<"\n";
   cout <<"Value of items was selected: "<< K[n][W];
}
int main() {
   cout << "Enter the number of items in a Knapsack:";
   int n, W;
   cin >> n;
   cout << "Enter the capacity of knapsack: ";
   cin >> W;
   int v[n], w[n];
   for (int i = 0; i < n; i++) {
      cout << "Enter weight and value for item " << i+1 << ":";
      cin >> w[i];
      cin >> v[i];
   }
   knapSack(W, w, v, n);
   return 0;
}