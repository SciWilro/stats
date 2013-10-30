#include <stdint.h>
#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>

double binom_2sided(int32_t succ, int32_t obs, double rate);
double binom_1sided(int32_t succ, int32_t obs, double rate);

int main(int argc, char** argv) {
  FILE* test_file;
  int32_t succ;
  int32_t obs;
  double rate;
  double p_value;
  char name[100];
  if ((argc == 4) || (argc == 5)) {
    succ = atoi(argv[1]);
    obs = atoi(argv[2]);
    if (sscanf(argv[3], "%lg", &rate) != 1) {
      printf("Error: Invalid expected success rate '%s'.\n", argv[3]);
      return 3;
    }
    if ((succ < 0) || (obs < 0) || (rate < 0)) {
      printf("Error: Negative parameter.\n");
      return 3;
    } else if (succ > obs) {
      printf("Error: # successes > # observations.\n");
      return 3;
    } else if ((rate == 0) || (rate >= 1)) {
      printf("Error: Invalid expected success rate '%s'.\n", argv[3]);
      return 3;
    }
    if (argc == 4) {
      p_value = binom_2sided(succ, obs, rate);
    } else {
      if (argv[4][1] || ((argv[4][0] != '+') && (argv[4][0] != '-'))) {
	printf("Error: Invalid alternative hypothesis ('+' = more successes, '-' = fewer)\n");
        return 3;
      }
      if (argv[4][0] == '+') {
        p_value = binom_1sided(obs - succ, obs, 1 - rate);
      } else {
        p_value = binom_1sided(succ, obs, rate);
      }
    }
    printf("P-value: %g\n", p_value);
    return 0;
  } else if (argc != 2) {
    printf(
"Binomial test    https://github.com/chrchang/stats\n"
"(C) 2013 Christopher Chang, GNU General Public License version 3\n\n"
"  binom_test [success ct] [total obs ct] [expected succ rate] <+ | ->\n"
"  binom_test [filename]\n\n"
"If a filename is provided, each line of the file is expected to contain an ID\n"
"in the first column, and then 3 values (in succ-obs-rate order).\n");
    return 1;
  }
  test_file = fopen(argv[1], "r");
  if (!test_file) {
    printf("Error: Unable to open file.\n");
    return 2;
  }
  while (!feof(test_file)) {
    fscanf(test_file, "%s %d %d %lg\n", name, &succ, &obs, &rate);
    p_value = binom_2sided(succ, obs, rate);
    printf("P-value for %s: %g\n", name, p_value);
  }
  fclose(test_file);
  return 0;
}
