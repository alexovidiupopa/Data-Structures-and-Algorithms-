
class Bag:

    # creates a new, empty Bag
    """theta(1)"""
    def __init__(self):
        self.__elements = []
        self.__frequencies = []

    # adds a new element to the Bag
    """O(n)"""
    def add(self, e):
        if e in self.__elements: 
            index = self.__elements.index(e);
            self.__frequencies[index]+=1
            return 
        self.__elements.append(e)
        self.__frequencies.append(1)

    # removes one occurrence of an element from a Bag
    # returns True if an element was actually removed (the Bag contained the element e), or False if nothing was removed
    """O(n)"""
    def remove(self, e):
        if e in self.__elements:
            index = self.__elements.index(e)
            self.__frequencies[index]-=1
            if self.__frequencies[index] == 0:
                del self.__frequencies[index]
                del self.__elements[index]
            return True
        return False
    # searches for an element e in the Bag
    # returns True if the Bag contains the element, False otherwise
    """theta(1)"""
    def search(self, e):
        return e in self.__elements

    # counts and returns the number of times the element e appears in the bag
    """O(n)"""
    def nrOccurrences(self, e):
        if e in self.__elements:
            index = self.__elements.index(e)
            return self.__frequencies[index]
        return 0

    # returns the size of the Bag (the number of elements)
    """theta(n)"""
    def size(self):
        size = 0
        for i in range(len(self.__elements)):
            size+=self.__frequencies[i]
        return size
    # returns True if the Bag is empty, False otherwise
    """theta(1)"""
    def isEmpty(self):
        return self.__elements == []
    
    # returns a BagIterator for the Bag
    """theta(1)"""
    def iterator(self):
        return BagIterator(self)


class BagIterator:

    #creates an iterator for the Bag b, set to the first element of the bag, or invalid if the Bag is empty
    """theta(1)"""
    def __init__(self, b):
        self.__it = b
        self.__currentPosition = 0
        self.__currentFrequency = 0

    # returns True if the iterator is valid
    """theta(1)"""
    def valid(self):
        return self.__currentPosition<len(self.__it._Bag__elements)

    # returns the current element from the iterator.
    # throws ValueError if the iterator is not valid
    """theta(1)"""
    def getCurrent(self):
        if self.valid():
            return self.__it._Bag__elements[self.__currentPosition]
        else: 
            raise ValueError("")
    # moves the iterator to the next element
    #throws ValueError if the iterator is not valid
    """theta(1)"""
    def next(self):
        if self.valid():
            if self.__currentFrequency == self.__it._Bag__frequencies[self.__currentPosition]-1:
                self.__currentPosition+=1
                self.__currentFrequency = -1
            self.__currentFrequency+=1
        else:
            raise ValueError("")

    # sets the iterator to the first element from the Bag
    """theta(1)"""
    def first(self):
        self.__currentPosition = 0
        self.__currentFrequency = 0
