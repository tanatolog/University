#!/bin/bash

mpicc task1.c -o task # Компилируем
echo "Программа скомпилирована"

sockets=2 # Количество ПР в блейде
cores_per_socket=4 # Количесво ядер в ПР

create_rankfile() {
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
    echo "\nrankfile создан"
}

# Запуск с нужным количеством процессов
process_count=1 # Количество процессов
nodes=("10.128.1.170") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=2 # Количество процессов
nodes=("10.128.1.170") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=3 # Количество процессов
nodes=("10.128.1.170") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=4 # Количество процессов
nodes=("10.128.1.170") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=5 # Количество процессов
nodes=("10.128.1.170") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=6 # Количество процессов
nodes=("10.128.1.170") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=7 # Количество процессов
nodes=("10.128.1.170") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=8 # Количество процессов
nodes=("10.128.1.170") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=9 # Количество процессов
nodes=("10.128.1.170" "10.128.1.169") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=10 # Количество процессов
nodes=("10.128.1.170" "10.128.1.169") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=11 # Количество процессов
nodes=("10.128.1.170" "10.128.1.169") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи

# Запуск с нужным количеством процессов
process_count=12 # Количество процессов
nodes=("10.128.1.170" "10.128.1.169") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи# Запуск с нужным количеством процессов

process_count=13 # Количество процессов
nodes=("10.128.1.170" "10.128.1.169") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи# Запуск с нужным количеством процессов

process_count=14 # Количество процессов
nodes=("10.128.1.170" "10.128.1.169") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи# Запуск с нужным количеством процессов

process_count=15 # Количество процессов
nodes=("10.128.1.170" "10.128.1.169") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи# Запуск с нужным количеством процессов

process_count=16 # Количество процессов
nodes=("10.128.1.170" "10.128.1.169") # IP вычислительных узлов (блейдов) 10.128.1.169
node_number=${#nodes[@]} # Вычисляем количество элементов массива

create_rankfile
echo "Запуск теста $process_count"
mpirun -rf rankfile task # Запуск задачи
