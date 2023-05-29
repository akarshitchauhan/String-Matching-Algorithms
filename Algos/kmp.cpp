#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int cou = 0;
void computeLPSArray(char *pat, int M, int *lps);

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
            // printf("Found pattern at index %d \n", i-j);
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
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
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

int main()
{
    char txt[] = "ABCCDDAEFG";
    char pat[] = "CDD";

    clock_t begin = clock();
    KMPSearch(pat, txt);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) * 1000 / CLOCKS_PER_SEC;
    cout << "Number of matches of \"" << pat << "\" is " << cou << endl
         << "Time taken:" << elapsed_secs << endl;
    cou = 0;

    return 0;
}