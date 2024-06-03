const http = require('http');
const fs = require('fs');

UPDATE_KEYWORD = 'update';
START_KEYWORD = 'start';
SID_KEYWORD = 'session';
const param_keys = [SID_KEYWORD];

/* util functions */
function makeSid(params){
   const now_s = String(new Date().getTime()); 
   const now_abbrev = now_s.substring(now_s.length-4, now_s.length);
   const ts = String(process.hrtime.bigint());
   const ts_abbrev = ts.substring(ts.length-4, ts.length);
   const ip = params.ip || '';
   const rand = String(Math.random()).substring(2, 12);
   const buff = Buffer.from(`${now_abbrev}${ts_abbrev}${rand}`);
   console.log(buff.toString());
   console.log(`${now_abbrev}.${ts_abbrev}.${rand}`);
   return buff.toString('base64');
}

/* election functions */
function always(method, path, params){
    return true;
}

function update(method, path, params){
    return method === "POST" && UPDATE_KEYWORD in params;
}

function start(method, path, params){
    return method === "GET" && START_KEYWORD in params;
}

function hasSession(method, path, params){
    return SID_KEYWORD in params;
}

/* response serve functions */
function dataServe(res, now, method, path, params){
    const obj = {
        currentTime: now.toISOString(),
    };

    const tzArg = params[TZ_KEYWORD] && params[TZ_KEYWORD].toUpperCase();
    const tz = tzlist.tzabbrev[tzArg];
    let code = 500;
    if(tz){
        const adjusted = adjustTime(now, tz);
        obj.ajustedTime = adjusted.toISOString();
        obj.timezone = structuredClone(tz);
        obj.timezone.abbrev = tzArg;
        success = true;
        code = 200;
    }else{
        obj.error = "Timezone not found in international list, looking for "+tzArg;
        code = 400;
    }

    res.writeHead(code, {'Content-Type': 'application/json'});
    res.end(JSON.stringify(obj));
}

function startServe(res, now, method, path, params){
    // start a new session
    const code = 200;
    const obj = {
        currentTime: now.toISOString(),
        sid: makeSid(params)
    };

    res.writeHead(code, {'Content-Type': 'application/json'});
    res.end(JSON.stringify(obj));
}

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

/* handler instantiation */
const handlers = [
    new Handler([update, hasSession], dataServe),
    new Handler([start], startServe),
    new Handler([always], notFoundServe)
];

const errorHandler = new Handler(always, errorServe);

class Serve {
    /* server and handler runner */
    handleRequest(res, now, method, path, params){
        let done = false;
        for(let i = 0; i < handlers.length; i++){
          let handle = handlers[i];
          if(handle.elect(method, path, params)){
              handle.handle(res, now, method, path, params); 
              done = true;
              break;
          }
        }
        
        if(!done){
            errorHandler.handle(res, now, method, path, params);
        }
    }
    getNow(){
        return new Date();
    }
    serve(port){
        /* server instantiation */
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
            if(param_keys.indexOf(s) !== -1){
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


module.exports = {Serve};
