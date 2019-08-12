#!/usr/bin/env python

def compute_metrics(luts,frequency,latency,field):
    ex_time = latency / frequency
    performance = 1 / (ex_time * luts)
    throughput = field / ex_time
    efficiency = throughput / luts
    print("Throughput = {}, Perf = {}, ExTime = {}, Efficiency = {}".format(throughput,performance,ex_time,efficiency))

luts = 18416
frequency = 119.04
latency = 12
field = 163
compute_metrics(luts,frequency,latency,field)

luts = 18260
frequency = 118.638
latency = 9
field = 163
compute_metrics(luts,frequency,latency,field)
