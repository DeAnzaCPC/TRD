/**
 * Author: Ralph
 * Description: 
 * Time: O(N)
 */

int order[2][MAXN], classes[2][MAXN], cnt[MAXN];
int n;

// sorts order by value in class
void countSort(int classCount) {
  fill(cnt, cnt + classCount, 0);
  for (int i = 0; i < n; i++) {
    cnt[classes[0][i]]++;
  }
  for (int i = 1; i < classCount; i++) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = n - 1; i >= 0; i--) {
    order[1][--cnt[classes[0][order[0][i]]]] = order[0][i];
  }
  swap(order[0], order[1]);
}

int main() {
  string str;
  cin >> str;
  n = str.length();

  int classCount = 26;
  for (int i = 0; i < n; i++) {
    order[0][i] = i;
    classes[0][i] = str[i] - 'a';
  }

  for (int i = -1, shift = 0; shift == 0 || (1 << i) < n;
       i++, shift = (1 << i)) {
    for (int j = 0; j < n; j++) {
      order[0][j] -= shift;
      if (order[0][j] < 0)
        order[0][j] += n;
    }
    countSort(classCount);
    classes[1][order[0][0]] = 0;
    classCount = 1;
    for (int j = 0; j < n; j++) {
      pair<int, int> cur = {classes[0][order[0][j]],
                            classes[0][(order[0][j] + shift) % n]};
      pair<int, int> prev = {classes[0][order[0][j - 1]],
                             classes[0][(order[0][j - 1] + shift) % n]};
      if (cur != prev)
        classCount++;
      classes[1][order[0][j]] = classCount - 1;
    }
    swap(classes[0], classes[1]);
  }

  cout << str.substr(order[0][0]) << str.substr(0, order[0][0]) << endl;
}