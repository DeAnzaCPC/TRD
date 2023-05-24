/**
 * Author: Ralph
 * Description: 
 */
// excludes points on the side of a hull
struct Point {
  int x, y;
};

// returns dist squared
int dist(Point a, Point b) {
  return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

Point p = {10005, 10005};

Point cows[50005];
int order[50005];
int hull[50005];

bool comp(int cow1, int cow2) {
  Point a = cows[cow1];
  Point b = cows[cow2];
  if ((a.x - p.x) * (b.y - p.y) > (b.x - p.x) * (a.y - p.y))
    return true;
  else if ((a.x - p.x) * (b.y - p.y) == (b.x - p.x) * (a.y - p.y)) {
    return dist(a, p) < dist(b, p);
  }
  return false;
}

bool ccw(int cow1, int cow2, int cow3) {
  Point p1 = cows[cow1];
  Point p2 = cows[cow2];
  Point p3 = cows[cow3];
  return (p1.x - p2.x) * (p3.y - p2.y) >= (p3.x - p2.x) * (p1.y - p2.y);
}

// checks if vector sides of convex hull with bases at i and j are ccw
// parallel means cw
bool ccwVect(int i, int j) {
  return (cows[hull[i + 1]].x - cows[hull[i]].x) *
             (cows[hull[j + 1]].y - cows[hull[j]].y) >
         (cows[hull[j + 1]].x - cows[hull[j]].x) *
             (cows[hull[i + 1]].y - cows[hull[i]].y);
}

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> cows[i].x >> cows[i].y;
    if (cows[i].y < p.y || (cows[i].y == p.y && cows[i].x < p.x))
      p = cows[i];
    order[i] = i;
  }

  sort(order, order + n, comp);

  int sz = 0;
  for (int i = 0; i < n; i++) {
    while (sz > 1 && ccw(hull[sz - 2], hull[sz - 1], order[i]))
      sz--;
    hull[sz++] = order[i];
  }
  hull[sz] = hull[0];
  hull[sz + 1] = hull[1];

  int j = 1, maxDist = 0;
  int ans[2] = {0, 0};
  for (int i = 0; i <= sz; i++) {
    while (ccwVect(i, j)) {
      j++;
      if (j >= sz)
        j -= sz;
    }
    int cur[2] = {min(hull[i], hull[j]), max(hull[i], hull[j])};
    if (dist(cows[hull[i]], cows[hull[j]]) > maxDist ||
        (dist(cows[hull[i]], cows[hull[j]]) == maxDist &&
         lexicographical_compare(cur, cur + 1, ans, ans + 1))) {
      maxDist = dist(cows[hull[i]], cows[hull[j]]);
      ans[0] = cur[0];
      ans[1] = cur[1];
    }
  }

  cout << ans[0] + 1 << " " << ans[1] + 1 << endl;
}
