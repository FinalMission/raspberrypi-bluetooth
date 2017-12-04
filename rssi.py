import subprocess
import time
import sys

CS_MAC = 'F4:0F:24:29:73:C0'
INTERVAL = 1

if(sys.argv[2]):
    INTERVAL = int(sys.argv[2])

while(1):
    subprocess.call('hcitool rssi {0}'.format(CS_MAC), shell=True)
    time.sleep(INTERVAL)
