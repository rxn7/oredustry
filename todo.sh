#!/usr/bin/env bash

grep --include=\*.{cpp,h} -rnw 'src' -e "TODO:\|FIXME:"
