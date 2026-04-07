class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError
        
        self._capacity = capacity
        self._size = 0
        
    def __str__(self):
        return f"🍪: {self.size}"

    def deposit(self, n):
        if n < 0:
            raise ValueError("n can't be negative")
        
        if self.size + n > self.capacity:
            raise ValueError("Not enough capacity")

        self._size += n
        
    def withdraw(self, n):
        if n < 0:
            raise ValueError("n can't be negative")
        
        if self.size - n < 0:
            raise ValueError("Not enough cookies")

        self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


def main():
    jar = Jar()
    print(jar.capacity)
    print(str(jar))

    jar.deposit(2)
    print(str(jar))

    jar.withdraw(1)
    print(str(jar))
    
main()
