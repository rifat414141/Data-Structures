#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int idx;
int Try[N][54];
int value(char ch)
{
    if (isupper(ch))
        return ch - 'A';
    else
        return ch - 'a' + 26;
}
void insert(string &word)
{
    int curr = 0;
    for (int i = 0; i < word.size(); ++i)
    {
        if (Try[curr][value(word[i])] == -1)
        {
            Try[curr][value(word[i])] = ++idx;
            memset(Try[idx], -1, sizeof(Try[idx]));
            Try[idx][52] = 0;
            Try[idx][53] = 0;
        }
        curr = Try[curr][value(word[i])];
        Try[curr][53]++;
    }
    Try[curr][52]+=1;
}
bool search(string &word)
{
    int curr = 0;
    for (int i = 0; i < word.size(); ++i)
    {
        if (Try[curr][value(word[i])] == -1)
        {
            return false;
        }
        curr = Try[curr][value(word[i])];
    }
    return Try[curr][52];
}
int countWordsEndingWith(string &word)
{
    int curr = 0;
    for (int i = 0; i < word.size(); ++i)
    {
        if (Try[curr][value(word[i])] == -1){
            return 0;
        }
        curr = Try[curr][value(word[i])];
    }
    return Try[curr][52];
}
void erase(string &word)
{
    if (!search(word))
        return;
    int curr = 0;
    for (int i = 0; i < word.size(); ++i)
    {
        curr = Try[curr][value(word[i])];
    }
    Try[curr][52]--;
}
int countWordsStartingWith(string &word)
{
    int curr = 0;
    for (int i = 0; i < word.size(); ++i)
    {
        if (Try[curr][value(word[i])] == -1)
            return 0;
        curr = Try[curr][value(word[i])];
    }
    return Try[curr][53];
}
