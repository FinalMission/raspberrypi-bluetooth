import subprocess
import time
import sys

CS_MAC = 'F4:0F:24:29:73:C0'
INTERVAL = 1
sys.argv[1] = INTERVAL

if(sys.argv[1]):
    INTERVAL = int(sys.argv[1])

print("Running {0} with interval {1}".format(sys.argv[0], INTERVAL))

while(1):
    subprocess.call('hcitool rssi {0}'.format(CS_MAC), shell=True)
    time.sleep(INTERVAL)
