const server = require('./server.js');

UPDATE_KEYWORD = 'update';
START_KEYWORD = 'start';
SID_KEYWORD = 'session';
const param_keys = [SID_KEYWORD];

/* election functions */
function update(method, path, params){
    return method === "POST" && UPDATE_KEYWORD in params;
}

function start(method, path, params){
    return method === "GET" && START_KEYWORD in params;
}

function hasSession(method, path, params){
    return SID_KEYWORD in params;
}

/* response serve handler functions */
function dataServe(res, now, method, path, params){
    const obj = {
        currentTime: now.toISOString(),
    };

    // fetch and update session data here

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

    // get default data here

    res.writeHead(code, {'Content-Type': 'application/json'});
    res.end(JSON.stringify(obj));
}

/* handler instantiation */
const handlers = [
    new Handler([start], startServe),
    new Handler([update, hasSession], dataServe),
    new Handler([server.always], server.notFoundServe)
];

export function DataServer_Make(){
    return server.Serve(param_keys, handlers);
}