#include <stdlib.h>
#include <string.h>
char* generateString(char* str1, char* str2) 
{
    int n = strlen(str1);
    int m = strlen(str2);
    int len = n + m - 1;

    char* word = (char*)malloc(len + 1);

    // Step 1: initialize with '?'
    for(int i = 0; i < len; i++) word[i] = '?';
    word[len] = '\0';

    // Step 2: apply 'T'
    for(int i = 0; i < n; i++) {
        if(str1[i] == 'T') {
            for(int j = 0; j < m; j++) {
                if(word[i + j] == '?' || word[i + j] == str2[j]) {
                    word[i + j] = str2[j];
                } else {
                    return ""; // conflict
                }
            }
        }
    }

    // Step 3: fill remaining with 'a'
    for(int i = 0; i < len; i++) {
        if(word[i] == '?') word[i] = 'a';
    }

    // Step 4: handle 'F'
    for(int i = 0; i < n; i++) {
        if(str1[i] == 'F') {

            // check if equal to str2
            int match = 1;
            for(int j = 0; j < m; j++) {
                if(word[i + j] != str2[j]) {
                    match = 0;
                    break;
                }
            }

            if(match) {
                // need to break it
                int changed = 0;

                for(int j = m - 1; j >= 0; j--) {
                    int pos = i + j;

                    // try changing this char
                    char original = word[pos];

                    for(char c = 'a'; c <= 'z'; c++) {
                        if(c == original) continue;

                        word[pos] = c;

                        // check all 'T' constraints still valid
                        int valid = 1;
                        for(int x = 0; x < n && valid; x++) {
                            if(str1[x] == 'T') {
                                for(int y = 0; y < m; y++) {
                                    if(word[x + y] != str2[y]) {
                                        valid = 0;
                                        break;
                                    }
                                }
                            }
                        }

                        if(valid) {
                            changed = 1;
                            break;
                        }
                    }

                    if(changed) break;
                    word[pos] = original; // revert
                }

                if(!changed) return ""; // cannot fix
            }
        }
    }

    return word;
    
}