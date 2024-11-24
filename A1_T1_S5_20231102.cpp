// File:A1_T1_S5_20231102.cpp
// Purpose: solve A1 --> T1
// Author:Abdallah Gamal Rabie
// Section: S5
// ID:20321102
// TA:
// Date: 10 Oct 2024

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <random>
using namespace std;
//****************************************
//problem 1
string correctSentence(string Sentence) {
    if (Sentence.length() > 100) {
        return "Error: The sentence is longer than 100 characters.";
    }

    string corrected_sentence = "";
    bool lastWasSpace = false;
    bool firstLetter = true;

    for (int i = 0; i < Sentence.length(); ++i) {
        if (Sentence[i] == ' ') {
            if (!lastWasSpace) {
                corrected_sentence += ' ';
                lastWasSpace = true;
            }
        } else {
            if (firstLetter && isalpha(Sentence[i])) {
                corrected_sentence += toupper(Sentence[i]);
                firstLetter = false;
            }
            else {
                corrected_sentence += tolower(Sentence[i]);
            }
            lastWasSpace = false;
        }
    }

    if (corrected_sentence.back() != '.') {
        corrected_sentence += '.';
    }

    return corrected_sentence;
}
//**********************************************************
//problem 4
void find_and_print_primes(int N) {
    // Check if N is less than 2 and prompt for a valid input
    if (N < 2) {
        cout << "Enter a number greater than or equal to 2: ";
        cin >> N;
    }

    // Create a vector with numbers from 2 to N
    vector<int> numbers;
    for (int i = 2; i <= N; i++) {
        numbers.push_back(i);
    }

    // Helper function to check if a number is prime
    auto check_prime = [](int n) {
        if (n <= 1) {
            return false;
        }
        for (int i = 2; i <= n / 2; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    };

    // Vector to hold prime numbers
    vector<int> prime_numbers;

    // Find prime numbers and store them in the prime_numbers vector
    for (int i = 0; i < numbers.size(); i++) {
        if (check_prime(numbers.at(i))) {
            prime_numbers.push_back(numbers.at(i));
        }
    }

    // Output the prime numbers
    cout << "Prime numbers are: ";
    for (int i = 0; i < prime_numbers.size(); i++) {
        cout << prime_numbers.at(i) << " ";
    }
    cout << endl;
}
//****************************************************************
//problem 7
struct dominoT {
    int leftDots;
    int rightDots;
};

bool Can_Form_Chain_Theory(const vector<dominoT>& dominos) {
    unordered_map<int, int> dotCount;

    for (const auto& domino : dominos) {
        dotCount[domino.leftDots]++;
        dotCount[domino.rightDots]++;
    }

    int odd_Count = 0;
    for (const auto& count : dotCount) {
        if (count.second % 2 != 0) {
            odd_Count++;
        }
    }

    return (odd_Count == 0 || odd_Count == 2);
}

string get_memo_Key(const vector<bool>& used) {
    string key;
    for (bool u : used) {
        key += (u ? '1' : '0');
    }
    return key;
}

bool CanChain(vector<dominoT>& dominos, int current, vector<bool>& used, int lastRightDot, vector<dominoT>& result, unordered_map<string, bool>& memo) {
    if (current == dominos.size()) {
        return true;
    }

    string key = get_memo_Key(used);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    for (int i = 0; i < dominos.size(); i++) {
        if (!used[i]) {
            if (dominos[i].leftDots == lastRightDot) {
                used[i] = true;
                result.push_back(dominos[i]);
                if (CanChain(dominos, current + 1, used, dominos[i].rightDots, result, memo)) {
                    return memo[key] = true;
                }
                result.pop_back();
                used[i] = false;
            }
            else if (dominos[i].rightDots == lastRightDot) {
                used[i] = true;
                result.push_back({dominos[i].rightDots, dominos[i].leftDots}); // Add reversed domino to result
                if (CanChain(dominos, current + 1, used, dominos[i].leftDots, result, memo)) {
                    return memo[key] = true;
                }
                result.pop_back();
                used[i] = false;
            }
        }
    }

    return memo[key] = false;
}

void solveDominoChain() {
    int n;
    cout << "Enter the number of domino pieces: ";
    cin >> n;
    cin.ignore();

    vector<dominoT> dominos(n);
    cout << "Enter the domino pieces (left right) in one line:" << endl;
    string line;
    getline(cin, line);

    stringstream ss(line);
    for (int i = 0; i < n; i++) {
        ss >> dominos[i].leftDots >> dominos[i].rightDots;
    }

    if (!Can_Form_Chain_Theory(dominos)) {
        cout << "No valid domino chain can be formed ." << endl;
        return;
    }

    sort(dominos.begin(), dominos.end(), [](const dominoT& a, const dominoT& b) {
        return (a.leftDots + a.rightDots) < (b.leftDots + b.rightDots);
    });

    vector<bool> used(n, false);
    vector<dominoT> result;
    unordered_map<string, bool> memo;
    bool canFormChain = false;

    for (int i = 0; i < n; i++) {
        used[i] = true;
        result.push_back(dominos[i]);
        canFormChain = CanChain(dominos, 1, used, dominos[i].rightDots, result, memo);
        used[i] = false;
        if (canFormChain) break;
        result.pop_back();
    }

    if (canFormChain) {
        cout << "A valid domino chain can be formed!" << endl;
        for (const auto& domino : result) {
            cout << domino.leftDots << "|" << domino.rightDots << " ";
        }
        cout << endl;
    } else {
        cout << "No valid domino chain can be formed." << endl;
    }
}
//****************************************************************
// problem 10
void alternword() {
    auto is_it_txt = [](const wstring& filename) {
        if (filename.substr(filename.find_last_of(L".") + 1) != L"txt") {
            return filename + L".txt";  // Append ".txt" if not already present
        }
        return filename;
    };

    auto Lookup_Table = [](unordered_map<wstring, vector<wstring>>& lookupTable, const wstring& filename) {
        wifstream file(filename.data());
        file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
        if (!file.is_open()) {
            wcerr << L"Error opening lookup file!" << endl;
            return;
        }

        wstring line;
        while (getline(file, line)) {
            size_t colonPos = line.find(L':');
            if (colonPos != wstring::npos) {
                wstring word = line.substr(0, colonPos);
                wstring alternativesStr = line.substr(colonPos + 1);
                vector<wstring> alternatives;

                wstringstream ss(alternativesStr);
                wstring alternative;
                while (getline(ss, alternative, L',')) {
                    alternatives.push_back(alternative);
                }

                lookupTable[word] = alternatives;
            }
        }
    };

    auto replace_words = [](const wstring& message, const unordered_map<wstring, vector<wstring>>& lookupTable) {
        wstringstream iss(message);
        wstring word;
        wstring result;
        random_device rrd;
        mt19937 gen(rrd());

        while (iss >> word) {
            if (lookupTable.find(word) != lookupTable.end()) {
                uniform_int_distribution<> dis(0, lookupTable.at(word).size() - 1);
                result += lookupTable.at(word)[dis(gen)] + L" ";
            } else {
                result += word + L" ";
            }
        }

        return result;
    };

    unordered_map<wstring, vector<wstring>> lookupTable;
    wstring message;
    wstring lookupFilename, messageFilename, outputFilename;

    wcout << L"***Enter the lookup table file name *** \n ";
    getline(wcin, lookupFilename);
    wcout << L"***Enter the message file name *** \n ";
    getline(wcin, messageFilename);
    wcout << L"***Enter the output file name *** \n ";
    getline(wcin, outputFilename);

    lookupFilename = is_it_txt(lookupFilename);
    messageFilename = is_it_txt(messageFilename);
    outputFilename = is_it_txt(outputFilename);

    Lookup_Table(lookupTable, lookupFilename);

    wifstream messageFile(messageFilename.data());
    messageFile.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!messageFile.is_open()) {
        wcerr << L"Error opening message file!" << endl;
        return;
    }

    wstring line;
    while (getline(messageFile, line)) {
        message += line + L" ";
    }

    wstring alteredMessage = replace_words(message, lookupTable);

    wofstream outputFile(outputFilename.data());
    outputFile.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!outputFile.is_open()) {
        wcerr << L"Error opening output file!" << endl;
        return;
    }
    outputFile << alteredMessage;

    wcout << L"Done!" << endl;
}
//***************************************************************

int main() {
    int pn;
    cout << "Which one do you want \n (1) correct sentence \n (2) find prime numbers \n (3) Dominos \n (4) altern word \n";
    cin >> pn;
    cin.ignore();

    if (pn == 1) {
        string Sentence;
        cout << "Enter a sentence: \n";
        getline(cin, Sentence);

        string result = correctSentence(Sentence);
        cout << result << endl;
    }
    else if (pn == 2) {
        int N;
        cout << "Enter N: ";
        cin >> N;
        find_and_print_primes(N);
    }
    else if (pn == 3) {
        solveDominoChain();
    }
    else if (pn == 4) {
        alternword();

    }
    else {
        cout << "Invalid input! Please try again!" << endl;
    }
    return 0;



}