# Чтение данных из файла и вывод их в формате строки экселя
import re

# Путь к файлу, где хранятся данные
file_path_facts = "E:/things/Рабочий стол/Рабочая папка/Учеба/4 курс 7 семестр/Раб 7 семестр/Теория принятия решений/Авто заполнение Anies/facts.txt"
file_path_result = "E:/things/Рабочий стол/Рабочая папка/Учеба/4 курс 7 семестр/Раб 7 семестр/Теория принятия решений/Авто заполнение Anies/result.txt"

# Чтение данных из файла
with open(file_path_facts, "r", encoding="cp1251") as file:
    data_facts = file.read()

with open(file_path_result, "r", encoding="cp1251") as file:
    data_result = file.read()

facts = re.findall(r'-?\d+,\d+', data_facts)        # Извлечение чисел с помощью регулярного выражения из fact.txt
pattern = r'([А-яA-Za-z]+)\n(-?\d+,\d+)'            # Регулярное выражение для извлечения стран и чисел из result.txt
matches = re.findall(pattern, data_result)

country_dict = {country: value for country, value in matches}   # Создаем словарь для хранения страны и ее числового значения

# Заданный порядок стран
ordered_countries = [ "Россия", "Китай", "США", "Индия", "Австралия", "Норвегия", "Гаити", "Афганистан" ]

# Формирование результата в нужном порядке
hypos = []
for country in ordered_countries:
    if country in country_dict:
        hypos.append(f"{country_dict[country]}")


# Преобразование списка в строку с разделением табуляцией
result = " ".join(facts + hypos)
print(result)

