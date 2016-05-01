import sys
import random

class Player:
	""" 
	A simple class example game

	"""
	global potions, BeastHP, yes, no
	potions = {'small':20 ,'medium':60, 'large': 80}
	BeastHP= 1000
	yes = ("yes", "y", "Y", "YES", "Yes")
	no = ("no", "No", "N", "n", "NO")

	def __init__(self,name):
		self.name = name
		self.health = 100
		self.armor = 100

	def drinkPotion(self, potion):
		if potion == "small":
			self.health += potions["small"]
		elif potion == "medium":
			self.health += potions["medium"]
		elif potion == "large":
			self.health += potions["large"]



	def printStats(self):
		print (" ")
		print ("Beast Health: " + str(BeastHP))
		print ("Name: " + player1.name)
		print ("Health: " + str(player1.health))
		print ("Armor: " + str(player1.armor))
		print (" ")


# begin playing
print ("Welcome to Beast Battle you will fight! ")

# create player
player = input("what is your name? ")
player1 = Player(player)

print (" ")
print ("Welcome " + player1.name + "!!!") 
# print stats
print ("your initial stats: ")
player1.printStats()

while True:

	# attack? -take damage
	print (" ")
	reponse = input("Attack? Y/N: ")
	print (" ")
	if reponse in yes:
		attack = random.randint(0,100)
		hit = random.randint(0,50)
		BeastHP -= attack
		player1.health -= hit

		if ( player1.health <= 0):
			print (" Unfortuneatly " + player1.name + " has died....:(")


		print ("You did " + str(attack) + " damage to Beast!!") 
		print ("But...You took " + str(hit) + " damage yourself. ") 
		player1.printStats()
	# take potion?

		print (" ")
		reponse = input("Take Potion? Y/N: ")
		print (" ")
		if reponse in yes:
			potion = input("Which potion? (small, medium, large): ")
			if potion == "small":
				player1.drinkPotion('small')
			elif potion == "medium":
				player1.drinkPotion('medium')
			elif potion == "large":
				player1.drinkPotion('large')

			if player1.health > 200:
				player1.health = 200;
		player1.printStats()
