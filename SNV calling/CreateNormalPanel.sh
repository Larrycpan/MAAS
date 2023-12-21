#!/bin/bash

module load bioinformatics/gatk-4.1.9.0

gatk CreateSomaticPanelOfNormals -R ./reference/refdata-cellranger-arc-GRCh38-2020-A-2.0.0/fasta/genome.fa \
	-V gendb://pon_db \
	-O pon.vcf.gz
