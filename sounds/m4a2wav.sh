for f in [0-9][0-9].m4a; do       
  ffmpeg -y -i $f T$(basename $f .m4a).WAV
done
