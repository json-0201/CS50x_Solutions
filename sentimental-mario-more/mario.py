# TODO
import cs50

while True:
    h = cs50.get_int("Height: ")
    if h > 0 and h < 9:
        break

for i in range(h):

    print(" " * (h-(i+1)), end="")     # Initial space

    print("#" * (i+1), end="")          # Left hash

    print("  ", end="")                 # Middle space

    print("#" * (i+1), end="")          # Right hash

    print()                             # New line