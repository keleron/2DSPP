"""ESTE DOCUMENTO UNICAMENTE TIENE UN PROPOSITO COMPLEMENTARIO, TOMA LOS OUTPUTS DE LA CARPETA INPUTS
Y LOS TRABAJA DE FORMA QUE PUEDAN SER VISTOS COMO LA TABLA DEL INFORME.
"""


import numpy as np
from PIL import Image
import matplotlib.patches as patches
import matplotlib.pyplot as plt
import os
lsx = os.listdir("inputs")
logs = list(filter(lambda x: x.endswith(".log"), lsx))
logs.sort()
txts = list(filter(lambda x: x.endswith(".TXT"), lsx))
instances = []
for name in logs:
    f = open(f"inputs/{name}", "r")
    data = f.read().split("==================")
    last = data[-1]
    sub_datos = last.split("\n")

    sub_datos[:] = [x for x in sub_datos if x]
    final = {
        "content": last,
        "name": name,
        "n": data[0].split()[0],
        "w": data[0].split()[1],
        "altura": sub_datos[0],
        "area": sub_datos[1].split()[0],
        "per": sub_datos[1].split()[1],
        "iter": sub_datos[1].split()[2]
    }

    instances.append(final)
    f.close()

print("name", "N", "W", "INUTILIZADO%", "ITERACIONES","ALTURA", "Z")
b = []
while True:
    a = input()
    if a=="FIN":
        break
    b.append(a)

c = 0
for e in instances:
    try:
        print(e["name"], e["n"], e["w"], e["per"], e["iter"], e["altura"], b[c])
    except:
        print("ERROR FILE CANNOT FIND SOLUTION")
    c+=1


# fig, ax = plt.subplots(1)
# plt.ylim(0, 100)
# plt.xlim(0, 100)
# rect = patches.Rectangle((0, 0), 40, 30, linewidth=4,
#                          edgecolor='r', facecolor='none')
# ax.add_patch(rect)

# plt.show()