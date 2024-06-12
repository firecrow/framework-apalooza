import {Model, Growth, Launch, Product, ProductSet} from "./calc.mjs";

/* util functions */
function InitStartModel(obj){
    const model = new Model(obj);
    model.prodSet = new ProductSet([
        new Product({
            name: "Alpha",
            key: "alpha",
            launch: new Launch({
                qrtr: 0,
                units: 10,
                price: 12.99,
            }),
            growth: new Growth({
                cycle: 4,
                min: 1.1,
                max: 1.4,
            })
        }),
        new Product({
            name: "Bravo",
            key: "bravo",
            launch: new Launch({
                qrtr: 3,
                units: 8,
                price: 50.45,
            }),
            growth: new Growth({
                cycle: 8,
                min: 1.0,
                max: 1.6,
            })
        }),
    ]);
    return model;
} 

export { InitStartModel };