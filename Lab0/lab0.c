/*
 * CO: Lab 0
 * Familiarize yourself with the workflow to modify, compile, and execute 
 * source files on a Linux environment.
 * This lab also will preview some of the major concepts we will cover
 * later in C.O.Project Fall 2024!
 *
 * Part 1: Number Representation and Bitwise Operators
 * Part 2: Pointer
 * Part 3: Structs
 * Part 4: Enumeration
 * Part 5: Macro Definition
 *
 */


/*
 * These #includes tell the compiler to include the named header files,
 * similar to imports in Java. The functions mentioned below are used
 * in our code.  Functions are like Java static methods that are not in
 * a class.
 *
 * assert.h - contains declaration of assert()
 * stdio.h  - contains declaration of printf()
 * stdlib.h - contains declaration of exit()
 * string.h - contains declaration of strcmp()
 *
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This #define tells the C preprocessor to do a straight substitution
 * of instances of the text "SIZE" in the code below with the text "500".
 * This example acts like a global variable without actually allocating
 * memory for a variable.
 *
 */
#define SIZE 500
#define uint16_t unsigned short
#define GetInstructionField(x,y) (((instruction) >> (y)) & \
                (((1) << (x - y + 1)) - (1)))


/* LOOK AT MAIN() AT THE BOTTOM OF THIS FILE FIRST */


/*
 * PART 1 - Number Representation and Bitwise Operators
 *
 * All data is internally stored as bits (binary digits).
 * The following operators perform computations using those bits:
 * ~ (NOT), & (AND), | (OR), ^ (XOR).
 * Here we play around with the binary representation of integers.
 *
 */
void part1()
{
        printf("*** LAB 0 PART 1 ***\n");

        /*
         * C has different integer datatypes, which determine the bit width
         * of the binary representation.
         * Here we use 'int', which is usually 32 bits wide, depending on
         * the system and programming language.
         *
         */
        int x=351, y=410;

        printf("x = %i\ny = %i\n", x, y);

        /*
         * Q1: The following line is an example. Feel free to copy and/or
         * modify it as needed for this lab.
         *
         */
        printf("x & x = %i\n", x & x);
}


/*
 * HELPER FUNCTION - fillArray()
 *
 * Fill a given array with values according to a formula.
 * C doesn't keep track of the length of arrays, so we have to specify it
 * as an explicit parameter (len), rather than looking it up from the array
 * as in Java.
 * The type of the array parameter here is int*, a pointer to an int. We'll
 * learn more about why int* is used here, but for now it is enough to
 * understand that "array" is an array of ints.
 *
 */
void fillArray(int *array, int len) 
{
        printf("Filling an array at address %p with %d "
                        "values\n", array, len);
        for (int i = 0; i < len; ++i) {
                array[i] = i * 3 + 2;
                /*
                 * assert() verifies that the given condition is true and
                 * exits the program otherwise. This is just a "sanity 
                 * check" to make sure that the line of code above is doing
                 * what we intend.
                 *
                 */
                assert(array[i] == i * 3 + 2);
        }
        printf("Done!\n");
}


/* PART 2 - Pointer */
void part2()
{
        printf("*** LAB 0 PART 2 ***\n");

        /** This is a block of memory big enough to store 10
         * ints. The name "array" here actually refers to the
         * address of this block of memory.
         * So, "array" itself is a pointer variable.
         * array[0] is the first int in this block of memory,
         * array[0] is equal to *(array).
         * array[1] is the second, and so on.
         * array[1] is equal to *(array + 1).
         * You need to make sure that you do not trigger array
         * access violation when using Pointers to access data,
         * such as *(array + 10), a.k.a. array[10].
         */
        int array[10];

        /** Q2A: What happens if the second argument is greater
         * than the size of the array (10)?
         */
        fillArray(array, 10);

        /* Use pointer to access value */
        for (int i = 0; i < 10; ++i) {
                printf("Array[%d] = %d\n", i, *(array + i));
        }

        int value = 351;


        /** In C, we can take the address of something using the
         * & operator. &value is of the type int*, meaning that
         * it is a pointer to an integer (it stores the address
         * in memory of where the actual int is located).
         */

        /** Q2B: Here we use the address of the variable "value"
         * as if it were an array of a single element. What data
         * is stored in value after the following code executes?
         * Think about why the result is what it is.
         */
        fillArray(&value, 1);
}



