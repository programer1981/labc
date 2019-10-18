#!/bin/bash
echo add alarm=1:
echo clean alarm=2:
read m
if [ $m -eq 1 ]; then
echo Enter hour 0-23
read a
echo Enter minute 0-59
read b
echo Enter date 1-31
read c
echo Enter month jan, feb etc
read e
echo Music will be played on $e $c at $a : $b
echo Enter directory of audiofile and name of file *.mp3
read pt
echo prefix
read p
echo $b $a $c $e "*" $pt "#$p">>/home/sasha/myscripts/cron.txt
crontab /home/sasha/myscripts/cron.txt
fi
if [ $m -eq 2 ]; then
read f
crontab -l | grep -v $f | crontab -
echo done1
fi
