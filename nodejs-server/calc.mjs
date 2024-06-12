import { ValidNum } from "./utils.mjs";

export class Launch {
    qtr;
    units;
    price;
    constructor(obj){
        this.qtr = obj.qtr;
        this.units = obj.units;
        this.price = obj.price;
    }
}

export class Growth {
    min;
    max;
    cycle;
    constructor(obj){
        this.min = obj.min;
        this.max = obj.max;
        this.cycle = obj.cycle;
    }
}

export class Product {
    name;
    key;
    description;
    launch;
    growth;
    constructor(obj){
        this.name = obj.name;
        this.key = obj.key;
        this.description = obj.description;
        this.launch = obj.launch;
        this.growth = obj.growth;
    }
}

export class ProductSet {
    idxMap;
    products;
    constructor(products){
        this.idxMap = new Map();
        this.products = [];
        if(products){
            for(let i = 0; i < products.length; i++){
                this.setProduct(products[i]);
            }
        }
    }
    getByName(key) {
        return this.products[this.idxMap.get(key) || ""] || null;
    }
    setProduct(prod){
        this.idxMap.set(prod.key, this.products.push(prod));
    }
}

export class Projection {
    startQrtr;
    prod;
    length;

    // rows
    prices;
    growth;
    units;
    totals;
    grandTotals;
    constructor(prod){
        this.prod = prod;
    }

    calcInput(start, end, callback) {
        const length = end - start;
        const row = Array.apply(null, Array(length));
        return row.map((_, idx) => callback(this, idx));
    }

    mapInput(start, end, callback) {
        const length = end - start;
        const row = new Array(length);
        for(let i = 0; i < length; i++){
            row[i] = callback(this, i) + (row[i-1] || 0);
        }
        return row;
    }
}

export function blankData(){
    return {
        headers: [],
        cells: [],
    }
}

function GetInPhase(growth, idx){
    const cycle = growth.cycle; 
    const min = growth.min;
    const max = growth.max;

    const phase = (idx % cycle) / cycle;
    if(phase < 0.5){
        // max is at 0.5
        return min + ((max - min) * (phase*2));
    }else{
        // back down to min at 1.0
        return min + ((max - min) * (1-((phase-0.5)*2)));
    }
}

function prependProductName(name, label, arr) {
    arr.unshift(name, label);
    return arr;
}

export class DataSet {
    headers;
    rows;
    constructor(obj){
        if(obj){
            this.headers = obj.headers || [];
            this.rows = obj.rows || [];
        }else{
            this.headers = [];
            this.rows = [];
        }
    }
}

export class Model {
    start;
    end;
    prodSet;
    constructor(obj){
        if(obj){
            this.start = obj.start;
            this.end = obj.end;
        }
    }
    getData(){
        if(!ValidNum(this.start) || !ValidNum(this.end)){
            return null;
        }

        const data = new DataSet();
        const model = this;

        const length = this.end - this.start;
        let headers = Array.apply(null, Array(length)).map((_, idx) =>  'Qrtr' + (idx+this.start));

        data.headers = prependProductName("", "", headers);

        for(let i = 0; i < this.prodSet.products.length; i++){
            const prod = this.prodSet.products[i];
            const projection = new Projection(prod);
            projection.prices = projection.calcInput(this.start, this.end, (projection, _) => {
                return projection.prod.launch.price;
            });

            projection.growth = projection.calcInput(this.start, this.end, (projection, idx) => {
                const growth = projection.prod.growth;
                idx += model.start;
                return GetInPhase(growth, idx);
            });

            projection.units = projection.calcInput(this.start, this.end, (projection, idx) => {
                return projection.growth[idx] * projection.prod.launch.units;
            });

            projection.totals = projection.calcInput(this.start, this.end, (projection, idx) => {
                return projection.units[idx] * projection.prod.launch.price;
            });

            projection.grandTotals = projection.mapInput(this.start, this.end, (projection, idx) => {
                return projection.totals[idx];
            });

            for(let k in {
                "prices": true,
                "growth": true,
                "units": true,
                "totals": true,
                "grandTotals": true,
            }){
                data.rows.push(prependProductName(prod.name, k, projection[k]));
            }
        }

        return data;
    }
}
