#include <stdio.h>
#include <stdlib.h>
#define PRICE 9

/* Metoda pokazujaca wszystkie stany automatu. Liczba tych stanow jest rowna liczbie wrzuconych monet*/
void show_states(int *state_list, int len){
    printf("LISTA STANOW \n");
    int i;
    for(i=0; i < len; i++){
        printf("stan %d to %s \n", i+1, state_list[i]);
    }
}

int main()
{
    printf("BILETOMAT \n");
    printf("Bilet na Plywalnie kosztuje 9 zl \n");

    /* 0 oznacza stan poczatkowy q0*/
    char state[3] = "q0";
    int sum = 0;
    int counter = 0;
    char **state_list = NULL;
    for(;;)
    {
        printf("Prosze wprowadzic monete 1 2 lub 5zl \n");

        int input;
        scanf("%d", &input);

        /* Uzytkownik wrzuca monety 1 2 lub 5. Suma wrzuconych monet deteerminuje aktualny stan*/
        if(input == 1 || input == 2 || input == 5)
        {
            sum+= input;
            //state = "q"+sum;
            snprintf(state, 3, "q%d", sum); // puts string into buffer

            //state_list[counter][4] = state;
            state_list = (char**)realloc(state_list, (counter)*sizeof(*state_list));
            state_list[counter] = (char*)malloc(sizeof(state));
            strcpy(state_list[counter], state);

            counter++;

            printf("wrzucono %d zl \n", input);
            printf("aktualny stan to %s \n", state);
            printf("W sumie wrzucono %d zl \n", sum);

            if(sum == PRICE)
            {
                printf("Bilet zostaje wydany \n");
                show_states(state_list, counter);
                return 1;
            }
            if(sum > PRICE){
                snprintf(state, 3, "q%d", 10); // puts string into buffer
                printf("Bilet nie zostaje wydany \n");
                printf("Zwracam monety \n");
                show_states(state_list, counter);
                return -1;
            }


        }
        else{
            printf("Wprowadzono symbol spoza alfabetu \n");
        }
    }
    return 0;
}
