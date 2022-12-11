# Clean ARP tables

ifconfig eth0 172.16.40.254/24
ifconfig eth1 172.16.41.253/24

route add default gw 172.16.41.254
