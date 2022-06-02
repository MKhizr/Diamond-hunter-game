#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

//2413235
//Muhammad Khizr Shahid

void initializeBoards(int, char**, char**);
int randomDiamond();
int getGuessedCoordinates(int*, int*);
int checkDiamonds(int, int, char**);
int provideHints(int, int, char**, char**);
void displayUserBoard(char**);

int main () {
    int i, n, score, Tscore, Hscore = -999, flag1, flag2, round, found, bsize = 7;
    int row, column;
    char **DBoard, **UBoard, choice;



    //creating user board and the diamond board
    DBoard = (char **)malloc(sizeof(char *)*bsize);
    UBoard = (char **)malloc(sizeof(char *)*bsize);

    for (i = 0; i < bsize; i++) {
         DBoard[i] = (char *)malloc(sizeof(char)*bsize);
         UBoard[i] = (char *)malloc(sizeof(char)*bsize);
    }

    do {
        flag1 = 0;
        flag2 = 0;
        round = 1;
        found = 0;
        Tscore = 0;

        //initial headings
        printf("*DIAMOND HUNTER*\n");
        printf("Let's get started!\n");

        //gets the number of diamonds from the user
        printf("Enter the number of diamonds to hunt: ");
        fflush(stdin);
        scanf("%d", &n);

        //calling the initialize boards function
        initializeBoards(n, DBoard, UBoard);

        //condition so that the user does not play for more than 10 rounds at-most
        while ((round < 11) && (found != n)) {

            //prints round number
            printf("\nRound %d:\n", round);

            //this loop executes at-least once
            do {
                //calls the getGuessedCoordinates function and gets the coordinates guessed by the user for the diamonds
                flag1 = getGuessedCoordinates(&row, &column);
                //if the guessed coordinates are not within the range, 0 is returned meaning an error will be printed
                if (flag1 == 0) {
                    //error check
                    //error to be printed below
                    printf("Please enter valid values for the co-ordinates! (1-7,1-7)\n");
                }
                //if the guessed coordinates are within the range, 1 is returned meaning that it then goes on to check the coordinates
                else {
                    //calls the checkDiamonds function and checks whether the guessed coordinates match the diamond coordinates or not
                    //1 is for coordinates matched
                    //0 is for coordinates not matched
                    flag2 = checkDiamonds(row, column, DBoard);

                    //if the coordinates do not match, if condition is carried out
                    if (flag2 == 0) {
                        UBoard[(column - 1)][(row - 1)] = provideHints(row, column, DBoard, UBoard); //gives the hints to the user//
                        //0 is added to the score
                        score = 0;
                        Tscore += score;
                        //prints score for that turn
                        printf("You got %d points!\n", score);
                    }
                    //if the coordinates match, else if condition is carried out
                    else if (flag2 == 1){
                        found++;
                        UBoard[(column - 1)][(row - 1)] = '*';
                        //100 is added to the score
                        score = 100;
                        Tscore += score;
                        //prints the score
                        printf("You got %d points!\n", score);
                    }
                }
            } while (flag1 != 1);

            //total is printed
            printf("Your total is %d points!\n\n", Tscore);

            //user board is displayed
            displayUserBoard(UBoard);

            //round is incremented
            round++;
        }

        //if the number of diamonds found are not equal to the number of diamonds set be the user to find then this statement is printed
        if (found != n) {
            printf("You have run out of rounds! Game Over!\n");
        }
        //if the number of diamonds found are equal to the number of diamonds set be the user to find then this statement is printed
        else {
            printf("You have found all the diamonds! You Win!\n");
        }

        printf("Your score was: %d\n", Tscore);

        //if total score is greater than high score, then high score is set as total score
        if (Tscore > Hscore) {
            Hscore = Tscore;
        }

        //high score is printed
        printf("The High score is: %d\n", Hscore);

        do {

            //asks the user whether he/she wants to play again or not
            printf("Would you like to play again (Y/N)? ");
            fflush(stdin);
            scanf("%c", &choice);

        //types of input accepted for condition
        } while (((choice != 'y') && (choice != 'Y')) && ((choice != 'N') && (choice != 'n')));

        printf("\n\n");
    //types of input accepted for condition
    } while ((choice != 'n') && (choice != 'N'));

    return 0;
}

