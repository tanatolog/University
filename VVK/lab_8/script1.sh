#!/bin/bash

mpicc task.c -o task || { echo "Ошибка компиляции!"; exit 1; } # Компилируем <code_path> <result_path>

nodes=("10.128.1.170") # IP вычислительных узлов (блейдов) 10.128.1.169
process_count=1 # Количество процессов

sockets=2 # Количество ПР в блейде
cores_per_socket=4 # Количесво ядер в ПР
output_file="output_${process_count}.txt" # Формируем имя файла
node_number=${#nodes[@]} # Вычисляем количество элементов массива

# Проверяем, достаточно ли доступных ядер
total_cores=$((node_number * sockets * cores_per_socket))
if [ "$process_count" -gt "$total_cores" ]; then
    echo "Ошибка: недостаточно доступных ядер для $process_count процессов (доступно: $total_cores)."
    exit 1
fi



echo "" > rankfile # Создаём (или перезаписываем) rankfile
# Данный файл позволяет задать количество задействованных процессоров и процессов для каждого узла

# Генерация rankfile
process_counter=0
for ((node_i=0; node_i<node_number; node_i++)); do # Цикл по узлам
    for ((socket_i=0; socket_i<sockets; socket_i++)); do # Цикл по ПР
        for ((core_i=0; core_i<cores_per_socket; core_i++)); do # Цикл по ядрам внутри ПР
            if [ "$process_counter" -ge "$process_count" ]; then
                break 3 # Прерываем все циклы, если заданное число процессов достигнуто
            fi
            echo "rank $process_counter=${nodes[$node_i]} slot=$socket_i:$core_i" >> rankfile # Записываем в rankfile
            process_counter=$((process_counter + 1))
        done
    done
done

echo "Rankfile создан для $process_count процессов:"
cat rankfile # Вывод rankfile в консоль

# Запуск задачи
mpirun -np $process_count -rf rankfile task 2>&1 | tee "$output_file" || { echo "Ошибка запуска задачи!"; exit 1; } # попробовать убрать -np $process_count, вдруг не будет работать