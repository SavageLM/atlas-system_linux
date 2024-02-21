#!/usr/bin/python3
"""
Finds and replaces a specified string
in a provided PID heap memory
"""

if __name__ == "__main__":
    from sys import argv

    if len(argv) != 4:
        exit("Unsupported  number of arguments")
    pid = int(argv[2])
    search_str = argv[3].encode()
    replace_str = argv[4].encode()
    try:
        mem_map = open(f"/proc/{pid}/maps", "r")
    except FileNotFoundError as error:
        exit(error)
    for line in mem_map:
        if line.endswith("[heap]\n"):
            heap_start, heap_end = \
                [int(x, 16) for x in line.split(" ")[0].split("-")]
    print("Target memory location found")
    mem_map.close()
    try:
        heap_mem = open(f"/proc/{pid}/maps", "r+b")
    except FileNotFoundError as error:
        exit(error)
    heap_mem.seek(heap_start)
    mem = heap_mem.read(heap_end - heap_start)
    str_at = mem.find(search_str)
    if str_at > -1:
        print(f"Target Located at {hex(str_at)}")
        heap_mem.seek(str_at)
        heap_mem.write(replace_str)
        print("Target Replaced")
    else:
        print("Unable to locate Target")
    heap_mem.close()
    print("Mission Complete")
