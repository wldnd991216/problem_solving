#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <string.h>



/*

 * %d %f %c %s \t

 * 5���� Ű���� �����ϱ�

 * ���ڿ��� �����̶� ��ġ���� ���� ��� return -1�� ���� ����ص� ��

 */



int vr_scanf(const char* str, void* a, void* b, void* c, void* d)
{
    char input_str[1024];  // �ӽ� ���ڿ�
    char* token;           // ���ڿ� �Ľ��� ���� ������
    int index = 0;         // ������ ������ �����ϱ� ���� �ε���

    // �Է� ���� ���ڿ��� input_str�� ����
    gets(input_str);

    // �Է� ���� ���ڿ��� ������ �������� �Ľ��Ͽ� ������ ����
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
            return -1; // �ε����� �� ���� �Ѿ ��� ���� ���
        }
        index++;
        token = strtok(NULL, str);
    }

    // �Էµ� ������ ������ ������ ���ĺ��� ���� ��� ���� ���
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