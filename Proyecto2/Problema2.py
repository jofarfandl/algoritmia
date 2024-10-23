# Funcion para imprimir la lista de tarjetas
from sys import dont_write_bytecode
maxx=[]
def printLIS(arr: list):
	for x in arr:
		print(x, end=" ")
	print()

#funcion para construir la subsecuencia mas larga 
def constructPrintLIS(arr: list, n: int):
	global maxx
	# L[i] - La subsecuencia mas larga
	# termina con arr[i]
	l = [[] for i in range(n)]
	# L[0] es igual a arr[0]
	l[0].append(arr[0])
	# Empieza en el indice 1
	for i in range(1, n):
		# Se hace para cada j menos que i
		for j in range(i):
			# L[i] = {Max(L[j])} + arr[i]
			# donde j < i y arr[j] < arr[i]
			if arr[i] > arr[j] and (len(l[i]) < len(l[j]) + 1):
				l[i] = l[j].copy()
		# L[i] termina con arr[i]
		l[i].append(arr[i])
	# L[i] ahora almacena una subsecuencia creciente de
	# arr[0..i] que termina con arr[i]
	print("l",l)#print que imprime todas las listas (opcional)
	maxx = l[0]
	# LIS será el máximo de todas las subsecuencias crecientes de arr
	for x in l:
		if len(x) > len(maxx):
			maxx = x
	# max contiene la subsecuencia mas larga
	printLIS(maxx)

if __name__ == "__main__":
	arr=[]
	file1=open('tarjetas_5.in','r')
	num=file1.readline()
	print(num)
	Lines=file1.readlines()[0:int(num)]
	for line in Lines:
		arr.append(int(line.strip()))

	n = len(arr)
	#construye y imprime la lista 
	constructPrintLIS(arr, n)
	f = open("prueba.out.txt", "w")
	f.write(str(n))
	f.write("\n")
	for i in maxx:
		f.write(str(i))
		f.write("\n")
	f.close()

file1.close