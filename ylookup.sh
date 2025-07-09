LINE=
for I in {0..199}
do
  LINE+="BA+$((0x20+(($I&0xF8)*40)+($I&7))),"
done
if (test $LINE) then :
  echo $LINE
fi
