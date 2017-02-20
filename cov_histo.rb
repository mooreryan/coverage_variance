#!/usr/bin/env ruby
Signal.trap("PIPE", "EXIT")

counts = Hash.new 0
ARGF.each_line do |line|
  unless line.start_with? "contig"
    ary = line.chomp.split "\t"

    mean_cov = ary[2].to_f.ceil

    counts[mean_cov] += 1
  end
end

total = counts.values.reduce(:+).to_f

cdf = 0

puts "cov.ceil\tcount\tpdf\tcdf"
counts.sort.each do |cov, count|
  pdf = count / total
  cdf += pdf
  printf "%s\t%s\t%.5f\t%.5f\n", cov, count, pdf, cdf
end
