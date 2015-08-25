#!/bin/bash
for x in $(for d in `ls *.log | cut -d"-" -f2 | cut -d. -f1 | sort -n`; do echo log-$d.log; done); do
  echo $x": "
  cat $x  | grep -v "Finished" \
          | sed -E 's/^Start\s*\((.+)\).+/\1/g' \
          | sed -E 's/Time: / : /g' \
          | tr -d pq \
          | sed ':loop; N; $!b loop; ;s/\n : /\t: /g' \
          | sed -E 's/^/\t/g'
done
