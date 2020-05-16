#include <stdio.h>
#include <stdlib.h>

void show_states(int *state_list, int len){
    int i;
    int aa = sizeof(state_list);
    printf("\n %d \n\n", aa);

    printf("LISTA STANOW \n");
    for(i=0; i < len; i++){
        printf("stan q%d to %d \n", i+1, state_list[i]);
    }
}

int main()
{
    printf("BILETOMAT XD \n");
    int state = 0;
    int *state_list= malloc(sizeof(int));
    int counter = 0;

    for(;;)
    {
        int input;
        printf("Prosze wprowadzic monete 1 2 lub 5zl \n");
        scanf("%d", &input);

        if(input == 1 || input == 2 || input == 5)
        {
            state+= input;
            state_list[counter] = state;

            counter++;

            if(state == 9)
            {
                printf("Bilet wydany :D \n");
                show_states(state_list, counter);
                return 1;
            }
            if(state >= 10){
                state = 10;
                printf("Bilet nie zostaje wydany \n");
                printf("Zwracam monety \n");
                show_states(state_list, counter);
                return -1;
            }
            printf("wrzucono %d zl \n", input);
            printf("aktualny stan to %d \n", state);
        }

        //state_list = malloc(counter*sizeof(int));

    }
    return 0;
}
