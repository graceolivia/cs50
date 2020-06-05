from cs50 import get_int
# remake of first C assignment

while True:
    num = get_int("Number:\n")
    if (num > 0) and (num < 9):
        break
    
spaces = num - 1
blocks = 1
# have to do the end='' thing or else there's an automatic space, which creates Trouble
for x in range(num):
    for y in range(spaces):
        print(" ", end='')
    for z in range(blocks):
        print("#", end='')
    print("  ", end='')
    for a in range(blocks):
        print("#", end='')
    print("\n", end='')
    spaces -= 1
    blocks += 1