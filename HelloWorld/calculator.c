#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_BIT_LENGTH 65  // 64��Ʈ ���� + ��ȣ ��Ʈ

// ������ ���ڿ��� ������Ű�� �Լ�
char* invert_bits(const char* bits) {
    size_t len = strlen(bits);
    char* inverted = malloc(len + 1);
    if (!inverted) return NULL;

    for (size_t i = 0; i < len; i++) {
        inverted[i] = (bits[i] == '0') ? '1' : '0';
    }
    inverted[len] = '\0';
    return inverted;
}

// 2�� ������ ����ϴ� �Լ�
char* two_complement(const char* bits) {
    char* inverted = invert_bits(bits);
    if (!inverted) return NULL;

    int len = (int)strlen(inverted);
    int carry = 1;
    for (int i = len - 1; i >= 0; i--) {
        if (inverted[i] == '1' && carry == 1) {
            inverted[i] = '0';
        }
        else if (inverted[i] == '0' && carry == 1) {
            inverted[i] = '1';
            carry = 0;
        }
        else {
            break;
        }
    }
    return inverted;
}

// ������ ������ ���ڿ��� ��ȯ�ϴ� �Լ�
char* int_to_bit(int num) {
    char* bits = malloc(MAX_BIT_LENGTH);
    if (!bits) return NULL;

    int index = MAX_BIT_LENGTH - 2;  // -2 for null terminator and sign bit
    int is_negative = (num < 0);

    if (is_negative) num = -num;

    do {
        bits[index--] = (num % 2) + '0';
        num /= 2;
    } while (num > 0 && index >= 0);

    // ���� ��Ʈ�� 0���� ä��
    while (index >= 1) {
        bits[index--] = '0';
    }

    // ��ȣ ��Ʈ ����
    bits[0] = is_negative ? '1' : '0';
    bits[MAX_BIT_LENGTH - 1] = '\0';

    if (is_negative) {
        char* temp = two_complement(bits);
        free(bits);
        return temp;
    }

    return bits;
}

// �� ������ ���ڿ��� ���ϴ� �Լ�
char* bit_add(const char* a, const char* b) {
    int len = (int)strlen(a);
    char* result = malloc(len + 1);
    if (!result) return NULL;

    int carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        result[i] = (sum % 2) + '0';
        carry = sum / 2;
    }
    result[len] = '\0';
    return result;
}

// ������ ���ڿ��� ������ ��ȯ�ϴ� �Լ�
int bit_to_int(const char* bits) {
    int result = 0;
    int is_negative = (bits[0] == '1');

    const char* bits_to_convert = bits;

    if (is_negative) {
        char* positive_bits = two_complement(bits);
        bits_to_convert = positive_bits;
    }

    for (size_t i = 1; i < strlen(bits_to_convert); i++) {
        result = (result << 1) | (bits_to_convert[i] - '0');
    }

    if (is_negative) {
        result = -result;
        free((char*)bits_to_convert);
    }

    return result;
}

long long multiply(int a, int b) {
    int result = 0;

    while (b != 0) {
        if (b & 1) {
            result += a;
        }
        a <<= 1;
        b >>= 1;
    }
    return result;
}

#include <stdio.h>

int divide(int dividend, int divisor) {
    int quotient = 0;

    if (divisor == 0) {
        printf("0���� ���� �� �����ϴ�.\n");
        return -1;
    }

    int sign = 1;
    if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0)) {
        sign = -1;
    }

    dividend = (dividend < 0) ? -dividend : dividend;
    divisor = (divisor < 0) ? -divisor : divisor;

    while (dividend >= divisor) {
        int temp = divisor;
        int multiple = 1;

        while (dividend >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }

        dividend -= temp;
        quotient += multiple;
    }
    return sign * quotient;
}


int sign_modes(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;
    if ((a < 0 && b < 0) || (a > 0 && b > 0))
        return 1;
    return -1;
}

void plus_minus_mod()
{
    int a, b;
    printf("�� ���� ������ �Է��ϼ���: ");
    scanf_s("%d %d", &a, &b);

    char* bit_a = int_to_bit(a);
    char* bit_b = int_to_bit(b);

    if (!bit_a || !bit_b) {
        printf("�޸� �Ҵ� ����\n");
        free(bit_a);
        free(bit_b);
        return;
    }

    //printf("A�� ������: %s\n", bit_a);
    //printf("B�� ������: %s\n", bit_b);

    char* sum_bits = bit_add(bit_a, bit_b);
    if (!sum_bits) {
        printf("���� ���� �� ���� �߻�\n");
        free(bit_a);
        free(bit_b);
        return;
    }

    /*printf("������ ��: %s\n", sum_bits);*/

    int result = bit_to_int(sum_bits);

    printf("���: %d\n", result);

    free(bit_a);
    free(bit_b);
    free(sum_bits);
}


void  mul_mod() {
    int x, y;
    printf("�� ���� ������ �Է��ϼ���: ");
    scanf_s("%d %d", &x, &y);

    long long result = multiply(x, y);
    printf("���: %lld\n", result);
}

void div_mod()
{
    int x, y;
    printf("�� ���� ������ �Է��ϼ���: ");
    scanf_s("%d %d", &x, &y);

    int quotient = divide(x, y);
    int remain = x - quotient * y;

    printf("��: %d ������: %d\n", quotient, remain);
    
}


int main(void) {
    int choice;

    while (1) {
        printf("���ϴ� ������ �����ϼ���:\n");
        printf("1. ����/����\n");
        printf("2. ����\n");
        printf("3. ������\n");
        printf("0. ����\n");
        printf("����: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            plus_minus_mod();
            printf("\n");
            break;
        case 2:
            mul_mod();
            printf("\n");
            break;
        case 3:
            div_mod();
            printf("\n");
            break;
        case 0:
            printf("���α׷��� �����մϴ�.\n");
            printf("\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �����ϼ���.\n");
            printf("\n");
            break;
        }
    }

    return 0;
}
