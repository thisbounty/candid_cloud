while true 
do
    if [ $(ls -1A /input | wc -l) -gt 0 ]; then
		for FULLFILE in /input/*; do
		   FILE="${FULLFILE##*/}"
		   echo "$FILE"
		   filename="${FILE%.*}"
           ./data/cc_trace $FILE 1 .55
           ./data/cc_trace $FILE 2 .60
           ./data/cc_trace $FILE 3 .65
		   rm /data/$FILE
		done
	fi
	sleep 5
done
