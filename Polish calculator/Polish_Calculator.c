#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 100
struct polska
{
    float number[SIZE];
};


int main () 
{
    struct polska polskaKalkulacka [SIZE];
    memset(&polskaKalkulacka, 0, SIZE * sizeof(struct polska));

    int count = 0;

    for( int i = 0; i < SIZE; i++)
    {
        char symbol;
        float answer;
        char line [SIZE];
        char* r = fgets(line, SIZE, stdin);

        if(strlen(line) == 0)
        {
            printf("no input\n");
            return 0;
        }

        if (r == NULL)
        {
            printf("no input\n");
            return 0;
        }
        if (*r == EOF)
        {
            printf("no input\n");
            return 0;
        }
        
        char* end = NULL;
        float value = strtof(line, &end);
        
        if(line[0] == '.')
        {
            printf("bad input\n");
            break;
        }

        polskaKalkulacka->number[i] = value;
        symbol = line[0];
        if (polskaKalkulacka->number[i-1] == 0 && symbol == '/')
        {
            printf("division by zero\n");
            return 0;
        }
        
        if (line[0] > ';' || line[1] > ';' || line[2] > ';')
        {
                printf("bad input\n");
                break;
        }

        if (symbol == '/' || symbol == '+' || symbol == '-' || symbol == '*')
        {
            switch(symbol)
                    {
                        case '+':
                            answer = polskaKalkulacka->number[i - (i - 4)]+polskaKalkulacka->number[i - ( i - 3)];
                            polskaKalkulacka->number[i - (i - 4)] = answer;
                            // i = 0;
                            break;
                        case '-':
                            answer = polskaKalkulacka->number[i - (i - 4)]-polskaKalkulacka->number[i - (i - 3)];
                            polskaKalkulacka->number[i - (i - 4)] = answer;
                            // i = 0;
                            break;
                        case '/':
                            answer = polskaKalkulacka->number[i - (i - 4)]/polskaKalkulacka->number[i - (i - 3)];
                            polskaKalkulacka->number[i - (i - 4)] = answer;
                            // i = 0;
                            break;
                        case '*':
                            answer = polskaKalkulacka->number[i - (i - 4)]*polskaKalkulacka->number[i - (i - 3)];
                            polskaKalkulacka->number[i - (i - 4)] = answer;
                            // i = 0;
                            break;
                        default:
                        break;
                    }
        }
        count++;
        if (symbol != '/' || symbol != '+' || symbol != '-' || symbol != '*')
        {           
            for (int j = 0; j < count; j++)
            {
                    printf("%0.2f ", polskaKalkulacka->number[j]);    
            }
            printf("\n");
        }   
    }
}
