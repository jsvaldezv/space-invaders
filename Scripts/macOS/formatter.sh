#!/bin/bash

echo '
    _                _     _                 
   (_)              | |   | |                
    _ _____   ____ _| | __| | ___ ______   __
   | / __\ \ / / _` | |/ _` |/ _ \_  /\ \ / /
   | \__ \\ V / (_| | | (_| |  __// /  \ V / 
   | |___/ \_/ \__,_|_|\__,_|\___/___|  \_/  
  _/ |                                       
 |__/ 
'

echo "=========================================="
echo "               Starting..."
echo "=========================================="

# ============================================================================

directory=Source

# Find all files in the directory and its subdirectories
file_list=$(find "$directory" -type f)

# Iterate over each file in the list
for file in $file_list; do
    echo "Formatting: $file"
	clang-format --style=file -i $file
done
