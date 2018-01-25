# RX-TX

The RX-TX toolset is used to measure the latency and jitter parameters of an ethernet connection.

## TX

### Synopsis
	Usage:
	  tx [OPTION...] DEVICE - transmit timestamped test packets

	Help Options:
	  -h, --help            Show help options

	Application Options:
	  -d, --destination     Destination MAC address
	  -i, --interval        Interval in milli seconds
	  -p, --prio            Set scheduler priority
	  -Q, --queue-prio      Set skb priority
	  -m, --memlock         Configure memlock (default is 1)
	  -P, --padding         Set the packet size
	  -v, --verbose         Be verbose
	  -V, --version         Show version inforamtion and exit

	This tool sends ethernet test packets.


## RX

### Synopsis

	Usage:
	  rx [OPTION...] DEVICE - receive timestamped test packets

	Help Options:
	  -h, --help          Show help options

	Application Options:
	  -v, --verbose       Be verbose
	  -q, --quiet         Suppress error messages
	  -s, --socket        Write packet results to socket
	  -e, --ethertype     Set ethertype to filter(Default is 0x0808, ETH_P_ALL is 0x3)
	  -f, --rxfilter      Set hw rx filterfilter
	  -p, --ptp           Set hw rx filterfilter
	  -V, --version       Show version inforamtion and exit

	This tool receives and analyzes incoming ethernet test packets.
