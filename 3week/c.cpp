#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <conio.h>

using namespace std;

int roman_to_arabic(string roman) {
    map<char, int> roman_map = { {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000} };
    map<char, int> roman_map2 = { {'I', 10}, {'V', 10}, {'X', 100}, {'L', 100}, {'C', 1000}, {'D', 1000}, {'M', 10000} };
    vector<int> numGroup;
    int arabic = 0;
    char prev = ' ';
    int sameCount = 0;

    for (char c : roman) {
        if (c == prev) {
            sameCount++;
            if (sameCount == 3) {
                cout << "잘못된 입력1 - 4연타 중복입니다 (예시 IIII)" << endl;
                return -1;
            }
        }
        else {
            sameCount = 0;
        }
        if (roman_map.find(c) == roman_map.end()) {
            cout << "잘못된 입력2 - 로마숫자: 아닙니다." << endl;
            return -1;
        }
        if (prev != ' ' && roman_map[c] > roman_map[prev]) {
            if (roman_map2[c] / roman_map2[prev] <= 10) {
                arabic += roman_map[c] - 2 * roman_map[prev];
                numGroup[numGroup.size() - 1] = roman_map[c] - roman_map[prev];
            }
            else {
                cout << "잘못된 입력3 - 음수숫자와 양수숫자의 차이가 너무 큽니다" << endl;
                return -1;
            }
        }
        else {
            if (arabic + roman_map[c] >= floor(arabic / roman_map2[c]) * roman_map2[c] + roman_map2[c]) {
                cout << "잘못된 입력4 - 작은 자릿수 숫자로 큰 자릿수 변동시켰습니다." << endl;
                return -1;
            }
            arabic += roman_map[c];
            numGroup.push_back(roman_map[c]);
        }
        prev = c;
    }
    int max = numGroup[0];
    for (int i = 1; i < numGroup.size(); i++) {
        if (numGroup[i] > max) {
            cout << "잘못된 입력니다. - 큰수에서 작은 수 순서 위반" << endl;
            return -1;
        }
        max = numGroup[i];
    }
    return arabic;
}

int main() {
    string roman;

    while (true) {
        roman = "";
        cout << "로마숫자를 입력하세요. (종료하려면 'esc' 입력) ";
        while (true) {
            char c = _getch();
            if (c == 27) {
                return 0;
            }
            else if (c == 13) {
                break;
            }
            else if (c == 8) {
                if (roman.size() > 0) {
                    cout << c;
                    cout << " ";
                    cout << c;
                    roman.pop_back();
                }
            }
            else {
                roman.push_back(c);
                cout << c;
            }
        }
        cout << endl;

        int arabic = roman_to_arabic(roman);
        if (arabic != -1) {
            cout << "아라비아 숫자는 " << arabic << endl;
        }
    }

    return 0;
}
