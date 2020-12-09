/*
 * @Author              : NogiNonoka
 * @Date                : 2020-11-14 20:32:45
 * @FilePath            : /CodeShelf/String/StringCompare_Knuth-Morris-Pratt.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  String Compare
 *  Knuth-Morris-Pratt
 *  Time Complexity: O(N+M)
 */

#include <iostream>
#include <string>
using namespace std;
const int MAXN = 1e5 + 7;

struct KMP
{
    // Serach word in text and return pos
    // Time Complexity: O(N+M)
    string text;
    string word;

    int nxt[MAXN];

    void getNext()
    {
        int j = 0, k = -1;
        nxt[0] = -1;
        while (j < (int)word.length())
        {
            if (k == -1 || word[j] == word[k])
            {
                ++j;
                ++k;
                if (word[j] == word[k])
                    nxt[j] = nxt[k];
                else 
                    nxt[j] = k;
            }
            else 
                k = nxt[k];
        }
    }

    int kmp()
    {
        getNext();
        int i = 0, j = 0;
        while (i < (int)text.length() && j < (int)text.length())
        {
            if (j == -1 || text[i] == word[j])
            {
                ++i;
                ++j;
            }
            else 
                j = nxt[j];
        }
        if (j == (int)word.length())
            return i - j + 1;
        else
            return -1;
    }

#ifdef DEBUG
    void showNext()
    {
        for (int i = 0; i < word.length(); ++i)
        {
            cout << word[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < word.length(); ++i)
        {
            cout << nxt[i] << " ";
        }
    }
#endif
}kmp;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    return 0;
}