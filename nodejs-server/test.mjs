import {TestSet} from './test_runner.mjs';
import {InitStartModel} from './data.mjs';

const calcBasicSet = new TestSet({
    func: () => {
        const model = InitStartModel();
        console.log(JSON.stringify(model));
    },
    cases: [0]
});

calcBasicSet.run();
