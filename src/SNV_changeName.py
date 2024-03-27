import os
import gzip

# Obtain all *vcf.gz files in the current directory
file_list = [filename for filename in os.listdir(".") if filename.endswith(".vcf.gz")]

for current_file in file_list:
    
    file_prefix = os.path.splitext(current_file)[0].split(".vcf")[0]

    
    tmp_file = f"{file_prefix}_tmp.vcf.gz"

    # Decompress current vcf file and write revised contents to a tmp file
    with gzip.open(current_file, 'rb') as f_in:
        with gzip.open(tmp_file, 'wb') as f_out:
            for line in f_in:
                decoded_line = line.decode('utf-8')
                if decoded_line.startswith("##tumor_sample"):
                    modified_line = decoded_line.replace("CRC-3-11773", file_prefix)
                    f_out.write(modified_line.encode('utf-8'))
                elif decoded_line.startswith("#CHROM"):
                    modified_line = decoded_line.replace("\tCRC-3-11773", "\t" + file_prefix)
                    f_out.write(modified_line.encode('utf-8'))
                else:
                    f_out.write(line)

    # Rename tmp file as the name of raw file
    os.rename(tmp_file, current_file)
