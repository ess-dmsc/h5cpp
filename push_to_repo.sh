#!/usr/bin/expect

set username [lindex $argv 0]
set password [lindex $argv 1]
set wait_time [lindex $argv 2]

spawn git push
expect "Username for 'https://github.com':"
send "$username\n"
expect "Password for 'https://cow-bot@github.com':"
send "$password\n"
sleep $wait_time
interact
