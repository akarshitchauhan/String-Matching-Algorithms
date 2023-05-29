#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int cou = 0;
#define d 256

/* pat -> pattern
    txt -> text
    q -> A prime number
*/
void search(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
    {
        h = (h * d) % q;
    }

    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
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

            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M)
                // printf("Pattern found at index %d \n", i);
                cou++;
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

int main()
{
    char txt[] = "ABCCDDAEFG";
    char pat[] = "CDD";
    int q = 13;
    clock_t begin = clock();
    search(pat, txt, q);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) * 1000 / CLOCKS_PER_SEC;
    cout << "Number of matches of \"" << pat << "\" is " << cou << endl
         << "Time taken:" << elapsed_secs << endl;
    cou = 0;

    return 0;
}