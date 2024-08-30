#include "names.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum { DOT, LEFT, CENTER, RIGHT } Position;
const Position die[6] = { DOT, DOT, DOT, LEFT, CENTER, RIGHT };
int length = 0;

Position rolldie(void) {
    int r = random() % 6;
    Position roll = die[r];
    //printf("Roll: %d\n", roll);
    return roll;
}

void taketurn(Position roll, int player, int arr[]) {
    if (roll != DOT && arr[player] > 0) {
        if (roll == LEFT) {
            //printf("Left\n");
            arr[player] -= 1;
            if (player == length - 1)
                arr[0] += 1;
            else
                arr[player + 1] += 1;
        } else if (roll == RIGHT) {
            //printf("Right\n");
            arr[player] -= 1;
            if (player == 0)
                arr[length - 1] += 1;
            else
                arr[player - 1] += 1;
        } else if (roll == CENTER) {
            //printf("Center\n");
            arr[player] -= 1;
        }
    } else {
        //printf("Dot\n");
    }
    //printf("Ada has %d, Marg has %d, Kath has %d\n", arr[0], arr[1], arr[2]);
}

int checkWinner(int arr[]) {
    int values = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i] > 0) {
            values++;
        }
    }
    if (values > 1) {
        return 1;
    } else {
        return 0;
    }
}
int main(void) {
    int num_players = 3;
    printf("Number of players (3 to 10)? ");
    int scanf_result = scanf("%d", &num_players);
    if (scanf_result < 1 || num_players < 3 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        num_players = 3;
    }
    length = num_players;
    int players[num_players];
    int chips[num_players];
    for (int i = 0; i < num_players; i++) {
        players[i] = i;
        chips[i] = 3;
    }

    unsigned seed = 4823;
    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);
    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
        seed = 4823;
    }
    srandom(seed);
    int roll = 0;
    int stop = 0;
    int run = 0;
    while (stop == 0) {
        for (int i = 0; i < num_players; i++) {
            if (checkWinner(chips) == 1) {
                if (chips[i] > 0) {
                    run = chips[i];
                    for (int j = 0; j < run && j < 3; j++) {
                        if (checkWinner(chips) == 1) {
                            roll = rolldie();
                            taketurn(roll, i, chips);
                        }
                    }
                    printf("%s: ends her turn with %d\n", player_name[i], chips[i]);
                }
            } else {
                stop = 1;
                break;
            }
        }
    }
    for (int i = 0; i < length; i++) {
        if (chips[i] != 0) {
            printf("%s won!\n", player_name[i]);
        }
    }
    return 0;
}
