#include <bits/stdc++.h>
#define ll long long int
using namespace std;
struct Node
{
    Node *links[26];
    int countEnd = 0;
    int countPrefix = 0;
    bool contains(char c)
    {
        return links[c - 'a'] != NULL;
    }
    void put(char c, Node *node)
    {
        links[c - 'a'] = node;
    }
    Node *get(char c)
    {
        return links[c - 'a'];
    }
    void increaseEnd()
    {
        countEnd++;
    }
    void increasePrefix()
    {
        countPrefix++;
    }
    bool isEnd()
    {
        return countEnd;
    }
    void decreaseEnd()
    {
        countEnd--;
    }
    void decreasePrefix()
    {
        countPrefix--;
    }
};
class Trie
{
private:
    Node *root;

public:
    Trie()
    {
        root = new Node();
    }
    void insert(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (!node->contains(word[i]))
            {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
            node->increasePrefix();
        }
        node->increaseEnd();
    }
    bool search(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (!node->contains(word[i]))
                return false;
            node = node->get(word[i]);
        }
        return node->isEnd();
    }
    bool startswith(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (!node->contains(word[i]))
                return false;
            node = node->get(word[i]);
        }
        return true;
    }
    int countWordsEqualTo(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (!node->contains(word[i]))
                return 0;
            node = node->get(word[i]);
        }
        return node->countEnd;
    }
    int countWordsStartingWith(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (!node->contains(word[i]))
                return 0;
            node = node->get(word[i]);
        }
        return node->countPrefix;
    }
    void erase(string word)
    {
        if (!search(word))
            return;
        Node *node = root;
        for (int i = 0; i < word.size(); ++i)
        {
            node = node->get(word[i]);
            node->decreasePrefix();
        }
        node->decreaseEnd();
        return;
    }
};
int main()
{
    Trie t;
    t.insert("rifat");
    t.insert("rifat");
    t.insert("rifat");
    t.insert("rif");
    t.insert("apple");
    t.insert("apps");
    t.erase("rifat");
    t.erase("rifat");
    t.erase("rifat");
    cout << t.countWordsStartingWith("rif") << endl;
    return 0;
}
