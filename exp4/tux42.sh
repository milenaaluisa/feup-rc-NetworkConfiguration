# Clean ARP tables
# Delete available routes

ifconfig eth0 172.16.41.1/24

echo 1 > /proc/sys/net/ipv4/ip_forward
echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts

route add default gw 172.16.41.254
route add -net 172.16.40.0/24 gw 172.16.41.253
