stats
=====

Standalone functions for calculating Hardy-Weinberg equilibrium and Fisher
2x2/2x3 exact test statistics.

Test program compilation:

gcc -O2 snphwe2.c snphwe_test.c -o snphwe_test

gcc -O2 fisher.c fisher_test.c -o fisher_test

Test program usage examples:

  snphwe_test snphwe_test.txt

  snphwe_test 16 3 81

  fisher_test fisher_test.txt

  fisher_test 20 30 40 50 60 70

fisher.c is covered by GPLv3 (see the LICENSE file).  For snphwe2.c usage
rules, refer to the Abecasis Lab's SNP-HWE page at
http://sph.umich.edu/csg/abecasis/Exact .