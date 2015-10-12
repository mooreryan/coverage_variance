/*
  Copyright 2015 Ryan Moore
  Contact: moorer@udel.edu

  coverage_variance is free software: you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  coverage_variance is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with coverage_variance.  If not, see
  <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

int main(int argc, char *argv[])
{
  int lineno = 0;
  int idx = 0;
  int size = 100000; // 100,000 starting contig size
  int prev_pos, pos, cov, same_contig;
  double total_cov = 0;
  double mean = 0;
  double total_deviation = 0;
  double variance = 0;
  double sd = 0;
  double cv = 0;

  /* will handle an absurd 1000 char contig name */
  char *prev_contig = calloc(1000, sizeof(char));
  char *contig      = calloc(1000, sizeof(char));

  int *coverages    = calloc(size, sizeof(int));

  printf("contig\t"
         "contig.length\t"
         "contig.read.cov.mean\t"
         "contig.read.cov.pop.var\t"
         "contig.read.cov.pop.sd\t"
         "contig.read.cov.pop.coef.of.variation\n");

  while(scanf("%s\t%d\t%d", contig, &pos, &cov) == 3) {
    lineno += 1;

    if (pos > size) {
      /* fprintf(stderr, "DOUBLING SIZE\n"); */
      size *= 2;
      assert(size > 0);

      int *tmp = realloc(coverages, size * sizeof(int));
      assert(tmp != NULL);

      coverages = tmp;
      assert(coverages != NULL);
    }

    same_contig = strcmp(prev_contig, contig);

    if (same_contig == 0 || lineno == 1) {
      coverages[pos - 1] = cov;
      total_cov += cov;
    } else {
      /* do the stats */
      mean = total_cov / prev_pos;
      for (idx = 0; idx < prev_pos; idx++) {
        total_deviation +=
          (coverages[idx] - mean) * (coverages[idx] - mean);
      }
      variance = total_deviation / prev_pos;
      sd = sqrt(variance);
      cv = sd / mean;
      printf("%s\t%d\t%f\t%f\t%f\t%f\n",
             prev_contig,
             prev_pos,
             mean,
             variance,
             sd,
             cv);

      /* reset the variables */
      total_cov = 0;
      total_deviation = 0;
    }

    strcpy(prev_contig, contig);
    prev_pos = pos;
    lineno += 1;
  }

  /* get the last contig */
  /* do the stats */
  mean = total_cov / prev_pos;
  for (idx = 0; idx < prev_pos; idx++) {
    total_deviation +=
      (coverages[idx] - mean) * (coverages[idx] - mean);
  }
  variance = total_deviation / prev_pos;
  sd = sqrt(variance);
  cv = sd / mean;
  printf("%s\t%d\t%f\t%f\t%f\t%f\n",
         prev_contig,
         prev_pos,
         mean,
         variance,
         sd,
         cv);

  free(contig);
  free(prev_contig);
  free(coverages);

  return 0;
}
