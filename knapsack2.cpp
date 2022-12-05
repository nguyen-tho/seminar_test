#include <iostream>
#include <math.h>
using namespace std;
/*
float max(float x, float y) {
   return (x > y) ? x : y;
}
*/
void knapSack(float W, float w[], float v[], int n) {
   float i, wt;
   float K[n + 1][(int)W + 1];
   for (i = 0; i <= n; i++) {
      for (wt = 0; wt <= W; wt++) {
         if (i == 0 || wt == 0)
         K[(int)i][(int)wt] = 0;
         else if (w[(int)i - 1] <= wt)
            K[(int)i][(int)wt] = max(v[(int)i - 1] + K[(int)i - 1][(int)(wt - w[(int)i - 1])], K[(int)i - 1][(int)wt]);
         else
        K[(int)i][(int)wt] = K[(int)i - 1][(int)wt];
      }
   }
   float cw = W, cn = n;// cw là khối lượng còn lại, cn là số vật còn lại
   cout<<"Item was selected: ";
   while(cw != 0 && cn != 0){
      if(K[(int)cn][(int)cw] != K[(int)cn-1][cw] ){
         cout<<cn<<" ";
         cw = cw - w[(int)cn-1];
      }
      cn--;
   }
   cout<<"\n";
   cout <<"Value of items was selected: "<< K[n][W];
}
float main() {
   cout << "Enter the number of items in a Knapsack:";
   float n, W;
   cin >> n;
   cout << "Enter the capacity of knapsack: ";
   cin >> W;
   float v[(int)n], w[(int)n];
   for (float i = 0; i < n; i++) {
      cout << "Enter weight and value for item " << i+1 << ":";
      cin >> w[(int)i];
      cin >> v[i];
   }
   knapSack(W, w, v, n);
   return 0;
}