# Coverage Variance #

Fast C program to get coverage variance from a BED file.

## Input file ##

BED file

    Sequence\tPosition\tCoverage

## Make & run it##

    git clone https://github.com/mooreryan/coverage_variance.git

    cd coverage_variance

    make coverage_variance

    ./coverage_variance < my_file.bed > cov_variance.txt

## Output ##

    contig	contig.length	contig.read.cov.mean	contig.read.cov.pop.var	contig.read.cov.pop.sd	contig.read.cov.pop.coef.of.variation
    k99_1	375	1.200000	0.160000	0.400000	0.333333
    k99_2	383	1.563969	0.428342	0.654478	0.418473
    k99_3	325	1.381538	0.236696	0.486514	0.352154
    k99_4	353	1.696884	0.816354	0.903523	0.532460
    k99_5	666	3.821321	1.980623	1.407346	0.368288
