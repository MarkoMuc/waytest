#!/bin/bash
set -xe

gcc -o globals globals.c -lwayland-client
./globals
