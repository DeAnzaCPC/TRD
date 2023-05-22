/**
 * Author: Ralph
 * Description: 
 * Time: O(N)
 */

string removeLeadingZeros(string a) {
  for (int i = 0; i < a.length(); i++) {
    if (a[i] != '0' || i == a.length() - 1) {
      return a.substr(i);
    }
  }
  return a;
}

string add(string a, string b) {
  string res = "";
  int sum = 0;
  for (int i = 0; i < max(a.length(), b.length()); i++) {
    if (i < a.length())
      sum += a[a.length() - 1 - i] - '0';
    if (i < b.length())
      sum += b[b.length() - 1 - i] - '0';

    res = (char)((sum % 10) + '0') + res;

    sum /= 10;
  }
  if (sum == 1)
    res = "1" + res;

  return removeLeadingZeros(res);
}

string multiply(string a, string b) {
  string res = "0";
  for (int j = 0; j < b.length(); j++) {
    // multiply a by digit of b
    string curDig = "";
    for (int i = 0; i < j; i++) {
      curDig += "0";
    }

    int carry = 0;
    for (int i = 0; i < a.length(); i++) {
      carry += (a[a.length() - 1 - i] - '0') * (b[b.length() - 1 - j] - '0');

      curDig = (char)((carry % 10) + '0') + curDig;

      carry /= 10;
    }
    if (carry != 0)
      curDig = (char)((carry % 10) + '0') + curDig;

    res = add(res, curDig);
  }

  return removeLeadingZeros(res);
}