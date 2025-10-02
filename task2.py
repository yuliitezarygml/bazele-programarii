def main():
    N = int(input("Введите число N: "))

    hours_days = N * 24
    minutes_days = hours_days * 60
    seconds_days = minutes_days * 60

    print(f"\nВ {N} днях:")
    print(f"{hours_days} часов, {minutes_days} минут, {seconds_days} секунд.")

    days_weeks = N * 7
    hours_weeks = days_weeks * 24
    minutes_weeks = hours_weeks * 60
    seconds_weeks = minutes_weeks * 60

    print(f"\nВ {N} неделях:")
    print(f"{hours_weeks} часов, {minutes_weeks} минут, {seconds_weeks} секунд.")


    days_may = 31
    hours_may = days_may * 24
    minutes_may = hours_may * 60
    seconds_may = minutes_may * 60

    print("\nВ месяце май:")
    print(f"{hours_may} часов, {minutes_may} минут, {seconds_may} секунд.")

if __name__ == "__main__":
    main()
