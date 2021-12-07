
echo "CYBERDINE SYSTEMS (JSWARE DIVISION)"
echo "WESTINGHOUSE M95A1 PHASED PLASMA RIFLE"
echo "40W RANGE WEAPON LOADING PROGRAM..."
echo ""

if [ -z "$1" ]; then
  echo "ERROR: INCORRECT USAGE ($0 {VOLUME})"
  ls -ld /Volumes/*
  exit 1
fi

for f in T[0-9][0-9].WAV; do       
  echo COPYING $f TO $1/$f ...
  cp $f $1/$f
done

echo ""
echo "COPYING COMPLETE"
echo "WEAPON LOADED SUCCESSFULLY"
