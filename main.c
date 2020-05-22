#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PRICE 9

enum States
{
    q0 = 0,
    q1 = 1,
    q2 = 2,
    q3 = 3,
    q4 = 4,
    q5 = 5,
    q6 = 6,
    q7 = 7,
    q8 = 8,
    q9 = 9,
    q10 = 10
};

/* Metoda pokazujaca wszystkie stany automatu. */
void show_states(char **state_list, int len)
{
    printf("LISTA STANOW TO : [");

    int i;
    for(i=0; i < len+1; i++)
    {
        printf(" %s ", state_list[i]);
    }
    printf("]\n");
}

/* Funkcja dla kazdego stanu zwraca liste mozliwych stanow nastepnych */
int *get_transitions_for_state(enum States state){

        enum States *transition = malloc(3*sizeof(int));

        switch(state){
            case q0:
                transition[0] = q1;
                transition[1] = q2;
                transition[2] = q5;
                break;
            case q1:
                transition[0] = q2;
                transition[1] = q3;
                transition[2] = q6;
                break;
            case q2:
                transition[0] = q3;
                transition[1] = q4;
                transition[2] = q7;
                break;
            case q3:
                transition[0] = q4;
                transition[1] = q5;
                transition[2] = q8;
                break;
            case q4:
                transition[0] = q5;
                transition[1] = q6;
                transition[2] = q9;
                break;

            case q5:
                transition[0] = q6;
                transition[1] = q7;
                transition[2] = q10;
                break;
            case q6:
                transition[0] = q7;
                transition[1] = q8;
                transition[2] = q10;
                break;
            case q7:
                transition[0] = q8;
                transition[1] = q9;
                transition[2] = q10;
                break;
            case q8:
                transition[0] = q9;
                transition[1] = q10;
                transition[2] = q10;
                break;
            case q9:
            case q10:
                transition[0] = q10;
                transition[1] = q10;
                transition[2] = q10;
                break;
        }

        return transition;
}

/* Funkcja zwraca odpowiedni stan w oparciu o monete wrzucana jak i stan obecny */
enum States get_state(int* next_states, int input){
    switch(input){
        case 1:
            return next_states[0];
        case 2:
            return next_states[1];
        case 5:
            return next_states[2];
    }
};

int main()
{

    printf("BILETOMAT \n");
    printf("Bilet na Plywalnie kosztuje 9 zl \n");

    /* Stan poczatkowy - q0 */
    enum States state =q0;

    int counter = 0;

    char state_name[4] = "q0";

    /* Lista stanow */
    char **state_list = NULL;

    /* przypisanie do listy stanow stanu poczatkowego q0 */
    state_list = (char**)realloc(state_list, (counter+1)*sizeof(*state_list));
    state_list[counter] = (char*)malloc(sizeof(state_name));

    strcpy(state_list[counter], state_name);

    for(;;)
    {
        printf("Prosze wprowadzic monete 1 2 lub 5 zl \n\n");

        int input;
        char term;

        if(scanf("%d%c", &input, &term) == 2 && term == '\n')
        {
            /* Uzytkownik wrzuca monety 1 2 lub 5. Suma wrzuconych monet determinuje aktualny stan */
            if(input == 1 || input == 2 || input == 5)
            {
                counter++;

                int *ways = get_transitions_for_state(state);

                /* na podstawie monety okreslany jest dany stan*/
                state = get_state(ways, input);

                /* konwersja stanu na ciag znakow - usyte w tablicy stanow*/
                snprintf(state_name, 4, "q%d", state);

                /* Alokacja miejsca w tablicy na kolejne nazwy stanow */
                state_list = (char**)realloc(state_list, (counter+1)*sizeof(*state_list));
                state_list[counter] = (char*)malloc(sizeof(state_name));

                /* Dodanie aktualnego stanu (nazwy) do tablicy */
                strcpy(state_list[counter], state_name);

                printf("wrzucono %d zl \n", input);
                printf("aktualny stan to %s \n", state_name);

                /* Aktualna suma oparta na aktualnym stanie */
                printf("W sumie wrzucono %d zl \n", (int)state);

                /* Stan akceptujacy - uzytkownik wrzucil dokladnie 9 zl */
                if(state == q9)
                {
                    printf("Bilet zostaje wydany \n");
                    show_states(state_list, counter);
                    free(state_list);
                    return 1;
                }

                /* Stan nieakceptujacy - uzytkownik wrzucil wiecej niz 9 zl. Monety zostaja wydane */
                else if(state == q10)
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
