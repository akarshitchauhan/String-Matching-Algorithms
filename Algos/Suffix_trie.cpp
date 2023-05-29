#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int cou = 0;
#define MAX_CHAR 256

class SuffixTrieNode
{
private:
    SuffixTrieNode *children[MAX_CHAR];
    list<int> *indexes;

public:
    SuffixTrieNode() // Constructor
    {

        indexes = new list<int>;

        for (int i = 0; i < MAX_CHAR; i++)
        {
            children[i] = NULL;
        }
    }

    void insertSuffix(string suffix, int index);

    list<int> *search(string pat);
};

class SuffixTrie
{
private:
    SuffixTrieNode root;

public:
    SuffixTrie(string txt)
    {

        for (int i = 0; i < txt.length(); i++)
        {
            root.insertSuffix(txt.substr(i), i);
        }
    }

    void search(string pat);
};

void SuffixTrieNode::insertSuffix(string s, int index)
{

    indexes->push_back(index);

    if (s.length() > 0)
    {

        char cIndex = s.at(0);

        if (children[cIndex] == NULL)
        {
            children[cIndex] = new SuffixTrieNode();
        }

        children[cIndex]->insertSuffix(s.substr(1), index + 1);
    }
}

list<int> *SuffixTrieNode::search(string s)
{

    if (s.length() == 0)
    {
        return indexes;
    }

    if (children[s.at(0)] != NULL)
    {
        return (children[s.at(0)])->search(s.substr(1));
    }

    else
        return NULL;
}

void SuffixTrie::search(string pat)
{
    list<int> *result = root.search(pat);

    if (result == NULL)
    {
        cout << "Pattern not found" << endl;
    }
    else
    {
        list<int>::iterator i;
        int patLen = pat.length();
        for (i = result->begin(); i != result->end(); ++i)
        {
            // cout << "Pattern found at position " << *i - patLen<< endl;
            cou++;
        }
    }
}

int main()
{
    char txt[] = "ABCCDDAEFG";
    char pat[] = "CDD";
    SuffixTrie S(txt);
    // printf("100%s100\n",txt );
    // char *pat = "ABABAAABAB";
    // char *pat ="learning";

    clock_t begin = clock();
    S.search(pat);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) * 1000 / CLOCKS_PER_SEC;
    // cout<<txt<<endl;
    cout << "Number of matches of \"" << pat << "\" is " << cou << endl
         << "Time taken:" << elapsed_secs << endl;
    cou = 0;

    return 0;
}