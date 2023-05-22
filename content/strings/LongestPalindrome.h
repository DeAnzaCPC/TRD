/**
 * Author: Ralph
 * Description: 
 * Time: O(N)
 */

int lpr[MAXN * 2];

int main() {
  string str;
  cin >> str;

  string s = "|";

  for (int i = 0; i < str.length(); i++) {
    s += str[i];
    s += '|';
  }

  int center = 0;
  int radius = 0;

  while (center < s.length()) {
    while (center - radius >= 0 && center + radius < s.length() &&
           s[center - radius] == s[center + radius]) {
      radius++;
    }
    radius--;
    lpr[center] = radius;

    int oldCenter = center;
    int oldRadius = radius;
    center++;

    while (center <= oldCenter + oldRadius) {
      int mirroredCenter = oldCenter - (center - oldCenter);
      int largestRadius = oldCenter + oldRadius - center;
      if (lpr[mirroredCenter] < largestRadius) {
        lpr[center] = lpr[mirroredCenter];
        center++;
      } else if (lpr[mirroredCenter] > largestRadius) {
        lpr[center] = largestRadius;
        center++;
      } else {
        radius = largestRadius;
        break;
      }
    }
  }

  int maxi = 0;
  for (int i = 0; i < s.length(); i++) {
    if (lpr[i] > lpr[maxi])
      maxi = i;
  }

  for (int i = maxi - lpr[maxi] + 1; i <= maxi + lpr[maxi] - 1; i += 2) {
    cout << s[i];
  }
  cout << endl;
}