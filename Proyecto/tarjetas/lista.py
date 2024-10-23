from itertools import combinations
from random import sample
lista=[]
def subAscendingList(arr):
	auxiliarlon=0
	'''Return the longest increasing subsequence'''
	for length in range(len(arr), 0, -1):#Search and judge in the order of decreasing length
		for sub in combinations(arr, length):#Determine whether the currently selected subsequence is in increasing order; the length is the decreasing length of the arr list, find from the arr list, and then permutate
			if list(sub) == sorted(sub):#Find the first one and return; sort the obtained sub in ascending order, if it is equal to the original list, it is the maximum length of the increasing list
				if(auxiliarlon<=len(sub)):
					auxiliarlon=len(sub)
					lista.append(sub)
	return lista
'''
The Python itertools module combination(iterable, r) method can create an iterator,
Returns all subsequences of length r in the iterable, and the items in the returned subsequence are sorted according to the order in the input iterable.
'''

arr=[]
n=int(input("Please enter the number of the given sequence:"))
file1=open('1000Altr2.txt','r')
Lines=file1.readlines(n)
for line in Lines:
	arr.append(line.strip())
print("The maximum increasing subsequence is:")
print(subAscendingList(arr))
