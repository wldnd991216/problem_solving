#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <string.h>



/*

 * %d %f %c %s \t

 * 5개의 키워드 구현하기

 * 문자열이 조금이라도 일치하지 않을 경우 return -1로 오류 출력해도 됨

 */



int vr_scanf(const char* str, void* a, void* b, void* c, void* d)
{
    char input_str[1024];  // 임시 문자열
    char* token;           // 문자열 파싱을 위한 포인터
    int index = 0;         // 지정된 변수를 저장하기 위한 인덱스

    // 입력 받은 문자열을 input_str에 저장
    gets(input_str);

    // 입력 받은 문자열을 지정된 형식으로 파싱하여 변수에 저장
    token = strtok(input_str, str);
    while (token != NULL) {
        switch (index) {
        case 0:
            sscanf(token, "%d", a);
            break;
        case 1:
            sscanf(token, "%c", b);
            break;
        case 2:
            sscanf(token, "%f", c);
            break;
        case 3:
            sscanf(token, "%s", d);
            break;
        default:
            return -1; // 인덱스가 네 개를 넘어갈 경우 오류 출력
        }
        index++;
        token = strtok(NULL, str);
    }

    // 입력된 변수의 개수가 지정된 형식보다 적을 경우 오류 출력
    if (index < 4) {
        return -1;
    }

    return 0;
}



int main()

{

    int a;

    char b;

    float c;

    char d[1024];



    printf("Enter values: ");



    int result = vr_scanf("%d|%c %f,%s", &a, &b, &c, d);



    if (result == 0)

        printf("Values entered: %d %c %f %s\n", a, b, c, d);

    else

        printf("Error\n");



    return 0;



}