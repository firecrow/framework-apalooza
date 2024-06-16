export function ValidNum(n) {
    return n || n === 0;
}

export function CompareFuzz(a, b, fuzz){
    return Math.abs(a - b) < fuzz;
}

function presentFormat(value){
    const t = typeof value;
    if(t === 'number'){
        return value.toFixed(2);
    }else{
        return value;
    }
}

export function FormatData(data){
    let r = false;
    if(Array.isArray(data)){
        for(let i = 0; i < data.length; i++){
            data[i] = FormatData(data[i]);
        }
    }else if(typeof data === 'object') {
        for(let k in data){
            if(typeof data[k] === 'number'){
                data[k] = presentFormat(data[k]);
            }else if(typeof data[k] === 'object'){
                FormatData(data[k]);
            }
        }
    }else{
        return presentFormat(data);
    }

    return data;
}
