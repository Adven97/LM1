#include <stdio.h>
#include <stdlib.h>
#define PRICE 9

void show_states(int *state_list, int len){
    printf("LISTA STANOW \n");
    int i;
    for(i=0; i < len; i++){
        printf("stan %d to q%d \n", i+1, state_list[i]);
    }
}

int main()
{
    printf("BILETOMAT \n");
    printf("Bilet na Basen koszyuje 9 zl \n");
    int state = 0;
    int counter = 0;
    int *state_list= malloc(sizeof(int));
    for(;;)
    {
        printf("Prosze wprowadzic monete 1 2 lub 5zl \n");
        int input;

        scanf("%d", &input);

        if(input == 1 || input == 2 || input == 5)
        {
            state+= input;
            state_list[counter] = state;

            counter++;

            if(state == PRICE)
            {
                printf("Bilet wydany \n");
                show_states(state_list, counter);
                return 1;
            }
            if(state > PRICE){
                state = 10;
                printf("Bilet nie zostaje wydany \n");
                printf("Zwracam monety \n");
                show_states(state_list, counter);
                return -1;
            }

            printf("wrzucono %d zl \n", input);
            printf("aktualny stan to %d \n", state);
        }
        else{
            printf("Wprowadzono symbol spoza alfabetu \n");
            state_list[counter] = 10;
            counter++;
        }
    }
    return 0;
}
