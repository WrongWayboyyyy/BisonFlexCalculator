from cgi import test
import subprocess as sb
import time
import sys
def run(args):
    return sb.run(args,
        capture_output=True, ).stdout.decode().strip()

def main():
    if (len(sys.argv) < 7):
        print("Invalid arguments")
        return
    exe_path = sys.argv[1]
    out_path = sys.argv[2]
    right_bound = int(sys.argv[3])
    step = int(sys.argv[4])
    iter = sys.argv[5]
    ver = sys.argv[6]

    for expr_len in range(1, right_bound, step):
        test_string = "x";
        for i in range(1, expr_len):
            test_string += f"*(x+{i})";
        args = [exe_path, ver, "-r " + iter, test_string]
        print(args)
        t = time.monotonic()
        run(args)
        end_t = time.monotonic()
        f = open(out_path, "a")
        f.write(f"{expr_len} {(end_t - t) / (int(iter))}\n")
        f.close()
        print(f" Step {expr_len} finished")
        
if __name__ == "__main__":
    main()