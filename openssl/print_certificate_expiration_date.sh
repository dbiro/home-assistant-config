#!/bin/bash
set -euo pipefail

# ensuring openssl package is installed
apk update 1>/dev/null
apk add openssl 1>/dev/null

my_domain="$(sed -n "s/^my_domain: \"\(.*\)\"/\1/p" /config/secrets.yaml)"
my_port=443
my_public_ip=$(dig $my_domain +short) # somehow openssl can not resolve my domain

# echo added for closing SSL connection automatically
echo -n Q |
    # connect and get SSL certificate
    openssl s_client -servername "$my_domain" -connect "$my_public_ip:$my_port" 2>/dev/null |
    # parse certificate and print its notAfter field in iso_8601 format
    openssl x509 -dateopt iso_8601 -enddate -noout |
    # remove 'notAfter=' from start of the result string (split on '=' and select 2nd item)
    cut -d = -f 2