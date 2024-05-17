#!/usr/bin/env python
import os

APP_JS_FILE_NAME = "app.js"

class Builder(object):
    def __init__(self):
        self.app_dirs = {} 

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

        except (IOError, AssertionError) as e:
            print("Error:  {}".format(e))
            return None
        
        return app_dict

    def add(self, app_dir):
        dir_dict =  self.gather_app(app_dir)
        if not dir_dict:
            raise ValueError("app_dir {} not valid".format(app_dir))

        self.app_dirs[app_dir] = dir_dict


if __name__ == "__main__":
    builder = Builder()
    builder.add('react-app')
    builder.add('svelte-app')
    print("dirs found {}".format(repr(builder.app_dirs)))
