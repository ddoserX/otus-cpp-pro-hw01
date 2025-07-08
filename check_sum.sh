#!/bin/bash

ref_md5sum="24e7a7b2270daee89c64d3ca5fb3da1a"

output_sum=$(cat ./data/ip_filter.tsv | ./build/vcpkg-debug/ip-filter | md5sum)

read -ra sum <<< $output_sum

if [[ "$ref_md5sum" == "${sum[0]}" ]]; then
    echo "md5sum is correct [${sum[0]}]"
fi