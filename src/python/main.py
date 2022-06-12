from collections import defaultdict
from google.protobuf import text_format
from math import floor
from matplotlib import pyplot
from output_pb2 import Tests, Storage, Traversal
from typing import List

import matplotlib
matplotlib.use('TkAgg')


def main():

    with open("output.proto") as f:
        message = text_format.Parse(f.read(), Tests())

    cache_miss: defaultdict[List] = defaultdict(list)
    locality1: defaultdict[List] = defaultdict(list)
    locality2: defaultdict[List] = defaultdict(list)

    for m in message.test:
        if m.HasField("cache_miss"):
            k = f"cache_miss-{Storage.Name(m.cache_miss.storage)}-{Traversal.Name(m.cache_miss.traversal)}"
            v = m.cache_miss.result.elapsed_us
            cache_miss[k].append(v)
        if m.HasField("locality1"):
            k = f"locality1-{Storage.Name(m.locality1.storage)}"
            v = m.locality1.result.elapsed_us
            locality1[k].append(v)
        if m.HasField("locality2"):
            k = f"locality2-{Storage.Name(m.locality2.storage)}"
            v = m.locality2.result.elapsed_us
            locality2[k].append(v)

    pyplot.style.use('_mpl-gallery')
    plot(cache_miss)
    plot(locality1)
    plot(locality2)
    pyplot.show()


def plot(data: defaultdict[List]):
    pyplot.figure()
    for k, v in data.items():
        length = floor(len(v) * 0.9)
        x = list(range(0, length))
        y = sorted(v)[0:length]
        pyplot.plot(x, y, label=k)
    pyplot.legend()


if __name__ == "__main__":
    main()
