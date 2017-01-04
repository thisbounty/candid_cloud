while true 
do
    if [ $(ls -1A /input | wc -l) -gt 0 ]; then
		for FULLFILE in /input/*; do
		   FILE="${FULLFILE##*/}"
		   echo "$FILE"
		   filename="${FILE%.*}"
		   mv /input/$FILE /data/$FILE
		   cd /data
		   ./prepareImage $FILE $filename.40 40
		   ./prepareImage $FILE $filename.50 50
		   ./prepareImage $FILE $filename.60 60
		   ./prepareImage $FILE $filename.70 70
		   ./prepareImage $FILE $filename.75 75
		   ./maskwc -m $filename.40.png -c /data/$FILE -o $filename.40out words.txt
		   ./maskwc -m $filename.50.png -c /data/$FILE -o $filename.50out words.txt
		   ./maskwc -m $filename.60.png -c /data/$FILE -o $filename.60out words.txt
		   rm /data/$FILE
		   rm /data/$filename.40.png
		   rm /data/$filename.50.png
		   rm /data/$filename.60.png
		   mv /data/$filename.40out.png /output/$filename.40.png
		   mv /data/$filename.50out.png /output/$filename.50.png
		   mv /data/$filename.60out.png /output/$filename.60.png
		done
	fi
	sleep 5
done
