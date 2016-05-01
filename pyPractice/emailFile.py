# Import smtplib for the actual sending function
import smtplib

# Import the email modules we'll need
from email.mime.text import MIMEText
from email.parser import Parser

# Open a plain text file for reading.  For this example, assume that
# the text file contains only ASCII characters.
# fp = parse("textfile.txt")
# Create a text/plain message
# msg = MIMEText(fp.read())
# fp.close()

# me == the sender's email address
# you == the recipient's email address
# msg['Subject'] = 'The contents of %s' % msg
# msg['From'] = "bjschwa2@ncsu.edu"
# msg['To'] = "bjschwa2@ncsu.edu"


headers = Parser().parsestr('From: bschwa2@ncsu.edu\n'
        'To: bschwa2@ncsu.edu\n'
        'Subject: Test message\n'
        '\n'
        'Body would go here\n')

#  Now the header items can be accessed as a dictionary:
print('To: %s' % headers['to'])
print('From: %s' % headers['from'])
print('Subject: %s' % headers['subject'])

# Send the message via our own SMTP server.
s = smtplib.SMTP('localhost:1025')
s.send_message(headers)
s.quit()