from math import sqrt; from itertools import count, islice #Bibliotecas utilizadas
import sys
import math
import random

def primo(n): #Função que gera os 5 mil primeiros primos de forma ingênua 
    return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))			
		
def miller(n): #Miller
	global primos #Chama a lista de primos
	x = n - 1 #Cria o n-1
	mcontador = 0 #Um contador para utilizar 50 bases
	tudo1 = True #Booleano para ver se tudo no Miller é 1
	menos1 = False #Booleano para ver se achou o -1
	
	while mcontador < 50: #50 bases
		a = random.choice(primos) #Base aleatória na lista de 50000 primos
		while x % 2 == 0: # Enquanto o número for ímpar
			a = int(a)
			x = int(x)
			n = int(n)
			temp = pow(a, x, n) #Eleva para ver se é diferente de 1 ou é -1
			if temp != 1: #Se é diferente de 1, muda o booleano, mas não quebra porque ainda pode aparecer o -1
				tudo1 = False
			if temp == n - 1: #Se aparecer o -1, já é inconclusivo. Logo, muda o booleano e quebra.
				menos1 = True
				break
			x //= 2 #Se não quenrou, pega a parte inteira da divisão por 2
			
		a = int(a) # Essas 8 linhas verificam o número ímpar que dá no final
		x = int(x)
		n = int(n)
		temp = pow(a, x, n)
		if temp != 1: #
			tudo1 = False
		if temp == n - 1:
			menos1 = True
			
		if menos1 == False and tudo1 ==	False: #Se não for tudo 1 e o menos 1 não apareceu, retorna composto
			return True
				
		menos1 = False #Se não deu composto, reseta as variáveis e testa com outra base
		tudo1 = True
		mcontador += 1
		x = n - 1
		
	return False #Se não deu composto com nenhuma base, retorna inconclusivo

def lucas(n): #Teste de Lucas
	global primos #Chama a lista de primos
	x = n - 1 #Inicializa o valor que vou testar
	x //= 2 # Já divido ele por 2, pois sei que é par (Assim me facilita, pois o n - 1 vai dar 1, até porque já sei isso pelo teste de Miller)
	i = 0 #Vai andar pela lista de primos
	contador = 0 #Contador para as 50 bases
	deNovo = False #Booleano para que, se deu inconclusivo, testar outra base

	while contador < 50: #Testa 50 bases
		
		a = random.choice(primos) #Pega uma base aleatória da lista de primos
		
		while x != 1: #Enquanto ainda for possível dividir o x, fica no loop
			
			while x % primos[i] == 0: #Testa o primo i na lista, se ele dividir o x, sei que é um dos fatores primos	
				n = int(n) #Testa se a base elevado ao fator primo é 1 na base n
				x = int(x)
				a = int(a)
				teste = pow(a, x, n)
				if teste == 1: #Se for 1, já sei que é inconclusivo, mudo a Booleana para testar em outra base e quebro o loop
					deNovo = True
					break
				x //= primos[i]	#Se não foi 1, divido o x pelo fator primo (isso se repete até o fator não dividir mais x)
				
			if deNovo == True: #Se quebrou porque quero testar de novo, vem pra cá e quebra o outro loop
				break	
				
			i += 1 # Se ainda não quebrou com o primo testado, testa o próximo para ver se é fator
			
			if i == len(primos): #Se já testou todos os 50 mil primos, testo em outra base
				deNovo == True
				break
					
		if deNovo == True: #Aqui reseta para outra base
				x = n - 1
				x //= 2
				i = 0
				contador += 1
				deNovo = False	
				continue
				
		else: #Se não achou nenhum número que a base elevada a ele desse 1 antes do x, então retorna que o número é primo
			return True
				
	return False #Se testou em todas as bases, e não encontrou a ordem em n - 1, retorna inconclusivo


pcontador = 2 #Contador para gerar 50 mil primos
p = 3 #Começa do primo 3, porque o 2 já coloquei na lista abaixo
primos = [2] #Começa a lista com o 2 

print("Gerando 50 mil primos (no meu pc isso leva cerca de 8 segundos)")

while pcontador <= 50000: #Mando os números ímpares para a função de verificar se é primo de forma ingênua, se for primo, o contador sobe em 1
	if primo(p) == True:
		primos.append(p)
		pcontador += 1
	p += 2	
	
print("50 mil primos gerados.")

print("Entre um numero: ")

x = int(input()) #Você entra o número que quer achar o primo acima

if x % 2 == 0: #Se o número for par, vira ímpar
	x += 1

if primos.count(x) != 0: #Se o número estiver na lista, pede para usa-lo
	print("Use o número", x)
	sys.exit()

while True: #Esse while ira será para testar outro número quando descobre que um é composto
	
	composto = False #Isso irá determinar se o número é composto dividindo pelos 50 mil primos
	dcontador = 0 #Esse contador irá até 50 mil
	
	while dcontador < 50000: #Se o contador chegar em 50 mil, quer dizer que nenhum primo conseguiu dividi-lo, logo não sei ainda se é composto
		if x % primos[dcontador] == 0: #Se dividiu, sei que é composto, então digo para o Booleano que é
			composto = True
			break
		dcontador += 1 #Se não dividiu, tenta dividir pelo próximo
		
	if composto == True: #Se for composto, pega o próximo ímpar e tenta novamente
		x += 2
		continue
	
	#Se não dividiu pelos 50 mil primeiros, ele vai para o miller	
				
	bmiller = miller(x) #Chama o miller
	
	if bmiller == True: #Se o miller retornar composto, aumenta o x em 2 e volta para o começo do while
		x += 2
		continue
	
	#Se o miller retornou inconclusivo, vai para o Lucas
		
	blucas = lucas(x) #Chama o Lucas
	
	if blucas == False: #Se o lucas retornou inconclusivo, aumenta o x em 2 e volta para o começo do while
		x += 2
		continue


	print("Use o primo:", x) #Se chegou até aqui, imprime o X achado e termina o programa!
	break	
	
	
	




