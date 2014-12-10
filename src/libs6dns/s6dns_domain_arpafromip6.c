/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/fmtscan.h>
#include <s6-dns/s6dns-domain.h>

void s6dns_domain_arpafromip6 (s6dns_domain_t *d, char const *ip6, unsigned int mask)
{
  register unsigned int i ;
  if (mask > 128) mask = 128 ;
  mask = mask ? 1 + ((mask-1) >> 2) : 0 ;
  d->len = 0 ;
  d->s[d->len++] = '.' ;
  for (i = 32 - mask ; i < 32 ; i++)
  {
    unsigned char c = ip6[15-(i>>1)] ;
    d->s[d->len++] = fmtscan_asc((i & 1) ? (c >> 4) : (c & 15)) ;
    d->s[d->len++] = '.' ;
  }
  byte_copy(d->s + d->len, 9, "ip6.arpa.") ; d->len += 9 ;
}
