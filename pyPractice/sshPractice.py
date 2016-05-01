import paramiko
import sys

nbytes = 4096
hostname = 'remote-linux.eos.ncsu.edu'
port = 22
username = 'bjschwa2' 
password = 'Bschwarz03'
command = 'ls'

client = paramiko.Transport((hostname, port))
client.connect(username=username, password=password)

stdout_data = []
stderr_data = []
session = client.open_channel(kind='session')
session.exec_command(command)
while True:
    if session.recv_ready():
        stdout_data.append(session.recv(nbytes))
    if session.recv_stderr_ready():
        stderr_data.append(session.recv_stderr(nbytes))
    if session.exit_status_ready():
        break

print ('exit status: ', session.recv_exit_status())
print (str(stdout_data))
print (str(stderr_data))

session.close()
client.close()