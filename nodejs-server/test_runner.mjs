import { CompareFuzz } from "./utils.mjs";

const TEST_STARTED = 'started';
const TEST_PASS = 'started';
const TEST_FAIL = 'started';

export function DeepCompare(a, b, fuzz, nested){
    nested = nested || [];
    let r = false;
    if(Array.isArray(a)){
        for(let i = 0; i < a.length; i++){
            nested.push(i);
            r = DeepCompare(a[i], b[i], fuzz, nested);
            if(!r){
                return nested;
            }
            nested.pop();
        }
    }else if(typeof a === 'object') {
        for(let k in a){
            nested.push(k);
            r = DeepCompare(a[k], b[k], fuzz, nested);
            if(!r){
                return nested;
            }
            nested.pop();
        }
    }else{
        r = CompareFuzz(a, b, fuzz);
        if(!r){
            return nested;
        }
    }

    return true;
}

class TestServer_Arg {
    method;
    path;
    params;
    constructor(method, path, params){
        this.method = method;
        this.path = path;
        this.params = params;
    }
    toString(){
        const paramJson = JSON.stringify(this.params);
        return `TestArg<${this.method},${this.path},${paramJson}>`;
    }
}

class TestCase {
    name;
    arg;
    result;
    constructor(name, arg, result){
        this.name = name;
        this.arg = arg;
        this.result = result;
    }
    toString(){
        return this.arg.toString();
    }
}

class TestSet {
    func;
    cases;
    results;
    constructor(obj){
        this.cases = obj.cases;
        this.func = obj.func;
        this.results = {
            pass: 0,
            fail: 0,
            total: 0,
        }
    }
    run(){
        for(let i = 0; i < this.cases.length; i++){
            const cse = this.cases[i];
            const res = this.func(cse);
            if(res == cse.result){
                this.results.pass++;
            }else{
                this.results.fail++;
            }
            this.results.total++;
        }
    }
}

class TestServer_MockRes {
    content;
    code;
    constructor(){
        this.content = "";
        this.code = 0;
    }
    writeHead(code, props){
        this.code = code;
    }
    end(content){
        this.content = content;
    }
}

/*
function RunCalcSet(set){
    for(let i = 0; i < set.length; i++){
        const test = set[i];
        const arg = set[i].arg;
        const result = set[i].result;



        if(res.code != result.code){
            throw new Error(`test failure code mismatch: have ${res.code}  expected ${result.code}  for ${test.name} - ${test} - ${res.content}`);
        }

        let adjusted = null;
        const tzArg = arg.params[serveTime.TZ_KEYWORD];
        if(tzArg){
            const tz = tzlist.tzabbrev[tzArg];
            adjusted = serveTime.adjustTime(now, tz);
        }

        const jsonData = JSON.parse(res.content);
        for(let key in result.response){
            if(/NOW/.test(result.response[key])){
                result.response[key] = result.response[key].replace('NOW', now.toISOString());
            }
            if(adjusted && /ADJUSTED/.test(result.response[key])){
                result.response[key] = result.response[key].replace('ADJUSTED', adjusted.toISOString());
            }
        }

        if(JSON.stringify(result.response) !== JSON.stringify(jsonData)){
            throw new Error(`test failed results mismatch for ${test.name} - ${test}`);
        }

        console.log(`TEST PASS: ${test.name}`);
    }
}
*/

export {
    TestCase,
    TestSet
};
