#vi /opt/scripts/system-info.sh

#!/bin/bash
echo -e "-------------------------------System Information----------------------------"
NOW=$(date +"%m-%d-%Y")
echo "$NOW"

echo -e "Hostname:\t\t"`hostname`
echo -e "System uptime:\t\t\t"`uptime | awk '{print $3,$4}' | sed 's/,//'`

echo -e "Main Memory Size" `grep MemTotal /proc/meminfo`
echo -e "Version:\t\t"`cat /sys/class/dmi/id/product_version`

echo -e "Machine Type:\t\t"`vserver=$(lscpu | grep Hypervisor | wc -l); if [ $vserver -gt 0 ]; then echo "VM"; else echo "Physical"; fi`
echo -e "Operating System:\t"`hostnamectl | grep "Operating System" | cut -d ' ' -f5-`
echo -e "Kernel:\t\t\t"`uname -r`
echo -e "Architecture:\t\t"`arch`


echo -e "Active User:\t\t"`w | cut -d ' ' -f1 | grep -v USER | xargs -n1`
echo -e "System IP address:\t\t"`hostname -I`
echo "------------------Number of jobs in kernal space-------------------------------"
ps -eo cmd,vsize,rss | grep -E ' 0 +0$' | wc -l
echo "------------------Number of jobs in user space-------------------------------"
jobs

echo -e "-------------------------------CPU/Memory Usage------------------------------"
echo -e "RAM Usage at  runninng insttances:\t"`free | awk '/Mem/{printf("%.2f%"), $3/$2*100}'`
 grep -m 1 'cpu cores' /proc/cpuinfo
echo -e "CPU Usage at runninng insttances:\t"`cat /proc/stat | awk '/cpu/{printf("%.2f%\n"), ($2+$4)*100/($2+$4+$5)}' |  awk '{print $0}' | head -1`
echo -e "CPU TYPE " `cat /proc/cpuinfo | grep 'vendor' | uniq`	
echo -e "CPU model name  " `cat /proc/cpuinfo | grep 'model name' | uniq`
echo ""

echo -e "-------------------------------Partions and disk usage--------------------------- "
df -h  
echo "----------------------------------TOTAL HARD DISK SIZE------------------------------" 
sudo fdisk -l | grep Disk

echo -e "-------------------------------For WWN Details-------------------------------"
vserver=$(lscpu | grep Hypervisor | wc -l)
if [ $vserver -gt 0 ]
then
echo "$(hostname) is a VM"




echo -e "-------------------------------Information about login users-------------------------------"
echo -e "List of Currently Login users" `w`

echo -e "List of USER ACCOUNT" 

cat /etc/passwd	

echo -e "LIST OF USER NAME ONLY"
awk -F':' '{ print $1}' /etc/passwd













echo -e "-----------------------------------------------------------------------------"
else

echo -e "-----------------------------------------------------------------------------"
fi
