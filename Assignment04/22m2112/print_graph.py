import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv("dataresult.csv")

plt.subplot(2, 1, 1)
plt.plot(df["NOC"].tolist(), df["TH"].tolist())

plt.xlabel("No. of Clients(Threads)")
plt.ylabel("Throughput (Requests per sec)")
plt.autoscale()

plt.subplot(2, 1, 2)
plt.plot(df["NOC"].tolist(), (df["ARTT"]).tolist())

plt.xlabel("No. of Clients(Threads)")
plt.ylabel("Average RTT(in sec)")
plt.autoscale()

plt.show()

plt.savefig('ResultGraph1')
