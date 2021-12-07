#!/bin/sh
echo "CYBERDINE SYSTEMS (JSWARE DIVISION)"
echo "WESTINGHOUSE M95A1 PHASED PLASMA RIFLE"
echo "40W RANGE WEAPON PREPARATION PROGRAM..."
echo ""

for f in [0-9][0-9].m4a; do
  wav=T$(basename $f .m4a).WAV
  echo PREPARING $f AS $wav ...    
  ffmpeg -y -i $f $wav >/dev/null 2>&1
done

echo ""
echo "PREPARATION COMPLETE"
echo "PROCEED TO TRANSFER FILES"
