#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>

using namespace std;

int cou = 0;

//---------------------------------------------------------------------------------//

// brute-force approach
void search(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    for (int i = 0; i <= N - M; i++)
    {
        int j;
        for (j = 0; j < M; j++)
        {
            if (txt[i + j] != pat[j])
            {
                break;
            }
        }
        if (j == M)
        {
            cou++;
        }
    }
}

//---------------------------------------------------------------------------------//

// KMP approach
void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
void KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];
    computeLPSArray(pat, M, lps);
    int i = 0;
    int j = 0;
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
        if (j == M)
        {
            cou++;
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i = i + 1;
            }
        }
    }
}

//---------------------------------------------------------------------------------//

// Suffix-trie approach

#define MAX_CHAR 256

class SuffixTrieNode
{
private:
    SuffixTrieNode *children[MAX_CHAR];
    list<int> *indexes;

public:
    SuffixTrieNode()
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

//---------------------------------------------------------------------------------//

// Ranbin-Karp approach

#define d 256

void rksearch(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    for (i = 0; i < M - 1; i++)
    {
        h = (h * d) % q;
    }
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }
    for (i = 0; i <= N - M; i++)
    {
        if (p == t)
        {
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    break;
                }
            }
            if (j == M)
            {
                cou++;
            }
        }
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
            {
                t = (t + q);
            }
        }
    }
}

//---------------------------------------------------------------------------------//

// Automaton-Matcher approach

#define NO_OF_CHARS 256

int NextState(char *pat, int M, int state, int x)
{
    if (state < M && x == pat[state])
    {
        return state + 1;
    }
    int ns, i;
    for (ns = state; ns > 0; ns--)
    {
        if (pat[ns - 1] == x)
        {
            for (i = 0; i < ns - 1; i++)
            {
                if (pat[i] != pat[state - ns + 1 + i])
                {
                    break;
                }
            }
            if (i == ns - 1)
            {
                return ns;
            }
        }
    }
    return 0;
}
void computeTF(char *pat, int M, int TF[][NO_OF_CHARS])
{
    int state, x;
    for (state = 0; state <= M; ++state)
    {
        for (x = 0; x < NO_OF_CHARS; ++x)
        {
            TF[state][x] = NextState(pat, M, state, x);
        }
    }
}
void amsearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int TF[M + 1][NO_OF_CHARS];
    computeTF(pat, M, TF);
    int i, state = 0;
    for (i = 0; i < N; i++)
    {
        state = TF[state][txt[i]];
        if (state == M)
        {
            cou++;
        }
    }
}

//---------------------------------------------------------------------------------//

void dispalyAlgoName()
{

    cout << "\t\t\t\t\t       From the following list of String Matching Algorithms select one: " << endl;
    cout << "\t\t\t\t\t       1. Brutte Force Approach" << endl;
    cout << "\t\t\t\t\t       2. Knuth-Morris-Pratt Algorithm" << endl;
    cout << "\t\t\t\t\t       3. Sufix Trie Approach" << endl;
    cout << "\t\t\t\t\t       4. Rabin-Karp Algortihm" << endl;
    cout << "\t\t\t\t\t       5. Automaton-Matcher Approach \n\n" << endl;
}

int main()
{
    char txt[1000];
    char pat[1000];
    string rtxt;
    string rpat;
    system("CLS");
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t       STRING MATCHING ALGORITHMS \n\n";
    dispalyAlgoName();
    int ch;
    cout << "\t\t\t\t\t       Enter your choice: ";
    cin >> ch;
    system("CLS");

    do
    {        
        getchar();
        cout << "\t\t\t\t\t       Enter or paste the source text: \n\n";
        getline(cin,rtxt);
        cout << "\t\t\t\t\t       Enter or paste the text to be checked: \n\n";
        getline(cin,rpat);
        system("CLS");

        int len1 = rtxt.length();
        int len2 = rpat.length();
        strcpy(txt, rtxt.c_str());
        strcpy(pat, rpat.c_str());

        cout << "\n\n       TEXT: " << txt << "\n\n";
        cout << "       PATTERN: " << pat << "\n\n";

        if (ch == 1)
        {
            search(pat, txt);
            cout << "       Number of matches of \"" << pat << "\" is " << cou << endl << endl;
            float a=0.0,b=0.0;
            a = cou*len2*100;
            b = a/len1;
            cout<< "       Percentage similar : " << b <<"%" << endl;
            system("PAUSE");
            system("CLS");
            cou = 0;
        }
        else if (ch == 2)
        {
            KMPSearch(pat, txt);
            cout << "       Number of matches of \"" << pat << "\" is " << cou << endl << endl;
            float a=0.0,b=0.0;
            a = cou*len2*100;
            b = a/len1;
            cout<< "       Percentage similar : " << b <<"%" << endl;
            system("PAUSE");
            system("CLS");
            cou = 0;
        }
        else if (ch == 3)
        {
            SuffixTrie S(txt);
            S.search(pat);
            cout << "       Number of matches of \"" << pat << "\" is " << cou << endl << endl;
            float a=0.0,b=0.0;
            a = cou*len2*100;
            b = a/len1;
            cout<< "      Percentage similar : " << b <<"%" << endl;
            system("PAUSE");
            system("CLS");
            cou = 0;
        }
        else if (ch == 4)
        {
            int q = 13;
            rksearch(pat, txt, q);
            cout << "       Number of matches of \"" << pat << "\" is " << cou << endl << endl;
            float a=0.0,b=0.0;
            a = cou*len2*100;
            b = a/len1;
            cout<< "       Percentage similar : " << b <<"%" << endl;
            system("PAUSE");
            system("CLS");
            cou = 0;
        }
        else if (ch == 5)
        {
            amsearch(pat, txt);
            cout << "       Number of matches of \"" << pat << "\" is " << cou << endl << endl;
            float a=0.0,b=0.0;
            a = cou*len2*100;
            b = a/len1;
            cout<< "       Percentage similar : " << b <<"%" << endl;
            system("PAUSE");
            system("CLS");
            cou = 0;
        }
        else
        {
            cout << "\t\t\t\t\t       Invalid Choice!" << endl;
            system("PAUSE");
            system("CLS");
        }
        int a;
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t       Press 0 to continue or -1 to exit: ";
        cin >> a;
        system("CLS");
        if (a == 0)
        {
            cout << "\n\n\n\n\n\n\n\n";
            dispalyAlgoName();
            cout << "\t\t\t\t\t       Enter your choice: ";
            cin >> ch;
            system("CLS");
        }
        else
        {
            exit(0);
        }
    } while (ch > 0);

    return 0;
}