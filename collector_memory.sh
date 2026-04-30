#!/bin/bash

ATOM=$1
EXECUTIONS=${2:-30}

if [ -z "$ATOM" ]; then
    echo "Error: Enter the name of the atom. Example: ./collector.sh omitted_curly"
    exit 1
fi

CSV_FILE="results_${ATOM}_memory.csv"

echo "Execution;Version;Dr;D1mr;Dw;D1mw" > "$CSV_FILE"
echo "Starting $EXECUTIONS executions for $ATOM..."
echo "------------------------------------------------"

for ((i=1; i<=EXECUTIONS; i++))
do
    echo -n "Running execution $i of $EXECUTIONS... "
    valgrind --tool=cachegrind --cache-sim=yes --cachegrind-out-file=cg_tmp.out ./benchmark_memory "$ATOM" > /dev/null 2>&1
    cg_annotate --show=Dr,D1mr,Dw,D1mw cg_tmp.out > tmp_cg.log

    extract_memory() {
        grep -i "${ATOM}" tmp_cg.log | grep -i "$1" | head -n 1 | sed 's/([^)]*)//g' | tr -d '<>,' | awk '{print $1";"$2";"$3";"$4}'
    }

    MEM_CONF=$(extract_memory "confus")
    MEM_CLEAN=$(extract_memory "clean")

    if [ -z "$MEM_CONF" ]; then MEM_CONF="0;0;0;0"; fi
    if [ -z "$MEM_CLEAN" ]; then MEM_CLEAN="0;0;0;0"; fi

    echo "$i;Confusing;$MEM_CONF" >> "$CSV_FILE"
    echo "$i;Clean;$MEM_CLEAN" >> "$CSV_FILE"

    echo "OK"
done

rm -f cg_tmp.out tmp_cg.log
echo "------------------------------------------------"
echo "Done! File generated: $CSV_FILE"