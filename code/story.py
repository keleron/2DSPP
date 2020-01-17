import os

lsx = os.listdir("inputs")
ls = list(filter(lambda x: x.endswith(".log"), lsx))
ls.sort()
# print(ls)
for name in ls:
    f = open(f"inputs/{name}", "r")
    info = f.read().split("==================")[1:]
    c = 0
    print(f"\n{name}")
    for solution in info:
        a,b = solution.split("\n")[2].split()[1:]
        a = round(float(a.replace("%",""))/100,2)
        print(f"({b},{a})",end="")
        # input()

        # print(name, str_list[1])
    f.close()
