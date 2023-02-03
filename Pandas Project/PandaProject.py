import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def range_calc():

    failed = 0
    passed = 0
    num = 0
    df = pd.read_csv("Data.csv")
    for i in range(0, 568):
        # print(df.iloc[i, 11],df.iloc[i, 0])
        if df.iloc[i, 11] < 6:
            failed += 1
        elif df.iloc[i, 11] >= 6:
            passed += 1
        else:
            num += 1
    print(
        f"People Failed: {failed}\nPeople Passed: {passed}\nPeople Apsent: {num}\nTotal Examise: {failed+passed+num}"
    )
    y = [failed, passed, num]
    mylabels = ["Failed", "Passed", "Apsent"]
    myexplode = [0.2, 0, 0]
    plt.pie(y, labels=mylabels, explode=myexplode, autopct="%1.1f%%")
    plt.legend(bbox_to_anchor=(0.043, 0.977))
    plt.show()


range_calc()
