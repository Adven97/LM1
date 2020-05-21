#include <stdio.h>
#include <stdlib.h>
#define PRICE 9
#define INITIAL_STATE 0

/* Metoda pokazujaca wszystkie stany automatu. Liczba tych stanow jest rowna liczbie wrzuconych monet*/
void show_states(int *state_list, int len)
{
    printf("LISTA STANOW \n");
    int i;
    for(i=0; i < len; i++)
    {
        printf("stan %d to q%d \n", i+1, state_list[i]);
    }
}

int main()
{
    printf("BILETOMAT \n");
    printf("Bilet na Plywalnie kosztuje 9 zl \n");

    /* 0 oznacza stan poczatkowy q0*/
    int state = INITIAL_STATE;
    int counter = 0;
    int *state_list= malloc(sizeof(int));

    for(;;)
    {
        printf("Prosze wprowadzic monete 1 2 lub 5zl \n");

        int input;
        scanf("%d", &input);

        /* Uzytkownik wrzuca monety 1 2 lub 5. Suma wrzuconych monet deteerminuje aktualny stan*/
        if(input == 1 || input == 2 || input == 5)
        {
            state+= input;

            /* Alokacja miejsca w tablicy na kolejne stany*/
            state_list = realloc(state_list, (counter+1)*sizeof(*state_list));
            state_list[counter] = state;

            counter++;

            printf("wrzucono %d zl \n", input);
            printf("aktualny stan to q%d \n", state);
            printf("W sumie wrzucono %d zl \n", state);

            /* Stan akceptujacy*/
            if(state == PRICE)
            {
                printf("Bilet zostaje wydany \n");
                show_states(state_list, counter);
                return 1;
            }

            /* Stan nieakceptujacy - -uytkownik wrzucil wiecej niz 9zl*/
            if(state > PRICE)
            {
                state = 10;
                printf("Bilet nie zostaje wydany \n");
                printf("Zwracam monety \n");
                show_states(state_list, counter);
                return -1;
            }
        }

        /* Uzytkownik wrzuca nieakceptowalne przez automat monety. Zostaja one zwrocone*/
        else
        {
            printf("Wprowadzono symbol spoza alfabetu \n");
            printf("Wrzucony element zostanie wydany \n");
        }
    }
    return 0;
}
