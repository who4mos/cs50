class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError
        self.max = capacity
        self.cookies = 0

    def __str__(self):
        return self.cookies * "🍪"

    def deposit(self, n):
        if n < 0 or self.cookies + n > self.max:
            raise ValueError

        self.cookies += n

    def withdraw(self, n):
        if n < 0 or n > self.cookies:
            raise ValueError

        self.cookies -= n

    def capacity(self):
        return self.max

    def size(self):
        return self.cookies

j = Jar(capacity=5)
print(j.capacity())
print(str(j))
j.deposit(2)
print(str(j))
j.withdraw(1)
print(j)
