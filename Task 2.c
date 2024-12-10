#include <stdio.h>
#include <string.h>
#define B 12

struct Player {
    char playerName[50];
    int ballScores[B];
    int totalScore;
};

void displayMatchScoreboard(struct Player player1, struct Player player2) 
{
    float average_p1,average_p2;
    printf("\nMatch Scoreboard:\n");

    printf("\n%s's Performance:\n", player1.playerName);
    printf("Ball Scores: ");
    for (int i = 0; i < B; i++) {
        printf("%d ", player1.ballScores[i]);
    }
    printf("\nTotal Score: %d\n", player1.totalScore);
    average_p1=player1.totalScore/(float)B;
    printf("Average Score: %.2f\n", average_p1);

    printf("\n%s's Performance:\n", player2.playerName);
    printf("Ball Scores: ");
    for (int i = 0; i < B; i++) 
    {
        printf("%d ", player2.ballScores[i]);
    }
    printf("\nTotal Score: %d\n", player2.totalScore);
    average_p2=player2.totalScore/(float)B;//float used here as both total score and b are integers
    printf("Average Score: %.2f\n", average_p2);
}


void findWinner(struct Player player1, struct Player player2) 
{
    printf("\nWinner is: ");
    if (player1.totalScore > player2.totalScore) 
    {
        printf("%s\n", player1.playerName);
    } else if (player2.totalScore > player1.totalScore) 
    {
        printf("%s\n", player2.playerName);
    } else {
        printf("Tie!\n");
    }
}

void playGame(struct Player *player) {
    for (int i = 0; i < B; i++) {
        int score;
        printf("Enter score for ball %d: ", i + 1);
        scanf("%d", &score);

        if (score >= 0 && score <= 6) {
            player->ballScores[i] = score;
            player->totalScore += score;
        } else {
            player->ballScores[i] = 0;
            printf("Score is invalid and marked as 0.\n");
        }
    }
}

int main() {
    struct Player player1, player2;

    printf("Enter first player name: ");
    fgets(player1.playerName, sizeof(player1.playerName), stdin);
    player1.playerName[strcspn(player1.playerName, "\n")] = '\0';//removing newline character so fgets works properly

    printf("Enter second player name: ");
    fgets(player2.playerName, sizeof(player2.playerName), stdin);
    player2.playerName[strcspn(player2.playerName, "\n")] = '\0';//used to remove newline character

    player1.totalScore = 0;
    player2.totalScore = 0;

    printf("\n%s's turn:\n", player1.playerName);
    playGame(&player1);

    printf("\n%s's turn:\n", player2.playerName);
    playGame(&player2);

    displayMatchScoreboard(player1, player2);
    findWinner(player1, player2);

    return 0;
}
