#!/bin/bash
for x in `ls *.log`; do
  echo $x": "
  cat $x  | grep -v "Finished" \
          | sed -E 's/^Start\s*\((.+)\).+/\1/g' \
          | sed -E 's/Time: / : /g' \
          | tr -d pq \
          | sed ':loop; N; $!b loop; ;s/\n : /\t: /g' \
          | sed -E 's/^/\t/g'
done
