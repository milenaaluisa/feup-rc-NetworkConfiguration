/interface bridge add name=bridge40
/interface bridge add name=bridge41

/interface bridge port remove [find interface=ether1]
/interface bridge port remove [find interface=ether12]
/interface bridge port remove [find interface=ether20]
/interface bridge port remove [find interface=ether22]

/interface bridge port add bridge=bridge40 interface=ether1
/interface bridge port add bridge=bridge40 interface=ether12
/interface bridge port add bridge=bridge41 interface=ether20
/interface bridge port add bridge=bridge41 interface=ether22
