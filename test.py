import os, glob, shutil, subprocess

def NpmCmd(cmd):
    return ". $HOME/.nvmrc && npm run {}".format(cmd)

class Tester(object):
    def __init__(self):
        self.app_dirs = {} 
        self.root_path = os.path.dirname(os.path.realpath(__file__))

    def run(self):
        for app_dir, cmd in self.app_dirs.items():
            self.test_app(app_dir, cmd)

    def test_app(self, app_dir, cmd):
       app_path = "{}/{}".format(self.root_path, app_dir)
       return_code = subprocess.call(["bash", "-c", cmd], cwd=app_path)
       if return_code != 0:
            raise ValueError("Error testing {}".format(app_path))


    def add(self, app_dir, cmd):
        self.app_dirs[app_dir] = cmd


if __name__ == "__main__":
    tester = Tester()
    tester.add('nodejs-server', NpmCmd("test"))
    tester.run()
