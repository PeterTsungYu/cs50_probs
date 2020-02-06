def main():
    height = get_validint()
    for x in range(height):
        # the left margin should align to the bottom-left corner
        print(" " * (height - (x + 1)) + "#" * (x + 1), end = "")
        print(" " * 2, end = "")
        # no extra space at the end of each line
        print("#" * (x + 1))

# get_validint() should prompt user input which has to be an int from 1 to 8, inclusive
# Otherwise, repeat the prompt
def get_validint():
    while True:
        h = int(input("Height: "))
        if 1 <= h <= 8:
            break
    return h

main()