void initializeBoards (int n, char **DB, char **UB) {
    int i, j, x, y;

    //these for loops populates the board with '?' everywhere on the board
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            DB[i][j] = '?';
            UB[i][j] = '?';
        }
    }

    //this for loop populates the board with '*' on the random number generated by randomDiamond function for x and for y
    for (i = 0; i < n; i++) {
        //random diamond function used twice to generate value for row and column
        x = randomDiamond();
        y = randomDiamond();
        if ((DB[y][x]) == '?') {
            DB[y][x] = '*';
        }
        //this else prevents the wastage of any turn if repetition of numbers is produced
        else {
            i--;
        }
    }

}

int randomDiamond () {
    //generates random number to represent coordinate of the diamond
    return rand() % 7;
}

int getGuessedCoordinates (int *R, int *C) {
    int temp1, temp2;

    //asks the user to enter the coordinates of the diamond and takes the input
    printf("Enter the coordinates of the diamond: ");
    fflush(stdin);
    scanf("(%d,%d)", &temp1, &temp2);

    *R = temp1;     //Uses the pointer to assign value to relevant variable in main function
    *C = temp2;

    //conditions to make sure that the numbers are within the required range
    if ((temp1 < 1) || (temp1 > 7)) {
        return 0;
    }
    else if ((temp2 < 1) || (temp2 > 7)) {
        return 0;
    }
    else {
        return 1;
    }


}

int checkDiamonds (int R, int C, char **DB) {

    //array starts from 0 at back-end instead of 1 but the user enters the number without this knowledge so to fix that issue the following is done
    R -= 1;
    C -= 1;

    //these conditions check whether the coordinates guessed by the user matches the coordinates of the diamonds present or not

    //returns 0 as false if the guessed coordinates do not match
    if ((DB[C][R]) == '?') {
        return 0;
    }
    //returns 1 as true if the guessed coordinates match
    else if ((DB[C][R]) == '*') {
        return 1;
    }

}

