export class Literal{
    constructor(obj){
        for(let k in obj){
            this[k] = obj[k];
        }
    }
}