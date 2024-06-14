import os, sys, subprocess

def npm_cmd(cmd):
    return ". $HOME/.nvmrc && npm run {}".format(cmd)

root = None
def local_path(path):
    global root
    if not root:
       root = os.path.dirname(os.path.realpath(__file__))

    return "{}/{}".format(root, path)

if __name__ == "__main__":
    for arg in sys.argv[1:]:
        print(arg)
        if arg == 'serve':
            return_code = subprocess.call(["bash", "-c", npm_cmd("serve")], cwd=local_path("nodejs-server"))
            if return_code != 0:
                raise ValueError("serve")
