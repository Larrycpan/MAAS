#!/bin/bash

module load bioinformatics/gatk-4.1.9.0

# Collect all generated VCF files
input_vcfs=$(find . -name "*.vcf.gz")

# Combine the individual VCF files using GenomicsDBImport
gatk --java-options "-Xmx1024g" GenomicsDBImport -R ./reference/refdata-cellranger-arc-GRCh38-2020-A-2.0.0/fasta/genome.fa \
	             -L ./reference/refdata-cellranger-arc-GRCh38-2020-A-2.0.0/star/chrNameLength_forGATKinterval.bed \
                     --genomicsdb-workspace-path pon_db \
		                    $(for vcf_file in $input_vcfs; do echo "-V $vcf_file"; done)
