import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from fourth import data_maker as dm
import threading
import os
try:
    a=dm('COM3')
except:
    a=dm('/dev/ttyAMA0')
t1=threading.Thread(target=a.make)
fig1, (ax1,ax2,ax3) = plt.subplots(3,1)
def pngfinder():
    if not(os.path.isdir(os.getcwd()+"/images")):
        os.mkdir(os.getcwd()+"/images")
    e=os.listdir(os.getcwd()+"/images")
    s=0
    for i in e:
        try:
            if str(i.split('.')[1])=="png":
                #print("\n"+str(i.split('.')[0]))
                ss=int(i.split('.')[0])
                if s<ss:
                    s=ss
                    print(s)
        except:
            print()
    s=s+1
    return s
def animate(i):

    data = pd.read_csv('data.csv')
    js2=pd.read_json('js2.json')
    x = data['Time']
    y1 = data['analog signal']
    y2 = data['classifier']
    print(js2)
    y3=[js2.values[0][0],js2.values[0][1],js2.values[0][2],js2.values[0][3],js2.values[0][4],js2.values[0][5],js2.values[0][6],js2.values[0][7],js2.values[0][8],js2.values[0][9],js2.values[0][10]]
    x2=['0','1','2','3','4','5','6','7','8','9','10']
    xplode=(0.1,0,0,0,0,0,0,0,0,0,0.1)
    print(y3[2])
    plt.cla()
    
    ax1.clear()
    ax2.clear()
    ax3.clear()
    
    ax1.plot(x, y1, label='analog')
    ax2.plot(x, y2, label='Classifier')
    ax3.pie(y3,labels=x2,explode=xplode)
    ax1.legend(loc='upper left')
    ax2.legend(loc='upper left')
    ax3.legend(loc='upper left')
    
    ax3.set_xlabel("time in half seconds")
    ax3.set_ylabel("Classifiers")
    plt.tight_layout()
    fig1.savefig(os.getcwd()+"/images/"+str(pngfinder())+".png")
    
    
    
t1.start()
ani = FuncAnimation(plt.gcf(), animate, interval=500)

#plt.tight_layout()
plt.show()