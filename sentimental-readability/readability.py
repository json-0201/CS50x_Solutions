# TODO
from cs50 import get_string

text = get_string("Text :")

counts = {"letter": 0, "word": 0, "sentence": 0}

# num_l, num_w, num_s = 0, 0, 0

for char in text:
    if (char.isalpha()):
        # num_l += 1
        counts["letter"] += 1

    if (char == " "):
        # num_w += 1
        counts["word"] += 1

    if (char == "." or char == "!" or char == "?"):
        # num_s += 1
        counts["sentence"] += 1

# num_w += 1
counts["word"] += 1

print(counts["letter"], counts["word"], counts["sentence"])

# index_l = num_l / num_w * 100
# index_s = num_s / num_w * 100

index_l = counts["letter"] / counts["word"] * 100
index_s = counts["sentence"] / counts["word"] * 100

index_final = 0.0588 * index_l - 0.296 * index_s - 15.8

if index_final > 15:
    print("Grade 16+")

elif index_final < 1:
    print("Before Grade 1")

else:
    print(f"Grade: {round(index_final)}")
