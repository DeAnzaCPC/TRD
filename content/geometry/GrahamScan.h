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

Point p = {46000, 46000};

bool comp(Point a, Point b) {
  if ((a.x - p.x) * (b.y - p.y) > (b.x - p.x) * (a.y - p.y))
    return true;
  else if ((a.x - p.x) * (b.y - p.y) == (b.x - p.x) * (a.y - p.y)) {
    return dist(a, p) < dist(b, p);
  }
  return false;
}

bool ccw(Point p1, Point p2, Point p3) {
  return (p1.x - p2.x) * (p3.y - p2.y) >= (p3.x - p2.x) * (p1.y - p2.y);
}

Point holes[5005];
Point hull[5005];

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> holes[i].x >> holes[i].y;
    if (holes[i].y < p.y || (holes[i].y == p.y && holes[i].x < p.x))
      p = holes[i];
  }

  sort(holes, holes + n, comp);

  int sz = 0;
  for (int i = 0; i < n; i++) {
    while (sz > 1 && ccw(hull[sz - 2], hull[sz - 1], holes[i]))
      sz--;
    hull[sz++] = holes[i];
  }

  double ans = 0;
  for (int i = 1; i < sz; i++) {
    ans += sqrt(dist(hull[i - 1], hull[i]));
  }
  ans += sqrt(dist(hull[sz - 1], hull[0]));

  cout << fixed << showpoint << setprecision(2);
  cout << ans << endl;
}