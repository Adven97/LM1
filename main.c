#include <stdio.h>
#include <stdlib.h>
#define PRICE 9

/* Metoda pokazujaca wszystkie stany automatu. Liczba tych stanow jest rowna liczbie wrzuconych monet */
void show_states(char **state_list, int len)
{
    printf("LISTA STANOW TO : [");

    int i;
    for(i=0; i < len; i++)
    {
        printf(" %s ", state_list[i]);
    }
    printf("]");
}

int main()
{
    printf("BILETOMAT \n");
    printf("Bilet na Plywalnie kosztuje 9 zl \n");

    /* Stan poczatkowy q0 */
    char state[4] = "q0";

    /* Suma wrzuconych monet */
    int sum = 0;

    int counter = 0;

    /* Lista stanow */
    char **state_list = NULL;
    for(;;)
    {
        printf("Prosze wprowadzic monete 1 2 lub 5 zl \n");

        int input;
        char term;

        if(scanf("%d%c", &input, &term) == 2 && term == '\n')
        {
            /* Uzytkownik wrzuca monety 1 2 lub 5. Suma wrzuconych monet deteerminuje aktualny stan */
            if(input == 1 || input == 2 || input == 5)
            {
                sum+= input;

                /* Ustawienie aktualnego stanu */
                if(sum <= 9)
                {
                    snprintf(state, 4, "q%d", sum);
                }
                else
                {
                    snprintf(state, 4, "q%d", 10);
                }

                /* Alokacja miejsca w tablicy na kolejne stany */
                state_list = (char**)realloc(state_list, (counter+1)*sizeof(*state_list));
                state_list[counter] = (char*)malloc(sizeof(state));
                strcpy(state_list[counter], state);

                counter++;

                printf("wrzucono %d zl \n", input);
                printf("aktualny stan to %s \n", state);
                printf("W sumie wrzucono %d zl \n", sum);

                /* Stan akceptujacy */
                if(sum == PRICE)
                {
                    printf("Bilet zostaje wydany \n");
                    show_states(state_list, counter);
                    free(state_list);
                    return 1;
                }

                if(sum > PRICE)
                {
                    printf("Bilet nie zostaje wydany \n");
                    printf("Zwracam monety \n");
                    show_states(state_list, counter);
                    free(state_list);
                    return -1;
                }
            }

            /* Uzytkownik wrzuca nieakceptowalne przez automat monety. Zostaja one zwrocone. Program zostaje przerwany */
            else
            {
                printf("Wprowadzono symbol spoza alfabetu \n");
                printf("Wrzucony element zostanie wydany \n");
                return -1;
            }
        }

        /* Uzytkownik wrzuca nieakceptowalne przez automat monety. Zostaja one zwrocone. Program zostaje przerwany */
        else
        {
            printf("Wprowadzono symbol spoza alfabetu \n");
            printf("Wrzucony element zostanie wydany \n");
            return -1;
        }
    }
    return 0;
}
