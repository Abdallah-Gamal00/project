#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

class StringSet {
private:
    vector<string> words;

    string Rephrase(const string& word) {
        string Rephrased;
        for (char c : word) {
            if (isalpha(c)) {
                Rephrased += tolower(c);
            }
        }
        return Rephrased;
    }

public:
    StringSet() = default;

    StringSet(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string word;
            while (file >> word) {
                word = Rephrase(word);
                if (!word.empty() && find(words.begin(), words.end(), word) == words.end()) {
                    words.push_back(word);
                }
            }
            file.close();
        }
    }
    StringSet(istream& input) {
        string word;
        while (input >> word) {
            word = Rephrase(word);
            if (!word.empty() && find(words.begin(), words.end(), word) == words.end()) {
                words.push_back(word);
            }
        }
    }
    void add_word(const string& word) {
        string normalized = Rephrase(word);
        if (!normalized.empty() && find(words.begin(), words.end(), normalized) == words.end()) {
            words.push_back(normalized);
        }
    }
    void remove_word(const string& word) {
        string normalized = Rephrase(word);
        words.erase(remove(words.begin(), words.end(), normalized), words.end());
    }
    void clear() {
        words.clear();
    }
    int size() const {
        return words.size();
    }
    void print_words() const {
        for (const auto& word : words) {
            cout << word << " ";
        }
        cout << endl;
    }
    StringSet operator+(const StringSet& other) const {
        StringSet result(*this);
        for (const auto& word : other.words) {
            if (find(result.words.begin(), result.words.end(), word) == result.words.end()) {
                result.words.push_back(word);
            }
        }
        return result;
    }
    StringSet operator*(const StringSet& other) const {
        StringSet result;
        for (const auto& word : words) {
            if (find(other.words.begin(), other.words.end(), word) != other.words.end()) {
                result.words.push_back(word);
            }
        }
        return result;
    }
    double similarity(const StringSet& other) const {
        int intersectionSize = (*this * other).size();
        int sizeA = this->size();
        int sizeB = other.size();

        if (sizeA == 0 || sizeB == 0) {
            return 0.0;
        }

        return intersectionSize / (sqrt(sizeA) * sqrt(sizeB));
    }
};
void displayMenu_1() {
    cout << "\nMenu 1 :\n";
    cout << "1. <<Load documents from files>>\n";
    cout << "2. <<Enter text directly>>\n";
    cout << "3. <<Run demo test cases>>\n";
    cout << "4. <<Exit>>\n";
    cout << "<<Enter your choice>>: ";
}
void displayMenu_2() {
    cout << "\nMenu 2 :\n";
    cout << "1. <<Add word to document>>\n";
    cout << "2. <<Remove word from document>>\n";
    cout << "3. <<Clear document>>\n";
    cout << "4. <<Show size of document>>\n";
    cout << "5. <<Show words in document>>\n";
    cout << "6. <<Back to Menu 1>>\n";
    cout << "<<Enter your choice>>: ";
}
void what_function(StringSet& doc) {
    int choice;
    do {
        displayMenu_2();
        cin >> choice;

        string word;
        switch (choice) {
            case 1:
                cout << "<<Enter word to add>>: ";
                cin >> word;
                doc.add_word(word);

                break;
            case 2:
                cout << "<<Enter word to remove>>: ";
                cin >> word;
                doc.remove_word(word);
                break;
            case 3:
                doc.clear();
                break;
            case 4:
                cout << "<<Size of document>>: " << doc.size() << endl;
                break;
            case 5:
                cout << "<<Words in document>>: ";
                doc.print_words();
                break;
            case 6:
                cout << "<<Back to Menu 1>>\n";
                break;
            default:
                cout << "<<Invalid choice>>\n";
        }
    } while (choice != 6);
}

