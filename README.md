# Coverage Variance #

Fast C program to get coverage variance from a BED file.

## Input file ##

BED file

    Sequence\tPosition\tCoverage

### Make the input file with SamTools

If you have a newer version of SamTools, this way is simpler and faster.

    samtools depth -a recruitment.sorted.bam > coverage.txt

### Make the input file with BedTools

With BedTools, you can make this type of BED file like so

    genomeCoverageBed -d -split -ibam recruitment.sorted.bam -g contigs.lengths.txt > coverage.txt

Where `contig.lengths.txt` has these columns

    contig_name\tlength

## Make & run it ##

    git clone https://github.com/mooreryan/coverage_variance.git

    cd coverage_variance

    make coverage_variance

    ./coverage_variance < my_file.bed > cov_variance.txt

### Everything can read from STDIN

All programs can read from stdin so you can pipe things like so....

    samtools depth -a recruitment.sorted.bam | coverage_variance | ruby cov_histo.rb > output

if you want.

## Output ##

    contig	contig.length	contig.read.cov.mean	contig.read.cov.pop.var	contig.read.cov.pop.sd	contig.read.cov.pop.coef.of.variation
    k99_1	375	1.200000	0.160000	0.400000	0.333333
    k99_2	383	1.563969	0.428342	0.654478	0.418473
    k99_3	325	1.381538	0.236696	0.486514	0.352154
    k99_4	353	1.696884	0.816354	0.903523	0.532460
    k99_5	666	3.821321	1.980623	1.407346	0.368288

## Coverage Histogram ##

You can use the ruby script `cov_histo.rb` to make a coverage histogram from the output of the `coverage_variance` program.
