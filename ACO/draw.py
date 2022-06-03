import matplotlib.pyplot as plt
Correction_X = [40, 25, 15, 10, 5, 0, 44, 35, 95, 85, 65]
COrrection_Y = [50, 85, 75, 35, 35, 40, 5, 5, 30, 35, 85]

path1 = [0,9,8,6,7,3,0]
path2 = [0,4,5,2,1,10,0]


plt.scatter(Correction_X, COrrection_Y, s=10, c='b')
for i,text in enumerate(Correction_X):
    plt.annotate(i, (Correction_X[i], COrrection_Y[i]))
plt.plot([Correction_X[i] for i in path1], [COrrection_Y[i] for i in path1], 'b')
for i in range(len(path1)-1):
    plt.arrow(Correction_X[path1[i]], COrrection_Y[path1[i]], (Correction_X[path1[i+1]]-Correction_X[path1[i]])/2, (COrrection_Y[path1[i+1]]-COrrection_Y[path1[i]])/2, head_width=1.5, head_length=1.5, fc='r', ec='r')
plt.plot([Correction_X[i] for i in path2], [COrrection_Y[i] for i in path2], 'g')
for i in range(len(path2)-1):
    plt.arrow(Correction_X[path2[i]], COrrection_Y[path2[i]], (Correction_X[path2[i+1]]-Correction_X[path2[i]])/2, (COrrection_Y[path2[i+1]]-COrrection_Y[path2[i]])/2, head_width=1.5, head_length=1.5, fc='r', ec='r')
plt.show()

# git上传好像有一点点问题，试一下