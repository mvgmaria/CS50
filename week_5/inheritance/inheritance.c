// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents (like nodes) and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator. You can put NULL instead, it is a way of initializing the
    // rand() funciton
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *child = malloc(sizeof(person));

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person (link the child to the parent)
        child->parents[0] = parent0;
        child->parents[1] = parent1;

        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        // From the childs parents, we pull up his alleles, and randomly chose one between index 0 and 1, so we are taking one or the other from each one, to make the two alelles of the child
        child->alleles[0] = child->parents[0]->alleles[rand() % 2];
        child->alleles[1] = child->parents[1]->alleles[rand() % 2];
    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        child->parents[0] = NULL;
        child->parents[1] = NULL;

        // TODO: Randomly assign alleles
        child->alleles[0] = random_allele();
        child->alleles[1] = random_allele();
    }

    // TODO: Return newly created person
    return child;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    // in the rand function, if you want to define a min value, you should put it before the
    // function followed by the + sign, so: 1 + rand(). Because in the case of a random result of 0,
    // it will be summed to the min value If we dont do that, it will start at 0. rand() indicates a
    // random number, without restrictions, so to implement a range we have to do it ourselves. For
    // the max range, you are going to use the modulo operator, so that the next number is going to
    // determine said range. The result of the rand() is going to be divided by that number, and it
    // is going to return the remainder. For the remainder to have 2 numbers, the modulo should be
    // 100 or more (any number by 100 is going to have max 2 decimals/remainder numbers), and so on
    // also, the number of the modulo will never be included in the range (if we dont use the min
    // value to reach it after the modulo operation), because we will never have the same remainder
    // as the divisor (any number/10 will never have a remainder of 10, it would be 0 in that case)
    // for example: 1 + rand() % 10 is going to give me numbers from 1 to 10, following this
    // function: variable = inf_limit + rand() % (sup_limit + 1 - inf_limit)

    // this returns a random number between 0 and 2
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
