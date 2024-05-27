#!/usr/bin/env python
import os, shutil, subprocess

APP_JS_FILE_NAME = "app.js"

class Builder(object):
    def __init__(self):
        self.app_dirs = {} 
        self.root_path = os.path.dirname(os.path.realpath(__file__))

    def gather_app(self, app_dir):
        app_dict = {}
        try:
           with open("{}/public/description.html".format(app_dir)) as x: 
              app_dict["description"] = x.read()

           with open("{}/public/name.txt".format(app_dir)) as x:
              app_dict["name"] = x.read().strip()

           path = "{}/public/{}".format(app_dir, APP_JS_FILE_NAME)
           assert os.path.exists(path)
           app_dict["js-filename"] = path

           app_path = "{}/{}".format(self.root_path, app_dir)
           print("[Building App: {}]".format(app_path))

           return_code = subprocess.call(["bash", "-c", ". $HOME/.nvmrc && npm run build"], cwd=app_path)
           if return_code != 0:
                raise ValueError("Error building {}".format(app_path))

        except (IOError, AssertionError) as e:
            print("Error:  {}".format(e))
            return None
        
        return app_dict

    def add(self, app_dir):
        dir_dict =  self.gather_app(app_dir)
        if not dir_dict:
            raise ValueError("app_dir '{}' not valid".format(app_dir))

        self.app_dirs[app_dir] = dir_dict


if __name__ == "__main__":
    builder = Builder()
    builder.add('react-app')
    builder.add('svelte-app')
    builder.add('angular-app')
    for key, app in builder.app_dirs.items():
        shutil.copy(app['js-filename'], "public/{}.js".format(key))
