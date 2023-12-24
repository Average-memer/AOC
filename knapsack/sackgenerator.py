import random

length = 32
totalweight = 0
totalvalue = 0

for i in range(length):
	weight = random.random() * 10
	value = random.random() * 15

	totalweight += weight
	totalvalue += value

	print(f"{{{value:.1f}, {weight:.1f}}},")

print(totalweight)
print(totalvalue)
