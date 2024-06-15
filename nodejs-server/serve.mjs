import http from 'http'

/* util functions */
function makeSid(params){
   // take two seperate time methods and some random to make a random identifier
   const now_s = String(new Date().getTime()); 
   const now_abbrev = now_s.substring(now_s.length-4, now_s.length);

   const ts = String(process.hrtime.bigint());
   const ts_abbrev = ts.substring(ts.length-4, ts.length);

   const rand = String(Math.random()).substring(2, 12);

   const buff = Buffer.from(`${now_abbrev}${ts_abbrev}${rand}`);
   return buff.toString('base64');
}

function ErrorLog(msg, params){
    console.log(msg, params);
}

function AccessLog(msg, params){
    console.log(msg, params);
}

/* generic election functions */
function always(method, path, params){
    return true;
}

/* generic result handlers */
function notFoundServe(res, now, method, path, params){
    const obj = {
        error: "Not Found",
    };
    res.writeHead(404, {'Content-Type': 'application/json'});
    res.end(JSON.stringify(obj));
}

function errorServe(res, now, method, path, params){
    const obj = {
        error: "Server Error (Internal)",
    };
    res.writeHead(500, {'Content-Type': 'application/json'});
    res.end(JSON.stringify(obj));
}


/* class for making handlers */
class Handler {
    process;
    constructor(electors, process){
        this.electors = electors;
        this.process = process;
    }

    elect(method, path, params){
        for(let i = 0; i < this.electors.length; i++){
            if(!this.electors[i](method, path, params)){
                return false
            }
        }
        return true;
    }

    handle(res, now, method, path, params){
        return this.process(res, now, method, path, params);
    }
}

class Serve {
    handlers;
    param_keys;
    host;
    constructor(param_keys, handlers){
        this.host = "";
        this.param_keys = param_keys;
        this.handlers = handlers;
    }
    /* server and handler runner */
    handleRequest(res, now, method, path, params){
        let done = false;
        let elected = null;
        for(let i = 0; i < this.handlers.length; i++){
          let handle = this.handlers[i];
          if(handle.elect(method, path, params)){
              elected = handle.process;
              break;
          }
        }

        if(elected){
            if(elected.call(this, res, now, method, path, params) !== false){
                done = true;
            }
        }else{
            errorHandler.handle.call(this, res, now, method, path, params);
        }
        
        if(!done){
            ErrorLog(`Error ${method} ${path} -> ${elected.name}`, params);
        }else{
            AccessLog(`Served ${method} ${path} -> ${elected.name}`, params);
        }
    }
    getNow(){
        return new Date();
    }
    serve(port, host){
        /* server instantiation */
        this.host = host;
        const self = this;
        http.createServer(function (req, res) {
            const method = req.method;
            const path = req.url;
            const params = self.parseParams(req, path);

            self.handleRequest(res, self.getNow(), method, path, params);
        }).listen(port);
    }
    /* parse the rest api into an object for all keywords 
     * that expect arguments listed in `param_keys` 
     */
    parseParams(req, url){
        /* The param parser allocates a value in an objcect based on the previous value 
         *being in the `param_keys` list 

         for example:
         
             /time/timezone/BST -> ['', 'time', 'timezone', 'BST']

         `timezone` is in the param_keys list as the value of TZ_KEYWORD
         when that is encountered it is saved as the value of `key`

         and then used to make

             params[key] = 'BST'

         when 'BST' is encountered as the next element in the array


         otherwise a null value is placed, for example

             params["time"] = null


         this will be checked above with a statement such as

             key in params

         which passes for null, and fails for undefined

         */
        let params = {};
        params['ip'] = req.headers['X-ip'] || req.headers['ip'];
        if(!url){
            return params;
        }
        const segs = url.split('/');
        if(!segs.length){
            return params;
        }

        let key = null;
        segs.shift();
        for(let i = 0; i < segs.length; i++){
            const s = segs[i];
            if(key){
                params[key] = s;        
                key = null;
                continue;
            }
            if(this.param_keys.indexOf(s) !== -1){
                key = s;
                params[key] = null;
                continue;
            }else{
                params[s] = null;
                continue;
            }
        }
        return params;
    }
}

const errorHandler = new Handler(always, errorServe);

export {Serve, Handler, makeSid, always, notFoundServe, errorServe};
