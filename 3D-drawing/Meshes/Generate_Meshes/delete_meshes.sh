cd ../
printf "deleting:\n"
ls *.bin
printf "last chance to abort\npress <enter> key to proceed\n"
read keypress
rm *.bin
printf "it is done\n"
