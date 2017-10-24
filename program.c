/* Computer game Rosetta */

#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <time.h>

/* Prototype of function that forms a string.
'position' - position of spaceship in string, 'width' - width of string,
'probability' - probability of the appearence of an asteroid in cell
of the field. Returns new position of spaceship in the string */
unsigned char create_line(unsigned char position, unsigned char width, \
    float probability);

/* Prototype of function that prints string and performs delay for 100 ms.
'*line' - pointer to the first element of string characters array.
Returns nothing */
void print_line(char *line);

/* Main function that calls function create_line in a cycle.
'argc' - amount of command line arguments,
'*argv[]' - array of pointers to received arguments.
Returns code that corresponds either successful, or
failed execution to OS */
signed char main(unsigned char argc, char *argv[]) {

    unsigned char i;

    unsigned char width = 40;
    unsigned short int height = 80;
    float probability = 0.01;

    unsigned char position;

    if(argc > 1) {

        for(i = 1; i < argc; i += 2) {

            if(!strcmp(argv[i], "-w")) {

                width = (unsigned char)atoi(argv[i + 1]);

                if(width < 1 || width > 200) {

                    printf("Error: unacceptable value of width!\n");
                    exit(EXIT_FAILURE);
                }
            }

            if(!strcmp(argv[i], "-h")) {

                height = (unsigned short int)atoi(argv[i + 1]);

                if(height < 1) {

                    printf("Error: unacceptable value of height!\n");
                    exit(EXIT_FAILURE);
                }
            }

            if(!strcmp(argv[i], "-p")) {

                probability = (float)atof(argv[i + 1]);

                if(probability < 0 || probability > 1) {

                    printf("Error: unacceptable value of probability!\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    srand(time(0));

    printf("\n");

    position = width / 2;

    for(i = 0; i < height; i++) {

        position = create_line(position, width, probability);

        if(position == 201)
            exit(EXIT_SUCCESS);
    }

    printf("You have successfully overcome the distance!\n");
    exit(EXIT_SUCCESS);
}

/* Function that forms the string */
unsigned char create_line(unsigned char position, unsigned char width, \
    float probability) {

    unsigned char i;

    float local_probability;

    char *line = (char*)malloc(sizeof(char) * (width + 1));

    signed char deviation = (signed char)((rand() % 3) - 1);


    if((position + deviation) > -1 && (position + deviation) < width)
        position += deviation;

    for(i = 0; i < width; i++) {

        local_probability = (float)rand() / RAND_MAX;

        if(local_probability < probability)
            *(line + i) = '*';
        else
            *(line + i) = ' ';
    }

    *(line + width) = '\0';

    if(*(line + position) == '*') {

        *(line + position) = '@';

        print_line(line);

        printf("You have collision with an asteriod!\n");

        free(line);
        return 201;
    }

    *(line + position) = '+';

    if(*(line + position - 1) == '*' || *(line + position + 1) == '*')
        *(line + position) = '0';
    
    print_line(line);
    free(line);

    return position;
}

/* Function that prints a string */
void print_line(char *line) {

    printf("%s\n", line);

    usleep(100000);
}