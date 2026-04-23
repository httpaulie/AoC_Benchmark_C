#!/bin/bash

ATOM=$1
EXECUTIONS=${2:-30}

if [ -z "$ATOM" ]; then
    echo "Error: Enter the name of the atom. Example: ./collector.sh omitted_curly"
    exit 1
fi

CSV_FILE="results_${ATOM}.csv"

echo "Execution;Version;Relative;ns_op;op_s;err_percent;ins_op;cyc_op;IPC;bra_op;miss_percent;total;Ir_Valgrind" > "$CSV_FILE"
echo "Starting $EXECUTIONS executions for the atom: $ATOM..."

for ((i=1; i<=EXECUTIONS; i++))
do
    echo -n "Running execution $i of $EXECUTIONS... "

    # --- NANOBENCH ---
    taskset -c 0 ./benchmark_linux "$ATOM" > tmp_nano.log
    
    sed -i 's/\x1b\[[0-9;]*m//g' tmp_nano.log

    L_CONF=$(grep -i "Confus" tmp_nano.log | tail -n 1)
    L_CLEAN=$(grep -i -e "Limpo" -e "Clean" -e ":wavy_dash:" tmp_nano.log | tail -n 1)

    extract_data() {
        echo "$1" | awk -F '|' '{print $2";"$3";"$4";"$5";"$6";"$7";"$8";"$9";"$10";"$11}' | tr -d ' ' | tr -d ',' | sed 's/\./,/g'
    }

    DATA_CONF=$(extract_data "$L_CONF")
    DATA_CLEAN=$(extract_data "$L_CLEAN")

    # --- VALGRIND ---
    valgrind --tool=cachegrind --cachegrind-out-file=cg_tmp.out ./benchmark_linux "$ATOM" > /dev/null 2>&1
    cg_annotate --auto=yes cg_tmp.out > tmp_cg.log

    IR_CONF=$(grep -i "${ATOM}" tmp_cg.log | grep -i "confus" | head -n 1 | tr -d '<>' | awk '{print $1}' | tr -d ',')
    IR_CLEAN=$(grep -i "${ATOM}" tmp_cg.log | grep -i "clean" | head -n 1 | tr -d '<>' | awk '{print $1}' | tr -d ',')

    if [ -z "$IR_CONF" ]; then IR_CONF="0"; fi
    if [ -z "$IR_CLEAN" ]; then IR_CLEAN="0"; fi

    echo "$i;Confusing;$DATA_CONF;$IR_CONF" >> "$CSV_FILE"
    echo "$i;Clean;$DATA_CLEAN;$IR_CLEAN" >> "$CSV_FILE"

    echo "OK"
    sleep 2
done

rm -f tmp_nano.log cg_tmp.out tmp_cg.log
echo "------------------------------------------------"
echo "Done! File generated: $CSV_FILE"