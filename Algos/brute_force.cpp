#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
 
int cou=0; 
void search(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
  

    for (int i = 0; i <= N - M; i++)
    {
        int j;
        for (j = 0; j < M; j++)
        {
            if (txt[i+j] != pat[j])
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
  
int main()
{
    char txt[] = "ABCCDDAEFG";
    char pat[] = "CDD";
    search(pat, txt);
    cout<<"Number of matches of \""<<pat<<"\" is "<<cou<<endl<<endl;
    cou=0;

   return 0;
}