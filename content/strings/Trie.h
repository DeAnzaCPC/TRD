/**
 * Author: Ralph
 * Description: Trie
 * Time: O(N)
 */

struct Node {
  Node *children[26];

  bool isEnd;
};

// creates/initializes a new node
Node *getNode() {
  Node *pNode = new Node;
  for (int i = 0; i < 26; i++) {
    pNode->children[i] = nullptr;
  }
  pNode->isEnd = false;
  return pNode;
}

void ins(Node *r, string word) {
  Node *curNode = r;
  for (int i = 0; i < word.length(); i++) {
    if (curNode->children[word[i] - 'a'] == nullptr)
      curNode->children[word[i] - 'a'] = getNode();
    curNode = curNode->children[word[i] - 'a'];
  }

  curNode->isEnd = true;
}

// search function not written because it was not needed for the problem

// single struct
struct Node {
  Node *children[26];
  bool isEnd;

  // create empty node, also used to create root
  static Node *getNode() {
    Node *pNode = new Node;
    for (int i = 0; i < 26; i++) {
      pNode->children[i] = nullptr;
    }
    pNode->isEnd = false;
    return pNode;
  }

  // should only be used by root
  void insert(string word) {
    Node *curNode = this;
    for (int i = 0; i < word.length(); i++) {
      if (curNode->children[word[i] - 'a'] == nullptr)
        curNode->children[word[i] - 'a'] = getNode();
      curNode = curNode->children[word[i] - 'a'];
    }
    curNode->isEnd = true;
  }
};
