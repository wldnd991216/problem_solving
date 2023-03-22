#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// 로마 숫자를 아라비아 숫자로 변환하는 함수
int romanToDecimal(char romanNum[]) {
    int decimalNum = 0;
    int i, len = strlen(romanNum);

    for (i = 0; i < len; i++) {
        switch (toupper(romanNum[i])) {
            case 'I':
                if (toupper(romanNum[i+1]) == 'V' || toupper(romanNum[i+1]) == 'X')
                    decimalNum -= 1;
                else
                    decimalNum += 1;
                break;
            case 'V':
                decimalNum += 5;
                break;
            case 'X':
                if (toupper(romanNum[i+1]) == 'L' || toupper(romanNum[i+1]) == 'C')
                    decimalNum -= 10;
                else
                    decimalNum += 10;
                break;
            case 'L':
                decimalNum += 50;
                break;
            case 'C':
                if (toupper(romanNum[i+1]) == 'D' || toupper(romanNum[i+1]) == 'M')
                    decimalNum -= 100;
                else
                    decimalNum += 100;
                break;
            case 'D':
                decimalNum += 500;
                break;
            case 'M':
                decimalNum += 1000;
                break;
            default:
                printf("잘못된 입력입니다.\n");
                return -1;
        }
    }

    return decimalNum;
}

int main() {
    char romanNum[100];

    while (true) {
        printf("로마 숫자를 입력하세요 (ESC를 누르면 종료됩니다): ");
        fgets(romanNum, sizeof(romanNum), stdin);
        
        // 입력된 문자열의 마지막이 개행문자인 경우 이를 삭제
        if (romanNum[strlen(romanNum) - 1] == '\n') {
            romanNum[strlen(romanNum) - 1] = '\0';
        }

        // 입력된 문자열이 ESC인 경우 게임 루프를 종료
        if (strcmp(romanNum, "ESC") == 0) {
            break;
        }

        // 로마 숫자를 아라비아 숫자로 변환하여 출력
        int decimalNum = romanToDecimal(romanNum);
        if (decimalNum != -1) {
            printf("아라비아 숫자: %d\n", decimalNum);
        }
    }

    return 0;
}
