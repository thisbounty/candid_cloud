while true 
do
    if [ $(ls -1A /input | wc -l) -gt 0 ]; then
		for FULLFILE in /input/*; do
		   FILE="${FULLFILE##*/}"
		   echo "$FILE"
		   filename="${FILE%.*}"
		   mv /input/$FILE /data/$FILE
		   cd /data
		   ./prepareImage $FILE $filename.1 70
		   ./prepareImage $FILE $filename.2 80
		   ./prepareImage $FILE $filename.3 85
		   ./maskwc -m $filename.1.png -c /data/$filename.png -M 2 -o $filename.1out words.txt
		   ./maskwc -m $filename.2.png -c /data/$filename.png -M 2 -o $filename.2out words.txt
		   ./maskwc -m $filename.3.png -c /data/$filename.png -M 2 -o $filename.3out words.txt
		   rm /data/$FILE
		   rm /data/$filename.1.png
		   rm /data/$filename.2.png
		   rm /data/$filename.3.png
		   mv /data/$filename.1out.png /output/$filename.1.png
		   mv /data/$filename.2out.png /output/$filename.2.png
		   mv /data/$filename.3out.png /output/$filename.3.png
		done
	fi
	sleep 5
done
