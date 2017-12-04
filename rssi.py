import subprocess
import time

CS_MAC = 'F4:0F:24:29:73:C0'

while(1):
    subprocess.call('hcitool rssi {0}'.format(CS-MAC), shell=True)
    time.sleep(1)
