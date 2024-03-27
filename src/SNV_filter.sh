#!/bin/bash

module load bioinformatics/gatk-4.1.9.0
mkdir -p filtered_vcfs

vcf_files=(*.vcf.gz)

parallel -j 20 --no-notice \
	"gatk FilterMutectCalls \
	  -R ./reference/refdata-cellranger-arc-GRCh38-2020-A-2.0.0/fasta/genome.fa \
	  -V {} \
          -O filtered_vcfs/{.}.filtered.vcf.gz" ::: "${vcf_files[@]}"

