#include "Recursion.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Return the sum of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * solve the problem recursively and
 * use an "n-1" type of decomposition
 *
 * NOTE: This function will NOT be graded and is merely provided for practice.
 */
int sumNums1(int x[], int n, int *calls) {
  *calls += 1;
  // TODO: Your code here
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return x[*calls - 1];
  }

  return x[*calls - 1] + sumNums1(x, n-1, calls);
  
  return 0;
}

/*
 * Return the sum of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * n may be either odd or even
 * solve the problem recursively and
 * use an "n/2" type of decomposition
 *
 * NOTE: This function will NOT be graded and is merely provided for practice.
 */
int sumNums2(int x[], int n, int *calls) {
  *calls += 1;
  // TODO: Your code here
  if (n == 0) {
    return 0;
  }

  if (n == 1) {
    return x[0];
  }

  if (n%2 == 0) {
    return sumNums2(x, n/2, calls) + sumNums2(x + (n/2), n/2, calls);
  } else {
    return x[n/2] + sumNums2(x, n/2, calls) + sumNums2(x + (n/2) + 1, n/2, calls);
  }
  return 0;
}

/*
 * Write a recursive function that revereses a positive n-digit integer x.
 * For example, if x = 12345, the function should return 54321.
 * Hint: use pow() from math.h
 */
int reverse(int x, int n, int *calls) {
  *calls += 1;
  // TODO: Your code here
  if (n == 0) {
    return 0;
  }

  if (n == 1) {
    return x;
  }

  return (x%10)*pow(10, n-1) + reverse(x/10, n-1, calls);
  return 0;
}

/*
 * Given a linked list, remove all nodes that contain the character val
 * Don't forget to free memory for any nodes you remove
*/
Node* remove_nodes(Node* head, char val, int* calls) {
  *calls += 1;
  // TODO: Your code here
  if (head == NULL) {
    return head;
  }

  Node* newHead = NULL;
  if (head->data == val) {
    newHead = head->next;
    free(head);
    return remove_nodes(newHead, val, calls);
  } else {
    head->next = remove_nodes(head->next, val, calls);
    return head;
  }
}

/* You are given a list of item weights that represent the weight of the ith
 * index item You are also given a maximum weight that your bag can hold.
 * Return the total weight of the subset of items that maximize the total weight
 * of the bag without going over the maximum weight
 */
int knapsack(int weights[], int n, int max_weight, int *calls) {
  *calls += 1;
  // TODO: Your code here
  if (n == 0) {
    return 0;
  }

  if (n == 1) {
    if (weights[0] <= max_weight) {
      return weights[0];
    } else {
      return 0;
    }
  }

  int first = weights[0] + knapsack(weights+1, n-1, max_weight-weights[0], calls);
  int second = knapsack(weights+1, n-1, max_weight, calls);

  if (first <= max_weight && second <= max_weight) {
    return fmax(first, second);
  } else if (first <= max_weight) {
    return first;
  } else if (second <= max_weight){
    return second;
  } else {
    return 0;
  }

  return 0;
}

// Given a binary tree, return the weight of the least weight path (the path
// with the smallest sum of node values)
int least_weight_path(BinaryNode *root, int *calls) {
  *calls += 1;
  // TODO: Your code here
  if (root == NULL) {
    return 0;
  }

  if (root->left == NULL && root->right == NULL) {
    return root->data;
  } else if (root->left == NULL) {
    return root->data + least_weight_path(root->left, calls);
  } else if (root->right == NULL) {
    return root->data + least_weight_path(root->right, calls);
  } else {
    return root->data + fmin(least_weight_path(root->left, calls), least_weight_path(root->right, calls));
  }


  return 0;
}

bool is_win(char board[3][3], char player) {
  // (Optional but recommended) TODO: Your code here

  //Horizontal
  int winner = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] != player) {
        winner = 0;
        break;
      }
    }
    if (winner) {
      return true;
    }

    winner = 1;
  }

  //Vertical
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 3; i++) {
      if (board[i][j] != player) {
        winner = 0;
        break;
      }
    }
    if (winner) {
      return true;
    }
    winner = 1;
  }

  //Diagonal left to right
  int ind = 0;
  while (ind != 3) {
    if (board[ind][ind] != player) {
      winner = 0;
    }
    ind++;
  }
  if (winner) {
    return true;
  }
  winner = 1;

  //Diagonal right to left
  int colInd = 2;
  int rowInd = 0;
  while (colInd != -1) {
    if (board[rowInd][colInd] != player) {
      winner = 0;
    }
    colInd--;
    rowInd++;
  }
  if (winner) {
    return true;
  }

  return false;
}

/*
 * Given a tic-tac-toe board, return a Record struct that contains the number of
 * ways that X can win, the number of ways that O can win, and the number of
 * draws from the current board position.
 * The possible values of the board are 'X', 'O', and ' ' (space character for empty)
 */
Record tic_tac_toe(char board[3][3], bool is_x_turn, int *calls) {
    *calls += 1;
    // TODO: Your code here
    Record finalRecord = {0, 0, 0};
    Record returnedRecord = {0, 0, 0};
    
    if (is_win(board, 'X')) {
        finalRecord = {1, 0, 0};
        return finalRecord;

    } else if (is_win(board, 'O')) {
        finalRecord = {0, 0, 1};
        return finalRecord;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                if (is_x_turn) {
                    board[i][j] = 'X';
                } else {
                    board[i][j] = 'O';
                }
                returnedRecord = tic_tac_toe(board, !is_x_turn, calls);
                finalRecord.x_wins += returnedRecord.x_wins;
                finalRecord.o_wins += returnedRecord.o_wins;
                finalRecord.draws += returnedRecord.draws;

                board[i][j] = ' ';
            } else {
              if (i == 2 && j == 2 && finalRecord.x_wins == 0 && finalRecord.o_wins == 0 && finalRecord.draws == 0) {
                finalRecord.draws++;
              }
            }
        }
    }

    /*if (!finalRecord.x_wins && !finalRecord.o_wins) {
        finalRecord.draws++;
    }*/
  
    return finalRecord;
  }

/*int my_win(char board[3][3], char player) {
  // (Optional but recommended) TODO: Your code here
  int totalWins = 0;
  int winner = 1;
  //Horizontal
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] != player) {
        winner = 0;
        break;
      }
    }
    if (winner) {
      totalWins++;
    }
    winner == 1;
  }

  //Vertical
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 3; i++) {
      if (board[i][j] != player) {
        winner = 0;
        break;
      }
    }
    if (winner) {
      totalWins++;
    }
    winner == 1;
  }

  //Diagonal left to right
  int ind = 0;
  while (ind != 3) {
    if (board[ind][ind] != player) {
      winner = 0;
    }
    ind++;
  }
  if (winner) {
    totalWins++;
  }
  winner = 1;

  //Diagonal right to left
  int newInd = 2;
  while (ind != -1) {
    if (board[ind][ind] != player) {
      winner = 0;
    }
    ind--;
  }
  if (winner) {
    totalWins++;
  }

  //Done checking
  return totalWins;
}*/
