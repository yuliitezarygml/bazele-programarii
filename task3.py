def main():
    N = int(input("Ион говорит число: "))

    numbers = [N - 2, N - 1, N, N + 1, N + 2]

    print("Василий говорит:", *numbers)

if __name__ == "__main__":
    main()
