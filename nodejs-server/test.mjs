import {TestSet, DeepCompare} from './test_runner.mjs';
import {InitStartModel} from './data.mjs';

const expectedAlpha = {
    "headers":["","","Qrtr1","Qrtr2","Qrtr3","Qrtr4","Qrtr5","Qrtr6","Qrtr7","Qrtr8","Qrtr9","Qrtr10"],
    "rows":[
        ["Alpha","prices",12.99,12.99,12.99,12.99,12.99,12.99,12.99,12.99,12.99,12.99],
        ["Alpha","growth",1.25,1.4,1.25,1.1,1.25,1.4,1.25,1.1,1.25,1.4],
        ["Alpha","units",12.5,14,12.5,11,12.5,14,12.5,11,12.5,14],
        ["Alpha","totals",162.375,181.86,162.375,142.89000000000001,162.375,181.86,162.375,142.89000000000001,162.375,181.86],
        ["Alpha","grandTotals",162.375,344.235,506.61,649.5,811.875,993.735,1156.1100000000001,1299.0000000000002,1461.3750000000002,1643.2350000000001],
        ["Bravo","prices",50.45,50.45,50.45,50.45,50.45,50.45,50.45,50.45,50.45,50.45],
        ["Bravo","growth",1.15,1.3,1.4500000000000002,1.6,1.4500000000000002,1.3,1.15,1,1.15,1.3],
        ["Bravo","units",9.2,10.4,11.600000000000001,12.8,11.600000000000001,10.4,9.2,8,9.2,10.4],
        ["Bravo","totals",464.14,524.6800000000001,585.2200000000001,645.7600000000001,585.2200000000001,524.6800000000001,464.14,403.6,464.14,524.6800000000001],
        ["Bravo","grandTotals",464.14,988.82,1574.0400000000002,2219.8,2805.0200000000004,3329.7000000000007,3793.8400000000006,4197.4400000000005,4661.580000000001,5186.260000000001]
    ]
}

const calcBasicSet = new TestSet({
    func: (args) => {
        const model = InitStartModel(args);
        console.log(JSON.stringify(model));
        const data = model.getData();
        const r = DeepCompare(data, expectedAlpha, []);
        if(r !== true){
            throw new Error('Error in calculation comparison', r);
        }
        return true;
    },
    cases: [{start: 0, end: 0}, {start: 0, end: 5},{start: 1, end: 11}]
});

calcBasicSet.run();
