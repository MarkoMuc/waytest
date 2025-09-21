#!/bin/bash
set -xe

gcc -o globals globals.c -lwayland-client
# ./globals

# gcc -o shared shared.c -lwayland-client
# ./shared

gcc -o client client.c -lwayland-client
 ./client
