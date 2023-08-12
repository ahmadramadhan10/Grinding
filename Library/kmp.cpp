#include <iostream>
#include <vector>
using namespace std;

vector<int> buildFailureTable(const string& pattern) {
    vector<int> table(pattern.length(), 0);
    int i = 1;
    int j = 0;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[j]) {
            j++;
            table[i] = j;
            i++;
        } else {
            if (j != 0) {
                j = table[j - 1];
            } else {
                table[i] = 0;
                i++;
            }
        }
    }
    return table;
}

vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> table = buildFailureTable(pattern);
    vector<int> occurrences;
    int i = 0;
    int j = 0;

    while (i < text.length()) {
        if (text[i] == pattern[j]) {
            i++;
            j++;

            if (j == pattern.length()) {
                occurrences.push_back(i - j);
                j = table[j - 1];
            }
        } else {
            if (j != 0) {
                j = table[j - 1];
            } else {
                i++;
            }
        }
    }

    return occurrences;
}

int main() {
    string text = "ABCABCDABABCDABCDABDE";
    string pattern = "AACDABA";
    vector<int> positions = kmpSearch(text, pattern);

    if (positions.empty()) {
        cout << "Pattern not found in the text." << endl;
    } else {
        cout << "Pattern found at positions: ";
        for (int pos : positions) {
            cout << pos << " ";
        }
        cout << endl;
    }

    return 0;
}
