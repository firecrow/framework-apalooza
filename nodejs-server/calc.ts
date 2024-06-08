type CalcFunc = (value:Projection, idx: number) => number;

export class Launch {
    qtr: number;
    units: number;
    price: number;
}

export class Growth {
    min: number;
    max: number;
    cycle: number;
}

export class Product {
    name:String;
    key:String;
    description: String;
    launch: Launch;
    growth: Growth;
}

export class ProductSet {
    idxMap: Map<String, number>;
    products: Array<Product>;
    getByName(key: String): Product {
        return this.products[this.idxMap.get(key) || ""] || null;
    }
    setProduct(prod: Product){
        this.idxMap.set(prod.key, this.products.push(prod));
    }
}

export class Projection {
    startQrtr:number;
    prod: Product;
    length: number;

    // rows
    prices:Array<number>;
    growth:Array<number>;
    units:Array<number>;
    totals:Array<number>;
    grandTotals:Array<number>;

    constructor(prod:Product){
        this.prod = prod;
    }

    calcInput(start:number, end:number, callback:CalcFunc): Array<number> {
        const length = end - start;
        const row = new Array(length);
        return row.map((_, idx) => callback(this, idx));
    }

    mapInput(start:number, end:number, callback:CalcFunc): Array<number> {
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

function GetInPhase(growth: Growth, idx: number): number{
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

function prependProductName(name: String, label: String, arr: Array<any>): Array<any> {
    const row = arr as Array<any>;
    row.unshift(name, label);
    return row;
}

export class DataSet {
    headers: Array<any>;
    rows:  Array<Array<any>>;
}

export class Model {
    start: number;
    end: number;
    prodSet: ProductSet;
    getData(){
        const data: DataSet =  new DataSet();

        const length = this.end - this.start;
        let headers = (new Array(length)).map((_, idx) =>  'Qrtr' + idx);
        data.headers = prependProductName("", "", headers);

        for(let i = 0; i < this.prodSet.products.length; i++){
            const prod = this.prodSet.products[i];
            const projection = new Projection(prod);
            const prices: Array<number> = projection.calcInput(this.start, this.end, (projection, _) => {
                return projection.prod.launch.price;
            });

            projection.growth = projection.calcInput(this.start, this.end, (projection, idx) => {
                const growth = projection.prod.growth;
                return GetInPhase(growth, idx);
            });

            projection.units = projection.calcInput(this.start, this.end, (projection, idx) => {
                return projection.growth[idx] * projection.prod.launch.units;
            });

            projection.totals = projection.calcInput(this.start, this.end, (projection, idx) => {
                return projection.units[idx] * projection.prod.launch.price;
            });

            projection.grandTotals = projection.calcInput(this.start, this.end, (projection, idx) => {
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