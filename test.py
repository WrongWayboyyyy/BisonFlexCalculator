import subprocess as sb
import time
import sys
def run(command, inp):
    return sb.run(command.split(), input=inp.encode(), 
        capture_output=True).stdout.decode().strip()

def main():
    if (len(sys.argv) < 4):
        print("Invalid arguments")
        return
    exe_name = sys.argv[1]
    file_name = sys.argv[2]
    right_bound = int(sys.argv[3])
    step = int(sys.argv[4])
    f = open(file_name, "w")
    f.write("")
    f.close()
    for expr_len in range(1, right_bound, step):
        s = "+".join(['2'] * expr_len)
        dp = []
        dp.append(0)
        t = time.monotonic()
        run(exe_name, s)
        end_t = time.monotonic()
        f = open(file_name, "a")
        f.write(f"{expr_len} {(end_t - t) / (1000 * 1000)}\n")
        f.close()
        print(f" Step {expr_len} finished")
        
if __name__ == "__main__":
    main()