void load_from_files() {
    string filename1, filename2;
    cout << "<<Enter the filename for Document 1>>: ";
    cin >> filename1;
    cout << "<<Enter the filename for Document 2>>: ";
    cin >> filename2;

    StringSet doc1(filename1);
    StringSet doc2(filename2);

    cout << "<<Words in Document 1>>: ";
    doc1.print_words();

    cout << "<<Words in Document 2>>: ";
    doc2.print_words();

    // Union and intersection of documents
    StringSet unionSet = doc1 + doc2;
    StringSet intersectionSet = doc1 * doc2;

    cout << "<<Union of Document 1 and 2>>: ";
    unionSet.print_words();
    cout << "<<Intersection of Document 1 and 2>>: ";
    intersectionSet.print_words();

    double sim = doc1.similarity(doc2);
    cout << "<<Similarity between Document 1 and 2>>: " << sim << endl;

    int docChoice;
    do {
        cout << "<<Which document do you want to perform additional actions on?>>\n";
        cout << "1. Document 1\n";
        cout << "2. Document 2\n";
        cout << "3. Back to Menu 1\n";
        cin >> docChoice;

        switch (docChoice) {
            case 1:
                what_function(doc1);
            break;
            case 2:
                what_function(doc2);
            break;
            case 3:
                cout << "<<Returning to Main Menu>>\n";
            break;
            default:
                cout << "<<Invalid choice>>\n";
        }
    } while (docChoice != 3);
}

void take_text() {
    cout << "<<Enter text for Document 1>>:\n";
    cin.ignore(); // Clear newline
    string text1;
    getline(cin, text1);
    istringstream stream1(text1);
    StringSet doc1(stream1);

    cout << "<<Enter text for Document 2>>:\n";
    string text2;
    getline(cin, text2);
    istringstream stream2(text2);
    StringSet doc2(stream2);

    cout << "<<Words in Document 1>>: ";
    doc1.print_words();

    cout << "<<Words in Document 2>>: ";
    doc2.print_words();

    StringSet unionSet = doc1 + doc2;
    StringSet intersectionSet = doc1 * doc2;

    cout << "<<Union of Document 1 and 2>>: ";
    unionSet.print_words();
    cout << "<<Intersection of Document 1 and 2>>: ";
    intersectionSet.print_words();

    double sim = doc1.similarity(doc2);
    cout << "<<Similarity between Document 1 and 2>>: " << sim << endl;

    int docChoice;
    do {
        cout << "<<Which document do you want to perform additional actions on?>>\n";
        cout << "1. Document 1\n";
        cout << "2. Document 2\n";
        cout << "3. Back to Menu 1\n";
        cin >> docChoice;

        switch (docChoice) {
            case 1:
                what_function(doc1);
            break;
            case 2:
                what_function(doc2);
            break;
            case 3:
                cout << "<<Returning to Menu 1>>\n";
            break;
            default:
                cout << "<<Invalid choice>>\n";
        }
    } while (docChoice != 3);
}

void demo_test_case() {
    cout << "Demo test case\n";
    istringstream demoText1("I went to Giza Zoo by bus");
    istringstream demoText2("I went to Orman Park by taxi");

    StringSet doc1(demoText1);
    StringSet doc2(demoText2);

    cout << "<<Words in Demo Document 1>>: ";
    doc1.print_words();

    cout << "<<Words in Demo Document 2>>: ";
    doc2.print_words();

    StringSet unionSet = doc1 + doc2;
    StringSet intersectionSet = doc1 * doc2;

    cout << "<<Union of Demo Document 1 and 2>>: ";
    unionSet.print_words();
    cout << "<<Intersection of Demo Document 1 and 2>>: ";
    intersectionSet.print_words();

    double sim = doc1.similarity(doc2);
    cout << "<<Similarity between Demo Document 1 and 2>>: " << sim << endl;

    int docChoice;
    do {
        cout << "<<Which document do you want to perform additional actions on?>>\n";
        cout << "1. Demo Document 1\n";
        cout << "2. Demo Document 2\n";
        cout << "3. Back to Menu 1\n";
        cin >> docChoice;

        switch (docChoice) {
            case 1:
                what_function(doc1);
            break;
            case 2:
                what_function(doc2);
            break;
            case 3:
                cout << "<<Returning to Menu 1>>\n";
            break;
            default:
                cout << "<<Invalid choice>>\n";
        }
    } while (docChoice != 3);
}
int main() {
    int choice;
    do {
        displayMenu_1();
        cin >> choice;

        switch (choice) {
            case 1:
                load_from_files();
                break;
            case 2:
                take_text();
                break;
            case 3:
                demo_test_case();
                break;
            case 4:
                cout << "<<Exiting program>>\n";
                return 0;
            default:
                cout << "<<Invalid choice>>\n";
        }
    } while (choice != 4);
}
