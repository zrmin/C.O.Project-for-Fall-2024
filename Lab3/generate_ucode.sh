#!/bin/bash

set -e

# 输入文件路径
input_file="ucode_original"

# 提取每行的0和1，保存到ucode3文件中
awk '{gsub(/[^01]/, ""); print}' "$input_file" | awk '{ print }' | sed '/^$/d' > ucode

echo "0 and 1 have been extracted and saved to ucode"