int provideHints (int R, int C, char **DB, char **UB) {
    int temp1, temp2, count = 48;
    R -= 1;
    C -= 1;
    temp1 = C;
    temp2 = R;

    //consider the 0 position of array as 1 here for the comments

    //extreme left border side of the board(first column only) and excluding the first and last row of the first column
    if ((temp1 == 0) && ((temp2 != 0) && (temp2 != 6))) { //?

        //consists of 5 blocks only hence 5 if conditions as hints
        if (DB[temp1][(temp2 - 1)] == '*') {
            count++;
        }
        if (DB[temp1][(temp2 + 1)] == '*') {
            count++;
        }
        if (DB[(temp1 + 1)][(temp2 - 1)] == '*') {
            count++;
        }
        if (DB[(temp1 + 1)][temp2] == '*') {
            count++;
        }
        if (DB[(temp1 + 1)][(temp2 + 1)] == '*') {
            count++;
        }
    }

    //extreme right border of the board(last column only) and excluding the first and last row of the last column
    else if ((temp1 == 6) && ((temp2 != 0) && (temp2 != 6))) { //!

        //consists of 5 blocks only hence 5 if conditions as hints
        if (DB[temp1][(temp2 - 1)] == '*') {
            count++;
        }
        if (DB[temp1][(temp2 + 1)] == '*') {
            count++;
        }
        if (DB[(temp1 - 1)][(temp2 - 1)] == '*') {
            count++;
        }
        if (DB[(temp1 - 1)][temp2] == '*') {
            count++;
        }
        if (DB[(temp1 - 1)][(temp2 + 1)] == '*') {
            count++;
        }
    }

    //extreme top border side of the board(first row only) and excluding the  first and last column of the first row
    else if ((temp2 == 0) && ((temp1 != 0) && (temp1 != 6))) { //+
        //consists of 5 blocks only hence 5 if conditions as hints
        if (DB[(temp1 - 1)][(temp2 + 1)] == '*') {
            count++;
        }
        if (DB[(temp1 - 1)][temp2] == '*') {
            count++;
        }
        if (DB[temp1][(temp2 + 1)] == '*') {
            count++;
        }
        if (DB[(temp1 + 1)][temp2] == '*') {
            count++;
        }
        if (DB[(temp1 + 1)][(temp2 + 1)] == '*') {
            count++;
        }
    }

    //extreme lower side of the board(last row only) and excluding the first and last column of the last row
    else if ((temp2 == 6) && ((temp1 != 0) && (temp1 != 6))) { //x
        //consists of 5 blocks only hence 5 if conditions as hints
        if (DB[(temp1 - 1)][temp2] == '*') {
            count++;
        }
        if (DB[(temp1 - 1)][(temp2 - 1)] == '*') {
            count++;
        }
        if (DB[temp1][(temp2 - 1)] == '*') {
            count++;
        }
        if (DB[(temp1 + 1)][temp2] == '*') {
            count++;
        }
        if (DB[(temp1 + 1)][(temp2 - 1)] == '*') {
            count++;
        }
    }

    //rest of the remaining board
    else if (((temp1 > 0) && (temp1 < 6)) && ((temp2 > 0) && (temp2 < 6))) { //*
        if (DB[(temp1 - 1)][(temp2 - 1)] == '*') {
            count++;
        }
        if (DB[(temp1 - 1)][temp2] == '*') {
            count++;
        }
        if (DB[(temp1 - 1)][(temp2 + 1)] == '*') {
            count++;
        }
        if (DB[temp1][(temp2 - 1)] == '*') {
            count++;
        }
        if (DB[temp1][(temp2 + 1)] == '*') {
            count++;
        }
        if (DB[(temp1 + 1)][(temp2 - 1)] == '*') {
            count++;
        }
        if (DB[(temp1 + 1)][temp2] == '*') {
            count++;
        }
        if (DB[(temp1 + 1)][(temp2 + 1)] == '*') {
            count++;
        }
    }

    //the four extreme corners of the entire board
    else { //o

        //top left corner
        if ((temp1 == 0) && (temp2 == 0)) {
            if (DB[(temp1 + 1)][(temp2)] == '*') {
                count++;
            }
            if (DB[temp1][(temp2 + 1)] == '*') {
                count++;
            }
            if (DB[(temp1 + 1)][(temp2 + 1)] == '*') {
                count++;
            }
        }
        //lower left corner
        else if ((temp1 == 0) && (temp2 == 6)) {
            if (DB[(temp1 + 1)][(temp2)] == '*') {
                count++;
            }
            if (DB[temp1][(temp2 - 1)] == '*') {
                count++;
            }
            if (DB[(temp1 + 1)][(temp2 - 1)] == '*') {
                count++;
            }
        }
        //top right corner
        else if ((temp1 == 6) && (temp2 == 0)) {
            if (DB[(temp1 - 1)][(temp2)] == '*') {
                count++;
            }
            if (DB[temp1][(temp2 + 1)] == '*') {
                count++;
            }
            if (DB[(temp1 - 1)][(temp2 + 1)] == '*') {
                count++;
            }
        }
        //lower right corner
        else {
            if (DB[(temp1 - 1)][(temp2)] == '*') {
                count++;
            }
            if (DB[temp1][(temp2 - 1)] == '*') {
                count++;
            }
            if (DB[(temp1 - 1)][(temp2 - 1)] == '*') {
                count++;
            }
        }
    }

    return count;
}

void displayUserBoard (char **UB) {
    int x, y;

    //this function displays the user board
    printf("\t1\t2\t3\t4\t5\t6\t7\n\n");
    for (x = 0; x < 7; x++) {
        printf("%d", x + 1);
        printf("\t");
        for (y = 0; y < 7; y++) {
            printf("%c\t", UB[y][x]);
        }
        printf("\n\n");
    }
}
