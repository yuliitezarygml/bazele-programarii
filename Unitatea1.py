def calc_medie_clasa():
    try:
        Z = int(input("Введите количество учеников с оценкой 10: "))
        N = int(input("Введите количество учеников с оценкой 9: "))
        O = int(input("Введите количество учеников с оценкой 8: "))
        S = int(input("Введите количество учеников с оценкой 7: "))
        P = int(input("Введите количество учеников с оценкой 4: "))

        if Z < 0 or N < 0 or O < 0 or S < 0 or P < 0:
            print("Ошибка: значения должны быть целыми неотрицательными числами.")
            return

        total_students = Z + N + O + S + P

        if total_students == 0:
            print("Ошибка: в классе нет учеников.")
            return

        total_score = Z * 10 + N * 9 + O * 8 + S * 7 + P * 4

        average = total_score / total_students

        print(f"Средняя оценка класса: {average:.2f}")

    except ValueError:
        print("Ошибка: введите корректные целые числа.")

calc_medie_clasa()
