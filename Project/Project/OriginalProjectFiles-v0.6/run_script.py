#!/usr/bin/python

import subprocess
import statistics

def main():

    time_collections = []

    for i in range(20):
        print("Run " + str(i) + " . . .")
        # Send command
        cmd = "./knn | awk '/Time: /{print $2}' | sed -r 's/[^0-9.]*//g' | tr '\n' ' ' "
        cmdOutput = subprocess.check_output(cmd, shell=True)

        str_cmdOutput = cmdOutput.decode('utf-8')
        l = len(str_cmdOutput)

        str_cmdOutput = str_cmdOutput[:l-1]

        time = float(str_cmdOutput)
        time_collections.append(time)

    print("Media: " + str(statistics.mean(time_collections)))
    print("Mediana: " + str(statistics.median(time_collections)))


main()
