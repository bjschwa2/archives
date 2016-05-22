from pexpect import pxssh
import getpass
try:
    s = pxssh.pxssh()
    hostname = "@remote-linux.eos.ncsu.edu"
    username = "bjschwa2"
    password = 'Bschwarz03'
    s.login(hostname, username, password)
    s.sendline('uptime')   # run a command
    s.prompt()             # match the prompt
    print(s.before)        # print everything before the prompt. 
    s.logout()
except pxssh.ExceptionPxssh as e:
    print("pxssh failed on login.")
    print(e)