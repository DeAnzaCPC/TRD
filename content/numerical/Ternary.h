/**
 * Author: Sunho
 * Description: Ternary search
 */
int l = -1, r = n;
while (r - l > 1){
  int mid = (r + l)>>1;
  if (f(mid) > f(mid + 1)) 
    r = mid;
  else 
    l = mid; 
}
//lo + 1 is the answer