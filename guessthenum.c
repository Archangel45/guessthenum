#include <stdio.h>
#include <stdlib.h>

/* Gotta include these babies */
#include <editline/readline.h>
#include <histedit.h>

typedef struct {
	int min;
	int max;
	int secret_number;
} gen_num_t;

gen_num_t gen_range(int min, int max) {
	/* Set the structure */
	gen_num_t set_struct;

	set_struct.min = min;
	set_struct.max = max;

	/* BUG: I'm stupid enough to not know how to do a proper random range!
	 * Forgive me! >_< */
	set_struct.secret_number = rand() % max - min;

	return set_struct;
}

int gen_low(gen_num_t gen_struct, int lst) {
	/* Compare if lst < gen_struct.secret_number */
	return lst < gen_struct.secret_number;
}

int gen_high(gen_num_t gen_struct, int gtr) {
	/* Compare if gtr > gen_struct.secret_number */
	return gtr > gen_struct.secret_number;
}

int gen_exact(gen_num_t gen_struct, int ex) {
	/* Compare if ex == gen_struct.secret_number
	 * This means you have won. :) */
	return ex == gen_struct.secret_number;
}

int main(int argc, char** argv) {
	/* Initialize the struct and get a struct that
	 * number_rand.min is 1 and number_rand.max is 10.
	 *
	 * Secret number will not be shown by the user, unless
	 * they called number_rand.secret_number. ;) */

	gen_num_t number_rand = gen_range(1, 10);
	
	printf("Pick a number between %d-%d\n",
			number_rand.min, number_rand.max);

	/* Ahh... The eternal loop of death! */
	while (1) {

		/* Inform the user what range they should guess. */
		char* input = readline("Pick a number: ");
		add_history(input); /* Add it to the history incase you want to go back */

		if (gen_exact(number_rand, atoi(input))) {
			puts("Yay, you won! ^^");
			break;
		}

		else if (gen_low(number_rand, atoi(input))) {
			puts("Sorry, you gotta guess high! :P");
		}

		else if (gen_high(number_rand, atoi(input))) {
			puts("Sorry, you gotta guess low! :P");
		}
	}
	printf("The secret number was %d! :D\n", number_rand.secret_number);

	return(0);	
}
