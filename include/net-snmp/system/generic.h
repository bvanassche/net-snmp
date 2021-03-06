#ifndef __NET_SNMP_SYSTEM_GENERIC_H__
#define __NET_SNMP_SYSTEM_GENERIC_H__

/*
 * nlist symbols in ip.c 
 */
#define IPSTAT_SYMBOL "ipstat"
#define IP_FORWARDING_SYMBOL "ipforwarding"
#define TCP_TTL_SYMBOL "tcpDefaultTTL"

/*
 * nlist symbols in interfaces.c 
 */
#define IFNET_SYMBOL "ifnet"
#define IFADDR_SYMBOL "in_ifaddr"

/*
 * load average lookup symbol 
 */
#define LOADAVE_SYMBOL "avenrun"

/*
 * process nlist symbols. 
 */
#define NPROC_SYMBOL "nproc"
#define PROC_SYMBOL "proc"

/*
 * icmp.c nlist symbols 
 */
#define ICMPSTAT_SYMBOL "icmpstat"

/*
 * tcp.c nlist symbols 
 */
#define TCPSTAT_SYMBOL "tcpstat"
#define TCP_SYMBOL "tcb"

/*
 * upd.c nlist symbols 
 */
#define UDPSTAT_SYMBOL "udpstat"
#define UDB_SYMBOL "udb"

/*
 * var_route.c nlist symbols 
 */
#define RTTABLES_SYMBOL "rt_table"
#define RTHASHSIZE_SYMBOL "rthashsize"
#define RTHOST_SYMBOL "rthost"
#define RTNET_SYMBOL "rtnet"

/*
 * udp_inpcb list symbol 
 */
#define INP_NEXT_SYMBOL inp_next

#endif /* !__NET_SNMP_SYSTEM_GENERIC_H__ */
