#!/bin/bash

module load bioinformatics/gatk-4.1.9.0

bam_directory="./CRC/CRC-3-11773/raw_data/cancer.split.bam/"
ls "${bam_directory}"*.bam > bam_list.txt

operation() {
	  input_bam="$1"
	  output_file="${input_bam%.bam}.vcf.gz"
	  gatk Mutect2 -I "$input_bam" -R ./reference/refdata-cellranger-arc-GRCh38-2020-A-2.0.0/fasta/genome.fa \  
	                               -O "$output_file" --germline-resource ./reference/GATK/af-only-gnomad.hg38.vcf.gz \ 
								   --panel-of-normals ./CRC/CRC-3-11773/analysis/3.SNV_calling/1.normal_panel/pon.vcf.gz
      }

export -f operation

cat bam_list.txt | parallel -j 60 --bar 'bash -c "operation {}"'


