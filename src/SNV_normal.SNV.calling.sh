#!/bin/bash

module load bioinformatics/gatk-4.1.9.0

# Define the number of threads to use
num_threads=60

# Find all BAM files in the current directory and pass them to parallel for processing
input_bams=$(ls *.bam)
parallel -j $num_threads 'gatk Mutect2 -R ./reference/refdata-cellranger-arc-GRCh38-2020-A-2.0.0/fasta/genome.fa -I {} -max-mnp-distance 0 -O {.}.vcf.gz' ::: $input_bams

