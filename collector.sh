#!/bin/bash

ATOM=$1
EXECUTIONS=${2:-30}

if [ -z "$ATOM" ]; then
    echo "Error: Enter the name of the atom. Example: ./collector.sh omitted_curly"
    exit 1
fi

CSV_FILE="result_${ATOM}_cpu.csv"

echo "Execution;Version;Relative;ns_op;op_s;err_percent;ins_op;cyc_op;IPC;bra_op;miss_percent;total" > "$CSV_FILE"

echo "Starting $EXECUTIONS executions for $ATOM..."
echo "------------------------------------------------"

for ((i=1; i<=EXECUTIONS; i++))
do
    SUCCESS=0
    
    while [ $SUCCESS -eq 0 ]; do
        echo -n "Running execution $i of $EXECUTIONS... "

        taskset -c 0 ./benchmark_linux "$ATOM" > tmp_nano.log

        sed -i 's/\x1b\[[0-9;]*m//g' tmp_nano.log

        L_CONF=$(grep -i "Confus" tmp_nano.log | tail -n 1)
        L_CLEAN=$(grep -i -e "Limpo" -e "Clean" -e ":wavy_dash:" tmp_nano.log | tail -n 1)

        ERR_C=$(echo "$L_CONF" | awk -F '|' '{print $5}' | tr -d ' %')
        ERR_L=$(echo "$L_CLEAN" | awk -F '|' '{print $5}' | tr -d ' %')

        # Verifica se alguma das execuções ultrapassou 5% de erro
        BAD=$(echo "$ERR_C $ERR_L" | awk '{if ($1 > 5.0 || $2 > 5.0) print 1; else print 0}')

        if [ "$BAD" -eq 1 ]; then
            echo "Rejected (High Error: Confusing=$ERR_C%, Clean=$ERR_L%). Retrying..."
            sleep 2
            continue
        fi
        
        SUCCESS=1
    done

    extract_data() {
        echo "$1" | awk -F '|' '{print $2";"$3";"$4";"$5";"$6";"$7";"$8";"$9";"$10";"$11}' | tr -d ' ' | tr -d ',' | sed 's/\./,/g'
    }

    DATA_CONF=$(extract_data "$L_CONF")
    DATA_CLEAN=$(extract_data "$L_CLEAN")

    echo "$i;Confusing;$DATA_CONF" >> "$CSV_FILE"
    echo "$i;Clean;$DATA_CLEAN" >> "$CSV_FILE"

    echo "OK"
    sleep 2
done

rm -f tmp_nano.log

echo "------------------------------------------------"
echo "Done! File generated: $CSV_FILE"