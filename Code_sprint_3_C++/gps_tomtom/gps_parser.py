import subprocess
import re

def main():
	cmd = "cat /dev/ttyS0"
	t = 0
	p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
	stdout = []
	while t < 5 :
        	line = p.stdout.readline()
		stdout.append(line)
		t += 1
	to_be_parsed = ''.join(stdout)
	#print(to_be_parsed)
	print(parse(to_be_parsed))

#$GPGGA,183359.000,4334.2237,N,00127.9992,E
#GPGGA,191423.500,4334.2280,N,00127.9980,E

def parse(line_to_parse):
	pattern = "GPGGA,.*,.*,.*,.*,E"
	position = re.search(pattern, line_to_parse)
	#un-used1,un-used2,lat,lat_hemi,longi,longi_hemi = line_to_parse.split(",")
	un_used1,un_used2,lat,lat_hemi,longi,longi_hemi = str(position.group(0)).split(',')
	return "##latitude: {0} {1} ##longitude: {2} {3} ".format(lat,lat_hemi,longi,longi_hemi)
	#return position.group(0)
main()