/** PART 3 Definition - Scores
 *
 * Structs are blocks of memory composed of smaller parts,
 * each of which has a name and is called a field. The
 * following struct definition has four int fields named
 * hw, lab, midterm, and final.
 * In this case, we use typedef to give structs of this
 * type a name, Scores, which can be used like we use
 * other types such as int or char.
 */
typedef struct {
        int hw;
        int lab;
        int midterm;
        int final;
} Scores;


/* PART 3 - Structs */
void part3()
{
        printf("*** LAB 0 PART 3 ***\n");

        /** The following creates an instance of Scores. The
         * space taken up in memory by student is equivalent
         * to an array of four ints, although we can refer to
         * the ints stored in it by name as well.
         */
        Scores student;

        /** Set the first int to have a value of 0 and verify
         *  that the value changed.
         */
        student.hw = 0;
        assert(student.hw == 0);

        /** Depending on whether or not you like to live
         *  dangerously, the following is either exciting or
         *  terrifying. Though &student is of type Scores* (a
         *  pointer to a Scores struct), we can use a cast to
         *  pretend that it is actually an array of integers
         *  instead.  It's all just memory after all!
         *  The "(int*)" tells the C compiler that we want to
         *  treat "&student" as an address of an int (in this
         *  case, the start of an array) rather than an address
         *  of a Scores struct.
         */
        fillArray((int*) &student, 4);

        /** We can confirm that fillArray updated the values
         * in the Scores struct:
         */
        assert(student.hw == 2);
        assert(student.lab == 5);
        assert(student.midterm == 8);
        assert(student.final == 11);


        /** Q3: Given that we were able to get our program to
         * treat &student as an int array, we should be able
         * to use array indexing syntax to access the struct 
         * values as well (this is possible, but not practical).
         * Uncomment and modify the left-hand side of the assert
         * statement below to use array indexing ([#]) so that
         * the condition passes.
         * Order of operations can be confusing, so parentheses
         * generally improve readability.
         */

        /* assert( student == 8 ); */
}


/** PART 4 Definition - bool
 *
 * There is no 'bool' type in C's basic data types.
 * We implement the 'bool' type by using enumeration.
 */
typedef enum {
        false = 0,
        true = 1
} bool;

/* PART 4 - enum */
void part4()
{
        printf("*** LAB 0 PART 4 ***\n");

        int imm5 = -25;
        bool ValidImm5 = true;

        if (imm5 > 15 || imm5 < -16)
                ValidImm5 = false;
        else
                ValidImm5 = true;

        if (ValidImm5)
                printf("Valid Imm5\n");
        else
                printf("Error: Invalid Imm5 : %d\n", imm5);

}

/* PART 5 - Macro Definition */
void part5()
{
        printf("*** LAB 0 PART 5 ***\n");

        /** ADD R2, R1, #0 in LC-3,
         *  0x1460 is its machine code
         */
        uint16_t instruction = 0x1460;
        int opcode = GetInstructionField(15, 12);

        printf("opcode is %d\n", opcode);
}

/*
 * main() is the entry point of the program. It has two parameters: 
 * argc is the number of arguments that were passed on the command line; 
 * argv is an array of those arguments as strings.
 * Strings in C are arrays of chars.
 *
 */
int main(int argc, char* argv[])
{
        /*
         * input checking - note that the executable name is included in
         * the argument count
         *
         */

        /* Corner case */
        if (!strcmp(argv[1], "0")) {
                printf("No part 0 in this lab!\n");
                exit(0);
        }

        if ( argc != 2 || !atoi(argv[1]) ) {
                printf("Usage: %s <num>\n", argv[0]);
                exit(0);
        }

        /*
         * atoi() is a library function that converts a String
         * to an integer
         *
         */
        switch(atoi(argv[1])) {
        case 1:   part1();
                  break;
        case 2:   part2();
                  break;
        case 3:   part3();
                  break;
        case 4:   part4();
                  break;
        case 5:   part5();
                  break;
        default:  printf("No part %s in this lab!\n", argv[1]);
                  exit(0);
        }

        return 0;
}
