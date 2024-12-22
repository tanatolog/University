#!/bin/bash
# Данный пример лишь показывает как можно осуществить
# выполнение вашей программы множество раз
# с различными параметрами загрузки узлов,
# а не демонстрирует правильный вариант для всех заданий

mpicc task.c -o task # Компилируем

nodes=("10.128.1.170")
node_number=${#nodes[@]} # количество элементов массива
sockets=2
cores_per_socket=4

task_param=1

echo "" > rankfile # Создаём (или перезаписываем) rankfile

for ((node_i=0; node_i<node_number; node_i++)); do # Цикл по узлам
    for ((socket_i=0; socket_i<sockets; socket_i++)); do # Цикл по сокетам
        for ((core_i=0; core_i<cores_per_socket; core_i++)); do # Цикл по ядрам внутри сокета

        echo "rank $((node_i * sockets * cores_per_socket + socket_i * cores_per_socket + core_i))=${nodes[$node_i]} slot=$socket_i:$core_i" >> rankfile # Записываем в rankfile

        done
    done
done

mpirun -rf rankfile task 2 # Запуск задачи 
# В конец строки можно добавить аргументы для запускаемой программы (если такие необходимы)

nodes+=("10.128.1.169") # добавляем новый узел
node_number=${#nodes[@]} # количество элементов массива

echo "" > rankfile # Создаём (или перезаписываем) rankfile

for ((node_i=0; node_i<node_number; node_i++)); do # Цикл по узлам
    for ((socket_i=0; socket_i<sockets; socket_i++)); do # Цикл по сокетам
        for ((core_i=0; core_i<cores_per_socket; core_i++)); do # Цикл по ядрам внутри сокета

        echo "rank $((node_i * sockets * cores_per_socket + socket_i * cores_per_socket + core_i))=${nodes[$node_i]} slot=$socket_i:$core_i" >> rankfile # Записываем в rankfile

        done
    done
done

mpirun -rf rankfile task 3 > output.txt # Опционально можно перенаправить консольный вывод в файл