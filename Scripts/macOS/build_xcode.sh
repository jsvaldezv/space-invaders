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

# ============================================================================

filename="Config.cfg"

PROJECT_NAME=$(grep 'PROJECT_NAME' $filename | awk -F '=' '{print $2}')
PROJECT_VERSION=$(grep 'PROJECT_VERSION' $filename | awk -F '=' '{print $2}')
CPP_VERSION=$(grep 'CPP_VERSION' $filename | awk -F '=' '{print $2}')
GENERATOR=Xcode

# ============================================================================

echo "=========================================="
echo "         Creating $GENERATOR project..."
echo "=========================================="

cmake -G $GENERATOR -B $GENERATOR \
	-D PROJECT_NAME=$PROJECT_NAME \
	-D PROJECT_VERSION=$PROJECT_VERSION \
	-D CPP_VERSION=$CPP_VERSION

echo "=========================================="
echo "             Opening $GENERATOR..."
echo "=========================================="

open $GENERATOR/$PROJECT_NAME.xcodeproj