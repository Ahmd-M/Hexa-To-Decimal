#include <stdio.h>
#include <string.h>
#define SIZE 255

int isHexa(char letter);
int isPossibleHexa(char previous, char double_previous);
long HexaToDecimal(char hex[SIZE]);

void main()
{
    int N;
    scanf("%d", &N);

    while (N--)
    {
        char HASH[SIZE], HEXAS[SIZE][SIZE];
        scanf("%s", HASH);

        int i, j, hexaChar, hexaString, flag = 0, LOCKED[SIZE];
        LOCKED[0] = -1;
        for (i = 2, j = hexaChar = hexaString = 0; HASH[i]; i++)
        {
            if (isPossibleHexa(HASH[i - 1], HASH[i - 2]) && (i - 2 != LOCKED[j]))
                flag = 1;
            if (flag)
            {
                if (isHexa(HASH[i]))
                {
                    HEXAS[hexaString][hexaChar++] = HASH[i];
                    if (!isHexa(HASH[i + 1]) || hexaChar == 8)
                    {
                        LOCKED[++j] = i;
                        HEXAS[hexaString++][hexaChar] = '\0';
                        hexaChar = flag = 0;
                    }
                }
                else
                    flag = 0;
            }
        }

        char hex[8];
        long decimal;
        i = -1;
        while (++i < hexaString) // hexaString = number of hexadecimals encountered + 1
        {
            strcpy(hex, HEXAS[i]);
            decimal = HexaToDecimal(hex);
            printf("0x%s %li\n", hex, decimal);
        }
    }
}

int isHexa(char letter)
{
    return (letter >= '0' && letter <= '9') ||
           (letter >= 'A' && letter <= 'F') ||
           (letter >= 'a' && letter <= 'f');
}

int isPossibleHexa(char previous, char double_previous)
{
    return (double_previous == '0') && (previous == 'x' || previous == 'X');
}

long HexaToDecimal(char hex[8])
{
    long decimal = 0;
    int i, base = 1, length = strlen(hex);

    for (i = --length; i >= 0; i--)
    {
        char letter = hex[i];
        if (letter >= '0' && letter <= '9')
            decimal += (letter - 48) * base;
        else if (letter >= 'A' && letter <= 'F')
            decimal += (letter - 55) * base;
        else
            decimal += (letter - 87) * base;
        base *= 16;
    }

    return decimal;
}
