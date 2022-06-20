import subprocess as sb
import time
import sys

def run(args):
    return sb.run(args,
        capture_output=True, ).stdout.decode().strip()
    
versions = {'-p' :'parse', '-a' : 'ast', '-j' : 'jit'}

def main():
    if (len(sys.argv) < 6):
        print("Invalid arguments")
        return
    exe_path = sys.argv[1]
    out_path = sys.argv[2]
    right_bound = int(sys.argv[3])
    step = int(sys.argv[4])
    iter = sys.argv[5]
    f = open(out_path, "w")
    for mode in ["-p", "-a", "-j"]:
        version = versions[mode]
        for expr_len in range(0, right_bound + 1, step):
            test_string = "x";
            for i in range(1, expr_len):
                test_string += f"*(x+{i})";
            args = [exe_path, mode, "-r " + iter, test_string]
            print(args)
            t = time.monotonic()
            run(args)
            end_t = time.monotonic()
            f.write(f"{expr_len},{(end_t - t) / (int(iter))},{version}\n")
            print(f" Step {expr_len} finished")
        
    f.close()
        
if __name__ == "__main__":
    main()