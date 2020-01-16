import os
ls = os.listdir("inputs")
ls = list(filter(lambda x: x.endswith(".log"), ls))
instances = []
for e in ls:
    f=open(f"inputs/{e}", "r")
    contents =f.read()
    final = contents.split("==================")[-1]
    instances.append(final)
    f.close()

for e in instances:
    try:
        print(e.split("\n")[2])
    except:
        print("ERROR FILE CANNOT FIND SOLUTION")
