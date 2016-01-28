#!/usr/bin/env bash

DIR=example-images/bin/data
DB_URL="https://raw.githubusercontent.com/liuliu/ccv/unstable/samples/image-net-2012.sqlite3"
DB_FILE="$DIR/image-net-2012.sqlite3"
WORDS_URL="https://raw.githubusercontent.com/liuliu/ccv/unstable/samples/image-net-2012.words"
WORDS_FILE="$DIR/image-net-2012.words"
mkdir -p $DIR
if [ ! -e $DB_FILE ] ; then
	echo "Downloading image-net-2012 network (ccv)"
	curl -o $DB_FILE $DB_URL
	curl -o $WORDS_FILE $WORDS_URL
fi
echo "Downloaded: image-net-2012 network (ccv)"
