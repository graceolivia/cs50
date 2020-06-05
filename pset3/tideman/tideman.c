#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle_checker(int win, int lose);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        printf("\n");
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //check if vote matches candidate name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            //update rank
            ranks[rank] = i;
            return true;
        }
    }
    return false;


}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    // TODO
    for (int i = 0; i < candidate_count; i++)
        {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int x = ranks[i];
            int y = ranks[j];
            preferences[x][y] += 1;
        }

    }


    //tester
      for (int b = 0; b < candidate_count; b++)
        {
            for (int c = 0; c < candidate_count; c++)
            {
                printf("%i ", preferences[b][c]);

            }
            printf("\n");
        }


    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }

        }
    }

    //tester

    printf("The pairs: \n");
    for (int a = 0; a < pair_count; a++)
    {
        printf("Winner: %s with %i \n", candidates[pairs[a].winner], preferences[pairs[a].winner][pairs[a].loser]);
        printf("Loser: %s with %i \n\n", candidates[pairs[a].loser], preferences[pairs[a].loser][pairs[a].winner]);
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int differences[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        //make an array with all the differences
        int win = pairs[i].winner;
        int lose = pairs[i].loser;
        differences[i] = preferences[win][lose] - preferences[lose][win];
        printf("Difference: %i \n", differences[i]);
    }

    //reorder the differences array
    for (int j = 0; j < pair_count; j++)
    {
        int largest = j;
        for (int k = j + 1; k < pair_count; k++)
        {
            if (differences[k] > differences[j])
                largest = k;

        }
        int temp = differences[j];
        differences[j] = differences[largest];
        differences[largest] = temp;

        pair tempPair = pairs[j];
        pairs[j] = pairs[largest];
        pairs[largest] = tempPair;
    }


 //tester

    printf("Sorted:\n");
   for (int i = 0; i < pair_count; i++)
    {
         printf("Winner: %s with %i \n", candidates[pairs[i].winner], preferences[pairs[i].winner][pairs[i].loser]);
        printf("Loser: %s with %i \n\n", candidates[pairs[i].loser], preferences[pairs[i].loser][pairs[i].winner]);
    }

    return;
}



// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
        for(int i = 0; i < pair_count; i++)
        {
            if(!cycle_checker(pairs[i].winner, pairs[i].loser))
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
                printf("Locked: %i over %i \n", pairs[i].winner, pairs[i].loser);
            }
        }

    return;
}

bool cycle_checker(int win, int lose)
{
    //base case:
    if(locked[lose][win] == true)
    {
        return true;
    }

//recursion
    for(int i = 0; i < candidate_count; i++)
    {
        if ((locked[i][win]) == true)
        {
            if (cycle_checker(i, lose) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    bool isWinner;
    for (int i = 0; i < candidate_count; i++)
    {

        isWinner = true;
            for (int j = 0; j < candidate_count; j++)
            {
                if (locked[j][i] == true)
                {
                    isWinner = false;
                }
            }
            if (isWinner == true)
            {
                printf("%s\n", candidates[i]);
            }
    }
    return;
}

